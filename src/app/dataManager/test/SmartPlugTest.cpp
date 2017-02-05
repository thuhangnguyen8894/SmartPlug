/****************************************************************************/
/*!
 * @file SmartPlugTest.cpp
 * @brief Unittest for SmartPlug class
 *
 * Copyright (c) Tien Nguyen Anh 2016 
 *
 * @detail The testing file of the implementation of SmartPlug class
 *
 * Modified History
 * ---------------
 * 2017-Jan-03 Created tien.nguyenanh94@gmail.com
 * 2017-Jan-07 Modified tn-trang.tran@outlook.com
 * 2017-Jan-11 Modified tn-trang.tran@outlook.com
 * 2017-Jan-18 Modified tn-trang.tran@outlook.com
 */
/****************************************************************************/

#include <gtest/gtest.h>

#include "smartplug.h"

class SmartPlugTest : public ::testing::Test
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

TEST_F(SmartPlugTest, TestDefaultConstructorAndGetter)
{
    SmartPlug smartplug;

    strcpy(smartplug.id.idSmartPlug, "SP01");

    strcpy(smartplug.info.sender.ip, "192.168.0.100");

    smartplug.info.sender.port = 5563;

    strcpy(smartplug.info.data.smartPlugStatus, "ON");
    
    smartplug.info.datetimesp.monthSP = 1;
    smartplug.info.datetimesp.daySP = 22;
    smartplug.info.datetimesp.yearSP = 2017;
    smartplug.info.datetimesp.hourSP = 11;
    smartplug.info.datetimesp.minSP = 50;
    smartplug.info.datetimesp.secSP = 45;

    EXPECT_EQ("SP01", smartplug.id.idSmartPlug);
    EXPECT_EQ("192.168.0.100", smartplug.info.sender.ip);
    EXPECT_EQ(5563, smartplug.info.sender.port);
    EXPECT_EQ("ON", smartplug.info.data.smartPlugStatus);
    EXPECT_EQ(1, smartplug.info.datetimesp.monthSP);
    EXPECT_EQ(22, smartplug.info.datetimesp.daySP);
    EXPECT_EQ(2017, smartplug.info.datetimesp.yearSP);
    EXPECT_EQ(11, smartplug.info.datetimesp.hourSP);
    EXPECT_EQ(50, smartplug.info.datetimesp.minSP);
    EXPECT_EQ(45, smartplug.info.datetimesp.secSP);
}
