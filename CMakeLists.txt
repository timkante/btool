cmake_minimum_required(VERSION 3.15)
project(bibParser)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include_directories(
        "${CMAKE_SOURCE_DIR}/include"
)

set(MAIN_SOURCES
        src/main/add.cpp)

set(MAIN_HEADERS
        include/add.hpp)

add_library(${PROJECT_NAME} SHARED ${MAIN_SOURCES} ${MAIN_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)

enable_testing()

add_subdirectory(dependencies/googletest)
add_subdirectory(src/test)

add_executable(${PROJECT_NAME}Run main.cpp)
target_link_libraries(${PROJECT_NAME}Run PUBLIC ${PROJECT_NAME})