#include <gtest/gtest.h>
#include <Parser.hpp>

static const std::string TRANSLATION_TABLE_PATH = "../../src/translationTable.json";

TEST(ParserTest, constructionTest) {
    ASSERT_NO_THROW(Parser("","",TranslationTable(TRANSLATION_TABLE_PATH)));
}

TEST(ParserTest, parseFileTest) {
    boost::filesystem::ifstream in("../../test/res/publications.bib");
    ASSERT_NO_THROW(Parser("","article",TranslationTable(TRANSLATION_TABLE_PATH)).parseFile(in));
}

TEST(ParserTest, parseFilesTest) {
    ASSERT_NO_THROW(Parser("","",TranslationTable(TRANSLATION_TABLE_PATH)).parseFiles("../../test/res"));
}
