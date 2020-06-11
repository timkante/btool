#include <gtest/gtest.h>
#include <StyleProperties.hpp>
#include <FieldConstraint.hpp>
#include <vector>

TEST(StylePropertiesTests, noArgConstructionTest){
    ASSERT_NO_THROW(StyleProperties());
}

TEST(StylePropertiesTests, constructionTest) {
    std::vector<FieldConstraint> required = {
            FieldConstraint("first name", std::regex(R"(\w+)")),
            FieldConstraint("second name", std::regex(R"(\w{7,})"))};
    std::vector<FieldConstraint> optional = {
            FieldConstraint("first name", std::regex(R"(\w+)")),
            FieldConstraint("second name", std::regex(R"(\w{7,})"))};
    ASSERT_NO_THROW(StyleProperties("a name", required, optional));
}
