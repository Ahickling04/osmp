cmake_minimum_required(VERSION 3.15)

# Project name and version
project(OSMP VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to build shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# ============================================
# Source Files
# ============================================
set(SOURCES
    src/main.cpp
    src/fileHandling.cpp
)

set(HEADERS
    src/fileHandling.h
    # Add your header files here
)

# ============================================
# Executable
# ============================================
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ============================================
# Custom Library Paths
# ============================================
# Add your custom library directories here
set(CUSTOM_LIBRARY_DIRS
    # Example: ${CMAKE_CURRENT_SOURCE_DIR}/external/lib
    # Example: /path/to/your/libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/include/toml++
)

# Add your custom include directories here
set(CUSTOM_INCLUDE_DIRS
    # Example: ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    # Example: /path/to/your/includes
)

# Apply custom paths if specified
if(CUSTOM_LIBRARY_DIRS)
    link_directories(${CUSTOM_LIBRARY_DIRS})
endif()

if(CUSTOM_INCLUDE_DIRS)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CUSTOM_INCLUDE_DIRS})
endif()

# ============================================
# Link Libraries
# ============================================
# Add your custom libraries here
set(CUSTOM_LIBRARIES
    # Example: mylib
    # Example: pthread
    # Example: ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libcustom.a
    #${CMAKE_CURRENT_SOURCE_DIR}/include/toml++/toml.h
)

if(CUSTOM_LIBRARIES)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CUSTOM_LIBRARIES}, ${wxWidgets_LIBRARIES})
endif()
#target_link_libraries(myapp ${wxWidgets_LIBRARIES})
# ============================================
# Platform-Specific Settings
# ============================================
if(WIN32)
    # Windows-specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WINDOWS)
    # Add Windows-specific libraries
    # target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
    find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
elseif(APPLE)
    # macOS-specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_MACOS)
    # Add macOS frameworks if needed
    # find_library(COCOA_LIBRARY Cocoa)
    # target_link_libraries(${PROJECT_NAME} PRIVATE ${COCOA_LIBRARY})
elseif(UNIX)
    # Linux-specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_LINUX)
    # Add Linux-specific libraries
    # target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)
endif()

# ============================================
# Compiler Warnings
# ============================================
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ============================================
# Build Type Configuration
# ============================================
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
endif()

# ============================================
# Find and Link Common Packages (Optional)
# ============================================
# Uncomment these to use common packages

# Example: OpenGL
# find_package(OpenGL REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# Example: Threads
# find_package(Threads REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Example: Boost
# find_package(Boost REQUIRED COMPONENTS system filesystem)
# target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system Boost::filesystem)

# ============================================
# Installation
# ============================================
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

# ============================================
# Print Configuration Summary
# ============================================
message(STATUS "")
message(STATUS "Configuration Summary:")
message(STATUS "  Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "")