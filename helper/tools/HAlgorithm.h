#ifndef __HELPER_TOOLS_HALGORITHM_H__
#define __HELPER_TOOLS_HALGORITHM_H__

#include "cocos2d.h"
#include "Cocos2dxhMacros.h"

NS_CC_H_BEGIN

#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)

class HAlgorithm : public Ref {
public:
	typedef std::vector<std::string> HStrArray;

	class HLine : public Ref {
    public:
		Point		m_point[2];
	};
public:
	static const char* valueForKey(const char *key, const std::map<std::string, std::string> &dict);

	static void split(const std::string &src, const char *token, HStrArray &vect);

	//计算交叉乘积(P1-P0)x(P2-P0)
	static float xmult(const Point &p1, const Point &p2, const Point &p0);

	//判点是否在线段上,包括端点
	static bool dot_online_in(const Point &p, const HLine &line);

	//判两点在线段同侧,点在线段上返回0
	static bool same_side(const Point &p1, const Point &p2, const HLine &line);

	//判两直线平行
	static bool parallel(const HLine &line0, const HLine &line1);

	//判三点共线
	static bool dots_inline(const Point &p1, const Point &p2, const Point &p3);

	//判两线段相交,包括端点和部分重合
	static bool intersect_in(const HLine &line0, const HLine &line1);

	//计算两线段交点,请判线段是否相交(同时还是要判断是否平行!)
	static bool isLineIntersect(const HLine &line0, const HLine &line1, Point &p);
    
    // 判断线段与矩形是否相交
    static bool isLineIntersectWithRect(const HLine &INline, const Rect &INrect);
    
    // 计算两区域的相交区域
    static Rect getRectIntersect(const Rect &INrect0, const Rect &INrect1);
    
    static int encryptoBuffer(std::string &OUTdes, const std::string &INstr, const std::string &INpassword, const std::string &INkey);
    static int decryptoBuffer(std::string &OUTdes, const std::string &INstr, const std::string &INpassword, const std::string &INkey);
};
NS_CC_H_END
#endif // __HELPER_TOOLS_HALGORITHM_H__