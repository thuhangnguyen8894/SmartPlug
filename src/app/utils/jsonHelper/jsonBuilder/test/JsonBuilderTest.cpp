/****************************************************************************/
/*!
 * @file JsonBuilderTest.cpp
 * @brief Unittest for JsonBuilderTest class
 *
 * Copyright (c) 2017 Tien Anh Nguyen
 *
 * @detail The testing file of the implementation of JsonBuilderTest class
 *
 * Modified History
 * ---------------
 * 2017-Jan-03 Created tien.nguyenanh94@ogmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/
#include <cstdlib>
#include <gtest/gtest.h>

#include "JsonBuilder.h"

extern bool buildJsonMessageType(const MESSAGE_TYPE& messageType,
                                boost::property_tree::ptree& messageTypeTree);
extern bool buildSmartPlugStatusJson(const std::string& message,
                                    boost::property_tree::ptree& dataTree);

class JsonBuilderTest : public ::testing::Test
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


TEST_F(JsonBuilderTest, TestbuildJsonMessageType_RESULT_OK)
{
    boost::property_tree::ptree messageTypeTree;
    MESSAGE_TYPE messageType = MESSAGE_TYPE_SMART_PLUG_STATUS;
    
    boost::property_tree::ptree expectedTree;
    expectedTree.put(ATTR_JSON_MESSAGE_TYPE, ATTR_JSON_SMART_PLUG_STATUS_VALUE);

    bool status = buildJsonMessageType(messageType, messageTypeTree);

    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, messageTypeTree);
}

TEST_F(JsonBuilderTest, TestbuildJsonMessageType_MESSAGE_TYPE_DEFAULT)
{
    boost::property_tree::ptree messageTypeTree;
    MESSAGE_TYPE messageType = MESSAGE_TYPE_DEFAULT;
    
    bool status = buildJsonMessageType(messageType, messageTypeTree);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildSmartPlugStatusJson_SMART_PLUG_STATUS_ON_RESULT_OK)
{
    boost::property_tree::ptree dataTree;
    std::string message("PON");
    
    boost::property_tree::ptree expectedTree;
    expectedTree.put("SMART_PLUG_STATUS_VALUE", "ON");

    bool status = buildSmartPlugStatusJson(message, dataTree);

    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, dataTree);
}

TEST_F(JsonBuilderTest, TestbuildSmartPlugStatusJson_SMART_PLUG_STATUS_OFF_RESULT_OK)
{
    boost::property_tree::ptree dataTree;
    std::string message("POFF");
    
    boost::property_tree::ptree expectedTree;
    expectedTree.put("SMART_PLUG_STATUS_VALUE", "OFF");

    bool status = buildSmartPlugStatusJson(message, dataTree);

    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, dataTree);
}

TEST_F(JsonBuilderTest, TestbuildSmartPlugStatusJson_NOT_SENSOR_MESSAGE)
{
    boost::property_tree::ptree dataTree;
    std::string message("");

    bool status = buildSmartPlugStatusJson(message, dataTree);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildSmartPlugStatusJson_NOT_STATUS_MESSAGE)
{
    boost::property_tree::ptree dataTree;
    std::string message(";192.168.1.177:5600;1/18/2017  21:59:00");

    bool status = buildSmartPlugStatusJson(message, dataTree);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildJson_RESULT_OK)
{
    std::string jsonString;
    std::string message("PON;192.168.1.177:5600;1/18/2017  21:59:00");

    boost::property_tree::ptree expectedTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_1.json");

    boost::property_tree::read_json(jsonFilePath, expectedTree);

    bool status = buildJson(message, jsonString);
    boost::property_tree::ptree actualTree;
    std::stringstream stringStream(jsonString);
    boost::property_tree::read_json(stringStream, actualTree);
    
    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, actualTree);
}

TEST_F(JsonBuilderTest, TestbuildJson_MESSAGE_TYPE_RESULT_FAILURE_1)
{
    std::string jsonString;
    std::string message("RON;192.168.1.177:5600;1/18/2017  21:59:00");

    bool status = buildJson(message, jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildJson_RESULT_FAILURE_2)
{
    std::string jsonString;
    std::string message("RON");

    bool status = buildJson(message, jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildJson_RESULT_FAILURE_3)
{
    std::string jsonString;
    std::string message("LOFF");

    bool status = buildJson(message, jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildJson_MESSAGE_TYPE_RESULT_FAILURE_4)
{
    std::string jsonString;
    std::string message("RON;192.168.1.177:5600;1/18/2017  21:59:00  23:04:94");

    bool status = buildJson(message, jsonString);

    EXPECT_FALSE(status);
}