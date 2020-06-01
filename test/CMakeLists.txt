set(SuiteName bibParserTests)

set(TEST_SOURCES
        TranslationTableTest.cpp)

add_executable(${SuiteName} ${TEST_SOURCES})

target_link_libraries(${SuiteName} PUBLIC
        gtest_main
        ${PROJECT_NAME}
        ${Boost_LIBRARIES})

add_test(NAME ${SuiteName} COMMAND ${SuiteName})