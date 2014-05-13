/*
 @Copyright     2013 MoShuo Inc.
 @Author        hxl
 @Description   资源管理
 @History       (操作 -- 创建)(时间 -- 13-3-6)
 */

#include "HAlgorithm.h"

#include "../../external/cryptopp/aes.h"
#include "../../external/cryptopp/default.h"

using namespace std;
using namespace CryptoPP;

extern "C" {
int encryptoBuffer(char *OUTdes, const char *INsrc, int INlenSrc, const char *INpassword, int INlenPassword, const char *INkey, int INlenKey) {
    string des, src(INsrc, INlenSrc), password(INpassword, INlenPassword), key(INkey, INlenKey);
    cocos2d::h::HAlgorithm::encryptoBuffer(des, src, password, key);
    memcpy(OUTdes, des.c_str(), des.size());
    return des.size();
}
    
int decryptoBuffer(char *OUTdes, const char *INsrc, int INlenSrc, const char *INpassword, int INlenPassword, const char *INkey, int INlenKey) {
    string des, src(INsrc, INlenSrc), password(INpassword, INlenPassword), key(INkey, INlenKey);
    cocos2d::h::HAlgorithm::decryptoBuffer(des, src, password, key);
    memcpy(OUTdes, des.c_str(), des.size());
    return des.size();
}
}

NS_CC_H_BEGIN;

const char* HAlgorithm::valueForKey(const char *key, const std::map<std::string, std::string> &dict) {
    auto it = dict.find(key);
    return it != dict.end() ? it->second.c_str() : "";
}

void HAlgorithm::split(const string &src, const char *token, HStrArray &vect) {
    int nend=0;
    int nbegin=0;
    while(nend != -1) {
        nend = src.find(token, nbegin);
        if(nend == -1) {
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        }
        else {
            vect.push_back(src.substr(nbegin, nend-nbegin));
        }
        nbegin = nend + strlen(token);
    }
}

float HAlgorithm::xmult(const Point &p1, const Point &p2, const Point &p0) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

bool HAlgorithm::dot_online_in(const Point &p, const HLine &line) {
    return zero(xmult(p, line.m_point[0], line.m_point[1])) && (line.m_point[0].x - p.x) * (line.m_point[1].x - p.x) < eps && (line.m_point[0].y - p.y) * (line.m_point[1].y - p.y) < eps;
}

bool HAlgorithm::same_side(const Point &p1, const Point &p2, const HLine &line) {
    return xmult(line.m_point[0], p1, line.m_point[1]) * xmult(line.m_point[0], p2, line.m_point[1]) > eps;
}

bool HAlgorithm::parallel(const HLine &line0, const HLine &line1) {
    return zero((line0.m_point[0].x - line0.m_point[1].x) * (line1.m_point[0].y - line1.m_point[1].y) - (line1.m_point[0].x - line1.m_point[1].x) * (line0.m_point[0].y - line0.m_point[1].y));
}

bool HAlgorithm::dots_inline(const Point &p1, const Point &p2, const Point &p3) {
    return zero(xmult(p1, p2, p3));
}

bool HAlgorithm::intersect_in(const HLine &line0, const HLine &line1) {
    if (!dots_inline(line0.m_point[0], line0.m_point[1], line1.m_point[0]) || !dots_inline(line0.m_point[0],line0.m_point[1], line1.m_point[1])) {
        return !same_side(line0.m_point[0], line0.m_point[1], line1) && !same_side(line1.m_point[0], line1.m_point[1], line0);
    }
    return dot_online_in(line0.m_point[0],line1)||dot_online_in(line0.m_point[1],line1)||dot_online_in(line1.m_point[0],line0)||dot_online_in(line1.m_point[1],line0);
}

bool HAlgorithm::isLineIntersect(const HLine &line0, const HLine &line1, Point &p) {
    bool ret = intersect_in(line0, line1);
    if (ret) {
        p.x = line0.m_point[0].x;
        p.y = line0.m_point[0].y;
        float t = ((line0.m_point[0].x - line1.m_point[0].x) * (line1.m_point[0].y - line1.m_point[1].y) -(line0.m_point[0].y - line1.m_point[0].y) * (line1.m_point[0].x - line1.m_point[1].x)) 
        / ((line0.m_point[0].x - line0.m_point[1].x) * (line1.m_point[0].y - line1.m_point[1].y) - (line0.m_point[0].y - line0.m_point[1].y) * (line1.m_point[0].x - line1.m_point[1].x));
        p.x += ((line0.m_point[1].x - line0.m_point[0].x) * t);
        p.y += ((line0.m_point[1].y - line0.m_point[0].y) * t);
    }
    return ret;
}

bool HAlgorithm::isLineIntersectWithRect(const HLine &INline, const Rect &INrect) {
    HLine line[4];
    line[0].m_point[0] = INrect.origin;
    line[0].m_point[1] = INrect.origin + Point(INrect.size.width, 0);
    line[1].m_point[0] = line[0].m_point[1];
    line[1].m_point[1] = INrect.origin + Point(INrect.size.width, INrect.size.height);
    line[2].m_point[0] = line[1].m_point[1];
    line[2].m_point[1] = INrect.origin + Point(0, INrect.size.height);
    line[3].m_point[0] = line[2].m_point[1];
    line[4].m_point[1] = INrect.origin;
    for (int i = 0; i < 4; ++i) {
        if (intersect_in(INline,line[i])) {
            return true;
        }
    }
    return false;
}

Rect HAlgorithm::getRectIntersect(const Rect &INrect0, const Rect &INrect1) {
    Rect rectIntersect;
    if (!INrect0.intersectsRect(INrect1)) {
        return rectIntersect;
    }
    rectIntersect.origin.x = MAX(INrect0.getMinX(), INrect1.getMinX());
    rectIntersect.origin.y = MAX(INrect0.getMinY(), INrect1.getMinY());
    rectIntersect.size.width = MIN(INrect0.getMaxX(), INrect1.getMaxX()) - rectIntersect.origin.x;
    rectIntersect.size.height = MIN(INrect0.getMaxY(), INrect1.getMaxY()) - rectIntersect.origin.y;
    return rectIntersect;
}

int HAlgorithm::encryptoBuffer(string &OUTdes, const string &INstr, const string &INpassword, const string &INkey) {
    string messageMACed;
    
    //MAC消息认证
    StringSource(INstr,true, new DefaultEncryptorWithMAC((unsigned char*)INpassword.c_str(), INpassword.size(), new StringSink(messageMACed)));
    
    //AES—ECB加密
    ECB_Mode<AES>::Encryption  Encryptor((unsigned char*)INkey.c_str(), INkey.size());
    //ECB属于不带初始向量的分块模式，将原文分块时若不够整块则需要填充，此处的DEFAULT_PADDING即为使用默认数据填充。（若需详细资料可查阅相关Crypto++帮助文档）
    OUTdes.clear();
    StringSource(messageMACed, true, new StreamTransformationFilter(Encryptor, new StringSink(OUTdes),BlockPaddingSchemeDef::DEFAULT_PADDING, true));
    return OUTdes.size();
}

int HAlgorithm::decryptoBuffer(string &OUTdes, const string &INstr, const string &INpassword, const string &INkey) {
    string recoverMACed;
    
    //AES—ECB解密
    ECB_Mode< AES >::Decryption Decryptor((unsigned char*)INkey.c_str(), INkey.size());
    StringSource(INstr, true,new StreamTransformationFilter(Decryptor,new StringSink(recoverMACed),BlockPaddingSchemeDef::DEFAULT_PADDING,true));
    
    //去掉MAC
    StringSource(recoverMACed,true,new DefaultDecryptorWithMAC((unsigned char*)INpassword.c_str(), INpassword.size(),new StringSink(OUTdes)));
    return OUTdes.size();
}

NS_CC_H_END
