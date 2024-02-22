cmake_minimum_required(VERSION 3.10)

project(oxts-sdk-gal-c VERSION 0.1.0)
set(DESCRIPTION "OxTS library for base Generic Aiding API in C.")

set(OXTS_GAL_C_HEADERS
    ./include/oxts/gal-c/BasicCasts.h
    ./include/oxts/gal-c/BasicTypes.h
    ./include/oxts/gal-c/ccomtx.h
    ./include/oxts/gal-c/errors.h
    ./include/oxts/gal-c/gad_decode.h
    ./include/oxts/gal-c/gad_defines.h
    ./include/oxts/gal-c/gad_encode_bin.h
    ./include/oxts/gal-c/gad_encode_csv.h
    ./include/oxts/gal-c/gad_include_all.h
    ./include/oxts/gal-c/gad_struct.h
    ./include/oxts/gal-c/Lib_Compiler.h
    ./include/oxts/gal-c/Lib_Detect.h
    ./include/oxts/gal-c/oxts_misra.h
    ./include/oxts/gal-c/oxts_pointers.h
    ./include/oxts/gal-c/version.h
    )

set(OXTS_GAL_C_SOURCES
    ./src/BasicCasts.c
    ./src/ccomtx.c
    ./src/errors.c
    ./src/gad_decode.c
    ./src/gad_encode_bin.c
    ./src/gad_encode_csv.c
    ./src/gad_struct.c
    ./src/Lib_Compiler.c
    ./src/oxts_pointers.c
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

####
# Create targets
add_library(${PROJECT_NAME} #STATIC
    ${OXTS_GAL_C_HEADERS}
    ${OXTS_GAL_C_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


target_compile_definitions(${PROJECT_NAME}
    PRIVATE GAL_C_LIBRARY)

install (FILES ${OXTS_GAL_C_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/oxts/gal-c)
export_config()
