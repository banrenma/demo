#ifndef __NSKELETONDATACACHE__
#define __NSKELETONDATACACHE__
#include <string>
#include <map>
#include "base/CCRef.h"
#include "cocos2d.h"
#include <spine/SkeletonData.h>
#include <spine/Atlas.h>
#include <spine/SkeletonJson.h>

#define MAX_SKILL_NUM 4

class UtilBaseData:public cocos2d::Ref
{
public:
	UtilBaseData():m_iID(0),m_poSkeletonData(NULL),m_poAtlas(NULL)
	{

	}
	~UtilBaseData();
	UtilBaseData(int ID, const char * strJsonFile,const char *strAtlasFile)
	{
		m_iID =ID;
		m_strJsonFile= strJsonFile;
		m_strAtlasFile = strAtlasFile;
		m_poSkeletonData =  NULL;
		m_poAtlas = NULL;
	}
	UtilBaseData(UtilBaseData & data){
		m_iID =data.m_iID;
		m_strJsonFile= data.m_strJsonFile;
		m_strAtlasFile = data.m_strAtlasFile;
		m_poSkeletonData = data.m_poSkeletonData;
		m_poAtlas = data.m_poAtlas;
	}

	UtilBaseData operator =(UtilBaseData & data){
		m_iID =data.m_iID;
		m_strJsonFile= data.m_strJsonFile;
		m_strAtlasFile = data.m_strAtlasFile;
		m_poSkeletonData = data.m_poSkeletonData;
		m_poAtlas = data.m_poAtlas;
		return *this;
	}
	CC_SYNTHESIZE(int,m_iID,ID)
	CC_SYNTHESIZE(spSkeletonData *,m_poSkeletonData,SPSkeletonData)
	CC_SYNTHESIZE(spAtlas*,m_poAtlas,Atlas)
	CC_SYNTHESIZE(std::string,m_strJsonFile,JsonFile)
	CC_SYNTHESIZE(std::string,m_strAtlasFile,AtlasFile)
	virtual bool init(UtilBaseData & data);
	bool initSkeletonData();
};


class UtilData : public UtilBaseData
{
public:
	UtilData():UtilBaseData(),m_iTotalBlood(0),m_iAttack(0),m_iDefend(0),m_ucAttr(0)
	{

	}
	~UtilData(){}

	UtilData(int ID,int TotalBlood,int Attack,int Defend,unsigned char ucAttr, const char * strJsonFile,const char *strAtlasFile,const char ** str):UtilBaseData(ID,strJsonFile,strAtlasFile)
	{	
		m_iTotalBlood = TotalBlood;
		m_iAttack = Attack;
		m_iDefend = Defend;
		m_ucAttr = ucAttr;
		int i = 0;
		for(int i = 0; i < MAX_SKILL_NUM;i++)
		{
			if(str[i] != NULL)
			{
				m_vecSkill.push_back(str[i]);
			}
		}
	}
	UtilData(UtilData & data){
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

	}

	UtilData operator =(UtilData & data){
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
		return *this;
	}
	CC_SYNTHESIZE(int,m_iTotalBlood, TotalBlood)
	CC_SYNTHESIZE(int,m_iAttack, Attack)
	CC_SYNTHESIZE(int,m_iDefend, Defend)
	CC_SYNTHESIZE(unsigned char, m_ucAttr,ucAttr)
	CC_SYNTHESIZE(std::vector<std::string>,m_vecSkill, vecSkill)

	virtual bool init(UtilData & data);
};

class NSkeletonDataCache : public cocos2d::Ref
{
public:
	static NSkeletonDataCache * getInstance();
	
	bool AddSkeletonDataCache(UtilBaseData & data);
	bool AddSkeletonDataCache(UtilData & data);
	

	spSkeletonData * getSkeletonData(int ID);
	UtilBaseData * getData( int ID );

	bool RemoveSkeletonDataCache(int ID);
	bool RemoveAllSkeletonDataCache();
private:
	std::map<int,UtilBaseData *> m_SkeletonDataMap;
	NSkeletonDataCache();
	~NSkeletonDataCache();
	class NGarbage    //它的唯一工作就是在析构函数中删除NSkeletonDataCache的实例   
	{  
	public:  
		~NGarbage();  
	};  
	static NGarbage Garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数  
};

#endif 


