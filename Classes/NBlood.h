#ifndef  __NBLOOD__
#define  __NBLOOD__
#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
USING_NS_CC;
using namespace ui;


#define  CONSTREDFILE    "hp_red.png"
#define  CONSTYELLOWFILE "hp_yellow.png"
#define  CONSTGREENFILE  "hp_green.png"

class NBlood:public Node
{
public:
	NBlood();
	~NBlood();
	static NBlood * create(const std::string &Redfile,const std::string &Yellowfile,const std::string &Greenfile,int totalBlood, int PieceBlood = 1000);
	static NBlood * create(int totalBlood, int PieceBlood = 1000);
	bool init(const std::string &Redfile,const std::string &Yellowfile,const std::string &Greenfile,int totalBlood, int PieceBlood = 1000);
	Sprite*m_pRedBlood;
	Sprite*m_pYellowBlood;
	Sprite*m_pGreenBlood;
	//每帧 显示掉血量
	CC_SYNTHESIZE(int, m_iDefaultHurt, DefaultHurt);

	CC_SYNTHESIZE(int,m_iCur,CurBlood)

	CC_SYNTHESIZE(int,m_iTotal,ToTalBlood)
	/*一条血  的值*/
	CC_SYNTHESIZE(int,m_iPieceBlood,PieceBlood)
	//void showBlood(int hurt, int curBlood);
	virtual void update (float deltaTime);
private:
	int m_iCurTemp;
};





#endif