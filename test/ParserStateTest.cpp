
#include <gtest/gtest.h>
#include <ParserState.hpp>
#include <ParserException.hpp>
#include <GlobalParserState.hpp>
#include <StyleParserState.hpp>
#include <IdentifierParserState.hpp>

using namespace std::literals::string_literals;

template<class D, class S>
bool isType(const S *src) {
    return dynamic_cast<const D *>(src) != nullptr;
}

class ParserStateTest : public ::testing::Test {
protected:
    ParserContext context = ParserContext(""s);
    std::vector<BibElement> result;

    void SetUp() override {
        context = ParserContext("fixtureFile.bib"s);
        result = {};
    }
};

TEST_F(ParserStateTest, globalStateIgnoresEverythingButAt) {
    auto file = R"(some
non

at_ characters)"s;

    ParserState *globalState = new GlobalParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            globalState = globalState->handleCharacter(c);
        }
    }());
    ASSERT_TRUE(isType<GlobalParserState>(globalState));

    delete globalState;
}

TEST_F(ParserStateTest, globalStateSwitchesToStyleAtAt) {
    auto file = R"(some@)"s;
    ParserState *globalState = new GlobalParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            globalState = globalState->handleCharacter(c);
        }
    }());
    ASSERT_FALSE(isType<GlobalParserState>(globalState));
    ASSERT_TRUE(isType<StyleParserState>(globalState));

    delete globalState;
}

TEST_F(ParserStateTest, styleParserStateFailsWithWhitespace) {
    auto file = R"(here are spaces)"s;
    ParserState *styleState = new StyleParserState{context, result};

    ASSERT_ANY_THROW([&]() {
        for (const auto c : file) {
            styleState = styleState->handleCharacter(c);
        }
    }());

    delete styleState;
}

TEST_F(ParserStateTest, styleParserStateDontFailOnCorrectStyle) {
    auto file = R"(thisIsAValidStyle)"s;
    ParserState *styleState = new StyleParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            styleState = styleState->handleCharacter(c);
        }
    }());

    ASSERT_TRUE(isType<StyleParserState>(styleState));
    delete styleState;
}

TEST_F(ParserStateTest, styleParserStateSwitchesToIdentifierStateOnBrace) {
    auto file = R"(thisIsAValidStyle{)"s;
    ParserState *styleState = new StyleParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            styleState = styleState->handleCharacter(c);
        }
    }());

    ASSERT_FALSE(isType<StyleParserState>(styleState));
    ASSERT_TRUE(isType<IdentifierParserState>(styleState));
    delete styleState;
}

TEST_F(ParserStateTest, globalStateCanGoToIdentifierState) {
    auto file = R"(someUselessStuff @thisIsAValidStyle{)"s;
    ParserState *styleState = new GlobalParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            styleState = styleState->handleCharacter(c);
        }
    }());

    ASSERT_TRUE(isType<IdentifierParserState>(styleState));
    delete styleState;
}