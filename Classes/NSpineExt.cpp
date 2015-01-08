#include "NSpineExt.h"

Rect NSpineExt::getSkeletonBoundingBox( const std::string& slotName )
{
	spSlot * slot = findSlot(slotName);
	if(!slot)
	{
		log("can not find slot %s",slotName.c_str());
		return Rect::ZERO;
	}
	
	if(slot->attachment->type == SP_ATTACHMENT_BOUNDING_BOX)
	{
		Rect rt;
		spBoundingBoxAttachment* boundingBox = (spBoundingBoxAttachment*)slot->attachment;
		spBoundingBoxAttachment_computeWorldVertices(boundingBox,slot->bone,_worldVertices);
		for (int i = 0; i < boundingBox->verticesCount; i += 2) {
			rt.origin.x = std::min(_worldVertices[i],rt.origin.x);
			rt.origin.y = std::min(_worldVertices[i+1],rt.origin.y);
			rt.size.width =  std::max(_worldVertices[i], rt.size.width);
			rt.size.height =  std::max(_worldVertices[i+1], rt.size.height);
		}
		rt.size.width = rt.size.width - rt.origin.x;
		rt.size.height = rt.size.height - rt.origin.y;
		return rt;
	}
	return Rect::ZERO; 
}

NSpineExt* NSpineExt::create( int Id )
{
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	
	NSpineExt* node = new NSpineExt(pCache->getSkeletonData(Id));
	node->autorelease();
	return node;
}

NSpineExt::NSpineExt( spSkeletonData* skeletonData ):SkeletonAnimation(skeletonData)
{

}
