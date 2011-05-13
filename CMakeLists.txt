cmake_minimum_required(VERSION 2.6)

project(cheeze_glsl_type CXX)

# set output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(Boost REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

# test
enable_testing()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test tests)
foreach(src ${tests})
  string(REGEX REPLACE ".*/\([a-z_]*\).cxx" "\\1" exe ${src})
  add_executable(test_${exe} ${src})
  target_link_libraries(test_${exe} gtest gtest_main)
  add_test(NAME ${exe} COMMAND ${EXECUTABLE_OUTPUT_PATH}/test_${exe})
endforeach()
