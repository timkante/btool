#include <gtest/gtest.h>
#include <BibElement.hpp>

TEST(BibelementTests, constructionTest) {

    Field f1 = Field("name","value",false);
    Field f2 = Field("another name","another value",true);

    std::vector<Field> fields = {f1,f2};

    ASSERT_NO_THROW(BibElement("an id", "a style", fields));
    ASSERT_NO_THROW(BibElement("another id", "another style", fields));
}

