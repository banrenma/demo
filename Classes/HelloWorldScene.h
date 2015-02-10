#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Util.h"
#include "NSpineExt.h"
#include "ui/CocosGUI.h"
#include "aStar.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void clickEvent(Ref * btn);
	Util * ut;
	MapData * m_pMap;
	aStar * m_star;
	int m_mode;
	std::vector<Vec2> m_starPt;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
};

#endif // __HELLOWORLD_SCENE_H__
