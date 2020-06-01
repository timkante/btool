//
// Created by Tim Kante on 01.06.20.
//

#include <gtest/gtest.h>
#include <TranslationTable.hpp>

TEST(TranslationTableTest, constructorTest){
    ASSERT_NO_THROW(TranslationTable(std::string("../../src/translationTable.json")));
}