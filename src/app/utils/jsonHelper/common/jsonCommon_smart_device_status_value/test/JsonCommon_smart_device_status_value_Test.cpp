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
 */
/****************************************************************************/

#include <gtest/gtest.h>

#include "JsonCommon_smart_device_status_value.h"

class JsonCommon_smart_device_status_value_Test : public ::testing::Test
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
TEST_F(JsonCommon_smart_device_status_value_Test, TestisSensorMessage_RESULT_OK)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:OFF:UNACTIVE:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    bool status = isSensorMessage(message);
    EXPECT_TRUE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommon_smart_device_status_value_Test, TestisSensorMessage_RESULT_FAILURE_1)
{
    std::string message("SMART_DEVICE_STATUS_VALUE");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommon_smart_device_status_value_Test, TestisSensorMessage_RESULT_FAILURE_2)
{
    std::string message("192.168.1.177");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: false
 */
TEST_F(JsonCommon_smart_device_status_value_Test, TestisSensorMessage_RESULT_FAILURE_3)
{
    std::string message("192.168.1.177:8800");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Lower Boundary Testing
 * Expected Result: false
 */
TEST_F(JsonCommon_smart_device_status_value_Test, TestisSensorMessage_RESULT_FAILURE_4)
{
    std::string message("");
    bool status = isSensorMessage(message);
    EXPECT_FALSE(status);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: MESSAGE_TYPE_SMART_PLUG_STATUS
 */
TEST_F(JsonCommon_smart_device_status_value_Test, TestgetJSONMessageType_MESSAGE_TYPE_SMART_PLUG_STATUS)
{
    std::string message("SMART_DEVICE_STATUS_VALUE;SD001:OFF:UNACTIVE:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_SMART_DEVICE_STATUS);
}

/*!
 * Test Type      : Equivalence Class Testing
 * Expected Result: MESSAGE_TYPE_DEFAULT
 */
TEST_F(JsonCommon_smart_device_status_value_Test, TestgetJSONMessageType_DEFAULT_TYPE)
{
    std::string message("MESSAGE_TYPE_DEFAULT;SD001:OFF:UNACTIVE:8:R0001;192.168.0.100:8800;TI00000001_1/18/2017_21:59:00");
    MESSAGE_TYPE messageType = getJSONMessageType(message);
    EXPECT_EQ(messageType, MESSAGE_TYPE_DEFAULT);
}