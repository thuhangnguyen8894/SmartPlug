#ifndef __DBHelper_H_
#define __DBHelper_H_

#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>

#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/metadata.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "smartplug.h"

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "SmartPlug"

class DBSmartPlug
{
public:
    static std::string database;
	static DBSmartPlug* instance;
	static DBSmartPlug* getInstance();
    DBSmartPlug();
	sql::Connection* getConn(std::string userName, std::string password, std::string url);
	static void retrieve_db_metadata(sql::Connection* dbcon);
	void closeConn();
	bool insert_to_db(sql::Connection* conn, SmartPlug smartplug);
	bool delete_to_db(sql::Connection* conn, SmartPlug smartplug);
	bool update_status_to_db(sql::Connection* conn, SmartPlug* smartplug);
	void select_to_db(sql::Connection* conn);
	
	bool findSmartPlug(sql::Connection* conn, SmartPlug* smartplug);

private:
	sql::PreparedStatement* prep_stmt;
	sql::Connection* conn;
	sql::ResultSet* res;
	sql::Statement* stmt;
	sql::Driver* driver;
	sql::Savepoint* savepoint;

	std::string url;
	std::string user;
	std::string password;
};

#endif
