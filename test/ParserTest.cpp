#include <gtest/gtest.h>
#include <Parser.hpp>

struct ParserFixtureTest : public ::testing::Test {
    Parser sample;

    ParserFixtureTest() : sample{std::stringstream{R"(
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
    })"}, "article"} {};
};

TEST_F(ParserFixtureTest, parseEmptyFileContents) {
    std::stringstream input{""};
    ASSERT_EQ(sample.generate(input, "year"), std::vector<BibElement>());
}

TEST_F(ParserFixtureTest, parseCorrectContent) {
    std::stringstream input{R"(@article{FeigenspanSiFr11,
    author = {Janet Feigenspan and Norbert Siegmund and Jana Fruth},
    title = {{On the Role of Program Comprehension in Embedded Systems}},
    journal = {Softwaretechnik-Trends},
    year = {2011},
    volume = {31},
    number = {2},
    month = May,
    url = {http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}
})"};

    const std::vector<BibElement> expected{{
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
                     "http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf"}
            }}};
    ASSERT_EQ(sample.generate(input, "year"), expected);
}
