#ifndef __DBSmartDevice_H__
#define __DBSmartDevice_H__

#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <string.h>
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

#include "DataDef.h"

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "SMARTDEVICE"

class DBSmartDevice
{
public:
    static std::string database;
    static DBSmartDevice* instance;
    static DBSmartDevice* getInstance();
    DBSmartDevice();
    sql::Connection* getConn(std::string userName, std::string password, std::string url);
    static void retrieve_db_metadata(sql::Connection* dbcon);
    void closeConn();

    bool insert_to_table_Timer(sql::Connection* conn, const SmartDeviceInfo& device);
    bool insert_to_table_Device_Timer(sql::Connection* conn, const SmartDeviceInfo& device);
    bool select_idTimer_to_table_Timer(sql::Connection* conn, SmartDeviceInfo& device);

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
