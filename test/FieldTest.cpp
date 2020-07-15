#include <gtest/gtest.h>
#include <Field.hpp>

using namespace std::literals::string_literals;

TEST(FieldTests, constructionTest) {
  ASSERT_NO_THROW(([&](){
    const auto test = Field{"a name"s, "a value"s};
  }()));
  ASSERT_NO_THROW(([&](){
    const auto test = Field{"another name"s, "another value"s};
  }()));
}
