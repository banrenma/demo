#ifndef  __UTIL__
#define __UTIL__

//��̬��Ա  s_
//���Ա  m_
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
	enum class Controlstate
	{
		Util_useControl,
		Util_AiControl,
	};
	enum class state
	{
		Util_empty,
		Util_findTarget,
		Util_attackTarget,
		Util_escape
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
protected:
	Node * m_Blood; 
	Node * m_BeforeSkeletonNode;
	Node * m_BehindSkeletonNode;
	UtilData* m_data;


	Controlstate m_ControlState;
	state m_state;







protected:
	


	




};





#endif