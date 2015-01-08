#include "HelloWorldScene.h"
#include "Util.h"
#include "NSpineExt.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size gameSize = Director::getInstance()->getVisibleSize();
	//ÓÎÏ·±³¾°
	Sprite * bj= Sprite::create("1.png"); 
	bj->setPosition(gameSize.width/2,gameSize.height/2);
	this->addChild(bj);

	//
	DrawNode * drawNode = DrawNode::create();
	drawNode->drawLine(Vec2(0,150),Vec2(1280,150),Color4F::GREEN);
	this->addChild(drawNode);

	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();

	pCache->AddSkeletonDataCache("1001.json","1001.atlas",1001);
    
	NSpineExt* node = NSpineExt::create(1001);
	this->addChild(node);
	node->setPosition(200,200);
	Rect rt = node->getSkeletonBoundingBox("UtilBoundingBxo");
    return true;
}


