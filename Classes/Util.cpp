#include "Util.h"


int baseUtil:: s_iFightNum = 0;




float GetMoveToTime(Vec2 vc1,Vec2 vc2, float speed)
{
	float dx2 = (vc1.x - vc2.x)*(vc1.x - vc2.x);
	float dy2 = (vc1.y - vc2.y)*(vc1.y - vc2.y);
	float time = sqrt(dx2 + dy2)/(speed*60);
	return time;
}

Util::~Util()
{

}

Util * Util::create( UtilData & data )
{
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	UtilBaseData * pData = pCache->getData(data.getID());
	if(!pData)
	{
		pCache->AddSkeletonDataCache(data);
		pData =  pCache->getData(data.getID());
	}
	UtilData * poData = dynamic_cast<UtilData * >(pData);
	if(!poData)
	{
		return NULL;
	}
	Util * ut = new Util(poData);
	if(ut)
	{
		ut->autorelease();
		return ut;
	}
	CC_SAFE_DELETE(ut);
	return NULL;
}

bool Util::initUtil( )
{

	m_Blood = NBlood::create(m_data->getTotalBlood());
	m_BeforeSkeletonNode = Node::create();
	m_BehindSkeletonNode = Node::create();

	this->addChild(m_Blood,2);
	this->addChild(m_BeforeSkeletonNode,2);
	this->addChild(m_BehindSkeletonNode,-1);

	m_Blood->setPosition(this->getBoneLocalPosition("blood"));

	m_Target = NULL;

	return true;
}

void Util::update( float delta )
{
	NSpineExt::update(delta);

	m_Blood->setPosition(this->getBoneLocalPosition("blood"));
	m_BeforeSkeletonNode->setPosition(this->getBoneLocalPosition("weapon"));
}

Util::Util( UtilData * pData ):NSpineExt(pData->getSPSkeletonData())
{
	m_data = pData;
	initUtil();
}

void Util::setPosition( const Vec2 &position )
{
	Node::setPosition(position);
	setZOrder(720 - position.y);
}

void Util::setPosition( float x, float y )
{
	Node::setPosition(x,y);
	setZOrder(720 - y);
}

void Util::setPositionY( float y )
{
	Node::setPositionY(y);
	setZOrder(720 - y);
}





UtilMage * UtilMage::create( UtilData & data )
{
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	UtilBaseData * pData = pCache->getData(data.getID());
	if(!pData)
	{
		pCache->AddSkeletonDataCache(data);
		pData =  pCache->getData(data.getID());
	}
	UtilData * poData = dynamic_cast<UtilData * >(pData);
	if(!poData)
	{
		return NULL;
	}
	UtilMage * ut = new UtilMage(poData);
	if(ut)
	{
		ut->autorelease();
		return ut;
	}
	CC_SAFE_DELETE(ut);
	return NULL;
}

UtilMage::UtilMage( UtilData * pData ):Util(pData)
{
	
}

void UtilMage::setAnimationEvent(spTrackEntry* entry)
{
	UtilBaseData data1(2001,"2001.json","2001.atlas");
	UtilBaseData data2(3001,"3001.json","3001.atlas");
	UtilBaseData data3(4001,"4001.json","4001.atlas");
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();

	pCache->AddSkeletonDataCache(data1);
	pCache->AddSkeletonDataCache(data2);
	pCache->AddSkeletonDataCache(data3);


	setTrackEventListener(entry,[this](int trackIndex, spEvent* event){
		if(strcmp(event->data->name,"attack") == 0)
		{
			log("attack event");


			NSpineExt* node = NSpineExt::create(2001);
			node->setAnimation(0,"animation",false);
			getBeforeSkeletonNode()->addChild(node);

			/*		ClippingNode * nd = ClippingNode::create(node);
			LayerColor * color = LayerColor::create(Color4B(0,0,0,128),1280,720);
			nd->addChild(color);
			nd->setInverted(true);
			nd->setAlphaThreshold(0.5);
			this->getParent()->addChild(nd,0,10);*/
		}
		if(strcmp(event->data->name,"attakcend") == 0)
		{
			log("attakcend event");
			if(m_Target == NULL)
			{
				return;
			}
			getBeforeSkeletonNode()->removeAllChildrenWithCleanup(true);
			this->getParent()->removeChildByTag(10,true);
			NSpineExt* node2 = NSpineExt::create(3001);
			NSpineExt* node3 = NSpineExt::create(4001);
			this->m_Target->addChild(node2);
			this->m_Target->addChild(node3,1,333);
			node3->setVisible(false);
			Vec2 x1 = m_BeforeSkeletonNode->getPosition();
			Vec2 x2 = this->getPosition();
			Vec2 x3 = this->m_Target->getPosition();
			int aa = getFightNum();
			if(aa == 3)
			{
				int vv =1;
			}
			if(getScaleX() == -1)
			{
				x1.x *=-1;
			}

			Vec2 vc1 = (x1 + x2 - x3);
			if(this->m_Target->getScaleX() == -1)
			{
				vc1.x *=-1;
			}
			Vec2 vc2 = this->m_Target->getBoneLocalPosition("centerBone");

			node3->setPosition(vc2);
			node2->setAnimation(0,"animation",false);
			node2->setPosition(vc1);
			Util * ut = this->m_Target;
			
			int fromId = getFightNum();
			int toId = m_Target->getFightNum();

			node2->runAction(Sequence::create(MoveTo::create(GetMoveToTime(vc1,vc2,MAGE_SPEED),vc2),CallFunc::create([ut,node2,node3,fromId,toId](){
						
						nEvent * ev = new nEvent(fromId,toId,NEventName::HurtEvent,NEventType::None,NEventstate::Begin,0,NULL);
						EventManage::getInstance()->addEvent(ev);
						node3->setVisible(true);
						spTrackEntry* entry = node3->setAnimation(0,"animation",false);
						node3->setEndListener([node3](int trackIndex){ 
							node3->runAction(Sequence::create(CCDelayTime::create(0.5),CCCallFunc::create([node3](){node3->removeFromParentAndCleanup(true);}),NULL));
						});
						node2->removeFromParentAndCleanup(true);
				}),NULL));
		}
	});
}


UtilWarrior * UtilWarrior::create( UtilData & data )
{
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	UtilBaseData * pData = pCache->getData(data.getID());
	if(!pData)
	{
		pCache->AddSkeletonDataCache(data);
		pData =  pCache->getData(data.getID());
	}
	UtilData * poData = dynamic_cast<UtilData * >(pData);
	if(!poData)
	{
		return NULL;
	}
	UtilWarrior * ut = new UtilWarrior(poData);
	if(ut)
	{
		ut->autorelease();
		return ut;
	}
	CC_SAFE_DELETE(ut);
	return NULL;
}

UtilWarrior::UtilWarrior( UtilData * pData ):Util(pData)
{

}

void UtilWarrior::setAnimationEvent( spTrackEntry* entry )
{
	setTrackEventListener(entry,[this](int trackIndex, spEvent* event){
		if(strcmp(event->data->name,"attack") == 0)
		{
			log("attack event");
			nEvent * ev = new nEvent(this->getFightNum(),this->getTarget()->getFightNum(),NEventName::HurtEvent,NEventType::None,NEventstate::Begin,0,NULL);
			EventManage::getInstance()->addEvent(ev);
		}
	
	});
}
