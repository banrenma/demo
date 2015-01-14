#include "sqlite/DbSqlite.h"

USING_NS_CC;

static DbSqlite * pDbSqlite = NULL;
static sqlite3 * pDb = NULL;
static char * pErrMsg = NULL;//错误信息 
static int result;
static std::string sqlstr;
DbSqlite * DbSqlite::getInstance()
{
	if(pDbSqlite == NULL)
	{
		pDbSqlite = new DbSqlite();
		
	}
	return pDbSqlite;
}

bool DbSqlite::initDB( const char * name )
{
	std::string basePath = FileUtils::getInstance()->getWritablePath();
	std::string path = basePath + name;
	//打开一个数据库，如果该数据库不存在，则创建一个数据库文件  
	result = sqlite3_open(path.c_str(), &pDb);  
	if( result != SQLITE_OK )  
	{
		log( "打开数据库失败，错误码:%d ，错误原因:%s\n" , result, pErrMsg );  
		return false;
	}
	return true;
}

void DbSqlite::closeDB()
{
	sqlite3_close(pDb);  
}

//tableIsExist的回调函数  
int isExisted( void * para, int n_column, char ** column_value, char ** column_name )  
{  
    bool *isExisted_=(bool*)para;  
    *isExisted_=(**column_value)!='0';  
    return 0;  
}  
  
//判断表格是否存在  
bool DbSqlite::tableIsExist( std::string name )  
{  
    if (pDb!=NULL)  
    {  
        //判断表是否存在  
        bool tableIsExisted;  
        sqlstr = "select count(type) from sqlite_master where type='table' and name ='"+name+"'";  
        result =sqlite3_exec(pDb,sqlstr.c_str(),isExisted,&tableIsExisted,&pErrMsg);  
        return tableIsExisted;  
    }  
    return false;  
}  
  
//在数据库中判断名为name的表示否存在，如果不存在则创建这张表  
//@示例语句std::string sqls = "create table user(id integer,username text,password text)";  
void DbSqlite::createTable( std::string sql,std::string name )  
{  
    if (!tableIsExist(name))  
    {  
        //创建表，设置ID为主键，且自动增加  
        result = sqlite3_exec(pDb,sql.c_str(),NULL,NULL,&pErrMsg);  
        if( result != SQLITE_OK )  
            log( "创建表失败，错误码:%d ，错误原因:%s\n" , result, pErrMsg );  
    }  
      
}  
  
  
//删除表格  
//@示例语句sqlstr="drop table name";  
void DbSqlite::deleteTable( std::string sql,std::string name )  
{  
    if (tableIsExist(name))  
    {  
        result = sqlite3_exec(pDb,sql.c_str(),NULL,NULL,&pErrMsg);  
        if( result != SQLITE_OK )  
            log( "创建表失败，错误码:%d ，错误原因:%s\n" , result, pErrMsg );  
    }  
}  
  
  
//插入数据  
//@示例语句sqlstr=" insert into MyTable_1( name ) values ( '擎天柱' ) ";  
void DbSqlite::insertData( std::string sql ){  
    result = sqlite3_exec( pDb, sql.c_str() , NULL, NULL, &pErrMsg );  
    if(result != SQLITE_OK )  
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, pErrMsg );  
}  
  
  
//删除数据  
//@示例语句sqlstr="delete from MyTable_1 where ID = 2";  
void DbSqlite::deleteData( std::string sql )  
{  
    result=sqlite3_exec( pDb, sql.c_str() , NULL, NULL, &pErrMsg );  
    if(result != SQLITE_OK )  
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, pErrMsg );  
}  
  
  
//修改数据  
//@示例语句        sqlstr="update MyTable_1 set name='威震天' where ID = 3";  
void DbSqlite::updateData( std::string sql )  
{  
    result = sqlite3_exec( pDb, sql.c_str() , NULL, NULL, &pErrMsg );  
    if(result != SQLITE_OK )  
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, pErrMsg );  
}  
  
  
//getDataCount的回调函数  
int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name )  
{  
    int *count=(int*)para;  
    *count=n_column;  
    return 0;  
}  
//获取记录的条数  
//@示例语句std::string sqlsssss = "select count(*) from user";  
//@示例语句  取得表格字段的语句std::string sqlsssss = "select * from user";  
int DbSqlite::getDataCount( std::string sql )  
{  
    int count=0;  
    sqlite3_exec( pDb, sql.c_str() , loadRecordCount, &count, &pErrMsg );  
    return count;  
}  
  
  
//getDataInfo的回调函数  
int loadRecord( void * para, int n_column, char ** column_value, char ** column_name )  
{  
    log("n_column:%d",n_column);  
	Label * lb = (Label *)(para);
	std::string str,strtemp;

	lb->setString(column_value[1]);
    
    return 0;  
}  
//获取一条记录的信息 其中的pSend是一个实体类我们以后可以自定义一个继承了CCObject的类来代替他保存数据库中取出来的数据  
/* 
 *  这里最好扩展下，让  pSend  是一个vector 
 */  
void DbSqlite::getDataInfo( std::string sql,void *pSend )  
{  
    sqlite3_exec( pDb, sql.c_str() , loadRecord, pSend, &pErrMsg );  
}  

