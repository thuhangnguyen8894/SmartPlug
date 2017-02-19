/****************************************************************************/
/*!
 * @file JsonBuilderTest.cpp
 * @brief Unittest for JsonBuilderTest class
 *
 * Copyright (c) Tien Nguyen Anh 2016 
 *
 * @detail The testing file of the implementation of JsonBuilderTest class
 * Modified History
 * ---------------
 * 2017-Jan-07 Created tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/
#include <cstdlib>
#include <gtest/gtest.h>

#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "JsonBuilderForC.h"


class JsonBuilderForCTest : public ::testing::Test
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

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_RESULT_OK)
{
    char* jsonString = NULL;
    std::string message("PON:ACTIVE:8;192.168.1.177:5600;TI0001;1/18/2017  21:59:00");

    boost::property_tree::ptree expectedTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_update_status_device_1.json");

    boost::property_tree::read_json(jsonFilePath, expectedTree);

    bool status = buildJsonForC(message.c_str(), &jsonString);
    boost::property_tree::ptree actualTree;
    std::stringstream stringStream(jsonString);
    boost::property_tree::read_json(stringStream, actualTree);
    
    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, actualTree);
}

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_MESSAGE_TYPE_RESULT_FAILURE_1)
{
    char* jsonString = NULL;
    std::string message("RON:UNACTIVE:8;192.168.1.177:5600;TI0001;1/18/2017  21:59:00");

    bool status = buildJsonForC(message.c_str(), &jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_RESULT_FAILURE_2)
{
    char* jsonString = NULL;
    std::string message("RON");

    bool status = buildJsonForC(message.c_str(), &jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_RESULT_FAILURE_3)
{
    char* jsonString = NULL;
    std::string message("LOFF");

    bool status = buildJsonForC(message.c_str(), &jsonString);

    EXPECT_FALSE(status);
}