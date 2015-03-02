
#include "SpineAnimationExt.h"
#include "SpineData.h"
#include "LuaScriptHandlerMgr.h"
USING_NS_CC;


SpineAnimationExt* SpineAnimationExt::create( int ID,SpineAnimationExtDelegate * pDelegate /*= NULL*/ )
{
	SpineDataCache * pCache = SpineDataCache::getInstance();
	spSkeletonData* skeletonData = pCache->getSkeletonData(ID);
	if(!skeletonData)
	{
		log("getSkeletonData is NULL");
		return NULL;
	}
	SpineAnimationExt* node = new SpineAnimationExt(pCache->getSkeletonData(ID));
	node->autorelease();
	node->setID(ID);
	node->setDelegate(pDelegate);
	//node->updateWorldTransform();
	return node;
}


SpineAnimationExt* SpineAnimationExt::createWithData( spSkeletonData* skeletonData )
{
	SpineAnimationExt* node = new SpineAnimationExt(skeletonData);
	node->autorelease();
	//node->updateWorldTransform();
	return node;
}

SpineAnimationExt* SpineAnimationExt::createWithFile( const std::string& skeletonDataFile, spAtlas* atlas, float scale )
{
	SpineAnimationExt* node = new SpineAnimationExt(skeletonDataFile, atlas, scale);
	node->autorelease();
	//node->updateWorldTransform();
	return node;
}

SpineAnimationExt* SpineAnimationExt::createWithFile( const std::string& skeletonDataFile, const std::string& atlasFile, float scale )
{
	SpineAnimationExt* node = new SpineAnimationExt(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	//node->updateWorldTransform();
	return node;
}

SpineAnimationExt::SpineAnimationExt():m_iID(0),m_poDelegate(NULL)
{

}

SpineAnimationExt::SpineAnimationExt( spSkeletonData* skeletonData ):m_iID(0),m_poDelegate(NULL),SkeletonAnimation(skeletonData)
{
	//这里要调用一下updateWorldTransform 初始化 m0 m1 m00 m01
	updateWorldTransform();
}

SpineAnimationExt::SpineAnimationExt( const std::string& skeletonDataFile, spAtlas* atlas, float scale ):m_iID(0),m_poDelegate(NULL),SkeletonAnimation(skeletonDataFile, atlas, scale)
{
	//这里要调用一下updateWorldTransform 初始化 m0 m1 m00 m01
	updateWorldTransform();
}

SpineAnimationExt::SpineAnimationExt( const std::string& skeletonDataFile, const std::string& atlasFile, float scale ):m_iID(0),m_poDelegate(NULL),SkeletonAnimation(skeletonDataFile, atlasFile, scale)
{
	//这里要调用一下updateWorldTransform 初始化 m0 m1 m00 m01
	updateWorldTransform();
}


cocos2d::ValueVector SpineAnimationExt::getSkeletonLocalBoundingBox( const char * slotName )
{
	ValueVector data;
	spSlot * slot = findSlot(slotName);
	if(!slot)
	{
		log("can not find slot %s",slotName);
	}
	if(slot->attachment->type == SP_ATTACHMENT_BOUNDING_BOX)
	{
		Rect rt;
		spBoundingBoxAttachment* boundingBox = (spBoundingBoxAttachment*)slot->attachment;
		spBoundingBoxAttachment_computeWorldVertices(boundingBox,slot->bone,_worldVertices);
		for (int i = 0; i < boundingBox->verticesCount; i ++) {
			data.push_back(Value(_worldVertices[i]));
		}
	}
	return data;
}

cocos2d::ValueVector SpineAnimationExt::getSkeletonWorldBoundingBox( const char * slotName )
{
	ValueVector data;
	Vec2 position = getPosition();

	spSlot * slot = findSlot(slotName);
	if(!slot)
	{
		log("can not find slot %s",slotName);
	}
	if(slot->attachment->type == SP_ATTACHMENT_BOUNDING_BOX)
	{
		Rect rt;
		spBoundingBoxAttachment* boundingBox = (spBoundingBoxAttachment*)slot->attachment;
		spBoundingBoxAttachment_computeWorldVertices(boundingBox,slot->bone,_worldVertices);
		for (int i = 0; i < boundingBox->verticesCount; i ++) {
			if(i%2 == 0)
			{
				data.push_back(Value(_worldVertices[i]+position.x));
			}
			else
			{
				data.push_back(Value(_worldVertices[i]+position.y));
			}
		}
	}
	return data;
}

cocos2d::Vec2 SpineAnimationExt::getBoneWorldPosition( const char * boneName )
{
	spBone * bone = findBone(boneName);
	if(!bone)
	{
		return Vec2::ZERO;
	}
	Vec2 position = getPosition();
	return Vec2(bone->worldX + bone->skeleton->x + position.x,bone->worldY + bone->skeleton->y + position.y);
}

cocos2d::Vec2 SpineAnimationExt::getBoneLocalPosition( const char * boneName )
{
	spBone * bone = findBone(boneName);
	if(!bone)
	{
		return Vec2::ZERO;
	}
	return Vec2(bone->worldX + bone->skeleton->x,bone->worldY + bone->skeleton->y);
}

spTrackEntry* SpineAnimationExt::setAnimation( int trackIndex, const std::string& name, bool loop, int mix /*= 1*/ )
{
	spTrackEntry* pTrack = SkeletonAnimation::setAnimation(trackIndex,name,loop);
	pTrack->mix = mix;
	return pTrack;
}

spTrackEntry* SpineAnimationExt::addAnimation( int trackIndex, const std::string& name, bool loop, float delay /*= 0*/,int mix /*= 1*/ )
{
	spTrackEntry* pTrack = SkeletonAnimation::addAnimation(trackIndex,name,loop,delay);
	pTrack->mix = mix;
	return pTrack;
}

void SpineAnimationExt::update( float deltaTime )
{
	SkeletonAnimation::update(deltaTime);
	if(m_poDelegate)
	{
		m_poDelegate->SpineAnimationUpdate(this,deltaTime);
	}
}


SpineAnimationExt::~SpineAnimationExt()
{
	ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void*)this);

}



