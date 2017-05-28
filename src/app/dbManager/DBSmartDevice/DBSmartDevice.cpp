#include "DBSmartDevice.h"

static sql::Driver* MYSQL_DRIVER_INSTANCE = get_driver_instance();
static sql::Connection* MYSQL_DB_CONNECTION =
                    MYSQL_DRIVER_INSTANCE->connect(DBHOST, USER, PASSWORD);

DBSmartDevice::DBSmartDevice()
{
    this->user = USER;
    this->password = PASSWORD;
    this->url = DBHOST;
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
}

/*!
 * Function insert data to table Timer
 */
bool DBSmartDevice::insertToTableTimer(const SmartDeviceInfo& device)
{
    MYSQL_DB_CONNECTION->setSchema(DATABASE);
    MYSQL_DB_CONNECTION->setAutoCommit(0);
    std::cout << "Bao Khanh 01" << std::endl;
    std::string sql("INSERT INTO Timer(idTimer, day, month, year, hour, min, sec) VALUE(?,?,?,?,?,?,?)");
    this->prep_stmt = MYSQL_DB_CONNECTION->prepareStatement(sql);
    std::cout << "Bao Khanh 02" << std::endl;
    if (this->prep_stmt == NULL)
    {
        return false;
    }
    try
    {
        std::cout << "Bao Khanh 03" << std::endl;
        (this->prep_stmt)->setString(1, device.timer.idTimer);
        (this->prep_stmt)->setInt(2, device.timer.daySD);
        (this->prep_stmt)->setInt(3, device.timer.monthSD);
        (this->prep_stmt)->setInt(4, device.timer.yearSD);
        (this->prep_stmt)->setInt(5, device.timer.hourSD);
        (this->prep_stmt)->setInt(6, device.timer.minSD);
        (this->prep_stmt)->setInt(7, device.timer.secSD);
        std::cout << "Bao Khanh 04" << std::endl;
        int updateCount = prep_stmt->executeUpdate();
        std::cout << "updateCount" << updateCount << std::endl;
        if(updateCount > 0)
        {
            std::cout << "Bao Khanh 06" << std::endl;
            MYSQL_DB_CONNECTION->commit();
            return true;
        }
        std::cout << "Bao Khanh 05" << std::endl;
    }
    catch(sql::SQLException& e)
    {
        std::cout << "Bao Khanh 07" << std::endl;
        MYSQL_DB_CONNECTION->rollback();
        return false;
    }
    std::cout << "Bao Khanh 08" << std::endl;
    this->closeConn();

    return false;
}

/*!
 * Function insert data to table Device_Timer
 */
bool DBSmartDevice::insertToTableDeviceTimer(const SmartDeviceInfo& device)
{
    MYSQL_DB_CONNECTION->setSchema(DATABASE);
    MYSQL_DB_CONNECTION->setAutoCommit(0);
    
    std::string sql("INSERT INTO Device_Timer(idTimer, idSmartDevice, stateElectric, stateRelay) VALUE(?,?,?,?)");
    this->prep_stmt = MYSQL_DB_CONNECTION->prepareStatement(sql);

    if (this->prep_stmt == NULL)
    {
        return false;
    }

    try
    {
        (this->prep_stmt)->setString(1, device.deviceTimer.idTimer);
        (this->prep_stmt)->setString(2, device.deviceTimer.idSmartDevice);
        (this->prep_stmt)->setString(3, device.deviceTimer.stateElectric);
        (this->prep_stmt)->setString(4, device.deviceTimer.stateRelay);
        
        int updateCount = prep_stmt->executeUpdate();

        if(updateCount > 0)
        {
            MYSQL_DB_CONNECTION->commit();
            return true;
        }
    }
    catch(sql::SQLException& e)
    {
        MYSQL_DB_CONNECTION->rollback();

        std::cout << "rollback: " <<std::endl;
        std::cout << "#ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return false;
    }
    this->closeConn();
}

/*
 * Function selected idTimer from table Timer
 */
bool DBSmartDevice::selectIdTimerToTableTimer(SmartDeviceInfo& device)
{
    MYSQL_DB_CONNECTION->setSchema(DATABASE);
    MYSQL_DB_CONNECTION->setAutoCommit(0);

    std::string timer_idTimerStr(device.timer.idTimer);
    this->stmt = MYSQL_DB_CONNECTION->createStatement();
    std::string sql = "SELECT idTimer FROM Timer WHERE idTimer = '" 
                                                     + timer_idTimerStr + "'";   
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
            strcpy(device.deviceTimer.idTimer, idTimerStr.c_str());
        }
        MYSQL_DB_CONNECTION->commit();
        return true;
    }
    catch(sql::SQLException& e)
    {
        MYSQL_DB_CONNECTION->rollback();

        std::cout << "rollback: " <<std::endl;
        std::cout << "#ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return false;
    }

    this->closeConn();
}

/*
 * Function select array smart device from table SmartDevice
 */
bool DBSmartDevice::selectDeviceToTableSmartDevice(std::vector<SmartDeviceInfo>& vectorSmartDeviceInfos)
{
    MYSQL_DB_CONNECTION->setSchema(DATABASE);
    MYSQL_DB_CONNECTION->setAutoCommit(0);

    this->stmt = MYSQL_DB_CONNECTION->createStatement();
    std::string sql = "SELECT * FROM SmartDevice";   
    this->res = stmt->executeQuery(sql);

    try
    {
        if (this->res == NULL)
        {
            return false;
        }

        while((this->res)->next())
        {
            SmartDeviceInfo* item = new SmartDeviceInfo;

            strcpy(item->device.idSmartDevice, 
                      (char*)(this->res)->getString("idSmartDevice").c_str());
            strcpy(item->device.nameSmartDevice, 
                    (char*)(this->res)->getString("nameSmartDevice").c_str());
            strcpy(item->device.idRoom, 
                             (char*)(this->res)->getString("idRoom").c_str());

            vectorSmartDeviceInfos.push_back(*item);
        }
        MYSQL_DB_CONNECTION->commit();
        return true;
    }
    catch(sql::SQLException& e)
    {
        MYSQL_DB_CONNECTION->rollback();

        std::cout << "rollback: " <<std::endl;
        std::cout << "#ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return false;
    }

    this->closeConn();
}