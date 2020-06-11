#include <gtest/gtest.h>
#include <FieldConstraint.hpp>
#include <Field.hpp>

TEST(FieldConstraintTests, constructionTest) {
    ASSERT_NO_THROW(FieldConstraint("a word", std::regex(R"(\w+)")));
    ASSERT_NO_THROW(FieldConstraint("a long word", std::regex(R"(\w{7,})")));
}

TEST(FieldConstraintTests, fieldMatchingTest) {
    auto wordConstraint = FieldConstraint("a word", std::regex(R"(\w+)"));
    auto longWordConstraint = FieldConstraint("a long word", std::regex(R"(\w{7,})"));

    auto wordField = Field("a word", "word", true);
    auto longWordField = Field("a long word", "thisIsAReallyLongWord", true);

    ASSERT_TRUE(wordConstraint.matchedBy(wordField));
    ASSERT_FALSE(wordConstraint.matchedBy(longWordField));
    ASSERT_TRUE(longWordConstraint.matchedBy(longWordField));
    ASSERT_FALSE(longWordConstraint.matchedBy(wordField));
}
