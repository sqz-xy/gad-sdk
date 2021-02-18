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

set(OXTS_SDK_GAD_CPP_HEADERS
    ./include/oxts/gal-cpp/gad.hpp
    )

set(OXTS_SDK_GAD_CPP_SOURCES
    ./src/gal-cpp/gad.cpp
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(OXTS_SDK_GAL_CPP_NAME "oxts-sdk-gal-cpp")
# set(CMAKE_INSTALL_RPATH "\$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")


add_library(${OXTS_SDK_GAL_CPP_NAME} STATIC
            ${OXTS_SDK_GAD_CPP_HEADERS}
            ${OXTS_SDK_GAD_CPP_SOURCES}
            )

target_link_libraries(${OXTS_SDK_GAL_CPP_NAME} PUBLIC oxts-sdk-gal-c)


####
# Properties of targets

# Add definitions for targets
# Values:
#   * Debug: -DFOO_BAR_DEBUG=1
#   * Release: -DFOO_BAR_DEBUG=0
#   * other: -DFOO_BAR_DEBUG=0
target_compile_definitions(${OXTS_SDK_GAL_CPP_NAME} PUBLIC "OXTS_SDK_GAL_CPP_DEBUG=$<CONFIG:Debug>")

# Generate:
#   * ${CMAKE_CURRENT_BINARY_DIR}/generated_headers/foo/BAR_EXPORT.h with BAR_EXPORT
# Renaming because:
# * We need prefix 'foo' to fit OSX/iOS frameworks layout
# * File name match name of the macro
set(generated_headers "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(oxts_gal_cpp_export "${generated_headers}/oxts/gal-cpp/OXTS_GAL_CPP_EXPORT.h")

# https://cmake.org/cmake/help/v3.9/module/GenerateExportHeader.html
include(GenerateExportHeader)
generate_export_header(${OXTS_SDK_GAL_CPP_NAME} EXPORT_FILE_NAME ${oxts_gal_cpp_export})

# Global includes. Used by all targets
# Note:
#   * header location in project: Foo/Source/foo/Bar.hpp
#   * header can be included by C++ code `#include <foo/Bar.hpp>`
#   * header location in project: ${CMAKE_CURRENT_BINARY_DIR}/generated_headers/foo/BAR_EXPORT.h
#   * header can be included by: `#include <BAR_EXPORT.h>`
# target_include_directories(
#     baz PUBLIC
#     "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Source>"
#     "$<BUILD_INTERFACE:${generated_headers}>"
# )

# Link required library
# target_link_libraries(bar PUBLIC baz)

# Installation (https://github.com/forexample/package-example) {

# Introduce variables:
# * CMAKE_INSTALL_LIBDIR
# * CMAKE_INSTALL_BINDIR
# * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

# Layout. This works for all platforms:
#   * <prefix>/lib*/cmake/<PROJECT-NAME>
#   * <prefix>/lib*/
#   * <prefix>/include/
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}-config-version.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}-config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}-targets")
# set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS ${OXTS_SDK_GAL_CPP_NAME}
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
#   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
install(
    DIRECTORY "include/oxts/gal-cpp"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/oxts"
    FILES_MATCHING PATTERN "*.hpp"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../BAR_EXPORT.h -> <prefix>/include/foo/BAR_EXPORT.h
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../BAZ_EXPORT.h -> <prefix>/include/foo/BAZ_EXPORT.h
install(
    FILES "${oxts_gal_cpp_export}"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/oxts/gal-cpp"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

# CMAKE_MODULE_PATH is a CMAKE variable. It contains a list of paths
# which could be used to search CMAKE modules by "include()" or "find_package()", but the default value is empty.
# Add cmake dir to search list
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
