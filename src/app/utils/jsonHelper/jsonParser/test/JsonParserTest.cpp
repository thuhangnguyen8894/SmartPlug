
/****************************************************************************/
/*!
 * @file JsonBuilderTest.cpp
 * @brief Unittest for JsonBuilderTest class
 *
 * Copyright (c) Tien Nguyen Anh 2017
 *
 * @detail The testing file of the implementation of JsonBuilderTest class
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tn-trang.tran@outlook.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/

#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <regex>
#include <cstdlib>

#include <gtest/gtest.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "JsonParser.h"


class JsonParserTest : public ::testing::Test
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

TEST_F(JsonParserTest, TestparseDataSmartDeviceJson_RESULT_OK)
{
    bool status = false;
    char* jsonString = NULL;
    SmartDeviceInfo info;

    boost::property_tree::ptree pTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_update_status_device.json");

    boost::property_tree::read_json(jsonFilePath, pTree);
    std::stringstream jsonStrStream;
    boost::property_tree::write_json(jsonStrStream, pTree);
    status = parseDataSmartDeviceJson(jsonStrStream.str(), info);

    EXPECT_TRUE(status);
    EXPECT_TRUE(strcmp(info.device.idSmartDevice, "SD001") == 0);
    EXPECT_TRUE(strcmp(info.deviceTimer.stateRelay, "ACTIVE") == 0);
    EXPECT_TRUE(strcmp(info.deviceTimer.stateElectric, "ON") == 0);
    /*EXPECT_TRUE(strcmp(info.device.ip_port, "192.168.0.100:8800") == 0);*/
    EXPECT_TRUE(strcmp(info.device.idRoom, "R0001") == 0);
    EXPECT_TRUE(strcmp(info.device.nameSmartDevice, "DEVICE_LIGHT") == 0);

    EXPECT_TRUE(strcmp(info.timer.idTimer, "TI00000001") == 0);
    EXPECT_TRUE(info.timer.monthSD == 1);
    EXPECT_TRUE(info.timer.daySD == 18);
    EXPECT_TRUE(info.timer.yearSD == 2017);
    EXPECT_TRUE(info.timer.hourSD == 21);
    EXPECT_TRUE(info.timer.minSD == 59);
    EXPECT_TRUE(info.timer.secSD == 00);
    EXPECT_TRUE(info.sender.port == 8800);
    EXPECT_TRUE(strcmp(info.sender.ip, "192.168.0.100") == 0);
}

TEST_F(JsonParserTest, TestparseJsonToTopic_RESULT_OK)
{
    bool status = false;
    char* jsonString = NULL;
    std::string topic;

    boost::property_tree::ptree pTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_update_status_device.json");

    boost::property_tree::read_json(jsonFilePath, pTree);
    std::stringstream jsonStrStream;
    boost::property_tree::write_json(jsonStrStream, pTree);
    status = parseJsonToTopic(jsonStrStream.str(), topic);

    EXPECT_TRUE(status);
    EXPECT_TRUE(topic.compare("SMART_DEVICE_STATUS_VALUE") == 0);
}