#include "Util.h"


int baseUtil:: s_iFightNum = 0;






Util::~Util()
{

}

Util * Util::create( UtilData & data )
{
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	spSkeletonData * pSkeleton = pCache->getSkeletonData(data.m_ID);
	if(!pSkeleton)
	{
		pCache->AddSkeletonDataCache(data.m_strJsonFile.c_str(),data.m_strAtlasFile.c_str(),data.m_ID);
		pSkeleton =  pCache->getSkeletonData(data.m_ID);
	}

	Util * ut = new Util(pSkeleton);
	if(ut && ut->initUtil(data))
	{
		ut->autorelease();
		return ut;
	}
	CC_SAFE_DELETE(ut);
	return NULL;
}

bool Util::initUtil( UtilData & data )
{
	m_data = data;
	m_Blood = NBlood::create(m_data.m_iTotalBlood);
	m_BeforeSkeletonNode = Node::create();
	m_BehindSkeletonNode = Node::create();

	this->addChild(m_Blood,2);
	this->addChild(m_BeforeSkeletonNode,2);
	this->addChild(m_BehindSkeletonNode,-1);

	m_Blood->setPosition(this->getBoneLocalPosition("blood"));


	return true;
}

void Util::update( float delta )
{
	NSpineExt::update(delta);

	m_Blood->setPosition(this->getBoneLocalPosition("blood"));
	m_BeforeSkeletonNode->setPosition(this->getBoneLocalPosition("weapon"));
}


Util::Util(spSkeletonData * pSkeleton):NSpineExt(pSkeleton)
{

}



