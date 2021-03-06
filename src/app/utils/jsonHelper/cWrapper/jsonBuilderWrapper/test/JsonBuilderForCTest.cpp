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
    std::string message("PON;192.168.1.177:5600");

    boost::property_tree::ptree expectedTree;
    char* rootENV = std::getenv("LIDT_ROOT");
    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/");
    jsonFilePath.append("arduinoJsonMessage_1.json");

    boost::property_tree::read_json(jsonFilePath, expectedTree);

    bool status = buildJsonForC(message.c_str(), &jsonString);
    
    boost::property_tree::ptree actualTree;
    
    std::string str(jsonString);
    std::istringstream stringStream(str);
    boost::property_tree::read_json(stringStream, actualTree);
    
    EXPECT_TRUE(status);
    EXPECT_EQ(expectedTree, actualTree);
}

TEST_F(JsonBuilderForCTest, TestbuildJsonForC_MESSAGE_TYPE_RESULT_FAILURE_1)
{
    char* jsonString = NULL;
    std::string message("RON;192.168.1.177:5600");

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