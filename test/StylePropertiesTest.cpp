#include <gtest/gtest.h>
#include <StyleProperties.hpp>
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
