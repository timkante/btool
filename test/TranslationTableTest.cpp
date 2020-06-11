#include <gtest/gtest.h>
#include <sstream>
#include <TranslationTable.hpp>
#include <boost/filesystem/path.hpp>

TEST(TranslationTableTest, constructorTestFromPath) {
    ASSERT_NO_THROW(TranslationTable(boost::filesystem::path("../../src/translationTable.json")));
}

TEST(TranslationTableTest, constructorTestFromContent) {
    ASSERT_NO_THROW(TranslationTable(std::stringstream{R"({"key": "value"})"}));
}

TEST(TranslationTableTest, parsingCommonFields) {
    const std::string tableContent = R"(
{
    "commonRequiredFields": [
        {
            "title": "author",
            "format": "\\w+"
        },
        {
            "title": "title",
            "format": "\\w+"
        }
    ]
})";
    std::vector<FieldConstraint> expectedFields = {
            FieldConstraint("author", std::regex{R"(\w+)"}),
            FieldConstraint("title", std::regex{R"(\w+)"})
    };
    auto table = TranslationTable(std::stringstream(tableContent));
    ASSERT_EQ(table.commonProps.requiredFields, expectedFields);
}

TEST(TranslationTableTest, parsingWrongCommonFields) {
    const std::string tableContent = R"(
{
    "commonRequiredFields": [
        {
            "title": [
                "an",
                "error"
            ],
            "format": "\\w+"
        },
        {
            "title": "title",
            "format": "\\w+"
        }
    ]
})";
    std::vector<FieldConstraint> expectedFields = {
            FieldConstraint("title", std::regex{R"(\w+)"})
    };
    auto table = TranslationTable(std::stringstream(tableContent));
    ASSERT_EQ(table.commonProps.requiredFields, expectedFields);
}

TEST(TranslationTableTest, printTest) {
    std::stringstream receiver;
    TranslationTable(std::stringstream{R"({"key": "value"})"}).printAll(receiver);
    ASSERT_EQ(receiver.str(),
              "{\n    \"key\": \"value\"\n}\n");
}
