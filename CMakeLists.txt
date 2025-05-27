cmake_minimum_required(VERSION 4.0.1)
project(osmp)

add_executable(${PROJECT_NAME} src/main.cpp src/fileHandling.cpp)
#add_library(testlib include/lib.cpp)

target_link_libraries(${PROJECT_NAME} testlib)

add_subdirectory(include)
