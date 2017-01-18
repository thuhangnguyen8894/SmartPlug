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
    EXPECT_EQ("", smartplug.getId());
    EXPECT_EQ("", smartplug.getIP());
    EXPECT_EQ("", smartplug.getStatus());
}
