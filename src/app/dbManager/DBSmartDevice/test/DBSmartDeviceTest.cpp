#include <gtest/gtest.h>

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
#include "DBSmartDevice.h"

static sql::Driver* MYSQL_DRIVER_INSTANCE = get_driver_instance();
static sql::Connection* MYSQL_DB_CONNECTION =
                    MYSQL_DRIVER_INSTANCE->connect(DBHOST, USER, PASSWORD);

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "root"
#define PASSWORD "root"
#define DATABASE "SMARTDEVICE"

class DBSmartDeviceTest : public ::testing::Test
{
public:
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */
TEST_F(DBSmartDeviceTest, Test_selectDeviceToTableSmartDevice_RESULT_OK)
{
    SmartDeviceInfo item_0;
    strcpy(item_0.device.idSmartDevice, "SD002");
    strcpy(item_0.device.idRoom, "R0001");
    strcpy(item_0.device.nameSmartDevice, "DEVICE_LIGHT");

    SmartDeviceInfo item_1;
    strcpy(item_1.device.idSmartDevice, "SD003");
    strcpy(item_1.device.idRoom, "R0001");
    strcpy(item_1.device.nameSmartDevice, "DEVICE_PLUS");

    SmartDeviceInfo item_2;
    strcpy(item_2.device.idSmartDevice, "SD004");
    strcpy(item_2.device.idRoom, "R0001");
    strcpy(item_2.device.nameSmartDevice, "DEVICE_LIGHT");

    SmartDeviceInfo item_3;
    strcpy(item_3.device.idSmartDevice, "SD005");
    strcpy(item_3.device.idRoom, "R0001");
    strcpy(item_3.device.nameSmartDevice, "DEVICE_FAN");

    SmartDeviceInfo item_4;
    strcpy(item_4.device.idSmartDevice, "SD006");
    strcpy(item_4.device.idRoom, "R0001");
    strcpy(item_4.device.nameSmartDevice, "DEVICE_TIVI");

    std::vector<SmartDeviceInfo> vectorSmartDeviceInfos;
    vectorSmartDeviceInfos.push_back(item_0);
    vectorSmartDeviceInfos.push_back(item_1);
    vectorSmartDeviceInfos.push_back(item_2);
    vectorSmartDeviceInfos.push_back(item_3);
    vectorSmartDeviceInfos.push_back(item_4);

    DBSmartDevice db;
    std::vector<SmartDeviceInfo> vectorSmartDeviceInfosResult;
    bool status = db.selectDeviceToTableSmartDevice(vectorSmartDeviceInfosResult);
    EXPECT_TRUE(status);

    for( int i = 0 ; i < vectorSmartDeviceInfos.size() ; i++){
        EXPECT_EQ(strcmp(vectorSmartDeviceInfos[i].device.idSmartDevice, vectorSmartDeviceInfosResult[i]->device.idSmartDevice), 0);
        EXPECT_EQ(strcmp(vectorSmartDeviceInfos[i].device.idRoom, vectorSmartDeviceInfosResult[i]->device.idRoom),0);
        EXPECT_EQ(strcmp(vectorSmartDeviceInfos[i].device.idSmartDevice, vectorSmartDeviceInfosResult[i]->device.idSmartDevice),0);
    }
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(DBSmartDeviceTest, Test_insertToTableTimer_RESULT_FAILUR)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */
TEST_F(DBSmartDeviceTest, Test_insertToTableDeviceTimer_RESULT_OK)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(DBSmartDeviceTest, Test_insertToTableDeviceTimer_RESULT_FAILUR)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */
TEST_F(DBSmartDeviceTest, Test_selectIdTimerToTableTimer_RESULT_OK)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(DBSmartDeviceTest, Test_selectIdTimerToTableTimer_RESULT_FAILUR)
{
    
}