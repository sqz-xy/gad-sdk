cmake_minimum_required(VERSION 3.10)

project(oxts_sdk)

find_package(oxts-sdk-gal-cpp REQUIRED)

add_subdirectory(pybind11)

pybind11_add_module(oxts_sdk gal-py-bindings.cpp)

target_link_libraries(oxts_sdk PUBLIC oxts-sdk-gal-cpp)