/****************************************************************************/
/*!
 * @file CommonTest.cpp
 * @brief Unittest for CommonTest class
 *
 * Copyright (c) Trang Tran 2016 
 *
 * @detail The testing file of the implementation of CommonTest class
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tn-trang.tran@outlook.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
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
 * Input          : "on;192.168.1.177:5600"
 * Expected Result: true
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_OK)
{
    const char* message("on;192.168.1.177:5600");
    bool status = isSensorMessage(message);
    EXPECT_TRUE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "on"
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_1)
{
    const char* message("on");
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
    const char* message("192.168.1.177");
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
    const char* message("192.168.1.177:8800");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "on;192.168.1.177"
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_4)
{
    const char* message("on;192.168.1.177");
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
    const char* message("");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessage(const std::string& message)
 * Test Type      : Upper Boundary Testing
 * Input          : "onnnnn;192.168.1.177:5600"
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_6)
{
    const char* message("onnnnn;192.168.1.177:5600");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool getJSONMessageType(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "o"
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_ON)
{
    const char* message("o");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_PLUG_STATUS);
}

/*!
 * Test Function  : bool getJSONMessageType(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "O"
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_OFF)
{
    const char* message("O");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_PLUG_STATUS);
}

/*!
 * Test Function  : bool getJSONMessageType(const std::string& message)
 * Test Type      : Equivalence Class Testing
 * Input          : "W"
 * Expected Result: MESSAGE_TYPE_DEFAULT
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_DEFAULT_TYPE)
{
    const char* message("W");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_DEFAULT);
}