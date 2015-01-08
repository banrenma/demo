#ifndef  __UTIL__
#define __UTIL__

//静态成员  s_
//类成员  m_
#include "cocos2d.h"
USING_NS_CC;


class baseUtil
{
public:
	/**/
	static int s_iFightNum; 
	baseUtil(){log("baseUtil constructor  s_iFightNum= %d",s_iFightNum);m_iFightNum = s_iFightNum;s_iFightNum ++;}
	~baseUtil(){log("baseUtil delete");}
	static void resetUtilID(){s_iFightNum = 0;}
	CC_SYNTHESIZE(int, m_iFightNum, FightNum);

};


class Util:public Node ,public baseUtil
{
public:
	Util();
	~Util();
protected:
	
	//骨骼  -- 动画 --血条对象 --选中区域 --受击位置 --攻击特效位置 -- 攻击范围 -- 

	//状态机 对象




};





#endif