#include <StyleProperties.hpp>
#include <gtest/gtest.h>
#include <vector>

TEST(StylePropertiesTests, noArgConstructionTest) {
    ASSERT_NO_THROW(StyleProperties());
}

TEST(StylePropertiesTests, constructionTest) {
    std::vector<std::string> required = {
            "first name",
            "second name"
    };
    std::vector<std::string> optional = {
            "first name",
            "second name"
    };
    ASSERT_NO_THROW(StyleProperties("a name", required, optional));
}

TEST(StylePropertiesTests, equalityOperatorTest) {
    const auto first = StyleProperties("name", {"a", "b", "c"}, {"a", "b", "c"});
    const auto second = StyleProperties("name", {"a", "b", "c"}, {"a", "b", "c"});
    ASSERT_NO_THROW(ASSERT_EQ(first, second));
}