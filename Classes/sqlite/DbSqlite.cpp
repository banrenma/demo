#include "sqlite/DbSqlite.h"

USING_NS_CC;

static DbSqlite * pDbSqlite = NULL;
static sqlite3 * pDb = NULL;
static char * pErrMsg = NULL;//������Ϣ 
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
	//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�  
	result = sqlite3_open(path.c_str(), &pDb);  
	if( result != SQLITE_OK )  
	{
		log( "�����ݿ�ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, pErrMsg );  
		return false;
	}
	return true;
}

void DbSqlite::closeDB()
{
	sqlite3_close(pDb);  
}

//tableIsExist�Ļص�����  
int isExisted( void * para, int n_column, char ** column_value, char ** column_name )  
{  
    bool *isExisted_=(bool*)para;  
    *isExisted_=(**column_value)!='0';  
    return 0;  
}  
  
//�жϱ���Ƿ����  
bool DbSqlite::tableIsExist( std::string name )  
{  
    if (pDb!=NULL)  
    {  
        //�жϱ��Ƿ����  
        bool tableIsExisted;  
        sqlstr = "select count(type) from sqlite_master where type='table' and name ='"+name+"'";  
        result =sqlite3_exec(pDb,sqlstr.c_str(),isExisted,&tableIsExisted,&pErrMsg);  
        return tableIsExisted;  
    }  
    return false;  
}  
  
//�����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�  
//@ʾ�����std::string sqls = "create table user(id integer,username text,password text)";  
void DbSqlite::createTable( std::string sql,std::string name )  
{  
    if (!tableIsExist(name))  
    {  
        //����������IDΪ���������Զ�����  
        result = sqlite3_exec(pDb,sql.c_str(),NULL,NULL,&pErrMsg);  
        if( result != SQLITE_OK )  
            log( "������ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, pErrMsg );  
    }  
      
}  
  
  
//ɾ�����  
//@ʾ�����sqlstr="drop table name";  
void DbSqlite::deleteTable( std::string sql,std::string name )  
{  
    if (tableIsExist(name))  
    {  
        result = sqlite3_exec(pDb,sql.c_str(),NULL,NULL,&pErrMsg);  
        if( result != SQLITE_OK )  
            log( "������ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, pErrMsg );  
    }  
}  
  
  
//��������  
//@ʾ�����sqlstr=" insert into MyTable_1( name ) values ( '������' ) ";  
void DbSqlite::insertData( std::string sql ){  
    result = sqlite3_exec( pDb, sql.c_str() , NULL, NULL, &pErrMsg );  
    if(result != SQLITE_OK )  
        log( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, pErrMsg );  
}  
  
  
//ɾ������  
//@ʾ�����sqlstr="delete from MyTable_1 where ID = 2";  
void DbSqlite::deleteData( std::string sql )  
{  
    result=sqlite3_exec( pDb, sql.c_str() , NULL, NULL, &pErrMsg );  
    if(result != SQLITE_OK )  
        log( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, pErrMsg );  
}  
  
  
//�޸�����  
//@ʾ�����        sqlstr="update MyTable_1 set name='������' where ID = 3";  
void DbSqlite::updateData( std::string sql )  
{  
    result = sqlite3_exec( pDb, sql.c_str() , NULL, NULL, &pErrMsg );  
    if(result != SQLITE_OK )  
        log( "�����¼ʧ�ܣ�������:%d ������ԭ��:%s\n" , result, pErrMsg );  
}  
  
  
//getDataCount�Ļص�����  
int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name )  
{  
    int *count=(int*)para;  
    *count=n_column;  
    return 0;  
}  
//��ȡ��¼������  
//@ʾ�����std::string sqlsssss = "select count(*) from user";  
//@ʾ�����  ȡ�ñ���ֶε����std::string sqlsssss = "select * from user";  
int DbSqlite::getDataCount( std::string sql )  
{  
    int count=0;  
    sqlite3_exec( pDb, sql.c_str() , loadRecordCount, &count, &pErrMsg );  
    return count;  
}  
  
  
//getDataInfo�Ļص�����  
int loadRecord( void * para, int n_column, char ** column_value, char ** column_name )  
{  
    log("n_column:%d",n_column);  
	Label * lb = (Label *)(para);
	std::string str,strtemp;

	lb->setString(column_value[1]);
    
    return 0;  
}  
//��ȡһ����¼����Ϣ ���е�pSend��һ��ʵ���������Ժ�����Զ���һ���̳���CCObject�������������������ݿ���ȡ����������  
/* 
 *  ���������չ�£���  pSend  ��һ��vector 
 */  
void DbSqlite::getDataInfo( std::string sql,void *pSend )  
{  
    sqlite3_exec( pDb, sql.c_str() , loadRecord, pSend, &pErrMsg );  
}  

