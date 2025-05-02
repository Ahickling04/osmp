add_library(testlib lib.cpp)
add_library(fileHandlib fileHandling.cpp)

target_include_directories(fileHandlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(testlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
