cmake_minimum_required(VERSION 3.1)

project(oxts-sdk-docs VERSION 0.1.0)

if (NOT OXTS_SDK_BUILD_DOCS)
  message(STATUS "Building documents currently disabled.")
  return()
endif()

find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
  message(STATUS "Doxygen not found. Cannot build documentation without it.")
  return()
endif()

# set input and output files
set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# request to configure the file
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

set(COMPONENT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../oxts-sdk-core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../oxts-sdk-gal-c/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../oxts-sdk-gal-cpp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../oxts-sdk-udp/include
    #oxts-sdk-ncomdecoder/include (TBA)
    ${CMAKE_CURRENT_SOURCE_DIR}/../examples
    )

set(MAINPAGE_FILE ../README.md)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${MAINPAGE_FILE})

doxygen_add_docs(docs ALL
                 ${COMPONENT_DIRS} ${MAINPAGE_FILE}
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                 COMMENT "Generating documentation"
                 VERBATIM
                 )