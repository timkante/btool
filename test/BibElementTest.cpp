#include <gtest/gtest.h>
#include <BibElement.hpp>

TEST(BibelementTests, constructionTest) {
    std::vector<Field> fields = {
        Field("name", "value", false),
        Field("another name", "another value", true)
    };
    ASSERT_NO_THROW(BibElement("an id", "a style", fields));
    ASSERT_NO_THROW(BibElement("another id", "another style", fields));
}

