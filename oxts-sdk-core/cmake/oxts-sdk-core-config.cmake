get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/${OXTS_SDK_LIB_NAME}-targets.cmake)
get_filename_component(${PROJECT_NAME}_INCLUDE_DIRS "${SELF_DIR}/../../include/${PROJECT_NAME}" ABSOLUTE)
