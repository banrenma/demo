#ifndef __NSKELETONDATACACHE__
#define __NSKELETONDATACACHE__
#include <string>
#include <map>
#include "base/CCRef.h"
#include "cocos2d.h"
#include <spine/SkeletonData.h>
#include <spine/Atlas.h>
#include <spine/SkeletonJson.h>

class NSkeletonData :public cocos2d::Ref
{

public:
	NSkeletonData();
	bool init(const char *jsonpath,const char *atlaspath ,int ID);
	~NSkeletonData();
	CC_SYNTHESIZE(int,m_ID,ID)
	CC_SYNTHESIZE(spSkeletonData *,m_pskeletonData,SPSkeletonData)
	CC_SYNTHESIZE(spAtlas*,m_atlas,Atlas)
	

};



class NSkeletonDataCache : public cocos2d::Ref
{
public:
	static NSkeletonDataCache * getInstance();
	
	bool AddSkeletonDataCache(const char *jsonpath,const char *atlaspath,int ID);
	spSkeletonData * getSkeletonData(int ID);
	bool RemoveSkeletonDataCache(int ID);
	bool RemoveAllSkeletonDataCache();
private:
	std::map<int,NSkeletonData *> m_SkeletonDataMap;
	NSkeletonDataCache();
	~NSkeletonDataCache();
	class NGarbage    //����Ψһ��������������������ɾ��NSkeletonDataCache��ʵ��   
	{  
	public:  
		~NGarbage();  
	};  
	static NGarbage Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  
};

#endif 


