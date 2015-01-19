#include "UtilManage.h"

const char * aa[MAX_SKILL_NUM] = {{"walk"},{"aaa"}};
UtilData data1(1001,2000,100,10,0,"1001.json", "1001.atlas",aa);
const char * bb[MAX_SKILL_NUM] = {{"walk"},{"aaa"}};
UtilData data2(1002,2000,100,10,0,"1002.json", "1002.atlas",bb);
const char * cc[MAX_SKILL_NUM] = {{"walk"},{"aaa"}};
UtilData data3(1003,2000,100,10,0,"1003.json", "1003.atlas",cc);
const char * dd[MAX_SKILL_NUM] = {{"walk"},{"aaa"}};
UtilData data4(1004,2000,100,10,0,"1004.json", "1004.atlas",dd);
const char * ee[MAX_SKILL_NUM] = {{"walk"},{"aaa"}};
UtilData data5(1005,2000,100,10,0,"1005.json", "1005.atlas",ee);




void UtilManage::init()
{



}

void UtilManage::init( Layer * lay )
{
	Util * ut;
	ut= new Util(&data1);
	m_Hero.push_back(ut);
	lay->addChild(ut);
	ut= new Util(&data2);
	m_Hero.push_back(ut);
	lay->addChild(ut);
	ut= new Util(&data3);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut= new Util(&data4);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut= new Util(&data5);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	m_Layer = lay;
	m_curEvent = NULL;
	m_ManageEvent.empty();
	
	createTree();
}



void UtilManage::createTree()
{

	rootNode = new SelectorNode();

	//场景 阻塞其他事件
	SequenceNode * seq1 = new SequenceNode();

	ConditionNode * coud1 = new ConditionNode(std::bind(isCurEventEmpty,this));
	ConditionNode * coud2 = new ConditionNode(std::bind(isCurEventInProgress,this));
	ConditionNode * coud1 = new ConditionNode(std::bind(isCurEventEmpty,this));
	ConditionNode * coud2 = new ConditionNode(std::bind(isCurEventInProgress,this));
	seq1->addChild(coud1);

}

bool UtilManage::isCurEventEmpty()
{
	return m_curEvent != NULL;
}

bool UtilManage::isCurEventNameEqualChokeEvent()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_name == NEventName::ManageChokeEvent;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualFightBegin()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_type == NEventType::FightBegin;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualSceneBegin()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_type == NEventType::SceneBegin;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualNextScene()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_type == NEventType::NextScene;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualUtilEnter()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_type == NEventType::UtilEnter;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualStory()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_type == NEventType::Story;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualFightEnd()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_type == NEventType::FightEnd;
	}
	return false;
}



bool UtilManage::isCurEventInProgress()
{
	if(m_curEvent != NULL)
	{
		return m_curEvent->m_Eventstate == NEventstate::InPorgress;
	}
	return false;
}




void UtilManage::setCurEvent(nEvent * ev)
{
	m_curEvent = ev;
}

void UtilManage::postEvent(nEvent * ev)
{
	m_ManageEvent.push_back(ev);
}


cocos2d::Scene* batterScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = batterScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool batterScene::init()
{
	m_Manage = new UtilManage();
	m_Manage->init(this);

}

void batterScene::addUtilChild()
{


}
