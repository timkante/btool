#include <gtest/gtest.h>
#include <BibElement.hpp>
#include <StyleProperties.hpp>

struct BibElementFixtureTest : public ::testing::Test {
    const StyleProperties props;
    const BibElement completeElement;
    const BibElement incompleteElement;

    BibElementFixtureTest()
            : props{"style", {"reqField", "reqField2"}, {"optField"}},
              completeElement{"id",
                              "style",
                              {
                                      {"reqField", "a value"},
                                      {"someOtherField", "a value"},
                                      {"reqField2", "a value"}
                              }},
              incompleteElement{"id",
                                "style",
                                {
                                        {"reqField2", "value"}
                                }} {}

};

TEST_F(BibElementFixtureTest, completeElementTest) {
    ASSERT_TRUE(completeElement.isCompliantTo(props));
}

TEST_F(BibElementFixtureTest, incompleteElementTest) {
    ASSERT_FALSE(incompleteElement.isCompliantTo(props));
}

TEST(BibelementTests, constructionTest) {
    std::vector<Field> fields = {
            Field("name", "value"),
            Field("another name", "another value")
    };
    ASSERT_NO_THROW(BibElement("an id", "a style", fields));
    ASSERT_NO_THROW(BibElement("another id", "another style", fields));
}
