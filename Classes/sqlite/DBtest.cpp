#include "sqlite/DBtest.h"


DBtest::DBtest(const char * name):Node()
{
	this->autorelease();
	 pIns = DbSqlite::getInstance();
	 pIns->initDB(name);
	 std::string createTableSql = "create table login (id integer primary key autoincrement,name varchar(20),passwd varchar(20));";  
	 pIns->createTable(createTableSql.c_str(),"login");  

	 lb = Label::createWithTTF("init","Marker Felt.ttf",30);
	 lb->setPosition(Vec2(500,200));
	 lb->setColor(Color3B::RED);
	 this->addChild(lb);
	 this->scheduleUpdate();

	 updatetime = 0;
}

DBtest::~DBtest()
{
	pIns->deleteTable("drop table login","login");
	pIns->closeDB();
}

void DBtest::update( float dt )
{
	int count = 0;
	updatetime ++;
	char buf[100]={0};
	pIns->insertData("insert into login(name,passwd) values('bbbbb','123456')"); 
	count = pIns->getDataCount("select count(*) from login");
	sprintf(buf,"update time  %d  insertData %d",updatetime,count);
	lb->setString(buf);
}

