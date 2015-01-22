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
	enum class Controlstate
	{
		Util_useControl,
		Util_AiControl,
	};
	enum class state
	{
		Util_empty,
		Util_followUp,
		Util_attack,
		Util_skill,
	};
public:

	static Util * create(UtilData & data);
	bool initUtil();


	virtual void update(float delta);
	
	Util(UtilData * pData);
	Util(){}
	~Util();

	Node * getBeforeSkeletonNode(){ return m_BeforeSkeletonNode; }
	Node * getBehindSkeletonNode(){return m_BehindSkeletonNode; }

	CC_SYNTHESIZE(Controlstate,m_ControlState,ControlState)
	CC_SYNTHESIZE(state,m_state,State)
	CC_SYNTHESIZE(Util *,m_Target,Target)
	CC_SYNTHESIZE(Rect,m_UtilRect,UtilRect)
	CC_SYNTHESIZE(Rect,m_attackRect,attackRect)
protected:
	Node * m_Blood; 
	Node * m_BeforeSkeletonNode;
	Node * m_BehindSkeletonNode;
	UtilData* m_data;










protected:
	


	




};





#endif