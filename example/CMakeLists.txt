if(NOT Boost_FOUND OR NOT Boost_THREAD_FOUND OR NOT Boost_DATE_TIME_FOUND OR NOT Boost_SYSTEM_FOUND OR NOT
   Boost_FILESYSTEM_FOUND)
    cm_find_package(Boost REQUIRED COMPONENTS thread date_time system filesystem)
endif()

set(${CMAKE_PROJECT_NAME}_EXAMPLES)

function(add_example_executable)
    set(options COMPILE_ONLY WILL_FAIL NO_TEST_LIBS)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES)

    cmake_parse_arguments(PARSE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_executable(${PARSE_NAME} ${PARSE_SOURCES})
    set_target_properties(${PARSE_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED TRUE)
    target_include_directories(${PARSE_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ../include)
    target_link_libraries(${PARSE_NAME} boost::application ${Boost_LIBRARIES})

    set(${CMAKE_PROJECT_NAME}_EXAMPLES ${${CMAKE_PROJECT_NAME}_EXAMPLES} ${PARSE_NAME} PARENT_SCOPE)
endfunction()

add_example_executable(NAME application_mode_select SOURCES application_mode_select.cpp)
add_example_executable(NAME handling_errors_ec_version SOURCES handling_errors_ec_version.cpp)
add_example_executable(NAME handling_errors_ex_version SOURCES handling_errors_ex_version.cpp)
add_example_executable(NAME limit_single_instance SOURCES limit_single_instance.cpp)
add_example_executable(NAME limit_single_instance_boost_interprocess_named_mutex SOURCES
                       limit_single_instance_boost_interprocess_named_mutex.cpp)
add_example_executable(NAME limit_single_instance_callback SOURCES
                       limit_single_instance_callback.cpp)
add_example_executable(NAME limit_single_instance_callback_with_global_context SOURCES
                       limit_single_instance_callback_with_global_context.cpp)
add_example_executable(NAME my_own_termination_handler SOURCES my_own_termination_handler.cpp)
add_example_executable(NAME my_own_wait_for_termination_request SOURCES my_own_wait_for_termination_request.cpp)
add_example_executable(NAME myexception SOURCES myexception.cpp)
add_example_executable(NAME path SOURCES path.cpp)
add_example_executable(NAME pid SOURCES pid.cpp)
add_example_executable(NAME simple_application SOURCES simple_application.cpp)
add_example_executable(NAME simple_application_with_global_context SOURCES simple_application_with_global_context.cpp)
add_example_executable(NAME simple_server_application SOURCES simple_server_application.cpp)
add_example_executable(NAME simple_server_application_help SOURCES simple_server_application_help.cpp)
add_example_executable(NAME simple_server_application_with_auto_handler SOURCES
                       simple_server_application_with_auto_handler.cpp)
add_example_executable(NAME simple_server_application_with_auto_handler_and_global_context SOURCES
                       simple_server_application_with_auto_handler_and_global_context.cpp)
add_example_executable(NAME termination_handler SOURCES termination_handler.cpp)
add_example_executable(NAME termination_handler_with_global_context SOURCES termination_handler_with_global_context.cpp)
add_example_executable(NAME examples_test SOURCES test.cpp)
add_example_executable(NAME wait_for_termination_request SOURCES wait_for_termination_request.cpp)

add_custom_target(examples)

foreach(ITERATOR ${${CMAKE_PROJECT_NAME}_EXAMPLES})
    add_dependencies(examples ${ITERATOR})
endforeach()