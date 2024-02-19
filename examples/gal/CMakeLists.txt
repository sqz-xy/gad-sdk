cmake_minimum_required(VERSION 3.10)

# C++ Standard version. Minimum supported is C++11.
set(CMAKE_CXX_STANDARD 11)
# Explicitly set policy for _DIR behaviour
cmake_policy(SET CMP0074 NEW)

project(oxts-sdk-examples-gal VERSION 0.1.0)

add_compile_definitions(OXTS_MISRA_COMPLIANT=1)

# Example 1 - My First GAD
set(OXTS_SDK_EXAMPLES_GAL_STATIC my-first-gad-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./my-first-gad.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
# Example 2 - Static Aiding
set(OXTS_SDK_EXAMPLES_GAL_STATIC static-aiding-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./static-aiding.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
# Example 3 - Zero velocity wheelspeed
set(OXTS_SDK_EXAMPLES_GAL_STATIC zv-wheelspeed-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./zero-velocity-wheelspeed.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
# Example 4 - Heading
set(OXTS_SDK_EXAMPLES_GAL_STATIC heading-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./heading.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
    
