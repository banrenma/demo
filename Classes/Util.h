#ifndef  __UTIL__
#define __UTIL__

//��̬��Ա  s_
//���Ա  m_
#include "cocos2d.h"
USING_NS_CC;


class baseUtil
{
public:
	/**/
	static int s_iFightNum; 
	baseUtil(){log("baseUtil constructor  s_iFightNum= %d",s_iFightNum);m_iFightNum = s_iFightNum;s_iFightNum ++;}
	~baseUtil(){log("baseUtil delete");}
	static void resetUtilID(){s_iFightNum = 0;}
	CC_SYNTHESIZE(int, m_iFightNum, FightNum);

};


class Util:public Node ,public baseUtil
{
public:
	Util();
	~Util();
protected:
	
	//����  -- ���� --Ѫ������ --ѡ������ --�ܻ�λ�� --������Чλ�� -- ������Χ -- 

	//״̬�� ����




};





#endif