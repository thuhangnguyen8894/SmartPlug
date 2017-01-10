/****************************************************************************/
/*!
 * @file JsonBuilderTest.cpp
 * @brief Unittest for JsonBuilderTest class
 *
 * Copyright (c) Tien Nguyen Anh 2016 
 *
 * @detail The testing file of the implementation of JsonBuilderTest class
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
    //EXPECT_TRUE(info.data.lightIntensity == 33);
    EXPECT_TRUE(strcmp(info.data.smartPlugStatus, "OFF") == 0);
    EXPECT_TRUE(info.sender.port == 5600);
    EXPECT_TRUE(strcmp(info.sender.ip, "192.168.1.177") == 0);
}