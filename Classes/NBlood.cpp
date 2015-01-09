#include "NBlood.h"




NBlood * NBlood::create( const std::string &Redfile,const std::string &Yellowfile,const std::string &Greenfile,int totalBlood,int PieceBlood /*= 1000*/ )
{
	NBlood * pBlood = new NBlood();


	if ( pBlood && pBlood->init(Redfile,Yellowfile,Greenfile,totalBlood,PieceBlood))
	{
		pBlood->autorelease();
		return pBlood;
	}
	CC_SAFE_DELETE(pBlood);
	return NULL;
}

bool NBlood::init( const std::string &Redfile,const std::string &Yellowfile,const std::string &Greenfile,int totalBlood, int PieceBlood /*= 1000*/ )
{
	m_pRedBlood = Sprite::create(Redfile);
	m_pYellowBlood = Sprite::create(Yellowfile);
	m_pGreenBlood = Sprite::create(Greenfile);
	if(!m_pRedBlood || !m_pYellowBlood || !m_pGreenBlood )
	{
		log("NBlood init fail");
		return false;
	}
	m_iTotal = m_iCur = totalBlood;
	m_iPieceBlood = PieceBlood;
	this->addChild(m_pRedBlood,0);
	this->addChild(m_pYellowBlood,1);
	this->addChild(m_pGreenBlood,2);
	if(m_iTotal <= m_iPieceBlood)
	{
		m_pYellowBlood:setVisible(false);
	}
	return true;
}

void NBlood::showBlood( int hurt, int curBlood )
{
	m_iCur = 
	if(m_iCur <= m_iPieceBlood)


}

NBlood::NBlood():m_fSpeed(0.1)
{

}

NBlood::~NBlood()
{

}




