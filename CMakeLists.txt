cmake_minimum_required(VERSION 3.15)
project(bibParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SONAR "Build all profiling-files." OFF)

if (SONAR)
    add_compile_options(-Wall -Wextra -Wpedantic -fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
)

set(MAIN_SOURCES
        src/add.cpp)

set(MAIN_HEADERS
        src/add.hpp)

add_library(${PROJECT_NAME} STATIC ${MAIN_SOURCES} ${MAIN_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC src)

enable_testing()

add_subdirectory(dependencies/googletest)
add_subdirectory(test)

add_executable(${PROJECT_NAME}Run main.cpp)
target_link_libraries(${PROJECT_NAME}Run PUBLIC ${PROJECT_NAME})