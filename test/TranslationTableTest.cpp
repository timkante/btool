#include <TranslationTable.hpp>
#include <gtest/gtest.h>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <sstream>
#include <vector>

struct TranslationTableFixtureTest : public ::testing::Test {
    TranslationTable sample;

    TranslationTableFixtureTest() : sample{
            // language=json
            std::stringstream{R"(
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

TEST(TranslationTableTest, parsingInvalidStyleFieldsTest) {
    auto invalidContent = std::stringstream{R"(
        {
            "styles": [
                {
                    "name": "garbage",
                    "abc": "def"
                }
            ]
        }
    )"};
    const auto table = TranslationTable(std::move(invalidContent));
    const auto expected = std::vector<StyleProperties>{{"garbage", {}, {}}};
    ASSERT_EQ(table.getStyleProperties(), expected);
}

TEST(TranslationTableTest, parsingInvalidStyleNameTest) {
    auto invalidContent = std::stringstream{R"(
        {
            "styles": [
                {
                    "someKey": "garbage",
                    "requiredFields": "def",
                    "optionalFields": "def"
                }
            ]
        }
    )"};
    const auto table = TranslationTable(std::move(invalidContent));
    const auto expected = std::vector<StyleProperties>{{"", {}, {}}};
    ASSERT_EQ(table.getStyleProperties(), expected);
}

TEST(TranslationTableTest, parsingInvalidStylesTest) {
    auto invalidContent = std::stringstream{R"(
        {
            "not styles": [
                {
                    "name": "garbage",
                    "requiredFields": "def",
                    "optionalFields": "def"
                }
            ]
        }
    )"};
    const auto table = TranslationTable(std::move(invalidContent));
    const auto expected = std::vector<StyleProperties>{};
    ASSERT_EQ(table.getStyleProperties(), expected);
}

TEST(TranslationTableTest, parsingInvalidFileContent) {
    auto invalidContent = std::stringstream{R"(
        {,
            "some": [
                {
                    "invalid": "json"
                },
            ],
        }
    )"};
    const auto table = TranslationTable(std::move(invalidContent));
    const auto expected = std::vector<StyleProperties>{};
    ASSERT_EQ(table.getStyleProperties(), expected);
}

TEST(TranslationTableTest, parsingInvalidFile) {
    auto invalidFile = boost::filesystem::path("./someUnExistingFile.json");
    const auto table = TranslationTable(invalidFile);
    const auto expected = std::vector<StyleProperties>{};
    ASSERT_EQ(table.getStyleProperties(), expected);
}

TEST(TranslationTableTest, parsingDirectory) {
    auto invalidFile = boost::filesystem::path(".");
    const auto table = TranslationTable(invalidFile);
    const auto expected = std::vector<StyleProperties>{};
    ASSERT_EQ(table.getStyleProperties(), expected);
}