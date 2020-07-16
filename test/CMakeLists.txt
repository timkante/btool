set(SuiteName bibParserTests)

set(TEST_SOURCES
        TranslationTableFixtureTest.cpp
        FieldTest.cpp
        StylePropertiesTest.cpp
        BibElementFixtureTest.cpp
        ParserFixtureTest.cpp
        ParserStateFixtureTest.cpp GeneratorFixtureTest.cpp)

add_executable(${SuiteName} ${TEST_SOURCES})

target_link_libraries(${SuiteName} PUBLIC
        gtest_main
        ${PROJECT_NAME})

add_test(NAME ${SuiteName} COMMAND ${SuiteName})
