#include "HelloWorldScene.h"
#include "Util.h"
#include "NSpineExt.h"
#include "ui/CocosGUI.h"
#include "sqlite/DbSqlite.h"
#include "sqlite/DBtest.h"

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
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//ÓÎÏ·±³¾°
	Sprite * bj= Sprite::create("1.png"); 
	bj->setPosition(gameSize.width/2,gameSize.height/2);
	this->addChild(bj);

	//
	DrawNode * drawNode = DrawNode::create();
	int width = gameSize.width,height = gameSize.height;
	int maxx = width % 24 == 0 ? width/24:width/24 +1;
	int maxy = height % 24 == 0 ? height/24:height/24 +1;
	for(int i =0; i < maxx; i++)
	{
		drawNode->drawLine(Vec2(i*24,0),Vec2(i*24,height),Color4F(0.65f, 0.65f, 0.65f, 0.5));
	}
	for(int i =0; i <maxy; i++)
	{
		drawNode->drawLine(Vec2(origin.x,i*24),Vec2(gameSize.width,i*24),Color4F(0.65f, 0.65f, 0.65f, 0.5));
	}	

	m_pMap = new MapData(maxx,maxy);
	m_star = new aStar(m_pMap);


	//drawNode->drawLine(Vec2(0,150),Vec2(1280,150),Color4F::GREEN);

	this->addChild(drawNode);

	DrawNode * drawNode1 = DrawNode::create();
	DrawNode * drawNode2 = DrawNode::create();
	DrawNode * drawNode3 = DrawNode::create();
	this->addChild(drawNode1,0,331);
	this->addChild(drawNode2,0,332);
	this->addChild(drawNode3,0,333);
	//NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();

	//pCache->AddSkeletonDataCache("1001.json","1001.atlas",1001);
	NSkeletonDataCache * pCache = NSkeletonDataCache::getInstance();
	UtilBaseData data1(2001,"2001.json","2001.atlas");

	pCache->AddSkeletonDataCache(data1);
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




	
	const char * aa[MAX_SKILL_NUM] = {{"walk"},{"aaa"}};


	UtilData data(1001,2000,100,10,0,"1001.json", "1001.atlas",aa);

	 ut = Util::create(data);
	ut->setPosition(200,200);
	ut->setScaleX(-1);

	
	this->addChild(ut);


	//DBtest * tst = new DBtest("dbtest.db");

	//this->addChild(tst);
	//tst->setPosition( 300,400);
	//db test


	setTouchEnabled(true);
	setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);

    return true;
}


  void HelloWorld::clickEvent(Ref * btn)
  {
	  Button * bt = dynamic_cast<Button *>(btn);
	  if(bt->getTag() == 1)
	  {
		    log("1111111111111111111111111111111");
		 /* ut->setAnimation(0,"walk",true);
		  ut->addAnimation(0,"attack11",false);*/
		  m_mode = 1;
		   DrawNode * draw1 = (DrawNode *)this->getChildByTag(331);
		   draw1->clear();
		   m_pMap->resetGridWeight();

	  }
	  else if(bt->getTag() == 2)
	  {



		  /*	  log("1111111111111111111111111111111");
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
		  });*/
		m_mode = 2;
		m_starPt.clear();
		DrawNode * draw2 = (DrawNode *)this->getChildByTag(332);
		draw2->clear();
		DrawNode * draw3 = (DrawNode *)this->getChildByTag(333);
		draw3->clear();

	  }

  }

  bool HelloWorld::onTouchBegan( Touch *touch, Event *unused_event )
  {
	  return true;
  }

  void HelloWorld::onTouchMoved( Touch *touch, Event *unused_event )
  {
	  Vec2 pt = touch->getLocation();
	  Vec2 grid;
	  grid.x = (int)(pt.x/24);
	  grid.y = (int)(pt.y/24);
	  DrawNode * draw1 = (DrawNode *)this->getChildByTag(331);
	  if(m_mode == 1)
	  {
		  if(m_pMap->getGridWeight(grid) != 200)
		  {
			  m_pMap->setGridWeight(grid,200);
			  draw1->drawSolidRect(Vec2(grid.x*24,grid.y*24),Vec2((grid.x+1)*24,(grid.y+1)*24),Color4F(0,0,0,1));
		  }

	  }

	  
  }

  void HelloWorld::onTouchEnded( Touch *touch, Event *unused_event )
  {
	  if(m_mode == 2)
	  {
		  Vec2 pt = touch->getLocation();
		  Vec2 grid;
		  grid.x = (int)(pt.x/24);
		  grid.y = (int)(pt.y/24);
		  DrawNode * draw2 = (DrawNode *)this->getChildByTag(332);
		  DrawNode * draw3 = (DrawNode *)this->getChildByTag(333);
		  if(m_starPt.size()<2)
		  {
			  draw2->drawSolidRect(Vec2(grid.x*24,grid.y*24),Vec2((grid.x+1)*24,(grid.y+1)*24),Color4F::GREEN);

			  m_starPt.push_back(grid);
			  if(m_starPt.size() == 2)
			  {
				  struct timeval now;
				  gettimeofday(&now, nullptr);  
					printf("begin time sec %ld %ld",now.tv_sec,now.tv_usec);
					std::vector<Vec2> path;
					/*	for(int j=0;j<100;j++)
					{*/
					  path = m_star->BeginSearchPath(m_starPt[0],m_starPt[1]);
				/*  }*/
				  gettimeofday(&now, nullptr);  
				  printf("begin time sec %ld %ld",now.tv_sec,now.tv_usec);
				  path.erase(path.begin());
				  path.erase(path.end()-1);
				  for(int k = 0; k < path.size();k++)
				  {
					  Vec2 temppt = path[k];
					  draw2->drawSolidRect(Vec2(temppt.x*24,temppt.y*24),Vec2((temppt.x+1)*24,(temppt.y+1)*24),Color4F::RED);

				  }
			  }
		  }
	  }


  }
