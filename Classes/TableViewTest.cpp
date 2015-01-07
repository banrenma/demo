#include "TableViewTest.h"


Size NData::tableCellSizeForIndex( TableView *table, ssize_t idx )
{
	return CCSizeMake(30,80);
}

TableViewCell* NData::tableCellAtIndex( TableView *table, ssize_t idx )
{
	
	TableViewCell * cell = table->cellAtIndex(idx);
	if(!cell)
	{
		cell = new TableViewCell();
	}
	Sprite* sp = Sprite::create(m_VecPicName[idx]);
	sp->setScale(0.1);
	sp->setAnchorPoint(Vec2(0,0));
	if(!sp)
	{
		cell->release();
	}
	cell->addChild(sp,0,1);
	cell->setZOrder(idx);
	return cell;
}

ssize_t NData::numberOfCellsInTableView( TableView *table )
{
	return m_VecPicName.size();
}

NData * NData::create( std::vector<std::string> & data )
{
	NData* ndata = new NData();
	if(ndata)
	{
		ndata->init(data);
		return ndata;
	}
	return NULL;
}

void NData::init( std::vector<std::string> & data )
{
	m_VecPicName = data;
}


void NTableViewDelegate::tableCellTouched( TableView* table, TableViewCell* cell )
{
	cell->getChildByTag(1)->setPosition(0,20);

}

void NTableViewDelegate::tableCellHighlight( TableView* table, TableViewCell* cell )
{
	cell->getChildByTag(1)->setPosition(0,20);
}

void NTableViewDelegate::tableCellUnhighlight( TableView* table, TableViewCell* cell )
{
	cell->getChildByTag(1)->setPosition(0,0);
}
