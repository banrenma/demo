#ifndef __SPINE_DATA__
#define __SPINE_DATA__
#include "cocos2d.h"
#include <spine/SkeletonData.h>
#include <spine/Atlas.h>
#include <spine/SkeletonJson.h>

class SpineBaseData:public cocos2d::Ref
{
public:
	SpineBaseData();
	~SpineBaseData();
	SpineBaseData(SpineBaseData & data);
	SpineBaseData operator =(SpineBaseData & data);
	CC_SYNTHESIZE(int,m_iID,ID)
	CC_SYNTHESIZE(spSkeletonData *,m_poSkeletonData,SPSkeletonData)
	CC_SYNTHESIZE(spAtlas*,m_poAtlas,Atlas)
	bool initSkeletonData(int ID,const char * pAtlasFile, const char * pJsonFile);
	static SpineBaseData * CreateSpineBaseData(int ID, const char * strJsonFile,const char *strAtlasFile);
};



class SpineDataCache : public cocos2d::Ref
{
public:
	static SpineDataCache * getInstance();

	bool AddSpineDataCache(int ID, const char * strJsonFile,const char *strAtlasFile);
	bool AddSpineDataCache( SpineBaseData *pData );

	spSkeletonData * getSkeletonData(int ID);
	SpineBaseData * getData( int ID );

	bool RemoveSkeletonDataCache(int ID);
	bool RemoveAllSkeletonDataCache();
private:
	std::map<int,SpineBaseData *> m_oSpineDataMap;
	SpineDataCache();
	~SpineDataCache();
	class NGarbage    //����Ψһ��������������������ɾ��SpineDataCache��ʵ��   
	{  
	public:  
		~NGarbage();  
	};  
	static NGarbage s_oGarbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  
};




#endif
