#include <gtest/gtest.h>
#include <BibElement.hpp>
#include <HtmlGenerator.hpp>
#include <XmlGenerator.hpp>
#include <PlainTextGenerator.hpp>

using namespace std::literals::string_literals;

/**
 * Tests for File-Generators
 * @example
 * @test Generator Fixture Tests
 */
struct GeneratorFixtureTest : public ::testing::Test {
  std::vector<BibElement> element{
      {
          {
              "FeigenspanSiFr11",
              "article",
              {
                  {"author", "{Janet Feigenspan and Norbert Siegmund and Jana Fruth}"},
                  {"title", "{{On the Role of Program Comprehension in Embedded Systems}}"},
                  {"journal", "{Softwaretechnik-Trends}"},
                  {"year", "{2011}"},
                  {"volume", "{31}"},
                  {"number", "{2}"},
                  {"month", "May"},
                  {"url",
                   "{http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}"
                  }
              }
          }
      }
  };
};

TEST_F(GeneratorFixtureTest, uniqueFields) {
  std::unordered_set<std::string> expected{
    "author",
    "title",
    "journal",
    "year",
    "volume",
    "number",
    "month",
    "url"
  };

  ASSERT_EQ(AbstractGenerator::uniqueFieldsOf(element), expected);
}

TEST_F(GeneratorFixtureTest, htmlGeneratorTest) {
  ASSERT_NO_THROW(([&](){
    const auto html = HtmlGenerator{element}.write();
    ASSERT_NE(html, "");
  }()));
}

TEST_F(GeneratorFixtureTest, xmlGeneratorTest) {
  ASSERT_NO_THROW(([&](){
    const auto xml = XmlGenerator{element}.write();
    ASSERT_NE(xml, "");
  }()));
}

TEST_F(GeneratorFixtureTest, plainTextGeneratorTest) {
  ASSERT_NO_THROW(([&](){
    const auto plain = PlainTextGenerator{element}.write();
    ASSERT_NE(plain, "");
  }()));
}

TEST_F(GeneratorFixtureTest, htmlGeneratorThrowsOnEmptyInput) {
  ASSERT_ANY_THROW([]() {
    HtmlGenerator({}).write();
  }());
}