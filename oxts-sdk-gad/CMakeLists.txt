cmake_minimum_required(VERSION 3.1)

project(oxts-sdk-gad)

set(OXTS_SDK_GAD_HEADERS
    #./include/oxts/decode_genaid.h
    ./include/oxts/gad_defines.h
    #./include/oxts/gad_encode.h
    #./include/oxts/gad_include_all.h
    ./include/oxts/gad_struct.h
    )

set(OXTS_SDK_GAD_SOURCES
    #./src/decode_genaid.c
    #./src/gad_encode.c
    ./src/gad_struct.c
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_library(${PROJECT_NAME} 
            ${OXTS_SDK_GAD_HEADERS}
            ${OXTS_SDK_GAD_SOURCES}
            )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>

        $<INSTALL_INTERFACE:include>
        )