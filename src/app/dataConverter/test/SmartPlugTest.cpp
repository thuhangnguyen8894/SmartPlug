/****************************************************************************/
/*!
 * @file LightIntensityTest.cpp
 * @brief Unittest for LightIntensity class
 *
 * Copyright (c) Tien Nguyen Anh 2016 
 *
 * @detail The testing file of the implementation of LightIntensity class
 */
/****************************************************************************/

#include <gtest/gtest.h>

#include "smartplug.h"

class SmartPlug : public ::testing::Test
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
    EXPECT_EQ(0, smartplug.getSmartPlug());
    EXPECT_EQ(0, smartplug.getMoment());
}
