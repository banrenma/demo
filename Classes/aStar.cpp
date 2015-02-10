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

MapData::~MapData()
{
	resetGridStarNode();
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

void MapData::resetGridStarNode()
{
	for(int x = 0; x < m_maxx; x++)
	{
		for(int y = 0; y < m_maxy; y ++)
		{
			if(m_data[Vec2(x,y)].m_aStarNode != NULL)
			{
				delete m_data[Vec2(x,y)].m_aStarNode;
				m_data[Vec2(x,y)].m_aStarNode = NULL;
			}
		}
	}
}

void MapData::resetGridWeight()
{
	for(int x = 0; x < m_maxx; x++)
	{
		for(int y = 0; y < m_maxy; y ++)
		{
			m_data[Vec2(x,y)].m_weight = 0;
		}
	}
}



std::vector<Vec2>  aStar::BeginSearchPath( Vec2 starPosition,Vec2 endPosition )
{
	std::vector<Vec2> path;
	m_vecOpen.clear();
	//第0个位置 不占用
	m_vecOpen.push_back(Vec2::ZERO);
	if(starPosition == endPosition || !isPtPonderable(starPosition) || !isPtPonderable(endPosition) )
	{
		return path;
	}
	
	m_vecOpen.push_back(starPosition);

	aStarNode * node = new aStarNode(NULL,0,getH(starPosition,endPosition),starPosition);
	m_pMapData->setGridaStarNode(starPosition,node);

	 while(m_vecOpen.size() > 1)
	 {
		 aStarNode * node1 = m_pMapData->getGridaStarNode(m_vecOpen[1]);

		 if(node1 == NULL)
		 {
			 log("error node1 is NULL");
			 break;
		 }
		 //把当前的节点 放到关闭列表中
		 node1->setState(2);
		 changeHeapDown();
		 // 删除f 最小的节点
		 for(int i=0; i < 8;i++)
		 {
			 int count = 0;
			 int dx = i%3 -1,dy = i/3 -1;
			 Vec2 pt(node1->getPt().x + dx,node1->getPt().y + dy);
			 //找到终点
			 if(pt == endPosition)
			 {
				 path.push_back(endPosition);
				 path.push_back(node1->getPt());
				 aStarNode * tempNode =node1->getParent();
				 while(tempNode !=NULL)
				 {
					 path.push_back(tempNode->getPt());
					 tempNode = tempNode->getParent();
				 }
				 goto GetPATH;
			 }
			 // 判断条件 该点有效    不是障碍物
			 
			 if(isPtPonderable(pt)  &&  m_pMapData->getGridWeight(pt) < 200)
			 {
				 if(dx != 0 && dy != 0)
				 {
					 if(isPtPonderable(Vec2(pt.x-dx,pt.y)) && m_pMapData->getGridWeight(Vec2(pt.x-dx,pt.y)) >= 200 \
						 && isPtPonderable(Vec2(pt.x,pt.y-dy)) && m_pMapData->getGridWeight(Vec2(pt.x,pt.y-dy)) >= 200)
					 {
						 int aa = 10;
						 continue;
					 }
				 }


				  int G = 0,H = 0;
				  aStarNode * node2 = m_pMapData->getGridaStarNode(pt);
				  //计算 G值
				  if(i%3 != 1 && i/3 !=1 )
				  {
					  G = node1->getG() + 14;
				  }
				  else
				  {
					  G = node1->getG() + 10;
				  }

				if(node2==NULL )
				{
					H = getH(pt,endPosition);
					node2 = new aStarNode(node1,G,H,pt);
					m_pMapData->setGridaStarNode(pt,node2);
 
					m_vecOpen.push_back(pt);
					//添加到末尾 从新排列
					changeHeapUp();

				}
				else if(node2->getState() == 1)
				{
					//比较 g值  从新生成堆
					if(G < node2->getG())
					{
						int index = 0;
						for(;index < m_vecOpen.size();index++ )
						{
							if(m_vecOpen[index] == pt)
							{
								break;
							}
						}
						changeHeapUp(index);
					}
		
				}
				//

			 }
		 }
		
	 }

GetPATH:
	 //没找到
	 m_pMapData->resetGridStarNode();
	 return path;
}



bool aStar::isPtPonderable( Vec2 pt )
{
	return (pt.x >=0 && pt.x < m_pMapData->getMaxx() && pt.y >=0 && pt.y <m_pMapData->getMaxy());
}



int aStar::getH( Vec2 pt,Vec2 targetPt )
{
	return (abs(targetPt.x - pt.x) + abs(targetPt.y - pt.y))*10;
}

void aStar::changeHeapDown()
{
	Vec2 pt = m_vecOpen[m_vecOpen.size()-1];
	m_vecOpen[1] = pt;
	m_vecOpen.pop_back();
	int i = 1;
	while(true)
	{

		if(2*i >= m_vecOpen.size())
		{
			break;
		}
		if(2*i+1 >= m_vecOpen.size())
		{
			if(compareF(m_vecOpen[i],m_vecOpen[2*i]))
			{
				Vec2 tp = m_vecOpen[i];
				m_vecOpen[i] = m_vecOpen[2*i];
				m_vecOpen[2*i] = tp;
			}
			break;
		}
		else
		{
			if(compareF(m_vecOpen[2*i],m_vecOpen[2*i+1]))
			{
				if(compareF(m_vecOpen[i],m_vecOpen[2*i+1]))
				{
					Vec2 tp = m_vecOpen[i];
					m_vecOpen[i] = m_vecOpen[2*i+1];
					m_vecOpen[2*i+1] = tp;
					i= 2*i+1;
				}
				else
				{
					break;
				}
			}
			else
			{
				if(compareF(m_vecOpen[i],m_vecOpen[2*i]))
				{
					Vec2 tp = m_vecOpen[i];
					m_vecOpen[i] = m_vecOpen[2*i];
					m_vecOpen[2*i] = tp;
					i= 2*i;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void aStar::changeHeapUp( int index /*= 0*/ )
{
	if(index == 0)
	{
		index = m_vecOpen.size()-1;
	}

	while(true)
	{
		if(index < 2)
		{
			break;
		}
		else
		{
			if(compareF(m_vecOpen[index/2],m_vecOpen[index]))
			{
				Vec2 tp = m_vecOpen[index/2];
				m_vecOpen[index/2] = m_vecOpen[index];
				m_vecOpen[index] = tp;
				index = index/2;
			}
			else
			{
				break;
			}
		}
	
	}
}

bool aStar::compareF( Vec2 pt1,Vec2 pt2 )
{
	aStarNode * node1 = m_pMapData->getGridaStarNode(pt1);
	aStarNode * node2 = m_pMapData->getGridaStarNode(pt2);
	return node1->getF() > node2->getF();
}

aStar::aStar( MapData * pMap )
{
	m_pMapData = pMap;
}
