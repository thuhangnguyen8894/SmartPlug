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
    Devices devices;

    strcpy(devices.idSmartDevice, "SP01");

    strcpy(devices.info.sender.ip, "192.168.0.100");

    devices.info.sender.port = 5563;

    strcpy(devices.info.data.smartPlugStatus, "ON");
    
    devices.info.datetimesp.monthSP = 1;
    devices.info.datetimesp.daySP = 22;
    devices.info.datetimesp.yearSP = 2017;
    devices.info.datetimesp.hourSP = 11;
    devices.info.datetimesp.minSP = 50;
    devices.info.datetimesp.secSP = 45;

    EXPECT_EQ("SP01", devices.idSmartDevice);
    EXPECT_EQ("192.168.0.100", devices.info.sender.ip);
    EXPECT_EQ(5563, devices.info.sender.port);
    EXPECT_EQ("ON", devices.info.data.smartPlugStatus);
    EXPECT_EQ(1, devices.info.datetimesp.monthSP);
    EXPECT_EQ(22, devices.info.datetimesp.daySP);
    EXPECT_EQ(2017, devices.info.datetimesp.yearSP);
    EXPECT_EQ(11, devices.info.datetimesp.hourSP);
    EXPECT_EQ(50, devices.info.datetimesp.minSP);
    EXPECT_EQ(45, devices.info.datetimesp.secSP);
}
