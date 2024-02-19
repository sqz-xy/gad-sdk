


# Building
set(SDK_LIST "")
list(APPEND SDK_LIST "gal-c")
list(APPEND SDK_LIST "gal-cpp")

set(BUILD_LIST)

function(add_sdk name)
    set(SDK_DIR "oxts-sdk-${name}")
    string(TOUPPER ${name} SDK_NAME)
    set(DEPENDENCY_LIST "${${SDK_NAME}_DEPENDENCY_LIST}")
    foreach(DEPENDENCY IN LISTS DEPENDENCY_LIST)
       add_sdk(${DEPENDENCY})
    endforeach()
    set(BUILD_LIST ${BUILD_LIST} ${SDK_DIR} PARENT_SCOPE)
endfunction()

function(add_sdks)
    if(BUILD_ONLY)
       set(SDK_LIST ${BUILD_ONLY})
    endif()
    foreach(SDK IN LISTS SDK_LIST)
        add_sdk(${SDK})
    endforeach()
    LIST(REMOVE_DUPLICATES BUILD_LIST)
    foreach(SDK_DIR IN LISTS BUILD_LIST)
        add_subdirectory("${SDK_DIR}")
    endforeach()
    set(BUILD_LIST ${BUILD_LIST} PARENT_SCOPE)
endfunction()

# Install section
include(CMakePackageConfigHelpers)
set(INCLUDE_DIRECTORY "include")
set(BINARY_DIRECTORY "bin")
set(LIBRARY_DIRECTORY "lib")
set(ARCHIVE_DIRECTORY "lib")

macro(export_config)
    # Install and export targets
    install (
        TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}-targets"
        ARCHIVE DESTINATION "${ARCHIVE_DIRECTORY}"
        LIBRARY DESTINATION "${LIBRARY_DIRECTORY}"
        RUNTIME DESTINATION "${BINARY_DIRECTORY}"
    )
    export(EXPORT "${PROJECT_NAME}-targets"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-targets.cmake"
    )
    set(ConfigPackageLocation "${LIBRARY_DIRECTORY}/cmake/${PROJECT_NAME}")
    install(EXPORT "${PROJECT_NAME}-targets"
        FILE "${PROJECT_NAME}-targets.cmake"
        DESTINATION ${ConfigPackageLocation}
    )

    # Create and install configuration files
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    if(${PROJECT_NAME} STREQUAL "oxts-sdk-gal-c")
         configure_file(
             "${OXTS_SDK_ROOT}/cmake/oxts-sdk-gal-c-config.cmake"
             "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
             @ONLY)
    elseif(${PROJECT_NAME} STREQUAL "oxts-sdk-gal-cpp")
         configure_file(
             "${OXTS_SDK_ROOT}/cmake/oxts-sdk-gal-cpp-config.cmake"
             "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
             @ONLY)
    else()
        message("Package not found in configuration list.")
    endif()
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        DESTINATION
        ${ConfigPackageLocation}
        COMPONENT
        Devel
    )

endmacro()
