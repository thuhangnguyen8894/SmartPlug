#ifndef __DBSmartPlug_H__
#define __DBSmartPlug_H__

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

#include "DataDef.h"

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "SMARTDEVICE"

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
    //bool insert_to_db(sql::Connection* conn, SmartDeviceInfo& smartplug);
    //bool delete_to_db(sql::Connection* conn, SmartDeviceInfo& smartplug);
    
    //bool update_to_db(sql::Connection* conn, const SmartDeviceInfo& smartplug);
    bool update_to_db(sql::Connection* conn, const std::string& stateElectric, const std::string& stateRelay, const std::string& ip_port_jack);
    //void select_to_db(sql::Connection* conn);

    std::string getIdTableSmartDevice(sql::Connection* conn, const std::string& ip_port_jack);

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
