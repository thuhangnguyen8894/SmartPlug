/****************************************************************************/
/*!
 * @file CommonTest.cpp
 * @brief Unittest for CommonTest class
 *
 * Copyright (c) 2017 Tien Anh Nguyen 
 *
 * @detail The testing file of the implementation of CommonTest class
 *
 * Modified History
 * ---------------
 * 2017-Jan-03 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/

#include <gtest/gtest.h>

#include "JsonCommon.h"

class JsonCommonTest : public ::testing::Test
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
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "PON;192.168.1.177:8800;1/18/2017  21:59:00"
 * Expected Result: true
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_OK)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:UNACTIVE:OFF:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    bool status = isSensorMessage(message);
    EXPECT_TRUE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "ON"
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_1)
{
    std::string message("SMART_DEVICE_STATUS_VALUE");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "192.168.1.177"
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_2)
{
    std::string message("192.168.1.177");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "192.168.1.177:8800"
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_3)
{
    std::string message("192.168.1.177:8800");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Lower Boundary Testing
 * Input          : ""
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_5)
{
    std::string message("");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool getJSONMessageType(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "PON;192.168.1.177:8800;1/18/2017  21:59:00"
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_STATUS)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:UNACTIVE:OFF:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_DEVICE_STATUS);
}

/*!
 * Test Function  : bool getJSONMessageType(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "AON;192.168.1.177:8800;1/18/2017  21:59:00"
 * Expected Result: MESSAGE_TYPE_DEFAULT
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_DEFAULT_TYPE)
{
    std::string message("MESSAGE_TYPE_DEFAULT;SD001:UNACTIVE:OFF:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_DEFAULT);
}