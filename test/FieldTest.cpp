#include <gtest/gtest.h>
#include <Field.hpp>

TEST(FieldTests, constructionTest) {
    ASSERT_NO_THROW(Field("a name", "a value", true));
    ASSERT_NO_THROW(Field("another name", "another value", false));
}
