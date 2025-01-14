# 'test' is the subproject name
project(test)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(../src  ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run test1.cpp)
target_link_libraries(Google_Tests_run src)
target_link_libraries(Google_Tests_run gtest gtest_main)