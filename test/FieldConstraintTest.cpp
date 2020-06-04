#include <gtest/gtest.h>
#include <FieldConstraint.hpp>

TEST(FieldConstraintTests, constructionTest) {
    std::regex word("(\\w+)");
    std::regex long_word("(\\w{7,})");
    ASSERT_NO_THROW(FieldConstraint("a name", word));
    ASSERT_NO_THROW(FieldConstraint("another name", long_word));
}