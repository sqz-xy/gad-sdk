cmake_minimum_required(VERSION 3.10)

# C++ Standard version. Minimum supported is C++11.
set(CMAKE_CXX_STANDARD 11)
# Explicitly set policy for _DIR behaviour
cmake_policy(SET CMP0074 NEW)

project(oxts-sdk-tests VERSION 0.1.0)

find_package(Boost REQUIRED )

add_compile_definitions(OXTS_MISRA_COMPLIANT=1)

set(OXTS_SDK_UNIT_TESTS unit_tests)
add_executable(${OXTS_SDK_UNIT_TESTS} ./gad_test.cpp)
target_link_libraries(${OXTS_SDK_UNIT_TESTS} 
    PUBLIC 
        oxts-sdk-gal-c
        oxts-sdk-gal-cpp
)

include_directories(${Boost_INCLUDE_DIR})


target_link_libraries(${OXTS_SDK_UNIT_TESTS} PUBLIC ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

