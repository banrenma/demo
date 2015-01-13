#ifndef  __UTIL__
#define __UTIL__

//静态成员  s_
//类成员  m_
#include "cocos2d.h"
#include "NSpineExt.h"
#include "NBlood.h"
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

class Util:public NSpineExt ,public baseUtil
{
public:

	static Util * create(UtilData & data);
	bool initUtil(UtilData & data);


	virtual void update(float delta);
	
	Util(spSkeletonData * pSkeleton);
	~Util();

	Node * getBeforeSkeletonNode(){ return m_BeforeSkeletonNode; }
	Node * getBehindSkeletonNode(){return m_BehindSkeletonNode; }
protected:
	Node * m_Blood; 
	Node * m_BeforeSkeletonNode;
	Node * m_BehindSkeletonNode;
	UtilData m_data;

protected:
	


	




};





#endif