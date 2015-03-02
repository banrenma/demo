
/********************************************************************
	created:	2015/03/01
	created:	1:3:2015   11:58
	filename: 	E:\SanguoDemo\sanguo\frameworks\runtime-src\Classes\SpineData.cpp
	file path:	E:\SanguoDemo\sanguo\frameworks\runtime-src\Classes
	file base:	SpineData
	file ext:	cpp
	author:		nieming
	
	purpose:	»º´æspine ¹Ç÷ÀÊý¾Ý
*********************************************************************/
#include "SpineData.h"
USING_NS_CC;

SpineBaseData::~SpineBaseData()
{
	if(m_poAtlas != NULL)
		spAtlas_dispose(m_poAtlas);
	if(m_poSkeletonData != NULL)
		spSkeletonData_dispose(m_poSkeletonData);
}

SpineBaseData::SpineBaseData()
:Ref(),
m_iID(0),
m_poSkeletonData(NULL),
m_poAtlas(NULL)
{

}

SpineBaseData::SpineBaseData( SpineBaseData & data )
{
	m_iID =data.m_iID;
	m_poSkeletonData = data.m_poSkeletonData;
	m_poAtlas = data.m_poAtlas;
}

SpineBaseData SpineBaseData::operator=( SpineBaseData & data )
{
	m_iID =data.m_iID;
	m_poSkeletonData = data.m_poSkeletonData;
	m_poAtlas = data.m_poAtlas;
	return *this;
}

bool SpineBaseData::initSkeletonData(int ID,const char * pAtlasFile, const char * pJsonFile)
{
	m_iID = ID;
	if(pAtlasFile == NULL || pJsonFile == NULL)
	{
		log("class pAtlasFile  or  pJsonFile is NULL");
		return false;
	}
	m_poAtlas = spAtlas_createFromFile(pAtlasFile, 0);
	if(m_poAtlas == NULL)
	{
		log("class SpineBaseData   m_atlas is NULL");
		return false;
	}
	spSkeletonJson* json = spSkeletonJson_create(m_poAtlas);
	json->scale = 1.0;
	m_poSkeletonData = spSkeletonJson_readSkeletonDataFile(json,pJsonFile);
	if(m_poSkeletonData == NULL || json->error)
	{
		log("class SpineBaseData Error reading skeleton data file  m_pskeletonData is NULL  or json->error %s",json->error);
		spSkeletonJson_dispose(json);
		return false;
	}
	spSkeletonJson_dispose(json);
	return true;
}

SpineBaseData * SpineBaseData::CreateSpineBaseData( int ID, const char * strJsonFile,const char *strAtlasFile )
{
	SpineBaseData * pData = new SpineBaseData();
	if(pData)
	{
		if(!pData->initSkeletonData(ID,strJsonFile,strAtlasFile))
		{
			delete pData;
			pData = NULL;
		}
	}
	return pData;
}




static SpineDataCache * pInstance = NULL;

SpineDataCache::NGarbage SpineDataCache::s_oGarbo;

SpineDataCache * SpineDataCache::getInstance()
{
	if(pInstance == NULL)
	{
		pInstance = new SpineDataCache();
	}
	return pInstance;
}

bool SpineDataCache::AddSpineDataCache( SpineBaseData *pData )
{
	if(pData == NULL)
	{
		return false;
	}
	std::map<int,SpineBaseData *>::iterator it = m_oSpineDataMap.find(pData->getID());
	if(it == m_oSpineDataMap.end())
	{
		m_oSpineDataMap[pData->getID()] = pData;
		return true;
	}
	return false;
}

bool SpineDataCache::AddSpineDataCache( int ID, const char * strJsonFile,const char *strAtlasFile )
{
	SpineBaseData * pData = SpineBaseData::CreateSpineBaseData(ID,strJsonFile,strAtlasFile);
	return AddSpineDataCache(pData);
}

bool SpineDataCache::RemoveSkeletonDataCache( int ID )
{
	std::map<int,SpineBaseData *>::iterator it = m_oSpineDataMap.find(ID);
	if(it != m_oSpineDataMap.end())
	{
		it->second->release();
		it->second = NULL;
		m_oSpineDataMap.erase(it);
		return true;
	}
	return false;
}

bool SpineDataCache::RemoveAllSkeletonDataCache()
{
	std::map<int,SpineBaseData *>::iterator it = m_oSpineDataMap.begin();
	for(;it != m_oSpineDataMap.end();it++)
	{
		it->second->release();
		it->second = NULL;
	}
	m_oSpineDataMap.clear();
	return true;
}

spSkeletonData * SpineDataCache::getSkeletonData( int ID )
{
	std::map<int,SpineBaseData *>::iterator it = m_oSpineDataMap.find(ID);
	if(it != m_oSpineDataMap.end())
	{
		return it->second->getSPSkeletonData();
	}
	return NULL;
}

SpineBaseData * SpineDataCache::getData( int ID )
{
	std::map<int,SpineBaseData *>::iterator it = m_oSpineDataMap.find(ID);
	if(it != m_oSpineDataMap.end())
	{
		return it->second;
	}
	return NULL;
}

SpineDataCache::SpineDataCache()
{
	m_oSpineDataMap.clear();
}

SpineDataCache::~SpineDataCache()
{
	RemoveAllSkeletonDataCache();
}

SpineDataCache::NGarbage::~NGarbage()
{
	if(pInstance != NULL)
	{
		delete pInstance;
	}
}




