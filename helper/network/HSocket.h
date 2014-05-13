#ifndef __HELPER_NETWORK_HSOCKET_H__
#define __HELPER_NETWORK_HSOCKET_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#include "HSocketInterface.h"

NS_CC_H_BEGIN

class HSocket : public Ref {
public:
    void setSocketDelegate(HSocketDelegateBase *socketDelegate);
    void setPacketFactory(HPacketFactoryBase *packetFactory);
    size_t send(HPacketBase *INpacket);
private:
    HSocket();
    ~HSocket();
    bool init(void *INcurl, void *INcurlm);
    void connect();
    
    void tickConnect(float INdt);
    void tickReceive(float INdt);
private:
    void *m_curl;
    void *m_curlm;
    HSocketDelegateBase *m_delegate;
    HPacketFactoryBase *_packetFactory;
    char m_buffer[MAX_BUFFER_LENGTH];
    char _bufTemp[MAX_BUFFER_LENGTH];
    uint16_t m_bufferLengthReceived;
    uint16_t m_bufferLengthPacket;
private:
    friend class HSocketManager;
};

class HSocketManager : public Ref {
private:
    class HSocketItem : public Ref {
    public:
        std::string m_ip;
        int m_port;
        std::string m_url;
        void *m_curl;
        void *m_curlm;
        HSocket *m_socket;
    };
public:    
    HSocket* connectIP(const char *INip, int32_t INport, int32_t INtimeout = -1);
    HSocket* connectURL(const char *INurl, int32_t INtimeout = -1);
    
    bool disconnectIP(const char *INip, int32_t INport);
    bool disconnectURL(const char *INurl);
public:
    static HSocketManager* getInstance();
    static void end();
private:
    HSocketManager();
    ~HSocketManager();
    bool init();
    
    HSocketItem* getSocketItem(const char *INip, int32_t INport);
    HSocketItem* getSocketItem(const char *INurl);
private:
    Vector<HSocketItem*> m_socketItems;
};

NS_CC_H_END

#endif //__HELPER_NETWORK_HSOCKET_H__
