#include "aStar.h"

MapData::MapData( int maxx,int maxy )
{
	for(int x = 0; x < maxx; x++)
	{
		for(int y = 0; y < maxy; y ++)
		{
			MapGridData data;
			data.m_weight = 0;
			data.m_aStarNode = NULL;
			m_data[Vec2(x,y)] = data;
		}
	}
	m_maxx = maxx;
	m_maxy = maxy;
}

void MapData::setGridWeight( Vec2 pt ,int weight)
{
	m_data[pt].m_weight = weight;
}

int MapData::getGridWeight(Vec2 pt)
{
	return m_data[pt].m_weight;
}

void MapData::setGridaStarNode( Vec2 pt,aStarNode* paStarNode )
{
	m_data[pt].m_aStarNode = paStarNode;
}

aStarNode* MapData::getGridaStarNode (Vec2 pt)
{
	return m_data[pt].m_aStarNode;
}

void MapData::resetGridVisit()
{
	for(int x = 0; x < m_maxx; x++)
	{
		for(int y = 0; y < m_maxy; y ++)
		{
			m_data[Vec2(x,y)].m_aStarNode = NULL;
		}
	}
}

