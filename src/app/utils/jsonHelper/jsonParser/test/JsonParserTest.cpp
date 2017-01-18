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

TEST_F(JsonParserTest, TestparseSmartPlugStatusJson_RESULT_OK)
{
    bool status = false;
    char* jsonString = NULL;
    SmartPlugInfo info;

    boost::property_tree::ptree pTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_2.json");

    boost::property_tree::read_json(jsonFilePath, pTree);
    std::stringstream jsonStrStream;
    boost::property_tree::write_json(jsonStrStream, pTree);
    status = parseSmartPlugStatusJson(jsonStrStream.str(), info);

    EXPECT_TRUE(status);
    EXPECT_TRUE(strcmp(info.data.smartPlugStatus, "OFF") == 0);
    EXPECT_TRUE(info.datetimesp.month == 1);
    EXPECT_TRUE(info.datetimesp.day == 18);
    EXPECT_TRUE(info.datetimesp.year == 2017);
    EXPECT_TRUE(info.datetimesp.hour == 21);
    EXPECT_TRUE(info.datetimesp.min == 59);
    EXPECT_TRUE(info.datetimesp.sec == 00);
    EXPECT_TRUE(info.sender.port == 5600);
    EXPECT_TRUE(strcmp(info.sender.ip, "192.168.1.177") == 0);
}