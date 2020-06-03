cmake_minimum_required(VERSION 3.15)
project(bibParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_DEBUG 1)
find_package(Boost 1.50 REQUIRED COMPONENTS system filesystem)

option(SONAR "Build all profiling-files." OFF)

if (SONAR)
    add_compile_options(-Wall -Wextra -Wpedantic -fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
)

set(MAIN_SOURCES
        src/TranslationTable.cpp
        src/Field.cpp
        src/fieldConstraint.cpp
        src/styleProperties.cpp)

set(MAIN_HEADERS
        src/TranslationTable.hpp
        src/Field.hpp
        src/fieldConstraint.h
        src/styleProperties.h)

add_library(${PROJECT_NAME} STATIC ${MAIN_SOURCES} ${MAIN_HEADERS})

if(Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem)
endif(Boost_FOUND)

target_include_directories(${PROJECT_NAME} PUBLIC src)

enable_testing()

add_subdirectory(dependencies/googletest)
add_subdirectory(test)

add_executable(${PROJECT_NAME}Run main.cpp)
target_link_libraries(${PROJECT_NAME}Run PUBLIC ${PROJECT_NAME})