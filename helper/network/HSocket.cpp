#include "HSocket.h"

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

void HSocket::setSocketDelegate(HSocketDelegateBase *socketDelegate) {
    Ref *obj = dynamic_cast<Ref*>(m_delegate);
    CC_SAFE_RELEASE(obj);
    m_delegate = socketDelegate;
    obj = dynamic_cast<Ref*>(m_delegate);
    CC_SAFE_RETAIN(obj);
}

void HSocket::setPacketFactory(HPacketFactoryBase *packetFactory) {
    Ref *obj = dynamic_cast<Ref*>(_packetFactory);
    CC_SAFE_RELEASE(obj);
    _packetFactory = packetFactory;
    obj = dynamic_cast<Ref*>(_packetFactory);
    CC_SAFE_RETAIN(obj);
}

size_t HSocket::send(HPacketBase *INpacket) {
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
    size_t ioLen;
    code = curl_easy_send(m_curl, INpacket->getBuffer(), INpacket->getLength(), &ioLen);
    if (code != CURLE_OK && code != CURLE_AGAIN) {
        CCLOG("send error: %s", curl_easy_strerror(code));
        return 0;
    }
    return ioLen;
}

HSocket::HSocket()
    : m_curl(nullptr)
    , m_curlm(nullptr)
    , m_delegate(nullptr)
    , _packetFactory(nullptr)
    , m_bufferLengthReceived(0)
    , m_bufferLengthPacket(0) {
    
}

HSocket::~HSocket() {
    
}

bool HSocket::init(void *INcurl, void *INcurlm) {
    m_curl = INcurl;
    m_curlm = INcurlm;
    return true;
}

void HSocket::connect() {
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule(schedule_selector(HSocket::tickConnect), this);
    scheduler->schedule(schedule_selector(HSocket::tickConnect), this, 0, false);
}

void HSocket::tickConnect(float INdt) {
    int running_handles;
    CURLMcode mcode = curl_multi_perform(m_curlm, &running_handles);
    if (mcode != CURLM_OK) {
        CCLOG("curl_multi_perform error: %s", curl_multi_strerror(mcode));
        CCDirector::getInstance()->getScheduler()->unschedule(schedule_selector(HSocket::tickConnect), this);
        if (m_delegate) {
            m_delegate->callbackConnectFailed();
        }
        return;
    }
    if (running_handles == 0) {
        CCDirector::getInstance()->getScheduler()->unschedule(schedule_selector(HSocket::tickConnect), this);
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
            CCDirector::getInstance()->getScheduler()->schedule(schedule_selector(HSocket::tickReceive), this, 0, false);
            if (m_delegate) {
                m_delegate->callbackConnected();
            }
        }
    }
}

void HSocket::tickReceive(float INdt) {    
    curl_socket_t socketHandle;
    CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_LASTSOCKET, &socketHandle);
    if (code != CURLE_OK) {
        CCLOG("socketExt error: %s", curl_easy_strerror(code));
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(HSocket::tickReceive), this);
        if (m_delegate) {
            m_delegate->callbackDisconnected();
        }
        return;
    }
    if (socketHandle == CURL_SOCKET_BAD) {
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(HSocket::tickReceive), this);
        if (m_delegate) {
            m_delegate->callbackDisconnected();
        }
        return;
    }
    memset(_bufTemp, 0, MAX_BUFFER_LENGTH);
    size_t ioLen;
    code = curl_easy_recv(m_curl, _bufTemp, MAX_BUFFER_LENGTH, &ioLen);
    if (code != CURLE_OK && code != CURLE_AGAIN) {
        CCLOG("recv error: %s", curl_easy_strerror(code));
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(HSocket::tickReceive), this);
        if (m_delegate) {
            m_delegate->callbackDisconnected();
        }
        return;
    }
    if (ioLen == 0) {
        return;
    }
    size_t indexA = 0;
    while (true) {
        uint16_t bufferLengthPacket = 0;
        if (m_bufferLengthReceived > 1) {
            bufferLengthPacket = ntohs(*((uint16_t*)m_buffer));
            CCLOG("%d---", bufferLengthPacket);
            if (m_bufferLengthReceived + ioLen >= bufferLengthPacket) {
                size_t lenUsed = bufferLengthPacket - m_bufferLengthReceived;
                memcpy(m_buffer + m_bufferLengthReceived, _bufTemp + indexA, lenUsed);
                if (m_delegate) {
                    auto packet = _packetFactory->createPacket(m_buffer + 2, bufferLengthPacket - 2);
                    m_delegate->callbackReceived(packet);
                }
                memmove(m_buffer, m_buffer + bufferLengthPacket, MAX_BUFFER_LENGTH - bufferLengthPacket);
                m_bufferLengthReceived = 0;
                ioLen -= lenUsed;
                indexA += lenUsed;
            }
            else {
                memcpy(m_buffer + m_bufferLengthReceived, _bufTemp + indexA, ioLen);
                m_bufferLengthReceived += ioLen;
                break;
            }
        }
        else {
            if (m_bufferLengthReceived + ioLen > 1) {
                size_t lenUsed = 2 - m_bufferLengthReceived;
                memcpy(m_buffer + m_bufferLengthReceived, _bufTemp + indexA, lenUsed);
                m_bufferLengthReceived += lenUsed;
                ioLen -= lenUsed;
                indexA += lenUsed;
            }
            else {
                memcpy(m_buffer + m_bufferLengthReceived, _bufTemp + indexA, ioLen);
                m_bufferLengthReceived += ioLen;
                break;
            }
        }
    }
}

#pragma mark - HSocketManager

static HSocketManager *s_sharedHSocketManager = NULL;

HSocketManager* HSocketManager::getInstance() {
    if (!s_sharedHSocketManager) {
        s_sharedHSocketManager = new HSocketManager();
        s_sharedHSocketManager->init();
    }
    return s_sharedHSocketManager;
}

void HSocketManager::end() {
    delete s_sharedHSocketManager;
    s_sharedHSocketManager = NULL;
}

HSocket* HSocketManager::connectIP(const char *INip, int32_t INport, int32_t INtimeout) {
    HSocketItem *item = this->getSocketItem(INip, INport);
    if (!item) {
        item = new HSocketItem();
        item->m_ip = INip;
        item->m_port = INport;
        item->m_curl = curl_easy_init();
        item->m_curlm = curl_multi_init();
        curl_multi_add_handle(item->m_curlm, item->m_curl);
        item->m_socket = new HSocket();
        item->m_socket->init(item->m_curl, item->m_curlm);
        item->autorelease();
        m_socketItems.pushBack(item);
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

HSocket* HSocketManager::connectURL(const char *INurl, int32_t INtimeout) {
    HSocketItem *item = this->getSocketItem(INurl);
    if (!item) {
        item = new HSocketItem();
        item->m_url = INurl;
        item->m_curl = curl_easy_init();
        item->m_curlm = curl_multi_init();
        curl_multi_add_handle(item->m_curlm, item->m_curl);
        item->m_socket = new HSocket();
        item->m_socket->init(item->m_curl, item->m_curlm);
        item->autorelease();
        m_socketItems.pushBack(item);
    }
    
    curl_easy_setopt(item->m_curl, CURLOPT_URL, INurl);
    curl_easy_setopt(item->m_curl, CURLOPT_CONNECT_ONLY, 1);
    if (INtimeout > 0) {
        curl_easy_setopt(item->m_curl, CURLOPT_CONNECTTIMEOUT_MS, INtimeout);
    }
    item->m_socket->connect();
    return item->m_socket;
}

bool HSocketManager::disconnectIP(const char *INip, int32_t INport) {
    HSocketItem *item = this->getSocketItem(INip, INport);
    if (!item) {
        CCLOG("disconnect warning: INip, %s, INport, %d", INip, INport);
        return false;
    }
    item->m_socket->setSocketDelegate(NULL);
    item->m_socket->release();
    CCDirector::getInstance()->getScheduler()->unscheduleAllForTarget(item->m_socket);
    curl_easy_cleanup(item->m_curl);
    curl_multi_cleanup(item->m_curlm);
    m_socketItems.eraseObject(item);
    return true;
}

bool HSocketManager::disconnectURL(const char *INurl) {
    HSocketItem *item = this->getSocketItem(INurl);
    if (!item) {
        CCLOG("disconnect warning: INurl, %s", INurl);
        return false;
    }
    item->m_socket->setSocketDelegate(NULL);
    item->m_socket->release();
    CCDirector::getInstance()->getScheduler()->unscheduleAllForTarget(item->m_socket);
    curl_easy_cleanup(item->m_curl);
    curl_multi_cleanup(item->m_curlm);
    m_socketItems.eraseObject(item);
    return true;
}

HSocketManager::HSocketManager() : m_socketItems(NULL) {
    
}

HSocketManager::~HSocketManager() {
    for (const auto &item : m_socketItems) {
        item->m_socket->release();
        curl_easy_cleanup(item->m_curl);
    }
}

bool HSocketManager::init() {
    return true;
}

HSocketManager::HSocketItem* HSocketManager::getSocketItem(const char *INip, int32_t INport) {
    for (const auto &item : m_socketItems) {
        if (item->m_ip.compare(INip) == 0 && item->m_port == INport) {
            return item;
        }
    }
    return NULL;
}

HSocketManager::HSocketItem* HSocketManager::getSocketItem(const char *INurl) {
    for (const auto &item : m_socketItems) {
        if (item->m_url.compare(INurl) == 0) {
            return item;
        }
    }
    return NULL;
}

NS_CC_H_END
