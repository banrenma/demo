#ifndef __SPINE_ANIMATION_EXT__
#define __SPINE_ANIMATION_EXT__

#include "spine/spine-cocos2dx.h"
#include "SpineData.h"

class SpineAnimationExtDelegate
{
public:
    virtual void SpineAnimationUpdate(SpineAnimationExt* table,float deltaTime) = 0;
};




class SpineAnimationExt:public spine::SkeletonAnimation
{
public:
	static SpineAnimationExt* create(int ID,SpineAnimationExtDelegate * pDelegate = NULL);
	static SpineAnimationExt* createWithData (spSkeletonData* skeletonData);
	static SpineAnimationExt* createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	static SpineAnimationExt* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
	
	
	SpineAnimationExt();
	SpineAnimationExt (spSkeletonData* skeletonData);
	SpineAnimationExt (const std::string& skeletonDataFile, spAtlas* atlas, float scale);
	SpineAnimationExt (const std::string& skeletonDataFile, const std::string& atlasFile, float scale);
	
	//当前骨骼的位置 
	cocos2d::ValueVector getSkeletonLocalBoundingBox(const char * slotName);
	cocos2d::ValueVector getSkeletonWorldBoundingBox(const char * slotName);

	cocos2d::Vec2 getBoneWorldPosition( const char * boneName );
	cocos2d::Vec2 getBoneLocalPosition( const char * boneName );

	//动画混合 	self->mix = 1;  
	spTrackEntry* setAnimation (int trackIndex, const std::string& name, bool loop, int mix = 1);
	spTrackEntry* addAnimation (int trackIndex, const std::string& name, bool loop, float delay = 0,int mix = 1);

	//添加一个 lua执行的接口
	virtual void update (float deltaTime);

	~SpineAnimationExt();
	
	CC_SYNTHESIZE(int,m_iID,ID)
	CC_SYNTHESIZE(SpineAnimationExtDelegate *,m_poDelegate,Delegate)
		

};











#endif