#include <gtest/gtest.h>
#include <ParserState.hpp>
#include <BibElement.hpp>
#include <ParserException.hpp>
#include <GlobalParserState.hpp>
#include <StyleParserState.hpp>
#include <KeyParserState.hpp>
#include <ValueParserState.hpp>
#include <IdentifierParserState.hpp>

using namespace std::literals::string_literals;

template<class D, class S>
bool isType(const S *src) {
  return dynamic_cast<const D *>(src) != nullptr;
}

/**
 * Tests for the Parser-States
 * @example
 * @test ParserState Fixture Tests
 */
class ParserStateFixtureTest : public ::testing::Test {
 protected:
  ParserContext context = ParserContext(""s);
  std::vector<BibElement> result;

  void SetUp() override {
    context = ParserContext("fixtureFile.bib"s);
    result = {};
  }
};

TEST_F(ParserStateFixtureTest, globalStateIgnoresEverythingButAt) {
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

TEST_F(ParserStateFixtureTest, globalStateSwitchesToStyleAtAt) {
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

TEST_F(ParserStateFixtureTest, styleParserStateFailsWithWhitespace) {
  const auto file = R"(here are spaces)"s;
  ParserState *state = new StyleParserState{context, result};

  ASSERT_ANY_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  delete state;
}

TEST_F(ParserStateFixtureTest, styleParserStateDontFailOnCorrectStyle) {
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

TEST_F(ParserStateFixtureTest, styleParserStateSwitchesToIdentifierStateOnBrace) {
  const auto file = R"(thisIsAValidStyle{)"s;
  ParserState *state = new StyleParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front().style, "thisIsAValidStyle"s);
  ASSERT_FALSE(isType<StyleParserState>(state));
  ASSERT_TRUE(isType<IdentifierParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, globalStateCanGoToIdentifierState) {
  const auto file = R"(someUselessStuff @thisIsAValidStyle{)"s;
  ParserState *state = new GlobalParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front().style, "thisIsAValidStyle"s);
  ASSERT_TRUE(isType<IdentifierParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, identifierCantContainWhitespace) {
  const auto file = R"(identifier with whitespace)"s;
  ParserState *state = new IdentifierParserState{context, result};

  ASSERT_ANY_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  delete state;
}

TEST_F(ParserStateFixtureTest, identifierEndsAtCommaAndIsSaved) {
  const auto file = R"(identifier,)"s;
  result.push_back({"", "", {}});
  ParserState *state = new IdentifierParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front().id, "identifier"s);
  ASSERT_TRUE(isType<KeyParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, keyStateIgnoresTrailingWhitespace) {
  const auto file = R"(    this is a key    )"s;
  ParserState *state = new KeyParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_TRUE(isType<KeyParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, keyStateExitsOnEqualSignAndTrimsKey) {
  const auto file = R"(    this is a key    =)"s;
  result.push_back({"", "", {}});
  ParserState *state = new KeyParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front().attributes.front().name, "this is a key"s);
  ASSERT_TRUE(isType<ValueParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, valueStateTrimsWhitespaceAndExitsToKeyState) {
  const auto file = R"(    this is a key    ,)"s;
  result.push_back({"", "", {{"", ""}}});
  ParserState *state = new ValueParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front().attributes.front().value, "this is a key"s);
  ASSERT_TRUE(isType<KeyParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, valueStateExitsOnCommaAndMatchingBraces) {
  const auto file = R"(   {{   this, is a key  }}  ,)"s;
  result.push_back({"", "", {{"", ""}}});
  ParserState *state = new ValueParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front().attributes.front().value, "{{   this, is a key  }}"s);
  ASSERT_TRUE(isType<KeyParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, keyStateExitsToGlobalStateOnClosingBrace) {
  const auto file = R"(} )"s;
  ParserState *state = new KeyParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_TRUE(isType<GlobalParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, valueStateExitsToGlobalStateOnClosingBrace) {
  const auto file = R"(} )"s;
  result.push_back({"", "", {{"", ""}}});
  ParserState *state = new ValueParserState{context, result};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_TRUE(isType<GlobalParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, canParseFullElement) {
  const auto file = R"(@inproceedings{Feigenspan11,
    author = {Janet Feigenspan},
    title = {{Program Comprehension of Feature-Oriented Software Development}},
    booktitle = {International Doctoral Symposium on Empirical Software Engineering (IDoESE)},
    year = {2011},
    month = Sep,
    url = {http://wwwiti.cs.uni-magdeburg.de/iti_db/publikationen/ps/auto/Feigenspan11.pdf}
})"s;
  ParserState *state = new GlobalParserState{context, result};

  BibElement expected{"Feigenspan11", "inproceedings", {
      {"author", "{Janet Feigenspan}"},
      {"title", "{{Program Comprehension of Feature-Oriented Software Development}}"},
      {"booktitle", "{International Doctoral Symposium on Empirical Software Engineering (IDoESE)}"},
      {"year", "{2011}"},
      {"month", "Sep"},
      {"url", "{http://wwwiti.cs.uni-magdeburg.de/iti_db/publikationen/ps/auto/Feigenspan11.pdf}"}
  }};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result.front(), expected);
  ASSERT_TRUE(isType<GlobalParserState>(state));
  delete state;
}

TEST_F(ParserStateFixtureTest, canParseMultipleElements) {
  const auto file = R"(
@inproceedings{Feigenspan11,
    author = {Janet Feigenspan},
    title = {{Program Comprehension of Feature-Oriented Software Development}},
    booktitle = {International Doctoral Symposium on Empirical Software Engineering (IDoESE)},
    year = {2011},
    month = Sep,
    url = {http://wwwiti.cs.uni-magdeburg.de/iti_db/publikationen/ps/auto/Feigenspan11.pdf}
}
@article{FeigenspanSiFr11,
    author = {Janet Feigenspan and Norbert Siegmund and Jana Fruth},
    title = {{On the Role of Program Comprehension in Embedded Systems}},
    journal = {Softwaretechnik-Trends},
    year = {2011},
    volume = {31},
    number = {2},
    month = May,
    url = {http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}
})"s;
  ParserState *state = new GlobalParserState{context, result};

  std::vector<BibElement> expected{
      {"Feigenspan11", "inproceedings", {
          {"author", "{Janet Feigenspan}"},
          {"title", "{{Program Comprehension of Feature-Oriented Software Development}}"},
          {"booktitle", "{International Doctoral Symposium on Empirical Software Engineering (IDoESE)}"},
          {"year", "{2011}"},
          {"month", "Sep"},
          {"url", "{http://wwwiti.cs.uni-magdeburg.de/iti_db/publikationen/ps/auto/Feigenspan11.pdf}"}
      }}, {"FeigenspanSiFr11", "article", {
          {"author", "{Janet Feigenspan and Norbert Siegmund and Jana Fruth}"},
          {"title", "{{On the Role of Program Comprehension in Embedded Systems}}"},
          {"journal", "{Softwaretechnik-Trends}"},
          {"year", "{2011}"},
          {"volume", "{31}"},
          {"number", "{2}"},
          {"month", "May"},
          {"url",
           "{http://www.uni-koblenz-landau.de/koblenz/fb4/institute/uebergreifend/sre/conferences/wsr/wsr2011/wsr2011_proceedings.pdf}"}
      }}};

  ASSERT_NO_THROW([&]() {
    for (const auto c : file) {
      state = state->handleCharacter(c);
    }
  }());

  ASSERT_EQ(result, expected);
  delete state;
}
