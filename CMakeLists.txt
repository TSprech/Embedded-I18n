cmake_minimum_required(VERSION 3.20)
project(Embedded-I18n)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -fconcepts)

add_link_options(--coverage) # Required to generate gcov data
add_compile_options(--coverage) # Required to generate gcov data

include_directories(include)

set(SOURCES)
set(TEST_SOURCES test/Test_GetString.cpp)
add_executable(Embedded-I18n main.cpp ${SOURCES} ${TEST_SOURCES})

add_subdirectory(test/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(Embedded-I18n gtest gtest_main)
