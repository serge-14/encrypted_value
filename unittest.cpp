// unittest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../encrypted_value.hpp"
#include "gtest/gtest.h"

TEST(encrypted_variable, create)
{
    misc::encrypted_variable<int> value(10);

    EXPECT_NE(10, value.value);
    EXPECT_EQ(10, (int)value);
}

TEST(encrypted_variable, copy)
{
    misc::encrypted_variable<int> value(1520);
    misc::encrypted_variable<int> other(value);

    EXPECT_EQ(1520, (int)value);
    EXPECT_EQ(1520, (int)other);
}

TEST(encrypted_variable, move)
{
    misc::encrypted_variable<int> value(1520);
    misc::encrypted_variable<int> other;

    other = std::move(value);

    EXPECT_EQ(1520, (int)other);
}

TEST(encrypted_variable, assign)
{
    misc::encrypted_variable<int> value(1520);
    misc::encrypted_variable<int> other;

    other = value;

    EXPECT_EQ(1520, (int)value);
    EXPECT_EQ(1520, (int)other);
}

TEST(encrypted_variable, change_value)
{
    misc::encrypted_variable<int> value(999);

    value = value + 1;

    EXPECT_EQ(1000, (int)value);
}