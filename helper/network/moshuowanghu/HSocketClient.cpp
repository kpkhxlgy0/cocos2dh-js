#include "HSocketClient.h"

#include "HSocketPacket.h"
#include "SocketEngine.h"

#include "curl/curl.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

NS_CC_H_BEGIN

void HSocketClient::setSocketClientDelegate(HSocketClientDelegate* INsocketDelegate){
    Object *obj = dynamic_cast<Object*>(m_delegate);
    CC_SAFE_RELEASE(obj);
    m_delegate = INsocketDelegate;
    obj = dynamic_cast<Object*>(m_delegate);
    CC_SAFE_RETAIN(obj);
}

size_t HSocketClient::send(HSocketPacket *INpacket){
    int running_handles;
    CURLMcode mcode = curl_multi_perform(m_curlm, &running_handles);
    if (mcode != CURLM_OK) {
        CCLOG("send error: %s", curl_multi_strerror(mcode));
        return 0;
    }
    if (running_handles > 0) {
        CCLOG("send error: not ready to send");
        return 0;
    }
    
    curl_socket_t socketHandle;
    CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_LASTSOCKET, &socketHandle);
    if (code != CURLE_OK) {
        CCLOG("socketExt error: %s", curl_easy_strerror(code));
        return 0;
    }
    // 加密
    if (INpacket->isUseCode()) {
        m_socketEngine->encode(INpacket);
    }
    
    size_t ioLen;
//    uint16_t bufferLen = INpacket->getLength() + 8;
//    char *buffer = new char[bufferLen];
//    *((uint8_t*)buffer) = htons(INhead.CmdInfo.cbVersion);
//    *((uint8_t*)(buffer + 1)) = htons(INhead.CmdInfo.cbCheckCode);
//    *((uint16_t*)(buffer + 2)) = htons(INhead.CmdInfo.wPacketSize);
//    *((uint16_t*)(buffer + 4)) = htons(INhead.CommandInfo.wMainCmdID);
//    *((uint16_t*)(buffer + 6)) = htons(INhead.CommandInfo.wMainCmdID);
//    memcpy(buffer + 8, INpacket->getBuffer(), INpacket->getLength());
    
    code = curl_easy_send(m_curl, INpacket->getBuffer(), INpacket->getLength(), &ioLen);
    if (code != CURLE_OK && code != CURLE_AGAIN) {
        CCLOG("send error: %s", curl_easy_strerror(code));
        return 0;
    }
    return ioLen;
}

HSocketClient::HSocketClient() : m_curl(NULL),
m_curlm(NULL),
m_delegate(NULL),
m_bufferLengthPacket(0),
m_bufferLengthReceived(0) {
    m_socketEngine = new SocketEngine();
}

HSocketClient::~HSocketClient(){
    delete m_socketEngine;
    Object *obj = dynamic_cast<Object*>(m_delegate);
    CC_SAFE_RELEASE(obj);
}

bool HSocketClient::init(void *INcurl, void *INcurlm){
    m_curl = INcurl;
    m_curlm = INcurlm;
    return true;
}

void HSocketClient::connect(){
    CCDirector::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(HSocketClient::tickConnect), this);
    CCDirector::getInstance()->getScheduler()->scheduleSelector(schedule_selector(HSocketClient::tickConnect), this, 0 ,false);
}

void HSocketClient::tickConnect(float INdt){
    int running_handles;
    CURLMcode mcode = curl_multi_perform(m_curlm, &running_handles);
    if (mcode != CURLM_OK) {
        CCLOG("curl_multi_perform error: %s", curl_multi_strerror(mcode));
        CCDirector::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(HSocketClient::tickConnect), this);
        if (m_delegate) {
            m_delegate->callbackConnectFailed();
        }
        return;
    }
    if (running_handles == 0) {
        CCDirector::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(HSocketClient::tickConnect), this);
        curl_socket_t socketHandle;
        CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_LASTSOCKET, &socketHandle);
        if (code != CURLE_OK) {
            CCLOG("socketExt error: %s", curl_easy_strerror(code));
            return;
        }
        if (socketHandle == CURL_SOCKET_BAD) {
            if (m_delegate) {
                m_delegate->callbackConnectFailed();
            }
        }
        else {
            CCDirector::getInstance()->getScheduler()->scheduleSelector(schedule_selector(HSocketClient::tickReceive), this, 0, false);
            if (m_delegate) {
                m_delegate->callbackConnectSuccess();
            }
        }
    }
}

void HSocketClient::tickReceive(float INdt){
    curl_socket_t socketHandle;
    CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_LASTSOCKET, &socketHandle);
    if (code != CURLE_OK) {
        CCLOG("socketExt error: %s", curl_easy_strerror(code));
        CCDirector::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(HSocketClient::tickReceive), this);
        if (m_delegate) {
            m_delegate->callbackDisconnect();
        }
        return;
    }
    if (socketHandle == CURL_SOCKET_BAD) {
        CCDirector::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(HSocketClient::tickReceive), this);
        if (m_delegate) {
            m_delegate->callbackDisconnect();
        }
        return;
    }
    char a[MAX_BUFFER_PACKET_LENGTH] = {0};
    size_t ioLen;
    code = curl_easy_recv(m_curl, a, MAX_BUFFER_PACKET_LENGTH, &ioLen);
    if (code != CURLE_OK && code != CURLE_AGAIN) {
        CCLOG("recv error: %s", curl_easy_strerror(code));
        return;
    }
    
    if (ioLen == 0) {
        return;
    }
    
    size_t indexA = 0;
    while (true) {
        uint16_t bufferLengthPacket = 0;
        if (m_bufferLengthReceived > 7) {
            bufferLengthPacket = ntohs(*((uint16_t*)(m_buffer + 2)));
//            CCLOG("bufferLengthPacket...%d", bufferLengthPacket);
//            CCLOG("m_bufferLengthReceived.....%d....%d", m_bufferLengthReceived, (int)ioLen);
            if (m_bufferLengthReceived + ioLen >= bufferLengthPacket) {
                size_t lenUsed = bufferLengthPacket - m_bufferLengthReceived;
                memcpy(m_buffer + m_bufferLengthReceived, a + indexA, lenUsed);
                if (m_delegate) {
                    HSocketPacket *packet = new HSocketPacket(true);
//                    packet->init();
                    packet->autorelease();

                    packet->writeData(m_buffer, bufferLengthPacket);
                    m_socketEngine->decode(packet);
                    m_delegate->callbackReceiveSuccess(packet);
                }
                memmove(m_buffer, m_buffer + bufferLengthPacket, MAX_BUFFER_PACKET_LENGTH - bufferLengthPacket);
                m_bufferLengthReceived = 0;
                ioLen -= lenUsed;
                indexA += lenUsed;
            }
            else {
                memcpy(m_buffer + m_bufferLengthReceived, a + indexA, ioLen);
                m_bufferLengthReceived += ioLen;
                break;
            }
        }
        else {
            if (m_bufferLengthReceived + ioLen > 7) {
                size_t lenUsed = 8 - m_bufferLengthReceived;
                memcpy(m_buffer + m_bufferLengthReceived, a + indexA, lenUsed);
                m_bufferLengthReceived += lenUsed;
                ioLen -= lenUsed;
                indexA += lenUsed;
            }
            else {
                memcpy(m_buffer + m_bufferLengthReceived, a + indexA, ioLen);
                m_bufferLengthReceived += ioLen;
                break;
            }
        }
    }
}

#pragma mark - HSocketClientManager

static HSocketClientManager* s_shareHSocketClientManager = NULL;

HSocketClientManager* HSocketClientManager::getInstance(){
    if (!s_shareHSocketClientManager) {
        s_shareHSocketClientManager = new HSocketClientManager();
        s_shareHSocketClientManager->init();
    }
    return s_shareHSocketClientManager;
}

void HSocketClientManager::end(){
    delete s_shareHSocketClientManager;
    s_shareHSocketClientManager = NULL;
}

HSocketClient* HSocketClientManager::connectIP(const char *INip, int32_t INport, int32_t INtimeout){
    HSocketClientItem *item = this->getSocketItem(INip, INport);
    if (!item) {
        item = new HSocketClientItem();
        item->m_ip = INip;
        item->m_port = INport;
        item->m_curl = curl_easy_init();
        item->m_curlm = curl_multi_init();
        curl_multi_add_handle(item->m_curlm, item->m_curl);
        item->m_socket = new HSocketClient();
        item->m_socket->init(item->m_curl, item->m_curlm);
        item->autorelease();
        m_arraySocketItems->addObject(item);
    }
    
    curl_easy_setopt(item->m_curl, CURLOPT_URL, INip);
    curl_easy_setopt(item->m_curl, CURLOPT_PORT, INport);
    curl_easy_setopt(item->m_curl, CURLOPT_CONNECT_ONLY, 1);
    if (INtimeout > 0) {
        curl_easy_setopt(item->m_curl, CURLOPT_CONNECTTIMEOUT_MS, INtimeout);
    }
    item->m_socket->connect();
    return item->m_socket;
}

HSocketClient* HSocketClientManager::connectURL(const char *INurl, int32_t INtimeout){
    HSocketClientItem *item = this->getSocketItem(INurl);
    if (!item) {
        item = new HSocketClientItem();
        item->m_url = INurl;
        item->m_curl = curl_easy_init();
        item->m_curlm = curl_multi_init();
        curl_multi_add_handle(item->m_curlm, item->m_curl);
        item->m_socket = new HSocketClient();
        item->m_socket->init(item->m_curl, item->m_curlm);
        item->autorelease();
        m_arraySocketItems->addObject(item);
    }
    
    curl_easy_setopt(item->m_curl, CURLOPT_URL, INurl);
    curl_easy_setopt(item->m_curl, CURLOPT_CONNECT_ONLY, 1);
    if (INtimeout > 0) {
        curl_easy_setopt(item->m_curl, CURLOPT_CONNECTTIMEOUT_MS, INtimeout);
    }
    item->m_socket->connect();
    return item->m_socket;
}

bool HSocketClientManager::disconnectIP(const char *INip, int32_t INport){
    HSocketClientItem *item = this->getSocketItem(INip, INport);
    if (!item) {
        CCLOG("disconnect warning: INip, %s, INport, %d", INip, INport);
        return false;
    }
    item->m_socket->setSocketClientDelegate(NULL);
    item->m_socket->release();
    CCDirector::getInstance()->getScheduler()->unscheduleAllForTarget(item->m_socket);
    curl_easy_cleanup(item->m_curl);
    curl_multi_cleanup(item->m_curlm);
    m_arraySocketItems->removeObject(item);
    return true;
}

bool HSocketClientManager::disconnectURL(const char *INurl){
    HSocketClientItem *item = this->getSocketItem(INurl);
    if (!item) {
        CCLOG("disconnect warning: INurl, %s", INurl);
        return false;
    }
    item->m_socket->setSocketClientDelegate(NULL);
    item->m_socket->release();
    CCDirector::getInstance()->getScheduler()->unscheduleAllForTarget(item->m_socket);
    curl_easy_cleanup(item->m_curl);
    curl_multi_cleanup(item->m_curlm);
    m_arraySocketItems->removeObject(item);
    return true;
}

HSocketClientManager::HSocketClientManager() : m_arraySocketItems(NULL){
    
}

HSocketClientManager::~HSocketClientManager(){
    if (m_arraySocketItems) {
        Object *element;
        CCARRAY_FOREACH(m_arraySocketItems, element) {
            HSocketClientItem *item = (HSocketClientItem*)element;
            item->m_socket->release();
            curl_easy_cleanup(item->m_curl);
        }
        m_arraySocketItems->release();
    }
}

bool HSocketClientManager::init(){
    m_arraySocketItems = CCArray::create();
    m_arraySocketItems->retain();
    return true;
}

HSocketClientManager::HSocketClientItem* HSocketClientManager::getSocketItem(const char *INip, int32_t INport){
    Object *element;
    CCARRAY_FOREACH(m_arraySocketItems, element) {
        HSocketClientItem *item = (HSocketClientItem*)element;
        if (item->m_ip.compare(INip) == 0 && item->m_port == INport) {
            return item;
        }
    }
    return NULL;
}

HSocketClientManager::HSocketClientItem* HSocketClientManager::getSocketItem(const char *INurl){
    Object *element;
    CCARRAY_FOREACH(m_arraySocketItems, element) {
        HSocketClientItem *item = (HSocketClientItem*)element;
        if (item->m_url.compare(INurl) == 0) {
            return item;
        }
    }
    return NULL;
}

NS_CC_H_END