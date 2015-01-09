#include "NSpineExt.h"

Rect NSpineExt::getSkeletonBoundingBox( const std::string& slotName )
{
	spSlot * slot = findSlot(slotName);
	if(!slot)
	{
		log("can not find slot %s",slotName.c_str());
		return Rect::ZERO;
	}
	//
	if(slot->attachment->type == SP_ATTACHMENT_BOUNDING_BOX)
	{
		Rect rt;
		spBoundingBoxAttachment* boundingBox = (spBoundingBoxAttachment*)slot->attachment;
		spBoundingBoxAttachment_computeWorldVertices(boundingBox,slot->bone,_worldVertices);
		for (int i = 0; i < boundingBox->verticesCount; i += 2) {
			if(i == 0)
			{
				rt.size.width = rt.origin.x = _worldVertices[i];
				rt.size.height = rt.origin.y = _worldVertices[i+1];
			}
			else
			{
				if(rt.origin.x > _worldVertices[i])
				{
					rt.origin.x = _worldVertices[i];
				}
				else
				{
					rt.size.width = _worldVertices[i];
				}
				if(rt.origin.y > _worldVertices[i+1])
				{
					rt.origin.y = _worldVertices[i+1];
				}
				else
				{
					rt.size.height = _worldVertices[i+1];
				}
			}

		}
		Vec2 position = getPosition();
		rt.size.width = rt.size.width - rt.origin.x;
		rt.size.height = rt.size.height - rt.origin.y;

		rt.origin.x += position.x;
		rt.origin.y += position.y;
		return rt;
	}
	return Rect::ZERO; 
}

//从缓存里面 创建
NSpineExt* NSpineExt::create( int Id )
{
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	
	NSpineExt* node = new NSpineExt(pCache->getSkeletonData(Id));
	node->autorelease();
	//这里要调用一下updateWorldTransform 初始化 m0 m1 m00 m01
	node->setID(Id);
	node->updateWorldTransform();
	return node;
}
//创建spine对象 接口
NSpineExt* NSpineExt::createWithData (spSkeletonData* skeletonData) {
	NSpineExt* node = new NSpineExt(skeletonData);
	node->autorelease();
	return node;
}
//创建spine对象 接口 文件方式
NSpineExt* NSpineExt::createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale) {
	NSpineExt* node = new NSpineExt(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}
//spine 导出 *.json--动画 骨骼关系  *.atlas --属性参数
NSpineExt* NSpineExt::createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
	NSpineExt* node = new NSpineExt(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

NSpineExt::NSpineExt( spSkeletonData* skeletonData ):m_ID(0),SkeletonAnimation(skeletonData)
{

}

NSpineExt::NSpineExt (const std::string& skeletonDataFile, spAtlas* atlas, float scale)
	: m_ID(0),SkeletonAnimation(skeletonDataFile, atlas, scale) {
		
}

NSpineExt::NSpineExt (const std::string& skeletonDataFile, const std::string& atlasFile, float scale)
	: m_ID(0),SkeletonAnimation(skeletonDataFile, atlasFile, scale) {
	
}

cocos2d::Vec2 NSpineExt::getBonePosition( const std::string& boneName )
{
	spBone * bone = findBone(boneName);
	if(!bone)
	{
		return Vec2::ZERO;
	}
	Vec2 position = getPosition();
	return Vec2(bone->worldX + bone->skeleton->x + position.x,bone->worldY + bone->skeleton->y + position.y);
}

NSpineExt::~NSpineExt()
{

}

