#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <TranslationTable.hpp>
#include <boost/filesystem/path.hpp>

TEST(TranslationTableTest, constructorTestFromPath) {
    ASSERT_NO_THROW(TranslationTable(boost::filesystem::path("../../src/translationTable.json")));
}

TEST(TranslationTableTest, constructorTestFromContent) {
    ASSERT_NO_THROW(TranslationTable(std::stringstream{R"({"key": "value"})"}));
}

TEST(TranslationTableTest, printTest) {
    std::stringstream receiver;
    TranslationTable(std::stringstream{R"({"key": "value"})"}).printAll(receiver);
    ASSERT_EQ(receiver.str(),
              "{\n    \"key\": \"value\"\n}\n");
}

TEST(TranslationTableTest, styleParsingTest) {
    std::stringstream file{R"(
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
}
)"};
    const auto table = TranslationTable(std::move(file));
    const auto expectedStyles = std::vector{
            StyleProperties("article",
                            std::vector<std::string>{
                                    "author",
                                    "title",
                            },
                            std::vector<std::string>{
                                    "some",
                                    "other",
                                    "field"
                            }),
            StyleProperties("book", std::vector<std::string>{
                                    "author",
                                    "title",
                                    "year",
                                    "publisher"
                            },
                            std::vector<std::string>{
                                    "volume",
                                    "series",
                                    "address",
                                    "edition",
                                    "month",
                                    "note",
                                    "isbn"
                            })
    };
    ASSERT_EQ(table.styleProps, expectedStyles);
}