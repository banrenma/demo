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

NSkeletonData::NSkeletonData()
{
	m_ID = 0;
	m_atlas = NULL;
	m_pskeletonData = NULL;
}
bool NSkeletonData::init( const char *jsonpath,const char *atlaspath ,int ID )
{
	if(jsonpath == NULL || atlaspath == NULL)
	{
		log("class NSkeletonData   jsonpath or atlaspath is NULL");
		return false;
	}

	m_ID = ID;
	m_atlas = spAtlas_createFromFile(atlaspath, 0);
	if(m_atlas == NULL)
	{
		log("class NSkeletonData   m_atlas is NULL");
		return false;
	}
	spSkeletonJson* json = spSkeletonJson_create(m_atlas);
	json->scale = 1.0;
	m_pskeletonData = spSkeletonJson_readSkeletonDataFile(json, jsonpath);
	if(m_pskeletonData == NULL || json->error)
	{
		log("class NSkeletonData Error reading skeleton data file  m_pskeletonData is NULL  or json->error %s",json->error);
		spSkeletonJson_dispose(json);
		return false;
	}
	spSkeletonJson_dispose(json);
	return true;
}

NSkeletonData::~NSkeletonData()
{
	if(m_atlas != NULL)
		 spAtlas_dispose(m_atlas);
	if(m_pskeletonData != NULL)
		spSkeletonData_dispose(m_pskeletonData);
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

bool NSkeletonDataCache::AddSkeletonDataCache( const char *jsonpath,const char *atlaspath,int ID )
{
	std::map<int,NSkeletonData *>::iterator it = m_SkeletonDataMap.find(ID);
	if(it == m_SkeletonDataMap.end())
	{
		NSkeletonData * pSkeletonData = new NSkeletonData();
		if(pSkeletonData)
		{
			if(pSkeletonData->init(jsonpath, atlaspath, ID))
			{
				m_SkeletonDataMap[ID] = pSkeletonData;
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
	std::map<int,NSkeletonData *>::iterator it = m_SkeletonDataMap.find(ID);
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
	std::map<int,NSkeletonData *>::iterator it = m_SkeletonDataMap.begin();
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
	std::map<int,NSkeletonData *>::iterator it = m_SkeletonDataMap.find(ID);
	if(it != m_SkeletonDataMap.end())
	{
		return it->second->getSPSkeletonData();
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

