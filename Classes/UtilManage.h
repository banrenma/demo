#ifndef  __UTIL_MANAGE__
#define __UTIL_MANAGE__
#include "cocos2d.h"
#include "NSkeletonDataCache.h"
#include "Util.h"
#include "BehaveTree.h"
USING_NS_CC;
//
enum class NEventType{
	//ManageChokeEvent 场景阻塞事件
	FightBegin,
	SceneBegin,      //
	NextScene,
	UtilEnter,
	Story,
	FightEnd,
	//ManageTimeLineEvent  定时器
	MonsterAdd,
	HeroAdd,
	InsertStory,

	// user
	HeroSelect,
	MoveHero,
	SelectTarget,
	HeroSkill,
	AutoFight,

	//ai
	searchTarget,
	attackTarget,
	switchTarget,
};


enum class NEventName{
	//场景事件
	ManageChokeEvent,
	ManageTimeLineEvent,      //
	UserControlEvent,
	AiEvent,
	HurtEvent,

};
enum class NEventstate
{
	Begin,
	InPorgress,
	End,
};


class  nEvent
{
public:	

public:
	nEvent(int m_fromID,int m_toID,NEventstate m_Eventstate,int time,NEventType  m_type,NEventName m_name)
	{
		this->m_fromID =m_fromID;
		this->m_toID= m_toID;
		this->m_Eventstate = m_Eventstate;
		this->time = time;
		this->m_name = m_name;
		this->m_type = m_type;

	}
	nEvent(nEvent & data){
		m_fromID =data.m_fromID;
		m_toID= data.m_toID;
		m_Eventstate = data.m_Eventstate;
		time = data.time;
		m_name = data.m_name;
		m_type = data.m_type;

	}

	nEvent operator =(nEvent & data){
		m_fromID =data.m_fromID;
		m_toID= data.m_toID;
		m_Eventstate = data.m_Eventstate;
		time = data.time;
		m_name = data.m_name;
		m_type = data.m_type;
		return *this;
	}


public:
	int m_fromID;
	int m_toID;
	NEventstate m_Eventstate;
	int time;
	NEventType  m_type;
	NEventName m_name;
};



class UtilManage
{

public:

	void init();
	void init(Layer * lay);
	void createTree();
	void setCurEvent(nEvent * ev);
	void postEvent(nEvent * ev);
	bool isCurEventEmpty();
	bool isCurEventInProgress();
	bool isCurEventNameEqualChokeEvent();

	bool isCurEventTypeEqualFightBegin();
	bool isCurEventTypeEqualSceneBegin();
	bool isCurEventTypeEqualNextScene();
	bool isCurEventTypeEqualUtilEnter();
	bool isCurEventTypeEqualStory();
	bool isCurEventTypeEqualFightEnd();
protected:
	std::vector<Util *> m_Hero;
	std::vector<Util *> m_Monster;
	std::vector<nEvent *>m_ManageEvent; //普通
	nEvent * m_curEvent;   //阻塞事件
	Layer * m_Layer;
	SelectorNode *rootNode;
};


class batterScene:public Layer
{
public:
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(batterScene);
	
	UtilManage * m_Manage;
	void addUtilChild();

};


#endif