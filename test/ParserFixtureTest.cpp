#include <gtest/gtest.h>
#include <Parser.hpp>
#include <BibElement.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

/**
 * Tests for the Parser
 * @example
 * @test Parser Fixture Tests
 */
struct ParserFixtureTest : public ::testing::Test {
  Parser sample;

  ParserFixtureTest() : sample{
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
                    "year",
                    "volume",
                    "number",
                    "month",
                    "url"
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
    })"}, {"article"}} {};
};

TEST_F(ParserFixtureTest, parseEmptyFileContents) {
  ASSERT_EQ(sample.generate(""sv, "year"s, "someFile.bib"s), std::vector<BibElement>());
}

TEST_F(ParserFixtureTest, parseCorrectContent) {
  auto const input = R"(@article{FeigenspanSiFr11,
    author = {Janet Feigenspan and Norbert Siegmund and Jana Fruth},
    title = {{On the Role of Program Comprehension in Embedded Systems}},
    journal = {Softwaretechnik-Trends},
    year = {2011},
    volume = {31},
    number = {2},
    month = May,
    url = {http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}
})"sv;

  const std::vector<BibElement> expected{
      {
          "FeigenspanSiFr11",
          "article",
          {
              {"author", "Janet Feigenspan and Norbert Siegmund and Jana Fruth"},
              {"title", "On the Role of Program Comprehension in Embedded Systems"},
              {"journal", "Softwaretechnik-Trends"},
              {"year", "2011"},
              {"volume", "31"},
              {"number", "2"},
              {"month", "May"},
              {"url",
               "http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf"
              }
          }
      }
  };
  auto const actual = sample.generate(input, "year"s, "someFile.bib"s);
  ASSERT_EQ(actual, expected);
}

TEST_F(ParserFixtureTest, parseNonRuleCompliantContent) {
  auto const input = R"(@article{FeigenspanSiFr11,
    author = {Janet Feigenspan and Norbert Siegmund and Jana Fruth},
    journal = {Softwaretechnik-Trends},
    year = {2011},
    volume = {31},
    number = {2},
    month = May,
    url = {http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}
})"sv;

  auto const actual = sample.generate(input, "year"s, "someFile.bib"s);
  ASSERT_EQ(actual, std::vector<BibElement>{});
}

TEST_F(ParserFixtureTest, parseDummyFile) {
  boost::filesystem::path target = boost::filesystem::path("../../test/res/publications.bib");
  ASSERT_NO_THROW([&]() {
    const auto elements = sample.generate(target, "author"s);
    ASSERT_EQ(elements.size(), 13u);
  }());
}

TEST_F(ParserFixtureTest, parseDummyFileInDirectory) {
  boost::filesystem::path target = boost::filesystem::path("../../test/res");
  ASSERT_NO_THROW([&]() {
    const auto elements = sample.generate(target, "author"s);
    ASSERT_EQ(elements.size(), 13u);
  }());
}

TEST_F(ParserFixtureTest, parseDummyFileThatDoesNotExist) {
  boost::filesystem::path target = boost::filesystem::path("../../test/res/someFileThatDoesNotExist.something");
  ASSERT_NO_THROW([&]() {
    const auto elements = sample.generate(target, "author"s);
    ASSERT_EQ(elements.size(), 0u);
  }());
}

TEST_F(ParserFixtureTest, sortingWorks) {
  const auto file = R"(
@article{Feigenspan11,
    author = {Janet Feigenspan},
    title = {{Program Comprehension of Feature-Oriented Software Development}},
    booktitle = {International Doctoral Symposium on Empirical Software Engineering (IDoESE)},
    year = {2011},
    month = Sep,
    url = {http://wwwiti.cs.uni-magdeburg.de/iti_db/publikationen/ps/auto/Feigenspan11.pdf}
}
@article{FeigenspanSiFr11,
    author = {Janet Feigenspan and Norbert Siegmund and Jana Fruth},
    title = {{On the Role of Program Comprehension in Embedded Systems}},
    journal = {Softwaretechnik-Trends},
    year = {2011},
    volume = {31},
    number = {2},
    month = May,
    url = {http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}
})"sv;

  std::vector<BibElement> expected{
      {"FeigenspanSiFr11", "article", {
          {"author", "Janet Feigenspan and Norbert Siegmund and Jana Fruth"},
          {"title", "On the Role of Program Comprehension in Embedded Systems"},
          {"journal", "Softwaretechnik-Trends"},
          {"year", "2011"},
          {"volume", "31"},
          {"number", "2"},
          {"month", "May"},
          {"url",
           "http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf"}
      }},
      {"Feigenspan11", "article", {
          {"author", "Janet Feigenspan"},
          {"title", "Program Comprehension of Feature-Oriented Software Development"},
          {"booktitle", "International Doctoral Symposium on Empirical Software Engineering (IDoESE)"},
          {"year", "2011"},
          {"month", "Sep"},
          {"url", "http://wwwiti.cs.uni-magdeburg.de/iti_db/publikationen/ps/auto/Feigenspan11.pdf"}
      }}};

  ASSERT_EQ(sample.generate(file, "title", "testfile.bib"), expected);
}