#ifndef  __EVENT_MANAGE__
#define __EVENT_MANAGE__
#include "cocos2d.h"
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

class EventManage
{
public:
	static EventManage * getInstance();

	bool isEmpty();
	void addEvent(nEvent * ev);
	nEvent * getEvent();


protected:
	EventManage(){};
	~EventManage(){};
	std::queue<nEvent *>m_ManageEvent; //普通
};




#endif