#ifndef  __UTIL__
#define __UTIL__

//静态成员  s_
//类成员  m_
#include "cocos2d.h"
#include "NSpineExt.h"
#include "NBlood.h"
#include "EventManage.h"
USING_NS_CC;


#define  UTIL_SPEED  4
#define  MAGE_SPEED  10





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
	virtual void setPosition(const Vec2 &position);
	virtual void setPosition(float x, float y);
	virtual void  setPositionY(float y);
	virtual void setAnimationEvent(spTrackEntry* entry){}

protected:
	Node * m_Blood; 
	Node * m_BeforeSkeletonNode;
	Node * m_BehindSkeletonNode;
	UtilData* m_data;


protected:
	

};

class UtilMage:public Util
{
public:
	static UtilMage * create(UtilData & data);
	UtilMage(UtilData * pData);
	virtual void setAnimationEvent(spTrackEntry* entry);
};
class UtilWarrior:public Util
{
public:
	static UtilWarrior * create(UtilData & data);
	UtilWarrior(UtilData * pData);
	virtual void setAnimationEvent(spTrackEntry* entry);
};

float GetMoveToTime(Vec2 vc1,Vec2 vc2, float speed);

#endif