cmake_minimum_required(VERSION 3.14)
project(SettingUpGoogleTests)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


add_executable(SettingUpGoogleTests main.cpp tests/ClassName.h tests/test.cpp tests/ARR.cpp tests/ARR.h tests/RB_Tree.h)
target_link_libraries(SettingUpGoogleTests   gtest gtest_main)