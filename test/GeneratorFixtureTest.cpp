#include <gtest/gtest.h>
#include <BibElement.hpp>
#include <HtmlGenerator.hpp>

using namespace std::literals::string_literals;

/**
 * Tests for File-Generators
 * @example
 * @test Generator Fixture Tests
 */
struct GeneratorFixtureTest : public ::testing::Test {
  const HtmlGenerator generator{
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

TEST_F(GeneratorFixtureTest, htmlGeneratorTest){
  ASSERT_EQ(generator.write(), "");
}