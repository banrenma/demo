#ifndef __NSPINEEXT__
#define __NSPINEEXT__
#include "spine/SkeletonAnimation.h"
#include "spine/spine-cocos2dx.h"
#include "spine/extension.h"
#include "NSkeletonDataCache.h"

using namespace spine;
USING_NS_CC;
class NSpineExt:public SkeletonAnimation
{
public:
	static NSpineExt* create(int Id);
	NSpineExt* createWithData (spSkeletonData* skeletonData);
	NSpineExt* createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale);
	NSpineExt* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale);

	NSpineExt (spSkeletonData* skeletonData);
	NSpineExt (const std::string& skeletonDataFile, spAtlas* atlas, float scale);
	NSpineExt (const std::string& skeletonDataFile, const std::string& atlasFile, float scale);
	Rect getSkeletonBoundingBox(const std::string& slotName);
	Vec2 getBonePosition(const std::string& boneName);
	CC_SYNTHESIZE(int,m_ID,ID)
	~NSpineExt();
};




#endif // !__NSPINEEXT__
