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
TEST_F(DBSmartDeviceTest, Test_insert_to_table_Timer_RESULT_OK)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(DBSmartDeviceTest, Test_insert_to_table_Timer_RESULT_FAILUR)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */
TEST_F(DBSmartDeviceTest, Test_insert_to_table_Device_Timer_RESULT_OK)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(DBSmartDeviceTest, Test_insert_to_table_Device_Timer_RESULT_FAILUR)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */
TEST_F(DBSmartDeviceTest, Test_select_idTimer_to_table_Timer_RESULT_OK)
{
    
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(DBSmartDeviceTest, Test_select_idTimer_to_table_Timer_RESULT_FAILUR)
{
    
}