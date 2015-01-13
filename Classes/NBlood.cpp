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

NBlood * NBlood::create( int totalBlood, int PieceBlood /*= 1000*/ )
{
	NBlood * pBlood = new NBlood();


	if ( pBlood && pBlood->init(CONSTREDFILE,CONSTYELLOWFILE,CONSTGREENFILE,totalBlood,PieceBlood))
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
	m_iTotal = m_iCur = m_iCurTemp = totalBlood;
	m_iPieceBlood = PieceBlood;
	m_iDefaultHurt = m_iPieceBlood/20;
	this->addChild(m_pRedBlood,0);
	this->addChild(m_pYellowBlood,1);
	this->addChild(m_pGreenBlood,2);
	this->scheduleUpdateWithPriority(1);
	return true;
}

void NBlood::update( float deltaTime )
{
	if(m_iCurTemp <= m_iCur)
	{
		return;
	}
	if(m_iCurTemp <= m_iCur - m_iDefaultHurt)
	{
		m_iCurTemp = m_iCur;
	}
	else
	{
		m_iCurTemp -= m_iDefaultHurt;
	}
	if(m_iCurTemp <= m_iPieceBlood)
	{
		m_pYellowBlood->setVisible(false);
	}
	else
	{
		m_pYellowBlood->setVisible(true);
	}
	m_pGreenBlood->setScaleX(((m_iCurTemp + m_iPieceBlood)%m_iPieceBlood) /(float)m_iPieceBlood);

}




NBlood::NBlood()
{

}

NBlood::~NBlood()
{

}





