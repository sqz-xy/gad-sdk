cmake_minimum_required(VERSION 3.1)

project(oxts-lib-gal-c VERSION 0.1.0)
set(DESCRIPTION "OxTS library for Generic Aiding functionality in C.")

set(OXTS_LIB_GAL_C_HEADERS
    ./include/oxts/gal-c/gad_decode.h
    ./include/oxts/gal-c/gad_defines.h
    ./include/oxts/gal-c/gad_encode.h
    ./include/oxts/gal-c/gad_include_all.h
    ./include/oxts/gal-c/gad_struct.h
    )

set(OXTS_LIB_GAL_C_SOURCES
    ./src/gad_decode.c
    ./src/gad_encode.c
    ./src/gad_struct.c
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)


add_library(${PROJECT_NAME} 
            ${OXTS_LIB_GAL_C_HEADERS}
            ${OXTS_LIB_GAL_C_SOURCES}
            )

add_subdirectory(lib/common)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC oxts-lib-common)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>

        $<INSTALL_INTERFACE:include>
        )


