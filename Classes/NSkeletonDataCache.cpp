/********************************************************************
	文件名称:	NSkeletonDataCache.cpp
	文件说明:	spine骨骼动画缓存
	创建日期:	22:12:2014   18:34
	作    者:	nie ming
*********************************************************************/

#include "NSkeletonDataCache.h"
USING_NS_CC;
/*************************************************
// 函数名称: 
// 函数说明: 
// 作    者: nie ming 
// Date: 2014/12/22
// 返 回 值: 
// 参    数: 
*************************************************/

//静态变量要在类外定义
bool UtilBaseData::init(UtilBaseData & data)
{
	m_iID =data.m_iID;
	m_strJsonFile= data.m_strJsonFile;
	m_strAtlasFile = data.m_strAtlasFile;
	m_poSkeletonData = data.m_poSkeletonData;
	m_poAtlas = data.m_poAtlas;
	return initSkeletonData();
}

bool UtilBaseData::initSkeletonData()
{
	m_poAtlas = spAtlas_createFromFile(m_strAtlasFile.c_str(), 0);
	if(m_poAtlas == NULL)
	{
		log("class UtilBaseData   m_atlas is NULL");
		return false;
	}
	spSkeletonJson* json = spSkeletonJson_create(m_poAtlas);
	json->scale = 1.0;
	m_poSkeletonData = spSkeletonJson_readSkeletonDataFile(json, m_strJsonFile.c_str());
	if(m_poSkeletonData == NULL || json->error)
	{
		log("class UtilBaseData Error reading skeleton data file  m_pskeletonData is NULL  or json->error %s",json->error);
		spSkeletonJson_dispose(json);
		return false;
	}
	spSkeletonJson_dispose(json);
	return true;
}

UtilBaseData::~UtilBaseData()
{
	if(m_poAtlas != NULL)
		spAtlas_dispose(m_poAtlas);
	if(m_poSkeletonData != NULL)
		spSkeletonData_dispose(m_poSkeletonData);
}



bool UtilData::init( UtilData & data )
{
	m_iID =data.m_iID;
	m_iTotalBlood = data.m_iTotalBlood;
	m_iAttack = data.m_iAttack;
	m_iDefend = data.m_iDefend;
	m_strJsonFile= data.m_strJsonFile;
	m_strAtlasFile = data.m_strAtlasFile;
	m_vecSkill = data.m_vecSkill;
	m_ucAttr = data.m_ucAttr;
	m_poSkeletonData = data.m_poSkeletonData;
	m_poAtlas = data.m_poAtlas;
	return initSkeletonData();
}

static NSkeletonDataCache * pInstance = NULL;

NSkeletonDataCache::NGarbage NSkeletonDataCache::Garbo;

NSkeletonDataCache * NSkeletonDataCache::getInstance()
{
	if(pInstance == NULL)
	{
		pInstance = new NSkeletonDataCache();
	}
	return pInstance;
}

bool NSkeletonDataCache::AddSkeletonDataCache( UtilBaseData & data )
{
	std::map<int,UtilBaseData *>::iterator it = m_SkeletonDataMap.find(data.getID());
	if(it == m_SkeletonDataMap.end())
	{
		UtilBaseData * pSkeletonData = new UtilBaseData();
		if(pSkeletonData)
		{
			if(pSkeletonData->init(data))
			{
				m_SkeletonDataMap[data.getID()] = pSkeletonData;
				return true;
			}
			else
			{
				pSkeletonData->release();
			}

		}
	}
	return false;
}

bool NSkeletonDataCache::AddSkeletonDataCache( UtilData & data )
{
	std::map<int,UtilBaseData *>::iterator it = m_SkeletonDataMap.find(data.getID());
	if(it == m_SkeletonDataMap.end())
	{
		UtilBaseData * pSkeletonData = new UtilData();
		if(pSkeletonData)
		{
			if(pSkeletonData->init(data))
			{
				m_SkeletonDataMap[data.getID()] = pSkeletonData;
				return true;
			}
			else
			{
				pSkeletonData->release();
			}

		}
	}
	return false;
}

bool NSkeletonDataCache::RemoveSkeletonDataCache( int ID )
{
	std::map<int,UtilBaseData *>::iterator it = m_SkeletonDataMap.find(ID);
	if(it != m_SkeletonDataMap.end())
	{
		it->second->release();
		it->second = NULL;
		m_SkeletonDataMap.erase(it);
		return true;
	}
	return false;
}

bool NSkeletonDataCache::RemoveAllSkeletonDataCache()
{
	std::map<int,UtilBaseData *>::iterator it = m_SkeletonDataMap.begin();
	for(;it != m_SkeletonDataMap.end();it++)
	{
		it->second->release();
		it->second = NULL;
	}
	m_SkeletonDataMap.empty();
	return true;
}

spSkeletonData * NSkeletonDataCache::getSkeletonData( int ID )
{
	std::map<int,UtilBaseData *>::iterator it = m_SkeletonDataMap.find(ID);
	if(it != m_SkeletonDataMap.end())
	{
		return it->second->getSPSkeletonData();
	}
	return NULL;
}

UtilBaseData * NSkeletonDataCache::getData( int ID )
{
	std::map<int,UtilBaseData *>::iterator it = m_SkeletonDataMap.find(ID);
	if(it != m_SkeletonDataMap.end())
	{
		return it->second;
	}
	return NULL;
}

NSkeletonDataCache::NSkeletonDataCache()
{
	m_SkeletonDataMap.empty();
}

NSkeletonDataCache::~NSkeletonDataCache()
{
	RemoveAllSkeletonDataCache();
}

NSkeletonDataCache::NGarbage::~NGarbage()
{
	if(pInstance != NULL)
	{
		delete pInstance;
	}
}




