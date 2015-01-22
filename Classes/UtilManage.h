#ifndef  __UTIL_MANAGE__
#define __UTIL_MANAGE__
#include "cocos2d.h"
#include "NSkeletonDataCache.h"
#include "Util.h"
#include "BehaveTree.h"

#define  UTIL_SPEED  4
USING_NS_CC;
//
enum class NEventType{
	//ManageChokeEvent 场景阻塞事件
	None,
	FightBegin,
	SceneBegin,      //
	NextScene,
	Story,
	FightEnd,

	//

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
	RegisterEvent,
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
	nEvent(int m_fromID,int m_toID,NEventName m_name,NEventType  m_type,NEventstate m_Eventstate,int time,void * m_args)
	{
		this->m_fromID =m_fromID;
		this->m_toID= m_toID;
		this->m_Eventstate = m_Eventstate;
		this->time = time;
		this->m_name = m_name;
		this->m_type = m_type;
		this->m_args = m_args;
	}
	nEvent(nEvent & data){
		m_fromID =data.m_fromID;
		m_toID= data.m_toID;
		m_Eventstate = data.m_Eventstate;
		time = data.time;
		m_name = data.m_name;
		m_type = data.m_type;
		m_args = data.m_args;
	}

	nEvent operator =(nEvent & data){
		m_fromID =data.m_fromID;
		m_toID= data.m_toID;
		m_Eventstate = data.m_Eventstate;
		time = data.time;
		m_name = data.m_name;
		m_type = data.m_type;
		m_args = data.m_args;
		return *this;
	}

	~nEvent()
	{
		if(m_args != NULL)
		{
			delete m_args;
		}
	}

public:
	int m_fromID;
	int m_toID;
	NEventstate m_Eventstate;
	int time;
	NEventType  m_type;
	NEventName m_name;
	void * m_args;
};



class UtilManage
{

public:

	void init();
	void init(Layer * lay);
	void createTree();
	void setCurEvent(nEvent * ev);
	void postEvent(nEvent * ev);
	//条件回调
	bool isCurEventEmpty();

	bool isCurEventStateInProgress();
	bool isCurEventStateBegin();
	bool isCurEventStateEnd();

	bool isCurEventNameEqualChokeEvent();

	bool isCurEventTypeEqualFightBegin();
	bool isCurEventTypeEqualSceneBegin();
	bool isCurEventTypeEqualNextScene();
	bool isCurEventTypeEqualStory();
	bool isCurEventTypeEqualFightEnd();

	//Action回调
	bool Action_PostSceneBeginEvent();
	bool Action_EndFight();
	bool Action_HeroEntrance();
	bool Action_RegisterEvent();
	bool Action_PostSceneBeginEndEvent();
	bool Action_EnterNextScene();


	bool isStoryTypeBoss();
	bool isStoryTalk();
	bool Action_PauseUtilAllAction();
	bool Action_PostStoryEndOrNext();
	bool Action_BossComming();
	bool Action_Talk();


	bool visit();
	bool Action_PostFightBeginEvent();

	Util * getHeroByID(int ID);
	Util * getMonsterByID(int ID);

	bool isPointInSelectHero(Vec2 pt);
	bool isMoveHero( Vec2 pt );


	void postCheckState();
	Util * getAllUtilByID(int ID);
protected:
	std::vector<Util *> m_Hero;
	std::vector<Util *> m_Monster;
	std::queue<nEvent *>m_ManageEvent; //普通
	nEvent *m_curEvent;
	nEvent * m_curChokeEvent;   //阻塞事件
	Layer * m_Layer;
	SelectorNode *rootNode;

	Sprite * m_selCircle;
	Sprite * m_selGreenCircle;
	int m_curSelectHero;
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
	ParticleSystemQuad * particle;
	MotionStreak * line;
	void update(float dt);
	void addUtilChild();
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 

};


#endif