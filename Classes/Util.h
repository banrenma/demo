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
	static int s_iUtilID; 
	baseUtil(){log("baseUtil constructor  s_iUtilID= %d",s_iUtilID);m_iID = s_iUtilID;s_iUtilID ++;}
	~baseUtil(){log("baseUtil delete");}
	static void resetUtilID(){s_iUtilID = 0;}
	CC_PROPERTY(int, m_iID, ID);

};
int baseUtil:: s_iUtilID = 0;

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