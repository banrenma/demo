#ifndef __TABLEVIEW__
#define __TABLEVIEW__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


class NData: public TableViewDataSource
{
public:
	static NData * create(std::vector<std::string> & data);
	void init(std::vector<std::string> & data);
	Size tableCellSizeForIndex(TableView *table, ssize_t idx);     
	TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	ssize_t numberOfCellsInTableView(TableView *table);

private:
	std::vector<std::string> m_VecPicName;
};



class NTableViewDelegate: public TableViewDelegate 
{
public:
	void tableCellTouched(TableView* table, TableViewCell* cell);
	void tableCellHighlight(TableView* table, TableViewCell* cell);
	void tableCellUnhighlight(TableView* table, TableViewCell* cell);
};





#endif