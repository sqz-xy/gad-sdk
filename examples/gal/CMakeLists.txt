cmake_minimum_required(VERSION 3.1)

# C++ Standard version. Minimum supported is C++11.
set(CMAKE_CXX_STANDARD 11)

project(oxts-sdk-examples-gal VERSION 0.1.0)

find_package(oxts-sdk-gal-cpp REQUIRED)


# Example 1 - Static Aiding
set(OXTS_SDK_EXAMPLES_GAL_STATIC static-aiding-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./static-aiding.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
# Example 2 - Static Aiding No Boost
set(OXTS_SDK_EXAMPLES_GAL_STATIC_NO_BOOST static-aiding-no-boost-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC_NO_BOOST} ./static-aiding-no-boost.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC_NO_BOOST} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
