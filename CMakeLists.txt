cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/share/modules/cmake")

include(CMConfig)
include(CMDeploy)
include(CMSetupVersion)

cm_workspace(boost)

macro(cm_find_package NAME)
    if(NOT "${NAME}" MATCHES "^${CMAKE_WORKSPACE_NAME}_.*$" AND NOT "${NAME}" STREQUAL CM)
        find_package(${ARGV})
    else()
        set(${ARGV0}_FOUND ON CACHE BOOL "")
    endif()
endmacro()

cm_find_package(CM)

cm_find_package(Boost COMPONENTS date_time filesystem thread program_options system regex atomic unit_test_framework)

cm_project(application WORKSPACE_NAME ${CMAKE_WORKSPACE_NAME})

cm_setup_version(VERSION 0.1.0)

option(BUILD_SHARED_LIBS "Build shared libraries" TRUE)
option(BUILD_EXAMPLES "Build examples" TRUE)
option(BUILD_TESTS "Build tests" TRUE)

add_library(${CMAKE_WORKSPACE_NAME}_${CURRENT_PROJECT_NAME} INTERFACE)
set_property(TARGET ${CMAKE_WORKSPACE_NAME}_${CURRENT_PROJECT_NAME} PROPERTY EXPORT_NAME application)

target_include_directories(${CMAKE_WORKSPACE_NAME}_${CURRENT_PROJECT_NAME} INTERFACE ${Boost_INCLUDE_DIRS})

cm_deploy(TARGETS ${CMAKE_WORKSPACE_NAME}_${CURRENT_PROJECT_NAME} INCLUDE include NAMESPACE ${CMAKE_WORKSPACE_NAME}::)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
