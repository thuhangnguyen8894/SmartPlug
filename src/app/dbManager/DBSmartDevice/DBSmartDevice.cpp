#include "DBSmartDevice.h"

DBSmartDevice* DBSmartDevice::instance = NULL;
std::string DBSmartDevice::database = DATABASE;

DBSmartDevice::DBSmartDevice()
{
    this->user = USER;
    this->password = PASSWORD;
    this->url = DBHOST;
}

DBSmartDevice* DBSmartDevice::getInstance()
{
    if(instance == NULL)
    {
    	instance = new DBSmartDevice();
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
sql::Connection* DBSmartDevice::getConn(std::string userName, std::string password, std::string url)
{
    this->driver = get_driver_instance();
    this->conn = driver->connect(url, userName, password);
    this->conn->setSchema(database);
    this->conn->setAutoCommit(0);
    return this->conn; 
}

void DBSmartDevice::closeConn()
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

bool DBSmartDevice::insert_to_table_Timer(sql::Connection* conn, const SmartDeviceInfo& device)
{
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    conn = dbSmartDevice->getConn(this->user, this->password, this->url);
    if (conn == NULL)
    {
       return false; 
    }
    std::string sql("INSERT INTO Timer(idTimer, daySD, monthSD, yearSD, hourSD, minuteSD, secondSD) VALUE(?,?,?,?,?,?,?)");
    this->prep_stmt = conn->prepareStatement(sql);
    if (this->prep_stmt == NULL)
    {
        return false;
    }
    try
    {
        (this->prep_stmt)->setString(1, device.timer.idTimer);
        (this->prep_stmt)->setInt(2, device.timer.daySD);
        (this->prep_stmt)->setInt(3, device.timer.monthSD);
        (this->prep_stmt)->setInt(4, device.timer.yearSD);
        (this->prep_stmt)->setInt(5, device.timer.hourSD);
        (this->prep_stmt)->setInt(6, device.timer.minSD);
        (this->prep_stmt)->setInt(7, device.timer.secSD);

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
    dbSmartDevice->closeConn();
}

bool DBSmartDevice::insert_to_table_Device_Timer(sql::Connection* conn, const SmartDeviceInfo& device)
{
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    conn = dbSmartDevice->getConn(this->user, this->password, this->url);
    if (conn == NULL)
    {
       return false; 
    }
    std::string sql("INSERT INTO Device_Timer(idTimer, idSmartDevice, stateElectric, stateRelay) VALUE(?,?,?,?)");
    this->prep_stmt = conn->prepareStatement(sql);
    if (this->prep_stmt == NULL)
    {
        return false;
    }
    try
    {
        (this->prep_stmt)->setString(1, device.timer.idTimer);
        (this->prep_stmt)->setString(2, device.device.idSmartDevice);
        (this->prep_stmt)->setString(3, device.device_timer.stateElectric);
        (this->prep_stmt)->setString(4, device.device_timer.stateRelay);

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
    dbSmartDevice->closeConn();
}

/*
 *
 */
/*std::string DBSmartDevice::getIdTableSmartDevice(sql::Connection* conn, const std::string& ip_port_jack)
{
    std::string idSmartDeviceStr = "";

    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    dbSmartDevice->getConn(this->user, this->password, this->url);

    std::string sql = "SELECT idSmartDevice FROM Device_Timer WHERE ip_port_jack = ?";
    
    (this->prep_stmt)->setString(1,ip_port_jack);

    this->prep_stmt = conn->prepareStatement(sql);

    this->res = prep_stmt->executeQuery();

    stmt = conn->createStatement();
    std::string sql = "SELECT idSmartDevice FROM Device_Timer WHERE ip_port_jack = '" + ip_port_jack + "'";
    this->res = stmt->executeQuery(sql);


    while(res->next())
    {
        idSmartDeviceStr = res->getString("idSmartDevice");
    }
    conn->commit();

    dbSmartDevice->closeConn();

    return idSmartDeviceStr;
}*/

/*
 * Function update statusElectric and statusRelay in table Device_Timer
 * When Electric is changing status
 */
//bool DBSmartDevice::update_to_db(sql::Connection* conn, const SmartDeviceInfo& device)
/*bool DBSmartDevice::update_to_db(sql::Connection* conn, const std::string& stateElectric, const std::string& stateRelay, const std::string& ip_port_jack)
{   
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    //create a database connection using the Driver 
    conn = dbSmartDevice->getConn(this->user, this->password, this->url);
    if (conn == NULL)
    {
       return false; 
    }

    //using PrepareStatement
    std::string sql = "UPDATE Device_Timer SET stateElectric = ?, stateRelay = ? WHERE ip_port_jack = ?";
    this->prep_stmt = conn->prepareStatement(sql);
    try
    {
    	(this->prep_stmt)->setString(1, smartplug.data.status_use_electric);
    	(this->prep_stmt)->setString(2, smartplug.data.status_electric);
        (this->prep_stmt)->setString(3, smartplug.data.ip_port_jack);

        (this->prep_stmt)->setString(1, stateElectric);
        (this->prep_stmt)->setString(2, stateRelay);
        (this->prep_stmt)->setString(3, ip_port_jack);

    	int updateCount = prep_stmt->executeUpdate();

        if (updateCount > 0)
        {
        	conn->commit();
        	return true;
        }
        else 
        {
            return false;
        }
    }
    catch(sql::SQLException& e)
    {
    	conn->rollback();
    	return false;
    }
    dbSmartDevice->closeConn();

    return true;
}*/

/*bool DBSmartDevice::delete_to_db(sql::Connection* conn, SmartDeviceInfo& device)
{
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    dbSmartDevice->getConn(this->user, this->password, this->url);
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

void DBSmartDevice::select_to_db(sql::Connection* conn)
{
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    dbSmartDevice->getConn(this->user, this->password, this->url);
    stmt = conn->createStatement();
 
    std::string sql = "SELECT * FROM smartplug";
    this->res = stmt->executeQuery(sql);

    while(res->next())
    {
    	std::cout << res->getString("id") <<std::endl;
    }
    conn->commit();

    dbSmartDevice->closeConn();
}*/