cmake_minimum_required(VERSION 3.15)
project(bibParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_DEBUG 1)
find_package(Boost 1.50 REQUIRED COMPONENTS system filesystem)

option(SONAR "Build all profiling-files." OFF)
add_compile_options(-std=c++17)

if (SONAR)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(UNIX OR APPLE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
)

set(MAIN_SOURCES
        src/TranslationTable.cpp
        src/Field.cpp
        src/BibElement.cpp
        src/StyleProperties.cpp
        src/Parser.cpp
        src/AbstractParserState.cpp
        src/ParserException.cpp
        src/StyleParserState.cpp
        src/GlobalParserState.cpp
        src/IdentifierParserState.cpp
        src/KeyParserState.cpp
        src/ValueParserState.cpp
        src/ParserContext.cpp
        src/AbstractGenerator.cpp
        src/GeneratorException.cpp
        src/HtmlGenerator.cpp)

set(MAIN_HEADERS
        src/TranslationTable.hpp
        src/Field.hpp
        src/BibElement.hpp
        src/StyleProperties.hpp
        src/Parser.hpp
        src/AbstractParserState.hpp
        src/ParserState.hpp
        src/ParserContext.hpp
        src/ParserException.hpp
        src/StyleParserState.hpp
        src/GlobalParserState.hpp
        src/IdentifierParserState.hpp
        src/KeyParserState.hpp
        src/ValueParserState.hpp
        src/AbstractGenerator.hpp
        src/Generator.hpp
        src/GeneratorException.hpp
        src/HtmlGenerator.hpp)

add_library(${PROJECT_NAME} STATIC ${MAIN_SOURCES} ${MAIN_HEADERS})

add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/googletest)

message(STATUS "Boost version: ${Boost_VERSION}")
target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC src)

enable_testing()
add_subdirectory(test)

add_executable(${PROJECT_NAME}Run main.cpp)
target_link_libraries(${PROJECT_NAME}Run PUBLIC ${PROJECT_NAME})