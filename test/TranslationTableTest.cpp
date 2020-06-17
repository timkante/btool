#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <TranslationTable.hpp>
#include <boost/filesystem/path.hpp>

struct TranslationTableFixtureTest : public ::testing::Test {
    TranslationTable sample;

    TranslationTableFixtureTest() : sample{std::stringstream{R"(
        {
            "sortableFields": [],
            "styles": [
                {
                "name": "article",
                "requiredFields": [
                    "author",
                    "title"
                ],
                "optionalFields": [
                    "some",
                    "other",
                    "field"
                ]
            },
            {
                "name": "book",
                "requiredFields": [
                    "author",
                    "title",
                    "year",
                    "publisher"
                ],
                "optionalFields": [
                    "volume",
                    "series",
                    "address",
                    "edition",
                    "month",
                    "note",
                    "isbn"
                ]
            }
        ]
    })"}
    } {};
};

TEST_F(TranslationTableFixtureTest, getAllStylesTest) {
    const auto expectedStyles = std::vector<StyleProperties>{
            {"article",
                    {
                            "author",
                            "title",
                    },
                    {
                            "some",
                            "other",
                            "field"
                    }},
            {"book",
                    {
                            "author",
                            "title",
                            "year",
                            "publisher"
                    },
                    {
                            "volume",
                            "series",
                            "address",
                            "edition",
                            "month",
                            "note",
                            "isbn"
                    }}
    };
    ASSERT_EQ(sample.getStyleProperties(), expectedStyles);
}

TEST_F(TranslationTableFixtureTest, getStyleTest) {
    ASSERT_EQ(sample.stylePropertiesOf("book"),
              StyleProperties("book",
                              {
                                      "author",
                                      "title",
                                      "year",
                                      "publisher"
                              },
                              {
                                      "volume",
                                      "series",
                                      "address",
                                      "edition",
                                      "month",
                                      "note",
                                      "isbn"
                              }));
}

TEST_F(TranslationTableFixtureTest, getInvalidStyleTest) {
    ASSERT_EQ(sample.stylePropertiesOf("invalid style"), std::nullopt);
}

TEST(TranslationTableTest, constructorTestFromPath) {
    ASSERT_NO_THROW(TranslationTable(boost::filesystem::path("../../src/translationTable.json")));
}

TEST(TranslationTableTest, constructorTestFromContent) {
    ASSERT_NO_THROW(TranslationTable(std::stringstream{R"({"key": "value"})"}));
}

TEST(TranslationTableTest, printTest) {
    std::stringstream receiver;
    TranslationTable(std::stringstream{R"({"key": "value"})"}).printAll(receiver);
    ASSERT_EQ(receiver.str(), "{\n    \"key\": \"value\"\n}\n");
}