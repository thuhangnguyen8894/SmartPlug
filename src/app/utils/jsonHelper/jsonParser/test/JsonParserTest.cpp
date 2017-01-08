/****************************************************************************/
/*!
 * @file JsonBuilderTest.cpp
 * @brief Unittest for JsonBuilderTest class
 *
 * Copyright (c) Trang Tran 2017 
 *
 * @detail The testing file of the implementation of JsonBuilderTest class
 *
 * Modified History
 * ---------------
 * 2017-Jan-05 Created tn-trang.tran@outlook.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/
#include <cstdlib>
#include <gtest/gtest.h>

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

TEST_F(JsonParserTest, TestparseSmartPlugJson_RESULT_OK)
{
    bool status = false;
    char* jsonString = NULL;
    smartplugInfo info;

    boost::property_tree::ptree pTree;
    char* rootENV = std::getenv("LIDT_ROOT");

    std::string jsonFilePath(rootENV);
    jsonFilePath.append("/testedData/jsonFiles/arduinoJsonMessage_1.json");
    //jsonFilePath.append("arduinoJsonMessage_1.json");
    std::stringstream jsonStrStream;
    boost::property_tree::write_json(jsonStrStream, pTree);
    //boost::property_tree::write_json(jsonStrStream, jsonFilePath);

    status = parseSmartPlugJson(jsonStrStream.str().c_str(), &info);

    EXPECT_TRUE(status);
    EXPECT_TRUE(info.data.smartplug == 33);
    EXPECT_TRUE(info.sender.port == 5600);
    EXPECT_TRUE(strcmp(info.sender.ip, "192.168.1.177") == 0);
}