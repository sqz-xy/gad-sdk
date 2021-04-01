include(CMakeFindDependencyMacro)
find_dependency(oxts-sdk-gal-c)
include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@-targets.cmake")