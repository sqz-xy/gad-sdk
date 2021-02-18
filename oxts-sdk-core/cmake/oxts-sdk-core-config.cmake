get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/oxts-sdk-core-targets.cmake)
get_filename_component(oxts-sdk-core_INCLUDE_DIRS "${SELF_DIR}/../../include/${PROJECT_NAME}" ABSOLUTE)
