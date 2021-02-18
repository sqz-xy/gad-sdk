get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/oxts-sdk-gal-cpp-targets.cmake)
get_filename_component(oxts-sdk-gal-cpp_INCLUDE_DIRS "${SELF_DIR}/../../include/${PROJECT_NAME}" ABSOLUTE)
