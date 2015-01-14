

#ifndef __DB_SQLITE__
#define  __DB_SQLITE__

#include "cocos2d.h"
#include "sqlite3/include/sqlite3.h"


class DbSqlite
{
public:
	static DbSqlite * getInstance();
	bool initDB(const char * name);
	void closeDB();  
	bool tableIsExist( std::string name );
	void createTable( std::string sql,std::string name );
	void deleteTable( std::string sql,std::string name );
	void insertData( std::string sql );
	void deleteData( std::string sql );
	void updateData( std::string sql );
	int getDataCount( std::string sql );
	void getDataInfo( std::string sql,void *pSend );
	

};

#endif // !__DB_SQLITE__


