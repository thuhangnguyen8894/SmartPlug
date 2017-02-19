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

#include "JsonParserForC.h"


class JsonParserForCTest : public ::testing::Test
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

TEST_F(JsonParserForCTest, TestparseSmartPlugStatusJsonForC_RESULT_OK)
{
    bool status = false;
    char* jsonString = NULL;
    SmartDeviceInfo info;

    boost::property_tree::ptree pTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_update_status_device_1.json");

    boost::property_tree::read_json(jsonFilePath, pTree);
    std::stringstream jsonStrStream;
    boost::property_tree::write_json(jsonStrStream, pTree);

    status = parseSmartPlugStatusJsonForC(jsonStrStream.str().c_str(), &info);

    EXPECT_TRUE(status);
    EXPECT_TRUE(strcmp(info.data.status_use_electric, "ON") == 0);
    EXPECT_TRUE(strcmp(info.data.status_electric, "ACTIVE") == 0);
    EXPECT_TRUE(strcmp(info.data.jack_relay, "8") == 0);
    EXPECT_TRUE(strcmp(info.id.id_timer, "TI0001") == 0);
    EXPECT_TRUE(info.datetimesp.monthSP == 1);
    EXPECT_TRUE(info.datetimesp.daySP == 18);
    EXPECT_TRUE(info.datetimesp.yearSP == 2017);
    EXPECT_TRUE(info.datetimesp.hourSP == 21);
    EXPECT_TRUE(info.datetimesp.minSP == 59);
    EXPECT_TRUE(info.datetimesp.secSP == 00);
    EXPECT_TRUE(info.sender.port == 5600);
    EXPECT_TRUE(strcmp(info.sender.ip, "192.168.1.177") == 0);
}