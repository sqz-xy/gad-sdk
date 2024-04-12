cmake_minimum_required(VERSION 3.10)


# define library version 
set(OXTS_SDK_GAL_VERSION_MAJOR 0 CACHE STRING "major version" FORCE)
set(OXTS_SDK_GAL_VERSION_MINOR 1 CACHE STRING "minor version" FORCE)
set(OXTS_SDK_GAL_VERSION_PATCH 0 CACHE STRING "patch version" FORCE)
set(OXTS_SDK_GAL_VERSION 
${OXTS_SDK_GAL_VERSION_MAJOR}.${OXTS_SDK_GAL_VERSION_MINOR}.${OXTS_SDK_GAL_VERSION_PATCH} 
CACHE STRING "version" FORCE
)

IF (WIN32)
    add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
ELSE()
    add_compile_options(-fPIC)
ENDIF()

project(oxts-sdk-gal-cpp VERSION ${OXTS_SDK_GAL_VERSION})
set(DESCRIPTION "Generic Aiding library for the OxTS SDK in C++.")

set(OXTS_GAL_CPP_HEADERS
    ./include/oxts/gal-cpp/basic_casts.hpp
    ./include/oxts/gal-cpp/basic_types.hpp
    ./include/oxts/gal-cpp/ccomtx.hpp
    ./include/oxts/gal-cpp/gad.hpp
    ./include/oxts/gal-cpp/gad_encoders/gad_encoder.hpp
    ./include/oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp
    ./include/oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp
    ./include/oxts/gal-cpp/gad_output/gad_output.hpp
    ./include/oxts/gal-cpp/gad_output/gad_output_file.hpp
    ./include/oxts/gal-cpp/gad_output/gad_output_udp.hpp
    ./include/oxts/gal-cpp/gad_defines.hpp
    ./include/oxts/gal-cpp/gad_handler.hpp
    ./include/oxts/gal-cpp/gad_struct.hpp
    ./include/oxts/gal-cpp/Lib_Detect.hpp
    ./include/oxts/gal-cpp/oxts_arrays.hpp
    ./include/oxts/gal-cpp/oxts_misra.hpp
    ./include/oxts/gal-cpp/oxts_sockets.hpp
    ./include/oxts/gal-cpp/udp_server_client.hpp
)

set(OXTS_GAL_CPP_SOURCES
    ./src/gal-cpp/ccomtx.cpp
    ./src/gal-cpp/gad.cpp
    ./src/gal-cpp/gad_encoder_bin.cpp
    ./src/gal-cpp/gad_encoder_csv.cpp
    ./src/gal-cpp/gad_handler.cpp
    ./src/gal-cpp/gad_output.cpp
    ./src/gal-cpp/oxts_sockets.cpp
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/oxts/gal-cpp/config.h.in 
               ${CMAKE_CURRENT_BINARY_DIR}/include/oxts/gal-cpp/config.h @ONLY
)

####
# Create targets
add_library(${PROJECT_NAME} STATIC
    ${OXTS_GAL_CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/oxts/gal-cpp 
         DESTINATION ${INCLUDE_DIRECTORY}/oxts
)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/include/oxts/gal-cpp/config.h 
         DESTINATION ${INCLUDE_DIRECTORY}/oxts/gal-cpp
)
export_config()
