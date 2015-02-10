#ifndef __ASTART__
#define __ASTART__
/*
 a*xub
*/
#include "cocos2d.h"
USING_NS_CC;
class aStarNode
{
public:
	aStarNode(){}
	aStarNode(aStarNode * pParent,int g,int h,Vec2 pt){
		m_pParent = pParent;
		m_if = g+h;
		m_ig = g;
		m_ih = h;
		m_pt = pt;
		m_iState = 0;
	}
	int getF(){return m_if;}
	int getG(){return m_ig;}
	int getH(){return m_ih;}
	int getState(){return m_iState;}
	void setState(int state){m_iState = state;}
	Vec2 getPt(){return m_pt;};
	aStarNode * getParent(){return m_pParent;}
	aStarNode(aStarNode & data)
	{
		m_pParent = data.m_pParent;
		m_if = data.m_if;
		m_ig = data.m_ig;
		m_ih = data.m_ih;
		m_pt = data.m_pt;
		m_iState = data.m_iState;
	}
	aStarNode  operator =(aStarNode & data)
	{
		m_pParent = data.m_pParent;
		m_if = data.m_if;
		m_ig = data.m_ig;
		m_ih = data.m_ih;
		m_pt = data.m_pt;
		m_iState = data.m_iState;
		return *this;
	}

	aStarNode * m_pParent;
	int m_if;
	int m_ig;
	int m_ih;
	Vec2 m_pt;
	int m_iState;
};
class MapGridData
{
public:
	int m_weight;
	aStarNode *  m_aStarNode;
	MapGridData(){}
	MapGridData(MapGridData & data)
	{
		m_weight = data.m_weight;
		m_aStarNode = data.m_aStarNode;
	}
	MapGridData  operator =(MapGridData & data)
	{
		m_weight = data.m_weight;
		m_aStarNode = data.m_aStarNode;
		return *this;
	}
};
class MapData
{
public:
	 MapData(int maxx,int maxy);
	~MapData();
	int m_maxx;
	int m_maxy;
	std::map<Vec2,MapGridData> m_data;
	void setGridWeight( Vec2 pt ,int weight);
	int getGridWeight(Vec2 pt);
	void resetGridStarNode();
	void resetGridWeight();
	void setGridaStarNode( Vec2 pt,aStarNode* paStarNode );
	aStarNode* getGridaStarNode (Vec2 pt);
	int getMaxx(){return m_maxx;};
	int getMaxy(){return m_maxy;};
};


class aStar
{
public:
	//enum class searchMode
	//{
	//	eightOrientation,
	//	fourOrientation
	//};
	aStar(MapData * pMap);
	std::vector<Vec2> BeginSearchPath(Vec2 starPosition,Vec2 endPosition);
protected:
	//���ڵ� �ƶ� ���ӽڵ� �Ĵ���
	//�ӽڵ� �ƶ��� Ŀ�ĵ� �Ĺ������
	virtual int getH(Vec2 pt,Vec2 targetPt);

	//���������޸� �ѽṹ ����Ҫ�� �����滻 ɾ��Ԫ�� �޸Ķѣ�
	void changeHeapDown();
	//���������޸ĶԽṹ����Ҫ�� �����޸�һ��Ԫ�أ�
	void changeHeapUp(int index = 0);

	//�Ƿ�����Ч��
	bool isPtPonderable(Vec2 pt);
	bool compareF(Vec2 pt1,Vec2 pt2);
	//�����б� �����
	std::vector<Vec2> m_vecOpen;
	MapData *m_pMapData;

};














#endif // __ASTART__



