#include "DBSmartPlug.h"

DBSmartPlug* DBSmartPlug::instance = NULL;
std::string DBSmartPlug::database = DATABASE;

DBSmartPlug::DBSmartPlug()
{
    this->user = USER;
    this->password = PASSWORD;
    this->url = DBHOST;
}

DBSmartPlug* DBSmartPlug::getInstance()
{
    if(instance == NULL)
    {
    	instance = new DBSmartPlug();
    }
    return instance;
}

/*retrieve information of database */
void retrieve_db_metadata(sql::Connection* conn)
{
    if (conn->isClosed())
    {
        throw std::runtime_error("FAILURE-Data connection closed");
    }

    sql::DatabaseMetaData* dbconn_meta = conn->getMetaData();
    
    std::cout << "Database User Name: "
          << dbconn_meta->getUserName()
          << std::endl;

    std::cout << "Driver Name: "
          << dbconn_meta->getDriverName()
          << std::endl;

    std::cout << "Driver version: "
          << dbconn_meta->getDriverVersion()
          << std::endl;

    std::cout << "Database is Read-Only Mode?"
          << dbconn_meta->isReadOnly()
          << std::endl;

    std::cout << "Maximum Connections: "
          << dbconn_meta->getMaxConnections()
          << std::endl;
}

/*foundation for connect database*/
sql::Connection* DBSmartPlug::getConn(std::string userName, std::string password, std::string url)
{
    this->driver = get_driver_instance();
    this->conn = driver->connect(url, userName, password);
    this->conn->setSchema(database);
    this->conn->setAutoCommit(0);
    return this->conn; 
}



void DBSmartPlug::closeConn()
{
    if (this->res != NULL)
    {
    	delete this->res;
    }
    if(this->stmt != NULL)
    {
    	delete this->stmt;
    }
    if(this->prep_stmt != NULL)
    {
    	delete this->prep_stmt;
    }
    if(this->conn != NULL)
    {
    	delete this->conn;
    }
}

bool DBSmartPlug::insert_to_db(sql::Connection* conn, SmartPlug smarplug)
{
    DBSmartPlug* dbSmartPlug = DBSmartPlug::getInstance();

    conn = dbSmartPlug->getConn(this->user, this->password, this->url);
    if (conn == NULL)
    {
       return false; 
    }
    std::string sql("INSERT INTO smartplug(id,ip,status) VALUE(?,?,?)");
    this->prep_stmt = conn->prepareStatement(sql);
    if (this->prep_stmt == NULL)
    {
        return false;
    }
    try
    {
        (this->prep_stmt)->setString(1,smarplug.getId());
        (this->prep_stmt)->setString(2,smarplug.getIP());
        (this->prep_stmt)->setString(3,smarplug.getStatus());

        int updateCount = prep_stmt->executeUpdate();

        if(updateCount > 0)
        {
        	conn->commit();
        	return true;
        }
    }
    catch(sql::SQLException& e)
    {
    	conn->rollback();
    	return false;
    }
    dbSmartPlug->closeConn();
}

bool DBSmartPlug::update_to_db(sql::Connection* conn, SmartPlug smarplug)
{
    DBSmartPlug* dbSmartPlug = DBSmartPlug::getInstance();

    /* create a database connection using the Driver */
    dbSmartPlug->getConn(this->user, this->password, this->url);

    /* using PrepareStatement */ 
    std::string sql = "UPDATE smartplug SET status = ? WHERE id = ?";
    this->prep_stmt = conn->prepareStatement(sql);
    try
    {
    	(this->prep_stmt)->setString(1,smarplug.getStatus());
    	(this->prep_stmt)->setString(2,smarplug.getId());

    	int updateCount = prep_stmt->executeUpdate();

        if(updateCount > 0)
        {
        	conn->commit();
        	return true;
        }
    }
    catch(sql::SQLException& e)
    {
    	conn->rollback();
    	return false;
    }
    dbSmartPlug->closeConn();

    return true;
}

bool DBSmartPlug::delete_to_db(sql::Connection* conn, SmartPlug smarplug)
{
    DBSmartPlug* dbSmartPlug = DBSmartPlug::getInstance();

    dbSmartPlug->getConn(this->user, this->password, this->url);
    std::string sql = "DELETE FROM smartplug WHERE id = ?";
    this->prep_stmt = conn->prepareStatement(sql);
    try
    {
    	(this->prep_stmt)->setString(1,smarplug.getId());

    	int updateCount = prep_stmt->executeUpdate();

    	if (updateCount > 0)
    	{
    		conn->commit();
    		return true;
    	}

    }
    catch(sql::SQLException& e)
    {
    	conn->rollback();
    	return false;
    }

    return true;
}

void DBSmartPlug::select_to_db(sql::Connection* conn)
{
    DBSmartPlug* dbSmartPlug = DBSmartPlug::getInstance();

    dbSmartPlug->getConn(this->user, this->password, this->url);
    stmt = conn->createStatement();
 
    std::string sql = "SELECT * FROM smartplug";
    this->res = stmt->executeQuery(sql);

    while(res->next())
    {
    	std::cout << res->getString("id") <<std::endl;
    }
    conn->commit();

    dbSmartPlug->closeConn();
}
