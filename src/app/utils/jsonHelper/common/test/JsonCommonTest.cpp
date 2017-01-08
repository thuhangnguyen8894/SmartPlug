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

TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_OK)
{
    const char* message("ABC");
    bool status = isSensorMessage(message);
    EXPECT_TRUE(status);
}

TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_1)
{
    const char* message("");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_2)
{
    const char* message("ABCDEF");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_3)
{
    const char* message("ABCDEFG");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

TEST_F(JsonCommonTest, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_ON)
{
    const char* message("N");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_PLUG_STATUS);
}

TEST_F(JsonCommonTest, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_OFF)
{
    const char* message("F");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_PLUG_STATUS);
}

TEST_F(JsonCommonTest, TestgetJSONMessageType_DEFAULT_TYPE)
{
    const char* message("W");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_DEFAULT);
}