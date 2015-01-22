#include "Util.h"


int baseUtil:: s_iFightNum = 0;






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




