cmake_minimum_required(VERSION 3.1)

project(oxts-sdk VERSION 0.1.0)

# C++ Standard version. Minimum supported is C++11.
set(CMAKE_CXX_STANDARD 11)

option(OXTS_SDK_BUILD_DOCS "Build SDK documentation" OFF)
option(OXTS_SDK_BUILD_EXAMPLES "Enable examples targets" OFF) # NOT YET IMPLEMENTED

# Add modules
add_subdirectory(oxts-sdk-core)
add_subdirectory(oxts-sdk-gal-c) 
add_subdirectory(oxts-sdk-gal-cpp) 
#add_subdirectory(oxts-sdk-ncomdecoder)

if (OXTS_SDK_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (OXTS_SDK_BUILD_DOCS)
    add_subdirectory(docs)
endif()

