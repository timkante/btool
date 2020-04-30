//
// Created by Tim Kante on 29.04.20.
//

#include <gtest/gtest.h>
#include <add.hpp>

TEST(addTest, addFunctionTest){
    auto* test = new(int);
    ASSERT_EQ(add(3, 4), 7);
    test = nullptr;
    ASSERT_EQ(add(0, 0), 0);
    ASSERT_EQ(add(12, 26), 38);
}