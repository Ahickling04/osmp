add_library(testlib lib.cpp)

target_include_directories(testlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
