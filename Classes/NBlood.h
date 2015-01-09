#ifndef  __NBLOOD__
#define  __NBLOOD__
#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
using namespace ui;


class NBlood:public Node
{
public:
	NBlood();
	~NBlood();
	static NBlood * create(const std::string &Redfile,const std::string &Yellowfile,const std::string &Greenfile,int totalBlood, int PieceBlood = 1000);

	bool init(const std::string &Redfile,const std::string &Yellowfile,const std::string &Greenfile,int totalBlood, int PieceBlood = 1000);
	Sprite*m_pRedBlood;
	Sprite*m_pYellowBlood;
	Sprite*m_pGreenBlood;

	CC_SYNTHESIZE(int, m_iFightNum, FightNum);

	CC_SYNTHESIZE(int,m_iCur,CurBlood)

	CC_SYNTHESIZE(int,m_iTotal,ToTalBlood)
	CC_SYNTHESIZE(float,m_fSpeed,Speed)
	/*一条血  的值*/
	CC_SYNTHESIZE(int,m_iPieceBlood,PieceBlood)
	void showBlood(int hurt, int curBlood);
	virtual void update (float deltaTime);
private:
	int m_iCurTemp;
};





#endif