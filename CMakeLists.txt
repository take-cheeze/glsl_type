cmake_minimum_required(VERSION 2.6)

project(cheeze_glsl_type CXX)

# set output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

foreach(i Boost GLUT Threads GTest)
  find_package(${i} REQUIRED)
  include_directories(${${i}_INCLUDE_DIRS} ${${i}_INCLUDE_DIR})
endforeach()

# test
enable_testing()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test tests)
foreach(i ${tests})
  string(REGEX REPLACE ".*/\([a-z_]*\).cxx" "\\1" exe ${i})
  add_executable(test_${exe} ${i})
  target_link_libraries(test_${exe}
    ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
  add_test(NAME ${exe} COMMAND ${EXECUTABLE_OUTPUT_PATH}/test_${exe})
endforeach()

# OpenGL
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/example examples)
#foreach(i ${examples})
#  string(REGEX REPLACE ".*/\([a-z_]*\).cxx" "\\1" exe ${i})
#  add_executable(example_${exe} MACOSX_BUNDLE ${i})
#  target_link_libraries(example_${exe} ${GLUT_LIBRARIES})
#endforeach()
