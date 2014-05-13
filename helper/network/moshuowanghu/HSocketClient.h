#ifndef __HSOCKETCLIENT_H__
#define __HSOCKETCLIENT_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

#define MAX_BUFFER_PACKET_LENGTH 4096

NS_CC_H_BEGIN

class HSocketPacket;
class SocketEngine;

class HSocketClientDelegate {
public:
    virtual void callbackConnectSuccess() = 0;
    virtual void callbackConnectFailed() = 0;
    virtual void callbackDisconnect() = 0;
    virtual void callbackReceiveSuccess(HSocketPacket* INsocketPacket) = 0;
};

class HSocketClient : public Object {
public:
    void setSocketClientDelegate(HSocketClientDelegate* INsocketDelegate);
    size_t send(HSocketPacket *INpacket);
private:
	HSocketClient();
	~HSocketClient();
	bool init(void *INcurl, void *INcurlm);
    void connect();
    
    void tickConnect(float INdt);
    void tickReceive(float INdt);
    
private:
    void*                       m_curl;
    void*                       m_curlm;
    HSocketClientDelegate*     m_delegate;
    HSocketPacket*              m_packet;
    char                        m_buffer[MAX_BUFFER_PACKET_LENGTH];
    uint16_t                    m_bufferLengthReceived;
    uint16_t                    m_bufferLengthPacket;
    SocketEngine *m_socketEngine;
private:
    friend class HSocketClientManager;
};

class HSocketClientManager : public Object {
private:
    class HSocketClientItem : public Object {
    public:
        std::string         m_ip;
        int                 m_port;
        std::string         m_url;
        void*               m_curl;
        void*               m_curlm;
        HSocketClient*      m_socket;
    };
public:
    HSocketClient* connectIP(const char *INip, int32_t INport, int32_t INtimeout);
    HSocketClient* connectURL(const char *INurl, int32_t INtimeout);
    
    bool disconnectIP(const char *INip, int32_t INport);
    bool disconnectURL(const char *INurl);
public:
    static HSocketClientManager* getInstance();
    static void end();
private:
    HSocketClientManager();
    ~HSocketClientManager();
    bool init();
    
    HSocketClientItem* getSocketItem(const char *INip, int32_t INport);
    HSocketClientItem* getSocketItem(const char *INurl);
private:
    Array     *m_arraySocketItems;
};

NS_CC_H_END

#endif //__HSOCKETCLIENT_H__
