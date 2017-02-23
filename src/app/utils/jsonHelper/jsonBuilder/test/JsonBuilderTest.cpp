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
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/
#include <cstdlib>
#include <gtest/gtest.h>

#include "JsonBuilder.h"

extern bool buildJsonMessageType(const MESSAGE_TYPE& messageType,
                                boost::property_tree::ptree& messageTypeTree);
extern bool buildDataSmartDeviceJson(const std::string& message, const std::string& ip_port_jack,
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
    MESSAGE_TYPE messageType = MESSAGE_TYPE_SMART_DEVICE_STATUS;
    
    boost::property_tree::ptree expectedTree;
    expectedTree.put(ATTR_JSON_MESSAGE_TYPE, ATTR_JSON_MESSAGE_TYPE_VALUE);

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

TEST_F(JsonBuilderTest, TestbuildDataSmartDeviceJson_SMART_DEVICE_DATA_ACTIVE_ON_RESULT_OK)
{
    boost::property_tree::ptree dataTree;
    std::string message("SD001:ACTIVE:ON:8:R0001");
    std::string ip_port_jack("192.168.0.100:8800");
    
    boost::property_tree::ptree expectedTree;
    expectedTree.put("ID_DEVICE", "SD001");
    expectedTree.put("RELAY_STATUS_VALUE", "ACTIVE");
    expectedTree.put("ELECTRIC_STATUS_VALUE", "ON");
    expectedTree.put("IP_PORT_JACK", "192.168.0.100:8800");
    expectedTree.put("ID_ROOM", "R0001");

    bool status = buildDataSmartDeviceJson(message, ip_port_jack, dataTree);

    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, dataTree);
}

TEST_F(JsonBuilderTest, TestbuildDataSmartDeviceJson_SMART_DEVICE_DATA_UNACTIVE_OFF_RESULT_OK)
{
    boost::property_tree::ptree dataTree;
    std::string message("SD001:UNACTIVE:OFF:8:R0001");
    std::string ip_port_jack("192.168.0.100:8800");
    
    boost::property_tree::ptree expectedTree;
    expectedTree.put("ID_DEVICE", "SD001");
    expectedTree.put("RELAY_STATUS_VALUE", "UNACTIVE");
    expectedTree.put("ELECTRIC_STATUS_VALUE", "OFF");
    expectedTree.put("IP_PORT_JACK", "192.168.0.100:8800");
    expectedTree.put("ID_ROOM", "R0001");

    bool status = buildDataSmartDeviceJson(message, ip_port_jack, dataTree);

    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, dataTree);
}

TEST_F(JsonBuilderTest, TestbuildDataSmartDeviceJson_NOT_SENSOR_MESSAGE)
{
    boost::property_tree::ptree dataTree;
    std::string message("");
    std::string ip_port_jack("192.168.0.100:8800");

    bool status = buildDataSmartDeviceJson(message, ip_port_jack, dataTree);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildDataSmartDeviceJson_NOT_STATUS_MESSAGE)
{
    boost::property_tree::ptree dataTree;
    std::string message("8:R0001");
    std::string ip_port_jack("192.168.0.100:8800");

    bool status = buildDataSmartDeviceJson(message, ip_port_jack, dataTree);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderTest, TestbuildJson_RESULT_OK)
{
    std::string jsonString;
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:ACTIVE:ON:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");

    boost::property_tree::ptree expectedTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_update_status_device.json");

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
    std::string message("MESSAGE_TYPE_DEFAULT;SD001:UNACTIVE:OFF:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");

    bool status = buildJson(message, jsonString);

    EXPECT_FALSE(status);
}