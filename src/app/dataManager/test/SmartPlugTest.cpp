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
