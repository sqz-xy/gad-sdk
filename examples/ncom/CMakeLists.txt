cmake_minimum_required(VERSION 3.1)

project(ncom-examples
        VERSION 0.1.0
        DESCRIPTION "Examples using the NCom decoding functionality from the 
        OxTS SDK (C++).")

#set(CMAKE_CXX_STANDARD 11)

## Locate OxTS SDK - To be added when library is building.
#find_package(OXTSSDK REQUIRED COMPONENTS ncom)

set(EXAMPLES "")
list(APPEND EXAMPLES "ncom_to_csv")
# ... additional examples to be added here


# Add executables for each example
foreach(EXAMPLE IN LISTS EXAMPLES)
    add_executable(${EXAMPLE} ${EXAMPLE}.c NComRxC.c)
    #target_link_libraries(${EXAMPLE} ${OXTSSDK_LINK_LIBRARIES})
endforeach()