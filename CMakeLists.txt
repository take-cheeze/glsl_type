cmake_minimum_required(VERSION 2.6)

project(cheeze_glsl_type CXX)

find_package(Boost REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

add_executable(vec_test vec_test.cxx)
target_link_libraries(vec_test gtest gtest_main)

enable_testing()

add_test(vec_test vec_test)
