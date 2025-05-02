cmake_minimum_required(VERSION 4.0.1)
project(osmp)

find_package(fmt)

add_executable(${PROJECT_NAME} src/main.cpp)
#add_library(testlib include/lib.cpp)

target_link_libraries(${PROJECT_NAME} fileHandlib testlib fmt::fmt)

add_subdirectory(include)
