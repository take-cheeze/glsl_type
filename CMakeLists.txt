cmake_minimum_required(VERSION 2.6)

project(cheeze_glsl_type CXX)

# set output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(Boost REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

# test
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_program(GTEST_CONFIG "gtest-config")
if(NOT GTEST_CONFIG)
  message(SEND_ERROR "gtest-config not found")
else()
  message(STATUS "gtest-config found")
endif()
exec_program(${GTEST_CONFIG} ARGS "--cppflags --cxxflags" OUTPUT_VARIABLE GTEST_CXX_FLAGS)
list(APPEND CMAKE_CXX_FLAGS ${GTEST_CXX_FLAGS})
exec_program(${GTEST_CONFIG} ARGS "--ldflags --libs" OUTPUT_VARIABLE GTEST_LINK_FLAGS)
list(APPEND LINK_FLAGS ${GTEST_LINK_FLAGS})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test tests)
foreach(i ${tests})
  string(REGEX REPLACE ".*/\([a-z_]*\).cxx" "\\1" exe ${i})
  add_executable(test_${exe} ${i})
  target_link_libraries(test_${exe} ${GTEST_BOTH_LIBRARIES})
  add_test(NAME ${exe} COMMAND ${EXECUTABLE_OUTPUT_PATH}/test_${exe})
endforeach()
