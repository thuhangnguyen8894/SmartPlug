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

/*!
 * Retrieve information of database 
 */
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

/*!
 * Foundation for connect database
 */
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

/*!
 * Function insert data to table Timer
 */
bool DBSmartDevice::insert_to_table_Timer(sql::Connection* conn, const SmartDeviceInfo& device)
{
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    conn = dbSmartDevice->getConn(this->user, this->password, this->url);
    if (conn == NULL)
    {
       return false; 
    }
    std::string sql("INSERT INTO Timer(idTimer, day, month, year, hour, min, sec) VALUE(?,?,?,?,?,?,?)");
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

/*!
 * Function insert data to table Device_Timer
 */
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
        (this->prep_stmt)->setString(1, device.device_timer.idTimer);
        (this->prep_stmt)->setString(2, device.device_timer.idSmartDevice);
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

        std::cout << "rollback: " <<std::endl;
        std::cout << "#ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return false;
    }
    dbSmartDevice->closeConn();
}

/*
 * Function selected idTimer from table Timer
 */
bool DBSmartDevice::select_idTimer_to_table_Timer(sql::Connection* conn, SmartDeviceInfo& device)
{
    DBSmartDevice* dbSmartDevice = DBSmartDevice::getInstance();

    conn = dbSmartDevice->getConn(this->user, this->password, this->url);
    if (conn == NULL)
    {
       return false; 
    }

    std::string timer_idTimerStr(device.timer.idTimer);
    this->stmt = conn->createStatement();
    std::string sql = "SELECT idTimer FROM Timer WHERE idTimer = '" + timer_idTimerStr + "'";   
    this->res = stmt->executeQuery(sql);

    try
    {
        if (this->res == NULL)
        {
            return false;
        }

        while((this->res)->next())
        {
            std::string idTimerStr = (this->res)->getString("idTimer");
            strcpy(device.device_timer.idTimer, idTimerStr.c_str());
        }
        conn->commit();
        return true;
    }
    catch(sql::SQLException& e)
    {
        conn->rollback();

        std::cout << "rollback: " <<std::endl;
        std::cout << "#ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return false;
    }

    dbSmartDevice->closeConn();
}