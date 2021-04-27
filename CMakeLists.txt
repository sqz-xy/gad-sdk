cmake_minimum_required(VERSION 3.1)

project(oxts-sdk)

# Add preprocessor definitions for the SDK version and platform name
add_definitions(-DOXTS_SDK_VERSION_STRING=\"${oxts-sdk_VERSION}\")
add_definitions(-DOXTS_SDK_VERSION_MAJOR=${oxts-sdk_VERSION_MAJOR})
add_definitions(-DOXTS_SDK_VERSION_MINOR=${oxts-sdk_VERSION_MINOR})
add_definitions(-DOXTS_SDK_VERSION_PATCH=${oxts-sdk_VERSION_PATCH})

# Building and installation options
#option(OXTS_SDK_BUILD_DOCS "Build SDK documentation." OFF)
option(OXTS_SDK_BUILD_EXAMPLES "Enable examples targets." ON) 
option(OXTS_SDK_DISABLE_BOOST "Use Boost library when building." OFF) 
# Used for cpp linting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ Standard version
set(CMAKE_CXX_STANDARD 11)

# Add cmake dir to search list
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Save root sdk folder path
get_filename_component(OXTS_SDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

# Include useful functions from /cmake. Manages dependencies between packages
# within the SDK.
include(sdk-management)

# Add the sdks
add_sdks()

# Optional extras
if (OXTS_SDK_BUILD_DOCS)
    add_subdirectory(docs)
endif()

if (OXTS_SDK_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

