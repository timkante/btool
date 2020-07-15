#include <gtest/gtest.h>
#include <BibElement.hpp>
#include <StyleProperties.hpp>

using namespace std::literals::string_literals;

struct BibElementFixtureTest : public ::testing::Test {
  const StyleProperties props;
  const BibElement completeElement;
  const BibElement incompleteElement;

  BibElementFixtureTest()
      : props{"style"s, {"reqField"s, "reqField2"s}, {"optField"s}},
        completeElement{"id"s,
                        "style"s,
                        {
                            {"reqField"s, "a value"s},
                            {"someOtherField"s, "a value"s},
                            {"reqField2"s, "a value"s}
                        }},
        incompleteElement{"id"s,
                          "style"s,
                          {
                              {"reqField2"s, "value"s}
                          }} {}

};

TEST_F(BibElementFixtureTest, completeElementTest) {
  ASSERT_TRUE(completeElement.isCompliantTo(props));
}

TEST_F(BibElementFixtureTest, incompleteElementTest) {
  ASSERT_FALSE(incompleteElement.isCompliantTo(props));
}

TEST(BibelementTests, constructionTest) {
  std::vector<Field> fields = {
      Field{"name"s, "value"s},
      Field{"another name"s, "another value"s}
  };
  ASSERT_NO_THROW((BibElement{"an id"s, "a style"s, fields}));
  ASSERT_NO_THROW((BibElement{"another id"s, "another style"s, fields}));
}
