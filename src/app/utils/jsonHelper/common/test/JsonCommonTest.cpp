/****************************************************************************/
/*!
 * @file CommonTest.cpp
 * @brief Unittest for CommonTest class
 *
 * Copyright (c) 2017 Tien Anh Nguyen 
 *
 * @detail The testing file of the implementation of CommonTest class
 *
 * Modified History
 * ---------------
 * 2017-Jan-03 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Feb-11 Modified tn-trang.tran@outlook.com
 * 2017-Mar-06 Modified thuhang.nguyen8894@gmail.com
 */
/****************************************************************************/

#include <gtest/gtest.h>

#include "JsonCommon.h"
#include <boost/property_tree/ptree.hpp>

class JsonCommonTest : public ::testing::Test
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


/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_OK)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:DEVICE_LIGHT:OFF:UNACTIVE:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    bool status = isSensorMessage(message);
    EXPECT_TRUE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_1)
{
    std::string message("SMART_DEVICE_STATUS_VALUE");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_2)
{
    std::string message("192.168.1.177");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_3)
{
    std::string message("192.168.1.177:8800");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Lower Boundary Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_RESULT_FAILURE_4)
{
    std::string message("");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_STATUS)
{
    std::string message("SMART_DEVICE_STATUS_VALUE");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_DEVICE_STATUS);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: MESSAGE_TYPE_DEFAULT
 */
TEST_F(JsonCommonTest, TestgetJSONMessageType_DEFAULT_TYPE)
{
    std::string message("MESSAGE_TYPE_DEFAULT");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_DEFAULT);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result[0]: 192.168.1.100
 * Expected Result[1]: 8800
 */
TEST_F(JsonCommonTest, TestsplitWordRegex_RESULT_OK)
{
    std::string message("192.168.1.100:8800");
    std::vector<std::string> status = splitWordRegex(message, COLON_SPLITTER);
    EXPECT_EQ(status[0], "192.168.1.100");
    EXPECT_EQ(status[1], "8800");
}

/*!
 * Test Type      : Lower Boundary Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_FAILURE_COLON_SPLITTER)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001.DEVICE_LIGHT.OFF.UNACTIVE.R0001;192.168.0.100/8800;TI00000001_1/18/2017_21/59/00");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_FAILURE_SLASH_SPLITTER)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:DEVICE_LIGHT:OFF:UNACTIVE:R0001;192.168.0.100:8800;TI00000001_1:18:2017_21:59:00");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommonTest, TestisSensorMessage_FAILURE_UNDERSCORS_SPLITTER)
{
    std::string message("SMARTDEVICE;SD001:DEVICE_LIGHT:OFF:UNACTIVE:R0001;192.168.0.100:8800;TI00000001:1/18/2017:21:59:00");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: SMART_DEVICE_STATUS_VALUE
 */
TEST_F(JsonCommonTest, TestconvertMessageTypeToStr_RESULT_OK)
{
    MESSAGE_TYPE message = MESSAGE_TYPE_SMART_DEVICE_STATUS;
    std::string value = convertMessageTypeToStr(message);
    EXPECT_EQ(value, MESSAGE_TYPE_SMART_DEVICE_STATUS_VALUE);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: MESSAGE_TYPE_DEFAULT
 */
TEST_F(JsonCommonTest, TestconvertMessageTypeToStr_RESULT_FAILURE)
{
    MESSAGE_TYPE message = MESSAGE_TYPE_DEFAULT;
    std::string value = convertMessageTypeToStr(message);
    EXPECT_EQ(value, MESSAGE_TYPE_DEFAULT_VALUE);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: true
 */

/*TEST_F(JsonCommon_smart_device_status_value_Test, TestconvertJsonStrToPtree_RESULT_OK)
{
    boost::property_tree::ptree pTree;
    std::string message("MESSAGE_TYPE : SMART_DEVICE_STATUS_VALUE");
    bool status = convertJsonStrToPtree(message, pTree);
    EXPECT_TRUE(status);
}*/
