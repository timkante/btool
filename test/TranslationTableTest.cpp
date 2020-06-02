//
// Created by Tim Kante on 01.06.20.
//

#include <gtest/gtest.h>
#include <sstream>
#include <TranslationTable.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

TEST(TranslationTableTest, constructorTestFromPath){
    ASSERT_NO_THROW(TranslationTable(boost::filesystem::path("../../src/translationTable.json")));
}

TEST(TranslationTableTest, constructorTestFromContent){
    ASSERT_NO_THROW(TranslationTable(std::stringstream{R"({"key": "value"})"}));
}

TEST(TranslationTableTest, printTest){
    ASSERT_EQ(TranslationTable(std::stringstream{R"({"key": "value"})"}).printAll().str(),
            "{\n    \"key\": \"value\"\n}\n");
}