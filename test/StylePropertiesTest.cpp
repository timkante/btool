#include <gtest/gtest.h>
#include <StyleProperties.hpp>
#include <FieldConstraint.hpp>
#include <vector>


TEST(StylePropertiesTests, constructionTest) {
    std::vector<FieldConstraint> required = {
            FieldConstraint("first name", std::regex("(\\w+)")),
            FieldConstraint("second name", std::regex("(\\w{7,})"))};
    std::vector<FieldConstraint> optional = {
            FieldConstraint("first name", std::regex("(\\w+)")),
            FieldConstraint("second name", std::regex("(\\w{7,})"))};
    ASSERT_NO_THROW(StyleProperties("a name", required, optional));
}
