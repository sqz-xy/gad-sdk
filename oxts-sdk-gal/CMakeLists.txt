cmake_minimum_required(VERSION 3.1)

project(oxts-sdk-gad VERSION 0.1.0)
set(DESCRIPTION "Generic Aiding library for the OxTS SDK in C++.")

set(OXTS_SDK_GAD_CPP_HEADERS
    ./include/oxts/gal-cpp/gad.h
    )


set(OXTS_SDK_GAD_CPP_SOURCES
    ./src/gal-cpp/gad.cpp
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_library(${PROJECT_NAME} 
            ${OXTS_SDK_GAD_CPP_HEADERS}
            ${OXTS_SDK_GAD_CPP_SOURCES}
            )

add_subdirectory(lib/oxts/gal-c)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC oxts-lib-gal-c)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )


# install (FILES ${OXTS_SDK_GAD_CPP_HEADERS} DESTINATION ${INCLUDE_DIRECTORY})