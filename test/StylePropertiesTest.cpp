#include <StyleProperties.hpp>
#include <gtest/gtest.h>
#include <vector>

using namespace std::literals::string_literals;

TEST(StylePropertiesTests, noArgConstructionTest) {
  ASSERT_NO_THROW(StyleProperties());
}

TEST(StylePropertiesTests, constructionTest) {
  std::unordered_set<std::string> required = {
      "first name"s,
      "second name"s
  };
  std::unordered_set<std::string> optional = {
      "first name"s,
      "second name"s
  };
  ASSERT_NO_THROW(([&](){
    const StyleProperties a{"a name"s, required, optional};
  }()));
}

TEST(StylePropertiesTests, equalityOperatorTest) {
  const auto first = StyleProperties{"name"s, {"a"s, "b"s, "c"s}, {"a"s, "b"s, "c"s}};
  const auto second = StyleProperties{"name"s, {"a"s, "c"s, "b"s}, {"c"s, "b"s, "a"s}};
  ASSERT_NO_THROW(ASSERT_EQ(first, second));
}
