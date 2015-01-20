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
	ut=  Util::create(data1);
	m_Hero.push_back(ut);
	lay->addChild(ut);
	ut->setPosition(30,60);
	ut->setScaleX(-1);
	ut->setAnimation(0,"stand",true);
	ut= Util::create(data2);
	m_Hero.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(30,300);
	ut->setScaleX(-1);
	ut= Util::create(data3);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(900,300);
	ut= Util::create(data4);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(1000,150);
	ut= Util::create(data5);
	m_Monster.push_back(ut);
	lay->addChild(ut);
	ut->setAnimation(0,"stand",true);
	ut->setPosition(950,450);
	m_Layer = lay;
	m_curChokeEvent = NULL;
	m_curEvent = NULL;
	m_ManageEvent.empty();
	
	createTree();
}



void UtilManage::createTree()
{

	rootNode = new SelectorNode();

	//���� ���������¼�
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
	//�¼� ״̬����
	ConditionNode * coud2_2 = new ConditionNode(std::bind(&UtilManage::isCurEventStateInProgress,this));
	ConditionNode * coud2_1 = new ConditionNode(std::bind(&UtilManage::isCurEventStateBegin,this));
	ConditionNode * coud2_3 = new ConditionNode(std::bind(&UtilManage::isCurEventStateEnd,this));


	//�¼�����
	//ConditionNode * coud3 = new ConditionNode(std::bind(isCurEventNameEqualChokeEvent,this));
	ConditionNode * coud4 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightBegin,this));
	ConditionNode * coud5 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualSceneBegin,this));
	ConditionNode * coud6 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualNextScene,this));
	ConditionNode * coud8 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualStory,this));
	ConditionNode * coud9 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightEnd,this));

	ConditionNode * coud10 = new ConditionNode(std::bind(&UtilManage::isStoryTypeBoss,this));
	ConditionNode * coud11 = new ConditionNode(std::bind(&UtilManage::isStoryTalk,this));

	ConditionNode * coud12 = new ConditionNode([this](){
		return !m_ManageEvent.empty();
	});
	ConditionNode * coud13 = new ConditionNode([this](){
		return m_curEvent->m_name == NEventName::RegisterEvent;
	});
	ConditionNode * coud14 = new ConditionNode([this](){
		return m_curEvent->m_name == NEventName::UserControlEvent;
	});
	ConditionNode * coud15 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightEnd,this));
	ConditionNode * coud16 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightEnd,this));
	ConditionNode * coud17 = new ConditionNode(std::bind(&UtilManage::isCurEventTypeEqualFightEnd,this));





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

		return true;
	});


	DecoratorBeforeAndEndNode * decNode = new DecoratorBeforeAndEndNode(sel3,[this](Behavior *p){
		if(m_ManageEvent.empty())
		{
			return true;
		}
		if(m_curEvent)
		{
			delete m_curEvent;
			m_curEvent = NULL;
		}
		m_curEvent = m_ManageEvent.front();
		m_ManageEvent.pop();
		return false;
	},
	[this](Behavior *p){
		return p->visit();
	});
	//�����¼�
	rootNode->addChild(seq1);
	seq1->addChild(coud1);
	seq1->addChild(sel1);
		sel1->addChild(seq2);
			//ս������
			seq2->addChild(coud9);
			seq2->addChild(act2);
		sel1->addChild(seq3);
			//ս����ʼ
			seq3->addChild(coud4);
			seq3->addChild(act1);
		//��ʼ����
		sel1->addChild(parFall1);
			parFall1->addChild(seq4);
				//���ڽ�����
				seq4->addChild(coud5);
				seq4->addChild(coud2_2);
			parFall1->addChild(seq5);
				//������ʼ
				seq5->addChild(coud5);
				seq5->addChild(coud2_1);
				seq5->addChild(act4);
				seq5->addChild(act5);
				//��������
			parFall1->addChild(seq6);
				seq6->addChild(coud5);
				seq6->addChild(coud2_3);
				seq6->addChild(act6);
		//��һ���ؿ�
		sel1->addChild(parFall2);
			parFall2->addChild(seq7);
				//���ڽ�����
				seq7->addChild(coud6);
				seq7->addChild(coud2_2);
			parFall2->addChild(seq8);
				//������ʼ
				seq8->addChild(coud6);
				seq8->addChild(coud2_1);
				seq8->addChild(act7);
				//��������
			parFall2->addChild(seq9);
				seq9->addChild(coud6);
				seq9->addChild(coud2_3);
				seq9->addChild(act1);

		//����
		sel1->addChild(parFall3);
			parFall3->addChild(seq10);
				//�������ڽ�����
				seq10->addChild(coud8);
				seq10->addChild(coud2_2);
			parFall3->addChild(seq11);
				//���鿪ʼ
				seq11->addChild(coud8);
				seq11->addChild(coud2_1);
				seq11->addChild(sel2);
						//boss����
					  sel2->addChild(seq12);
							seq12->addChild(coud10);
							seq12->addChild(act10);
							seq12->addChild(act8);
								//�Ի�
					  sel2->addChild(seq13);
							seq13->addChild(coud11);
							seq12->addChild(act10);
							seq13->addChild(act9);
				//�������
			parFall3->addChild(seq14);
				seq14->addChild(coud8);
				seq14->addChild(coud2_3);
				seq14->addChild(act11);
//��ѯ�¼�
				rootNode->addChild(parFall4);
					parFall4->addChild(seq15);
						seq15->addChild(coud12);
						seq15->addChild(decNode);
							sel3->addChild(seq16);
								//ע����¼�
								seq16->addChild(coud13);
								seq16->addChild(sel4);
							//����ai�¼� �ȴ���




								//����û��¼�
							sel3->addChild(seq17);
								seq17->addChild(coud14);
								seq17->addChild(sel5);
								//ѡ��Ӣ���¼�
									sel5->addChild(coud15)
									sel5->addChild(act12)
								//�ƶ�
									sel5->addChild(coud15)
									sel5->addChild(act12)
								//�ͷż���
									sel5->addChild(coud15)
									sel5->addChild(act12)
								//��������
									sel5->addChild(coud15)
									sel5->addChild(act12)
				//��� �Ƿ���Ӣ�۴��ڿ���״̬

				//��ʾ ����

}		

//�ж� ����û����������  ����� �ڷ���һ������ ���� ����һ����������¼�
bool UtilManage::Action_PostStoryEndOrNext()
{


	return true;
}

//��ͣ ��ǰ ʱ��  Ӣ�۶���
bool UtilManage::Action_PauseUtilAllAction()
{


	return true;
}

//boss���� ����
bool UtilManage::Action_BossComming()
{


	return true;
}
//̸�� ����
bool UtilManage::Action_Talk()
{


	return true;
}

//������һ���ؿ�  ����
bool UtilManage::Action_EnterNextScene()
{


	return true;
}

//�볡�����¼� post һ������ �� ����
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
//Ӣ���볡����
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
//���� config ע���¼� �� ���� ˢ�� ����
bool UtilManage::Action_RegisterEvent()
{

	return true;
}


// ��ǰս��������ʼ
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

// ��ǰս������
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

////ע�ᶨʱ������
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


//�ж��Ƿ��� boss���� ����
bool UtilManage::isStoryTypeBoss()
{
	
	return true;
}

//�ж��Ƿ��� �Ի� ����
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

void UtilManage::postEvent(nEvent * ev)
{
	m_ManageEvent.push_back(ev);
}

bool UtilManage::visit()
{
	rootNode->visit();
	return true;
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
	//��Ϸ����
	Sprite * bj= Sprite::create("1.png"); 
	bj->setPosition(gameSize.width/2,gameSize.height/2);
	this->addChild(bj);

	m_Manage = new UtilManage();
	m_Manage->init(this);
	m_Manage->Action_PostSceneBeginEvent();

	this->scheduleUpdate();
	return true;
}


void batterScene::update( float dt )
{
	m_Manage->visit();
}
