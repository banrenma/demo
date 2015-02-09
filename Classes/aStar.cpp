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


std::vector<Vec2>  aStar::BeginSearchPath( Vec2 starPosition,Vec2 endPosition )
{
	std::vector<Vec2> path;
	m_vecOpen.clear();
	//��0��λ�� ��ռ��
	m_vecOpen.push_back(Vec2::ZERO);
	if(starPosition == endPosition || isPtPonderable(starPosition) || isPtPonderable(endPosition) )
	{
		return path;
	}
	
	m_vecOpen.push_back(starPosition);

	aStarNode * node = new aStarNode(NULL,0,getH(starPosition,endPosition),starPosition);
	m_pMapData->setGridaStarNode(starPosition,node);

	 while(m_vecOpen.size() > 1)
	 {
		 aStarNode * node1 = m_pMapData->getGridaStarNode(*(m_vecOpen.begin()+1));
		 if(node1 == NULL)
		 {
			 log("error node1 is NULL");
			 break;
		 }
			 
		 // ɾ��f ��С�Ľڵ�
		 for(int i=0; i < 8;i++)
		 {
			 int count = 0;
			 Vec2 pt(node->getPt().x + i%3 -1,node->getPt().x + i/3 -1);
			 //�ҵ��յ�
			 if(pt == endPosition)
			 {
				 goto GetPATH;
			 }
			 // �ж����� �õ���Ч    �����ϰ���
			 if(isPtPonderable(pt)  &&  m_pMapData->getGridWeight(pt) <= 200)
			 {
				 //�������� �ر��б�
				  aStarNode * node2 = m_pMapData->getGridaStarNode(pt);
				if(node2==NULL )
				{
					//���һ���ֽڵ�open�б�
					//�滻�� ����Ԫ��
					if(count == 0)
					{
						//�滻�� ����Ԫ�� ��������

					}
					else
					{
						//��ӵ�ĩβ ��������
					}

				}
				else if(node2->isVisit() == true)
				{
					//�Ƚ� gֵ  �������ɶ�
					if(count == 0)
					{
						//ֱ�ӺͶ���Ԫ��
					}
					else
					{

					}
				}
				//

			 }
		 }
		
	 }
GetPATH:

	 //û�ҵ�
	 return path;


}



bool aStar::isPtPonderable( Vec2 pt )
{
	return pt.x >=0 && pt.x < m_pMapData->getMaxx() && pt.y >=0 && pt.y <m_pMapData->getMaxy();
}

void aStar::pushChildinOpen( aStarNode * node )
{

}
