/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   socket packet operation class
 @History       (operate -- create)(date -- 13-2-26)
 */

#ifndef __COCOS2DXH_CLASSES_HSOCKETPACKET__
#define __COCOS2DXH_CLASSES_HSOCKETPACKET__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

// net data define
#define SOCKET_VER						0x66								//net version
#define SOCKET_BUFFER					8192								//net buffer
#define SOCKET_PACKET					(SOCKET_BUFFER-sizeof(CMD_Head)-2*sizeof(int32_t))

//net core
struct CMD_Info {
    uint8_t								cbVersion;							//version identify
    uint8_t								cbCheckCode;						//check code
    uint16_t							wPacketSize;						//buffer size
};
//net command
struct CMD_Command {
    uint16_t							wMainCmdID;							//main command
    uint16_t							wSubCmdID;							//sub command
};
//net head
struct CMD_Head {
    CMD_Info							CmdInfo;							//base struct
    CMD_Command							CommandInfo;						//command information
};
//net buffer
struct CMD_Buffer
{
    CMD_Head							Head;								//head
    uint8_t								cbBuffer[SOCKET_PACKET];			//buffer
};

class HSocketPacket : public Object {
public:
    HSocketPacket(bool INuseCode = false);
    virtual ~HSocketPacket();
    void writeInt8(int8_t INvalue);
    void writeUInt8(uint8_t INvalue);
    void writeInt16(int16_t INvalue);
    void writeUInt16(uint16_t INvalue);
    void writeInt32(int32_t INvalue);
    void writeUInt32(uint32_t INvalue);
    void writeInt64(int64_t INvalue);
    void writeUInt64(uint64_t INvalue);
    void writeFloat(float INvalue);
    void writeDouble(double INvalue);
    void writeData(const void *INdata, size_t INsize);
    void readInt8(int8_t *OUTvalue);
    void readUInt8(uint8_t *OUTvalue);
    void readInt16(int16_t *OUTvalue);
    void readUInt16(uint16_t *OUTvalue);
    void readInt32(int32_t *OUTvalue);
    void readUInt32(uint32_t *OUTvalue);
    void readInt64(int64_t *OUTvalue);
    void readUInt64(uint64_t *OUTvalue);
    void readFloat(float *OUTvalue);
    void readDouble(double *OUTvalue);
    void readData(void *OUTdata, size_t INsize);
    const char* getBuffer();
    size_t getLength();
    void setData(const void *INdata, size_t INsize);
    bool isUseCode();
    void print();
private:
    void checkSize(size_t INsize);
private:
    char                *m_buffer;
    size_t              m_size;
    size_t              m_length;
    size_t              m_index;
    bool                m_useCode;
};

NS_CC_H_END

#endif // __COCOS2DXH_CLASSES_HSOCKETPACKET__
