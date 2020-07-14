
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
    const auto file = R"(some
non

at_ characters)"s;

    ParserState *state = new GlobalParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            state = state->handleCharacter(c);
        }
    }());
    ASSERT_TRUE(isType<GlobalParserState>(state));

    delete state;
}

TEST_F(ParserStateTest, globalStateSwitchesToStyleAtAt) {
    const auto file = R"(some@)"s;
    ParserState *state = new GlobalParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            state = state->handleCharacter(c);
        }
    }());
    ASSERT_FALSE(isType<GlobalParserState>(state));
    ASSERT_TRUE(isType<StyleParserState>(state));

    delete state;
}

TEST_F(ParserStateTest, styleParserStateFailsWithWhitespace) {
    const auto file = R"(here are spaces)"s;
    ParserState *state = new StyleParserState{context, result};

    ASSERT_ANY_THROW([&]() {
        for (const auto c : file) {
            state = state->handleCharacter(c);
        }
    }());

    delete state;
}

TEST_F(ParserStateTest, styleParserStateDontFailOnCorrectStyle) {
    const auto file = R"(thisIsAValidStyle)"s;
    ParserState *state = new StyleParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            state = state->handleCharacter(c);
        }
    }());

    ASSERT_TRUE(isType<StyleParserState>(state));
    delete state;
}

TEST_F(ParserStateTest, styleParserStateSwitchesToIdentifierStateOnBrace) {
    const auto file = R"(thisIsAValidStyle{)"s;
    ParserState *state = new StyleParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            state = state->handleCharacter(c);
        }
    }());

    ASSERT_FALSE(isType<StyleParserState>(state));
    ASSERT_TRUE(isType<IdentifierParserState>(state));
    delete state;
}

TEST_F(ParserStateTest, globalStateCanGoToIdentifierState) {
    const auto file = R"(someUselessStuff @thisIsAValidStyle{)"s;
    ParserState *state = new GlobalParserState{context, result};

    ASSERT_NO_THROW([&]() {
        for (const auto c : file) {
            state = state->handleCharacter(c);
        }
    }());

    ASSERT_TRUE(isType<IdentifierParserState>(state));
    delete state;
}