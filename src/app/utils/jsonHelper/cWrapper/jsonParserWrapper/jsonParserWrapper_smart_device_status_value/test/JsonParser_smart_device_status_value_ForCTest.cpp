/****************************************************************************/
/*!
 * @file JsonBuilderTest.cpp
 * @brief Unittest for JsonParserForCTest class
 *
 * Copyright (c) Tien Nguyen Anh 2016 
 *
 * @detail The testing file of the implementation of JsonBuilderTest class
 * Modified History
 * ---------------
 * 2017-Jan-07 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-13 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
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

#include "JsonParser_smart_device_status_value_ForC.h"


class JsonParser_smart_device_status_value_ForCTest : public ::testing::Test
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

TEST_F(JsonParser_smart_device_status_value_ForCTest, TestparseDataSmartDeviceJsonForC_RESULT_OK)
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

    status = parseDataSmartDeviceJsonForC(jsonStrStream.str().c_str(), &info);

    EXPECT_TRUE(status);
    EXPECT_TRUE(strcmp(info.device.idSmartDevice, "SD001") == 0);
    EXPECT_TRUE(strcmp(info.device_timer.stateRelay, "ACTIVE") == 0);
    EXPECT_TRUE(strcmp(info.device_timer.stateElectric, "ON") == 0);
    EXPECT_TRUE(strcmp(info.device.ip_port, "192.168.0.100:8800") == 0);
    EXPECT_TRUE(strcmp(info.device.idRoom, "R0001") == 0);

    EXPECT_TRUE(strcmp(info.timer.idTimer, "TI00000001") == 0);
    EXPECT_TRUE(info.timer.monthSP == 1);
    EXPECT_TRUE(info.timer.daySP == 18);
    EXPECT_TRUE(info.timer.yearSP == 2017);
    EXPECT_TRUE(info.timer.hourSP == 21);
    EXPECT_TRUE(info.timer.minSP == 59);
    EXPECT_TRUE(info.timer.secSP == 00);
    EXPECT_TRUE(info.sender.port == 8800);
    EXPECT_TRUE(strcmp(info.sender.ip, "192.168.0.100") == 0);
}