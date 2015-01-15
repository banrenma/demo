#ifndef __DBTEST__
#define  __DBTEST__
#include "sqlite/DbSqlite.h"
#include "cocos2d.h"
USING_NS_CC;

class DBtest:public Node
{
public:
	
	DBtest(const char * name);
	~DBtest();

	virtual void update(float dt);

	Label * lb;
	 DbSqlite * pIns;
	 int updatetime;
};




#endif // !__DBTEST__


