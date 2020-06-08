//
// Created by Martin on 03.06.2020.
//
#include <gtest/gtest.h>
#include <Parser.hpp>

TEST(ParserTest, constructionTest) {
    ASSERT_NO_THROW(Parser(".../.../src/translationTable.json",{".../.bib",".../.bib"} ));
}

TEST(ParserTest, generateTest) {
    ASSERT_NO_THROW(Parser(".../.../src/translationTable.json",{".../.bib",".../.bib"}).generate("year","PDF" ));
}

TEST(ParserTest, parseFileTest) {
    ASSERT_NO_THROW(Parser(".../.../src/translationTable.json",{".../.bib", ".../.bib"}).parseFile(".../.bib"));
}

TEST(ParserTest, parseFilesTest) {
    ASSERT_NO_THROW(Parser(".../.../src/translationTable.json",{".../.bib", ".../.bib"}).parseFiles({".../.bib",".../.bib"}, "book" ));
}

TEST(ParserTest, parseFieldTest) {
    ASSERT_NO_THROW(Parser(".../.../src/translationTable.json",{".../.bib", ".../.bib"}).parseField("author"));
}

TEST(ParserTest, parseElementTest) {
    ASSERT_NO_THROW(Parser(".../.../src/translationTable.json",{".../.bib", ".../.bib"}).parseElement("book"));
}
