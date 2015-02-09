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
		m_isVisit = false;
	}
	int getF(){return m_if;}
	int getG(){return m_ig;}
	int getH(){return m_ih;}
	bool isVisit(){return m_isVisit;}
	Vec2 getPt(){return m_pt;};
	aStarNode(aStarNode & data)
	{
		m_pParent = data.m_pParent;
		m_if = data.m_if;
		m_ig = data.m_ig;
		m_ih = data.m_ih;
		m_pt = data.m_pt;
		m_isVisit = data.m_isVisit;
	}
	aStarNode  operator =(aStarNode & data)
	{
		m_pParent = data.m_pParent;
		m_if = data.m_if;
		m_ig = data.m_ig;
		m_ih = data.m_ih;
		m_pt = data.m_pt;
		m_isVisit = data.m_isVisit;
		return *this;
	}

	aStarNode * m_pParent;
	int m_if;
	int m_ig;
	int m_ih;
	Vec2 m_pt;
	bool m_isVisit;
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
	~ MapData();
	int m_maxx;
	int m_maxy;
	std::map<Vec2,MapGridData> m_data;
	void setGridWeight( Vec2 pt ,int weight);
	int getGridWeight(Vec2 pt);
	void resetGridVisit();
	void setGridaStarNode( Vec2 pt,aStarNode* paStarNode );
	aStarNode* getGridaStarNode (Vec2 pt);
	int getMaxx(){return m_maxx;};
	int getMaxy(){return m_maxy;};
};


class aStar
{
public:
	enum class searchMode
	{
		eightOrientation,
		fourOrientation
	};
	aStar(MapData * pMap);
	std::vector<Vec2> BeginSearchPath(Vec2 starPosition,Vec2 endPosition);
protected:
	//父节点 移动 到子节点 的代价
	virtual int getG(Vec2 parentPt,Vec2 pt);
	//子节点 移动到 目的地 的估算代价
	virtual int getH(Vec2 pt,Vec2 targetPt);
	//从8个方向把子child 放到开放列表
	void pushChildinOpen(aStarNode * node);
	
	//是否是有效的
	bool isPtPonderable(Vec2 pt);
	//开放列表 二叉堆
	std::vector<Vec2> m_vecOpen;
	MapData *m_pMapData;

};
#endif // __ASTART__



