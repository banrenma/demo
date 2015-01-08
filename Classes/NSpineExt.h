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
	NSpineExt (spSkeletonData* skeletonData);
	Rect getSkeletonBoundingBox(const std::string& slotName);

private:

};




#endif // !__NSPINEEXT__
