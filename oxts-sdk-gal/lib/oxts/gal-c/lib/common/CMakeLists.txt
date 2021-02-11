cmake_minimum_required(VERSION 3.1)

project(oxts-lib-common VERSION 0.1.0)
set(DESCRIPTION "OxTS library for common C/C++ functionality.")

set(OXTS_LIB_COMMON_HEADERS
    ./include/oxts/common/BasicCasts.h
    ./include/oxts/common/BasicTypes.h
    ./include/oxts/common/ccomtx.h
    ./include/oxts/common/errors.h
    ./include/oxts/common/Lib_Compiler.h
    ./include/oxts/common/Lib_Detect.h
    ./include/oxts/common/version.h
    )

set(OXTS_LIB_COMMON_SOURCES
    ./src/BasicCasts.c
    ./src/ccomtx.cpp
    ./src/errors.c
    ./src/Lib_Compiler.c
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_library(${PROJECT_NAME} 
            ${OXTS_LIB_COMMON_HEADERS}
            ${OXTS_LIB_COMMON_SOURCES}
            )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>

        $<INSTALL_INTERFACE:include>
        )


install (FILES ${OXTS_SDK_GAD_HEADERS} DESTINATION ${INCLUDE_DIRECTORY})