cmake_minimum_required(VERSION 3.24)

# 1. DEFINE PROJECT (But don't find packages yet)
project(osmp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. FETCH VCPKG AUTOMATICALLY
include(FetchContent)
FetchContent_Declare(
  vcpkg
  GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(vcpkg)

# 3. BOOTSTRAP VCPKG (Crucial: This creates the vcpkg executable if it doesn't exist)
if(WIN32)
    set(VCPKG_EXEC "${vcpkg_SOURCE_DIR}/vcpkg.exe")
    set(BOOTSTRAP_SCRIPT "${vcpkg_SOURCE_DIR}/bootstrap-vcpkg.bat")
else()
    set(VCPKG_EXEC "${vcpkg_SOURCE_DIR}/vcpkg")
    set(BOOTSTRAP_SCRIPT "${vcpkg_SOURCE_DIR}/bootstrap-vcpkg.sh")
endif()

if(NOT EXISTS "${VCPKG_EXEC}")
    message(STATUS "Bootstrapping vcpkg...")
    execute_process(COMMAND "${BOOTSTRAP_SCRIPT}" WORKING_DIRECTORY "${vcpkg_SOURCE_DIR}")
endif()

# 4. POINT CMAKE TO THE TOOLCHAIN
set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)

# 5. NOW FIND PACKAGES
# vcpkg will now intercept this and download wxWidgets automatically
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})


# 6. EXECUTABLE
file(GLOB_RECURSE SOURCES "src/*.cpp")
if(WIN32)
    set(APP_TYPE WIN32)
endif()

add_executable(${PROJECT_NAME} ${APP_TYPE} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

# 7. AUTOMATIC DLL COPY (Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
    )
endif()
