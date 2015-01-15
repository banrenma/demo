

#ifndef __DB_SQLITE__
#define  __DB_SQLITE__

#include "cocos2d.h"
#include "sqlite3/include/sqlite3.h"

typedef int(* Sqlite_CallBack)( void * para, int n_column, char ** column_value, char ** column_name );

class DbSqlite
{
public:

	enum class dbType
	{
		DBNone,
		FileDB,
		MemoryDB,
	};
public:
	DbSqlite();
	~DbSqlite();
	static DbSqlite * getInstance();
	bool initDB( const char * name ,bool isWritablePath = true);
	void closeDB();  
	bool tableIsExist( std::string name );
	void createTable( std::string sql,std::string name );
	void deleteTable( std::string sql,std::string name );
	void insertData( std::string sql );
	void deleteData( std::string sql );
	void updateData( std::string sql );
	int getDataCount( std::string sql );
	void getDataInfo( std::string sql,void *pSend );
	void getDataInfo( std::string sql,void *pSend ,Sqlite_CallBack callback);
	bool initMemoryDB();
	sqlite3 * getpSqlite3();
	bool backup_init_DB(const char *zFilename, int isSave = false,bool isWritablePath = true);
protected:
	dbType m_eType;


	class DbGarbage    //����Ψһ��������������������ɾ��NSkeletonDataCache��ʵ��   
	{  
	public:  
		~DbGarbage();  
	};  
	static DbGarbage Garbo;  //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������  
};

#endif // !__DB_SQLITE__


