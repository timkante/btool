#include <gtest/gtest.h>
#include <FieldConstraint.hpp>
#include <Field.hpp>

TEST(FieldConstraintTests, constructionTest) {
    std::regex word("(\\w+)");
    std::regex long_word("(\\w{7,})");
    ASSERT_NO_THROW(FieldConstraint("a name", word));
    ASSERT_NO_THROW(FieldConstraint("another name", long_word));

    FieldConstraint field_constraint = FieldConstraint("a name", word);
    ASSERT_NO_THROW(field_constraint.matchesConstraint("a name", Field("a name", "a value", true)));
    ASSERT_NO_THROW(field_constraint.matchesConstraint("a name", Field("a name", "a value", false)));

    ASSERT_NO_THROW((field_constraint.matchesRegex("a name", word)));
}

