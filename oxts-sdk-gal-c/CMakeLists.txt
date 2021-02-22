cmake_minimum_required(VERSION 3.1)

project(oxts-sdk-gal-c VERSION 0.1.0)
set(DESCRIPTION "OxTS library for base Generic Aiding API in C.")

find_package(oxts-sdk-core REQUIRED)

set(OXTS_GAL_C_HEADERS
    ./include/oxts/gal-c/gad_decode.h
    ./include/oxts/gal-c/gad_defines.h
    ./include/oxts/gal-c/gad_encode.h
    ./include/oxts/gal-c/gad_include_all.h
    ./include/oxts/gal-c/gad_struct.h
    )

set(OXTS_GAL_C_SOURCES
    ./src/gad_decode.c
    ./src/gad_encode.c
    ./src/gad_struct.c
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
    PRIVATE ${oxts-sdk-core_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        oxts-sdk-core
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE GAL_C_LIBRARY)

install (FILES ${OXTS_GAL_C_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/oxts/gal-c)

export_config()

# TODO: Add testing
# if(OXTS_SDK_ENABLE_TESTING)
#     add_subdirectory(tests)
# endif()