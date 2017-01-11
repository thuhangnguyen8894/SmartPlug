/****************************************************************************/
/*!
 * @file CommonTest.cpp
 * @brief Unittest for CommonTest class
 *
 * Copyright (c) Tien Nguyen Anh 2016 
 *
 * @detail The testing file of the implementation of CommonTest class
 */
/****************************************************************************/

#include <gtest/gtest.h>

#include "JsonCommonForC.h"

class JsonCommonForCTest : public ::testing::Test
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
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "on;192.168.1.177:5600"
 * Expected Result: true
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_OK)
{
    std::string message("on;192.168.1.177:5600");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_TRUE(status);
}

/*!
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "on"
 * Expected Result: false
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_FAILURE_1)
{
    std::string message("on");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "192.168.1.177"
 * Expected Result: false
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_FAILURE_2)
{
    std::string message("192.168.1.177");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "192.168.1.177:8800"
 * Expected Result: false
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_FAILURE_3)
{
    std::string message("192.168.1.177:8800");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "on;192.168.1.177"
 * Expected Result: false
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_FAILURE_4)
{
    std::string message("on;192.168.1.177");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Lower Boundary Testing
 * Input          : ""
 * Expected Result: false
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_FAILURE_5)
{
    std::string message("");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool isSensorMessageForC(const char* message)
 * Test Type      : Upper Boundary Testing
 * Input          : "onnnnn;192.168.1.177:5600"
 * Expected Result: false
 */
TEST_F(JsonCommonForCTest, TestisSensorMessageForC_RESULT_FAILURE_6)
{
    std::string message("onnnnn;192.168.1.177:5600");
    bool status = isSensorMessageForC(message.c_str());
    EXPECT_FALSE(status);
}

/*!
 * Test Function  : bool getJSONMessageTypeForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "o"
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommonForCTest,
						TestgetJSONMessageTypeForC_MESSAGE_TYPE_SMART_PLUG_ON)
{
    std::string message("o");
    MESSAGE_TYPE messageType;
    getJSONMessageTypeForC(message.c_str(), &messageType);

    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_PLUG_ON);
}

/*!
 * Test Function  : bool getJSONMessageTypeForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "O"
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommonForCTest,
                        TestgetJSONMessageTypeForC_MESSAGE_TYPE_SMART_PLUG_ON)
{
    std::string message("O");
    MESSAGE_TYPE messageType;
    getJSONMessageTypeForC(message.c_str(), &messageType);

    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_PLUG_ON);
}

/*!
 * Test Function  : bool getJSONMessageTypeForC(const char* message)
 * Test Type      : Equivalence Class Testing
 * Input          : "W"
 * Expected Result: MESSAGE_TYPE_DEFAULT
 */
TEST_F(JsonCommonForCTest, TestgetJSONMessageTypeForC_DEFAULT_TYPE)
{
    std::string message("W");
    MESSAGE_TYPE messageType;
    getJSONMessageType(message.c_str(), &messageType);

    EXPECT_EQ(messageType, MESSAGE_TYPE_DEFAULT);
}