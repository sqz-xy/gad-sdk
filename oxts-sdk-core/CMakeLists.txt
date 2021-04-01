cmake_minimum_required(VERSION 3.1)

project(oxts-sdk-core VERSION 0.1.0)
set(DESCRIPTION "OxTS core library for common C/C++ functionality.")

# Find external packages:
# ...

# List header files
set(OXTS_CORE_HEADERS
    ./include/oxts/core/BasicCasts.h
    ./include/oxts/core/BasicTypes.h
    ./include/oxts/core/ccomtx.h
    ./include/oxts/core/errors.h
    ./include/oxts/core/Lib_Compiler.h
    ./include/oxts/core/Lib_Detect.h
    ./include/oxts/core/version.h
    )

# List source files
set(OXTS_CORE_SOURCES
    ./src/BasicCasts.c
    ./src/ccomtx.cpp
    ./src/errors.c
    ./src/Lib_Compiler.c
    )


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

####
# Create targets
add_library(${PROJECT_NAME} #STATIC
    ${OXTS_CORE_HEADERS}
    ${OXTS_CORE_SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE CORE_LIBRARY)

install (FILES ${OXTS_CORE_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/oxts/core)
export_config()
