cmake_minimum_required(VERSION 3.1)


# define library version 
set(OXTS_SDK_GAL_VERSION_MAJOR 0 CACHE STRING "major version" FORCE)
set(OXTS_SDK_GAL_VERSION_MINOR 1 CACHE STRING "minor version" FORCE)
set(OXTS_SDK_GAL_VERSION_PATCH 0 CACHE STRING "patch version" FORCE)
set(OXTS_SDK_GAL_VERSION 
${OXTS_SDK_GAL_VERSION_MAJOR}.${OXTS_SDK_GAL_VERSION_MINOR}.${OXTS_SDK_GAL_VERSION_PATCH} 
CACHE STRING "version" FORCE
)

project(oxts-sdk-gal-cpp VERSION ${OXTS_SDK_GAL_VERSION})
set(DESCRIPTION "Generic Aiding library for the OxTS SDK in C++.")

find_package(oxts-sdk-gal-c CONFIG REQUIRED)
find_package(Boost REQUIRED system thread regex)


set(OXTS_GAL_CPP_HEADERS
    ./include/oxts/gal-cpp/gad.hpp
    ./include/oxts/gal-cpp/gad_encoder.hpp
    ./include/oxts/gal-cpp/gad_output.hpp
    ./include/oxts/gal-cpp/gad_output_file.hpp
    ./include/oxts/gal-cpp/gad_output_udp.hpp
    ./include/oxts/gal-cpp/gad_handler.hpp
    ./include/oxts/gal-cpp/udp_server_client.h
)
    
set(OXTS_GAL_CPP_SOURCES
    ./src/gal-cpp/gad.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${Boost_INCLUDE_DIR})

####
# Create targets
add_library(${PROJECT_NAME} #STATIC
    ${OXTS_GAL_CPP_HEADERS}
    ${OXTS_GAL_CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${oxts-sdk-gal-c_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        oxts-sdk-gal-c
        ${Boost_LIBRARIES}

)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE GAL_CPP_LIBRARY
)

install (FILES ${OXTS_GAL_CPP_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/oxts/gal-cpp)
message(STATUS "install prefix: ${CMAKE_INSTALL_PREFIX}")
export_config()

# TODO: Add testing
# if(OXTS_SDK_ENABLE_TESTING)
#     add_subdirectory(tests)
# endif()