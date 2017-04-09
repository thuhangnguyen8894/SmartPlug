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
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:ON:ACTIVE:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");

    boost::property_tree::ptree expectedTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_update_status_device.json");

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
    std::string message("MESSAGE_TYPE_DEFAULT;SD001:UNACTIVE:OFF:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");

    bool status = buildJsonForC(message.c_str(), &jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_RESULT_FAILURE_2)
{
    char* jsonString = NULL;
    std::string message("MESSAGE_TYPE_DEFAULT;SD001:UNACTIVE:OFF:8:R0001");

    bool status = buildJsonForC(message.c_str(), &jsonString);

    EXPECT_FALSE(status);
}

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_RESULT_FAILURE_3)
{
    char* jsonString = NULL;
    std::string message("MESSAGE_TYPE_DEFAULT;SD001:ACTIVE:ON:8:R0001");

    bool status = buildJsonForC(message.c_str(), &jsonString);

    EXPECT_FALSE(status);
}