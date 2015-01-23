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
	ut=  UtilMage::create(data1);
	m_Hero.push_back(ut);
	lay->addChild(ut);
	ut->setPosition(30,60);
	ut->setScaleX(-1);
	ut->setAnimation(0,"stand",true);
	ut= UtilWarrior::create(data2);
	m_Hero.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(30,300);
	ut->setScaleX(-1);
	ut= UtilWarrior::create(data3);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(900,300);
	ut= UtilMage::create(data4);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(1000,150);
	ut= UtilMage::create(data5);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(950,450);
	m_Layer = lay;
	m_curChokeEvent = NULL;
	m_curEvent = NULL;
	m_ManageEvent = EventManage::getInstance();
	
	m_selGreenCircle = Sprite::create("circle_green.png");
	m_selCircle = Sprite::create("circle.png");
	m_selGreenCircle->setZOrder(-1);
	m_selCircle->setZOrder(-1);
	m_selGreenCircle->retain();
	m_selCircle->retain();
	m_curSelectHero = -1;
	createTree();
}


Util * UtilManage::getHeroByID(int ID)
{
	std::vector<Util *>::iterator it;
	for (it = m_Hero.begin();it != m_Hero.end();it++)
	{
		if((*it)->getFightNum() == ID)
			return (*it);
	}
	return NULL;
}
Util * UtilManage::getMonsterByID(int ID)
{
	std::vector<Util *>::iterator it;
	for (it = m_Monster.begin();it != m_Monster.end();it++)
	{
		if((*it)->getFightNum() == ID)
			return (*it);
	}
	return NULL;
}
Util * UtilManage::getAllUtilByID(int ID)
{
	std::vector<Util *>::iterator it;
	for (it = m_Hero.begin();it != m_Hero.end();it++)
	{
		if((*it)->getFightNum() == ID)
			return (*it);
	}
	for (it = m_Monster.begin();it != m_Monster.end();it++)
	{
		if((*it)->getFightNum() == ID)
			return (*it);
	}
	return NULL;
}



void UtilManage::createTree()
{

	rootNode = new SelectorNode();

	//场景 阻塞其他事件
	SequenceNode * seq1 = new SequenceNode();
	SequenceNode * seq2 = new SequenceNode();
	SequenceNode * seq3 = new SequenceNode();
	SequenceNode * seq4 = new SequenceNode();
	SequenceNode * seq5 = new SequenceNode();
	SequenceNode * seq6 = new SequenceNode();
	SequenceNode * seq7 = new SequenceNode();
	SequenceNode * seq8 = new SequenceNode();
	SequenceNode * seq9 = new SequenceNode();
	SequenceNode * seq10 = new SequenceNode();
	SequenceNode * seq11 = new SequenceNode();
	SequenceNode * seq12 = new SequenceNode();
	SequenceNode * seq13 = new SequenceNode();
	SequenceNode * seq14 = new SequenceNode();
	SequenceNode * seq15 = new SequenceNode();
	SequenceNode * seq16 = new SequenceNode();
	SequenceNode * seq17 = new SequenceNode();
	SequenceNode * seq18 = new SequenceNode();		
	SequenceNode * seq19 = new SequenceNode();
	SequenceNode * seq20 = new SequenceNode();	
	SequenceNode * seq21 = new SequenceNode();	
	SequenceNode * seq22 = new SequenceNode();	
	SequenceNode * seq23 = new SequenceNode();	
	SequenceNode * seq24 = new SequenceNode();	
	SequenceNode * seq25 = new SequenceNode();	
	SequenceNode * seq26 = new SequenceNode();	



	SelectorNode * sel1 = new SelectorNode();
	SelectorNode * sel2 = new SelectorNode();
	SelectorNode * sel3 = new SelectorNode();
	SelectorNode * sel4 = new SelectorNode();
	SelectorNode * sel5 = new SelectorNode();
	SelectorNode * sel6 = new SelectorNode();
	SelectorNode * sel7 = new SelectorNode();
	SelectorNode * sel8 = new SelectorNode();


	ParallelFallNode * parFall1 = new ParallelFallNode();
	ParallelFallNode * parFall2 = new ParallelFallNode();
	ParallelFallNode * parFall3 = new ParallelFallNode();
	ParallelFallNode * parFall4 = new ParallelFallNode();
	ParallelFallNode * parFall5 = new ParallelFallNode();
	ParallelFallNode * parFall6 = new ParallelFallNode();

	ConditionNode * coud1 = new ConditionNode(std::bind(&UtilManage::isCurEventEmpty,this));
	//事件 状态条件
	ConditionNode * coud2_2 = new ConditionNode(std::bind(&UtilManage::isCurEventStateInProgress,this));
	ConditionNode * coud2_1 = new ConditionNode(std::bind(&UtilManage::isCurEventStateBegin,this));
	ConditionNode * coud2_3 = new ConditionNode(std::bind(&UtilManage::isCurEventStateEnd,this));


	//事件名字
	//ConditionNode * coud3 = new ConditionNode(std::bind(isCurEventNameEqualChokeEvent,this));
	ConditionNode * coud4 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightBegin,this));
	ConditionNode * coud5 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualSceneBegin,this));
	ConditionNode * coud6 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualNextScene,this));
	ConditionNode * coud8 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualStory,this));
	ConditionNode * coud9 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightEnd,this));

	ConditionNode * coud10 = new ConditionNode(std::bind(&UtilManage::isStoryTypeBoss,this));
	ConditionNode * coud11 = new ConditionNode(std::bind(&UtilManage::isStoryTalk,this));

	ConditionNode * coud12 = new ConditionNode([this](){
		return !m_ManageEvent->isEmpty();
	});
	ConditionNode * coud13 = new ConditionNode([this](){
		return m_curEvent->m_name == NEventName::RegisterEvent;
	});
	ConditionNode * coud14 = new ConditionNode([this](){
		return m_curEvent->m_name == NEventName::UserControlEvent;
	});
	ConditionNode * coud15 = new ConditionNode([this](){
		return m_curEvent->m_type == NEventType::HeroSelect;
	});
	ConditionNode * coud16 = new ConditionNode([this](){
		return m_curEvent->m_type == NEventType::MoveHero;
	});
	ConditionNode * coud17 = new ConditionNode([this](){
		return m_curEvent->m_type == NEventType::SelectTarget;
	});
	ConditionNode * coud18 = new ConditionNode([this](){
		return m_curEvent->m_type == NEventType::HeroSkill;
	});


	ConditionNode * coud19 = new ConditionNode([this](){
		Util * ut = getAllUtilByID(m_curEvent->m_fromID);
		if(ut->getFightNum() == 1)
		{
			int aa;
			aa = 1;
		}
		return ut->getControlState() == Util::Controlstate::Util_useControl;
	});

	ConditionNode * coud20 = new ConditionNode([this](){
		Util * ut = getAllUtilByID(m_curEvent->m_fromID);
		if(ut->getTarget() == NULL)
		{
			return true;
		}
		return false;
	});
	ConditionNode * coud21 = new ConditionNode([this](){
		Util * ut = getAllUtilByID(m_curEvent->m_fromID);
		Rect rt = ut->getSkeletonBoundingBox("attackRect");
		if(rt.equals(Rect::ZERO))
		{
			return false;
		}
		if(!m_Layer->getChildByTag(222))
		{
			DrawNode * draw = DrawNode::create();
			draw->drawRect(rt.origin,Vec2(rt.getMaxX(),rt.getMaxY()),Color4F::RED);
			m_Layer->addChild(draw,0,222);
		}

		if(rt.intersectsRect(ut->getTarget()->getSkeletonBoundingBox("UtilBoundingBox")) )
		{
			return false;
		}
		return true;
	});

	ConditionNode * coud22 = new ConditionNode([this](){
		return true;
	});
	ConditionNode * coud23 = new ConditionNode([this](){
		return false;
	});



	ActionNode *act1 = new ActionNode(std::bind(&UtilManage::Action_PostSceneBeginEvent,this));
	ActionNode *act2 = new ActionNode(std::bind(&UtilManage::Action_EndFight,this));
	ActionNode *act4 = new ActionNode(std::bind(&UtilManage::Action_HeroEntrance,this));
	ActionNode *act5 = new ActionNode(std::bind(&UtilManage::Action_RegisterEvent,this));
	ActionNode *act6 = new ActionNode(std::bind(&UtilManage::Action_PostSceneBeginEndEvent,this));
	ActionNode *act7 = new ActionNode(std::bind(&UtilManage::Action_EnterNextScene,this));
	ActionNode *act8 = new ActionNode(std::bind(&UtilManage::Action_BossComming,this));
	ActionNode *act9 = new ActionNode(std::bind(&UtilManage::Action_Talk,this));
	ActionNode *act10 = new ActionNode(std::bind(&UtilManage::Action_PauseUtilAllAction,this));
	ActionNode *act11 = new ActionNode(std::bind(&UtilManage::Action_PostStoryEndOrNext,this));


	ActionNode *act12 = new ActionNode([this](){
		m_selGreenCircle->removeFromParentAndCleanup(true);
		Util * hero = getAllUtilByID(m_curEvent->m_fromID);
		hero->addChild(m_selGreenCircle);
		m_curSelectHero = m_curEvent->m_fromID;
		return true;
	});


	ActionNode *act13 = new ActionNode([this](){
		Util * hero = getAllUtilByID(m_curEvent->m_fromID);
		Vec2 * p = (Vec2 *)m_curEvent->m_args;
		hero->stopAllActions();
		hero->addAnimation(1,"walk",true);
		hero->setControlState(Util::Controlstate::Util_useControl);
		Vec2 vec2 = hero->getPosition();
		float dx2 = ((*p).x - vec2.x)*((*p).x - vec2.x);
		float dy2 = ((*p).y - vec2.y)*((*p).y - vec2.y);
		
		float time = sqrt(dx2 + dy2)/(UTIL_SPEED*60);
		
		Sequence * seq = Sequence::create(MoveTo::create(time,(*p)),CallFunc::create([this,hero](){
			hero->setControlState(Util::Controlstate::Util_AiControl);
			hero->clearTrack(1);
		}),nullptr);
		seq->setTag(101);
		hero->runAction(seq);
		return true;
	});


	ActionNode *act14 = new ActionNode([this](){
		Util * hero = getAllUtilByID(m_curEvent->m_fromID);
		Util * m_Monster = getAllUtilByID(m_curEvent->m_toID);
		hero->setTarget(m_Monster);
		return true;
	});


	ActionNode *act15 = new ActionNode([this](){
		Util * hero = getAllUtilByID(m_curEvent->m_fromID);
	


		return true;
	});

	ActionNode *act16 = new ActionNode([this](){
		Util * hero = getAllUtilByID(m_curEvent->m_fromID);


		
		return true;
	});
	ActionNode *act17 = new ActionNode([this](){
		
		Util * hero = getHeroByID(m_curEvent->m_fromID);
		if(hero)
		{
			hero->setTarget(*m_Monster.begin());
			return true;
		}
		hero = getMonsterByID(m_curEvent->m_fromID);
		if(hero)
		{
			hero->setTarget(*m_Hero.begin());
			return true;
		}

		return false;
	});
	ActionNode *act18 = new ActionNode([this](){
		Util * ut1 = getAllUtilByID(m_curEvent->m_fromID);
		Util * ut2 = ut1->getTarget();
		Vec2 vec1 = ut1->getPosition();
		Vec2 vec2 = ut2->getPosition();
		Vec2 pt;
		if(ut1->getFightNum() == 1)
		{
			int aa;
			aa = 1;
		}
		ut1->addAnimation(1,"walk",true);
		if(fabs(vec1.x - vec2.x) < 1 && fabs(vec1.y - vec2.y) < 1)
		{
			return false;
		}
		else if(fabs(vec1.x - vec2.x) < 1)
		{
			vec1.y >vec2.y?pt.y = vec1.y - UTIL_SPEED:pt.y = vec1.y + UTIL_SPEED;
			pt.x = vec1.x;
		}
		else if(fabs(vec1.y - vec2.y) < 1)
		{
			vec1.x >vec2.x?pt.x = vec1.x - UTIL_SPEED:pt.x = vec1.x + UTIL_SPEED;
			pt.y = vec1.y;
		}
		else
		{
			float dx2 = (vec1.x - vec2.x)*(vec1.x - vec2.x);
			float dy2 = (vec1.y - vec2.y)*(vec1.y - vec2.y);
			float speed = UTIL_SPEED *UTIL_SPEED;
			float dy = sqrt((speed * dy2)/(dx2 + dy2));
			float dx = sqrt((speed * dx2)/(dx2 + dy2));
			vec1.x >vec2.x?pt.x = vec1.x - dx:pt.x = vec1.x + dx;
			vec1.y >vec2.y?pt.y = vec1.y - dy:pt.y = vec1.y + dy;
		}
		
		ut1->setPosition(pt);
		return true;
	});
	ActionNode *act19 = new ActionNode([this](){
		Util * ut1 = getAllUtilByID(m_curEvent->m_fromID);

		spTrackEntry * sp = ut1->addAnimation(1,"attack01",false);
		ut1->setAnimationEvent(sp);

		return true;
	});

	ActionNode *act20 = new ActionNode([this](){

		postCheckState();

		return true;
	});

	DecoratorBeforeAndEndNode * decNode = new DecoratorBeforeAndEndNode(sel3,[this](Behavior *p){
		if(m_ManageEvent->isEmpty())
		{
			return true;
		}
		if(m_curEvent)
		{
			delete m_curEvent;
			m_curEvent = NULL;
		}
		m_curEvent = m_ManageEvent->getEvent();
		return false;
	},
	[this](Behavior *p){
		return p->visit();
	});
	//阻塞事件
	rootNode->addChild(seq1);
	seq1->addChild(coud1);
	seq1->addChild(sel1);
		sel1->addChild(seq2);
			//战斗结束
			seq2->addChild(coud9);
			seq2->addChild(act2);
		sel1->addChild(seq3);
			//战斗开始
			seq3->addChild(coud4);
			seq3->addChild(act1);
		//开始场景
		sel1->addChild(parFall1);
			parFall1->addChild(seq4);
				//正在进行中
				seq4->addChild(coud5);
				seq4->addChild(coud2_2);
			parFall1->addChild(seq5);
				//场景开始
				seq5->addChild(coud5);
				seq5->addChild(coud2_1);
				seq5->addChild(act4);
				seq5->addChild(act5);
				//场景结束
			parFall1->addChild(seq6);
				seq6->addChild(coud5);
				seq6->addChild(coud2_3);
				seq6->addChild(act6);
		//下一个关卡
		sel1->addChild(parFall2);
			parFall2->addChild(seq7);
				//正在进行中
				seq7->addChild(coud6);
				seq7->addChild(coud2_2);
			parFall2->addChild(seq8);
				//场景开始
				seq8->addChild(coud6);
				seq8->addChild(coud2_1);
				seq8->addChild(act7);
				//场景结束
			parFall2->addChild(seq9);
				seq9->addChild(coud6);
				seq9->addChild(coud2_3);
				seq9->addChild(act1);

		//剧情
		sel1->addChild(parFall3);
			parFall3->addChild(seq10);
				//剧情正在进行中
				seq10->addChild(coud8);
				seq10->addChild(coud2_2);
			parFall3->addChild(seq11);
				//剧情开始
				seq11->addChild(coud8);
				seq11->addChild(coud2_1);
				seq11->addChild(sel2);
						//boss出现
					  sel2->addChild(seq12);
							seq12->addChild(coud10);
							seq12->addChild(act10);
							seq12->addChild(act8);
								//对话
					  sel2->addChild(seq13);
							seq13->addChild(coud11);
							seq12->addChild(act10);
							seq13->addChild(act9);
				//剧情结束
			parFall3->addChild(seq14);
				seq14->addChild(coud8);
				seq14->addChild(coud2_3);
				seq14->addChild(act11);
//轮询事件
				rootNode->addChild(parFall4);
					parFall4->addChild(act20);
					parFall4->addChild(seq15);
						seq15->addChild(coud12);
						seq15->addChild(decNode);
							sel3->addChild(seq16);
								//注册的事件
								seq16->addChild(coud13);
								seq16->addChild(sel4);
							//电脑ai事件 先处理

								//添加用户事件
							sel3->addChild(seq17);
								seq17->addChild(coud14);
								
								seq17->addChild(sel5);

								//选择英雄事件
									sel5->addChild(seq18);
									seq18->addChild(coud15);
									seq18->addChild(act12);
								//移动
									sel5->addChild(seq19);
									seq19->addChild(coud16);
									seq19->addChild(act13);
								//释放技能 --
									sel5->addChild(seq20);
									seq20->addChild(coud18);
									seq20->addChild(act15);
								//攻击对象
									sel5->addChild(seq21);
									seq21->addChild(coud17);
									seq21->addChild(act14);
				//检测 是否有英雄处于空闲状态
				sel3->addChild(sel6);
				sel6->addChild(coud19);
					
					//逃跑
					sel6->addChild(seq22);
						seq22->addChild(coud23);
						seq22->addChild(act16);
					//无目标
					sel6->addChild(seq23);
						seq23->addChild(coud20);
						seq23->addChild(act17);

					//有目标不在攻击区域
					sel6->addChild(sel7);
						sel7->addChild(seq24);
						seq24->addChild(coud21);
						seq24->addChild(act18);
					//攻击
						sel7->addChild(seq25);
						seq25->addChild(coud22);
						seq25->addChild(act19);


				//显示 受伤

}		

//判断 还有没有其他剧情  如果有 在发出一个剧情 否则 发出一个剧情结束事件
bool UtilManage::Action_PostStoryEndOrNext()
{


	return true;
}

//暂停 当前 时间  英雄动作
bool UtilManage::Action_PauseUtilAllAction()
{


	return true;
}

//boss来了 剧情
bool UtilManage::Action_BossComming()
{


	return true;
}
//谈话 剧情
bool UtilManage::Action_Talk()
{


	return true;
}

//进入下一个关卡  动作
bool UtilManage::Action_EnterNextScene()
{


	return true;
}

//入场结束事件 post 一个结束 到 队列
bool UtilManage::Action_PostSceneBeginEndEvent()
{
	if(m_curChokeEvent)
	{
		delete m_curChokeEvent;
		m_curChokeEvent = NULL;
	}


	return true;
}

//
//英雄入场动做
bool UtilManage::Action_HeroEntrance()
{

	std::vector<Util *>::iterator it;
	for (it = m_Hero.begin();it != m_Hero.end();it++)
	{
	
		(*it)->setAnimation(0,"walk",true);
		(*it)->runAction(
		Sequence::create(MoveBy::create(2,Vec2(300,0)),
		CallFunc::create([this,it](){
			m_curChokeEvent->m_Eventstate = NEventstate::End;
			(*it)->setAnimation(0,"stand",true);
		}),nullptr)
		);
	}
	m_curChokeEvent->m_Eventstate = NEventstate::InPorgress;
	return true;
}
//更具 config 注册事件 ： 比如 刷怪 剧情
bool UtilManage::Action_RegisterEvent()
{

	return true;
}


// 当前战斗场景开始
bool UtilManage::isCurEventTypeEqualFightBegin()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_type == NEventType::FightBegin;
	}
	return false;
}

bool UtilManage::Action_PostSceneBeginEvent()
{
	if(m_curChokeEvent)
	{
		delete m_curChokeEvent;
		m_curChokeEvent = NULL;
	}
	m_curChokeEvent = new nEvent(0,0,NEventName::ManageChokeEvent,NEventType::SceneBegin,NEventstate::Begin,0,NULL);
	return true;
}

bool UtilManage::Action_PostFightBeginEvent()
{
	nEvent * ev = new nEvent(0,0,NEventName::ManageChokeEvent,NEventType::FightBegin,NEventstate::Begin,0,NULL);
	setCurEvent(ev);
	return true;
}

// 当前战斗结束
bool UtilManage::isCurEventTypeEqualFightEnd()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_type == NEventType::FightEnd;
	}
	return false;
}

bool UtilManage::Action_EndFight()
{

	return true;
}

////注册定时器函数
//bool UtilManage::Action_RegistTimeEvent()
//{
//
//	return true;
//}




bool UtilManage::isCurEventEmpty()
{
	return m_curChokeEvent != NULL;
}

bool UtilManage::isCurEventNameEqualChokeEvent()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_name == NEventName::ManageChokeEvent;
	}
	return false;
}



bool UtilManage::isCurEventTypeEqualSceneBegin()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_type == NEventType::SceneBegin;
	}
	return false;
}

bool UtilManage::isCurEventTypeEqualNextScene()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_type == NEventType::NextScene;
	}
	return false;
}



bool UtilManage::isCurEventTypeEqualStory()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_type == NEventType::Story;
	}
	return false;
}





bool UtilManage::isCurEventStateInProgress()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_Eventstate == NEventstate::InPorgress;
	}
	return false;
}
bool UtilManage::isCurEventStateBegin()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_Eventstate == NEventstate::Begin;
	}
	return false;
}
bool UtilManage::isCurEventStateEnd()
{
	if(m_curChokeEvent != NULL)
	{
		return m_curChokeEvent->m_Eventstate == NEventstate::End;
	}
	return false;
}


//判断是否是 boss来了 剧情
bool UtilManage::isStoryTypeBoss()
{
	
	return true;
}

//判断是否是 对话 剧情
bool UtilManage::isStoryTalk()
{

	return true;
}



void UtilManage::setCurEvent(nEvent * ev)
{
	if(m_curChokeEvent)
	{
		delete m_curChokeEvent;
		m_curChokeEvent = NULL;
	}
	m_curChokeEvent = ev;
}



bool UtilManage::visit()
{
	rootNode->visit();
	return true;
}

bool UtilManage::isPointInSelectHero( Vec2 pt )
{
	std::vector<Util *>::iterator it;
	for (it = m_Hero.begin();it != m_Hero.end();it++)
	{
		if((*it)->getSkeletonBoundingBox("UtilBoundingBox").containsPoint(pt))
		{
			nEvent* ev = new nEvent((*it)->getFightNum(),0,NEventName::UserControlEvent,NEventType::HeroSelect,NEventstate::Begin,0,NULL);
			EventManage::getInstance()->addEvent(ev);
			
			return true;
		}
	}
	return false;
}

bool UtilManage::isMoveHero( Vec2 pt )
{
	if(m_curSelectHero != -1)
	{
		nEvent* ev = new nEvent(m_curSelectHero,0,NEventName::UserControlEvent,NEventType::MoveHero,NEventstate::Begin,0,new Vec2(pt));
		EventManage::getInstance()->addEvent(ev);
		return true;
	}
	return false;
}

void UtilManage::postCheckState()
{
	std::vector<Util *>::iterator it;
	for (it = m_Hero.begin();it != m_Hero.end();it++)
	{
		
		nEvent* ev = new nEvent((*it)->getFightNum(),0,NEventName::AiEvent,NEventType::None,NEventstate::Begin,0,NULL);
		EventManage::getInstance()->addEvent(ev);

	}
	for (it = m_Monster.begin();it != m_Monster.end();it++)
	{
		nEvent* ev = new nEvent((*it)->getFightNum(),0,NEventName::AiEvent,NEventType::None,NEventstate::Begin,0,NULL);
		EventManage::getInstance()->addEvent(ev);

	}


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
	if ( !Layer::init() )
	{
		return false;
	}
	Size gameSize = Director::getInstance()->getVisibleSize();
	//游戏背景
	Sprite * bj= Sprite::create("1.png"); 
	bj->setPosition(gameSize.width/2,gameSize.height/2);
	this->addChild(bj);

	m_Manage = new UtilManage();
	m_Manage->init(this);
	m_Manage->Action_PostSceneBeginEvent();

	this->scheduleUpdate();
	this->setTouchEnabled(true);
	this->setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);

	particle = ParticleSystemQuad::create("zidian.plist");
	
	this->addChild(particle);
	line = MotionStreak::create(0.3f, 1.0f, 10.0f, Color3B(248, 177, 221),"line.png");
	line->setZOrder(1);
	this->addChild(line);
	return true;
}


void batterScene::update( float dt )
{
	m_Manage->visit();
}

void batterScene::onTouchEnded( Touch *touch, Event *unused_event )
{
	particle->stopSystem();
	line->reset();


}

bool batterScene::onTouchBegan( Touch *touch, Event *unused_event )
{
	
	
	particle->resetSystem();
	particle->setPosition(touch->getLocation());

	Vec2 pt = touch->getLocation();
	if(m_Manage->isPointInSelectHero(pt))
	{
		return true;
	}

	if(m_Manage->isMoveHero(pt))
	{
		return true;
	}
	

	return true;
}

void batterScene::onTouchMoved( Touch *touch, Event *unused_event )
{
	particle->setPosition(touch->getLocation());
	line->setPosition(touch->getLocation());
	
}


