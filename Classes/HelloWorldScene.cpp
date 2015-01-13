#include "HelloWorldScene.h"
#include "Util.h"
#include "NSpineExt.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
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

	//NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();

	//pCache->AddSkeletonDataCache("1001.json","1001.atlas",1001);
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	pCache->AddSkeletonDataCache("2001.json","2001.atlas",2001);
	//NSpineExt* node = NSpineExt::create(1001);
	//this->addChild(node);
	//node->setPosition(200,200);
	//Rect rt = node->getSkeletonBoundingBox("UtilBoundingBox");

	//DrawNode * dw = DrawNode::create();
	//dw->drawRect(rt.origin,Vec2(rt.size.width + rt.origin.x,rt.size.height + rt.origin.y),Color4F::BLUE);

	Button * btn = Button::create("button_normal_bule.png","button_normal_bule_dianji.png","button_normal_bule_hui.png");
	//btn->addClickEventListener([=](Ref* sender){
	//	ut->setAnimation(0,"walk",true);
	//});
	
	btn->addClickEventListener(std::bind(&HelloWorld::clickEvent,this,std::placeholders::_1));

	this->addChild(btn,0,1);
	btn->setPosition(Vec2(120,50));
	Label *lb = Label::createWithTTF("walk","Marker Felt.ttf",30);
	lb->setPosition(Vec2(btn->getSize().width/2,btn->getSize().height/2));
	btn->addChild(lb);

	Button * btn2 = Button::create("button_normal_bule.png","button_normal_bule_dianji.png","button_normal_bule_hui.png");
	//btn->addClickEventListener([=](Ref* sender){
	//	ut->setAnimation(0,"walk",true);
	//});

	btn2->addClickEventListener(std::bind(&HelloWorld::clickEvent,this,std::placeholders::_1));

	this->addChild(btn2,0,2);
	btn2->setPosition(Vec2(360,50));
	Label *lb2 = Label::createWithTTF("attack","Marker Felt.ttf",30);
	lb2->setPosition(Vec2(btn2->getSize().width/2,btn2->getSize().height/2));
	btn2->addChild(lb2);




	
	std::vector<std::string>  skill;
	std::vector<int>  attr;
	std::string file1 = "1001.json";
	std::string file2 = "1001.atlas";

	UtilData data(1001,2000,100,10,file1,file2,skill,attr);

	 ut = Util::create(data);
	ut->setPosition(200,200);
	ut->setScaleX(-1);
	this->addChild(ut);


    return true;
}


  void HelloWorld::clickEvent(Ref * btn)
  {
	  Button * bt = dynamic_cast<Button *>(btn);
	  if(bt->getTag() == 1)
	  {
		  log("1111111111111111111111111111111");
		  ut->setAnimation(0,"walk",true);
	  }
	  else if(bt->getTag() == 2)
	  {
		  log("1111111111111111111111111111111");
		  spTrackEntry* entry = ut->setAnimation(0,"attack11",false);
		  ut->setTrackEventListener(entry,[=](int trackIndex, spEvent* event){
			  if(strcmp(event->data->name,"attack") == 0)
			  {
				  log("attack event");
				 

				  NSpineExt* node = NSpineExt::create(2001);
				  node->setAnimation(0,"animation",false);
				 ut->getBeforeSkeletonNode()->addChild(node);

				  ClippingNode * nd = ClippingNode::create(node);
				  LayerColor * color = LayerColor::create(Color4B(0,0,0,128),1280,720);
				  nd->addChild(color);
					nd->setInverted(true);
					nd->setAlphaThreshold(0.5);
				  this->addChild(nd,0,10);
				


			  }
			  if(strcmp(event->data->name,"attakcend") == 0)
			  {
				  log("attakcend event");
				  ut->getBeforeSkeletonNode()->removeAllChildrenWithCleanup(true);
				  this->removeChildByTag(10,true);
			  }
		  });


	  }

  }
