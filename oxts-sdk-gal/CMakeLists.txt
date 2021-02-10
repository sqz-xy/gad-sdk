cmake_minimum_required(VERSION 3.1)

project(oxts-sdk-gad)
set(DESCRIPTION "Generic Aiding library for the OxTS SDK C++.")

set(OXTS_SDK_GAD_HEADERS
    #./include/oxts/gal/decode_genaid.h
    ./include/oxts/gal/gad_defines.h
    #./include/oxts/gal/gad_encode.h
    #./include/oxts/gal/gad_include_all.h
    ./include/oxts/gal/gad_struct.h
    )

set(OXTS_SDK_LIB_HEADERS
    ./include/oxts/lib/BasicTypes.h)

set(OXTS_SDK_GAD_SOURCES
    #./src/gal/decode_genaid.c
    #./src/gal/gad_encode.c
    ./src/gal/gad_struct.c
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_library(${PROJECT_NAME} 
            ${OXTS_SDK_GAD_HEADERS}
            ${OXTS_SDK_LIB_HEADERS}
            ${OXTS_SDK_GAD_SOURCES}
            )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>

        $<INSTALL_INTERFACE:include>
        )


install (FILES ${OXTS_SDK_GAD_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/oxts)