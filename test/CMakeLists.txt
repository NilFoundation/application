include(CMTest)

cm_test_link_libraries(${CMAKE_WORKSPACE_NAME}_application
                       ${Boost_LIBRARIES})

cm_test(NAME args_aspect_test SOURCES args_aspect_test.cpp)
set_target_properties(args_aspect_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(args_aspect_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME aspect_map_test SOURCES aspect_map_test.cpp)
set_target_properties(aspect_map_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(aspect_map_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME auto_app_test SOURCES auto_app_test.cpp)
set_target_properties(auto_app_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(auto_app_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME auto_handler_global_context_test SOURCES auto_handler_global_context_test.cpp)
set_target_properties(auto_handler_global_context_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(auto_handler_global_context_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME auto_handler_test SOURCES auto_handler_test.cpp)
set_target_properties(auto_handler_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(auto_handler_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME ensure_single_instance_test SOURCES ensure_single_instance_test.cpp)
set_target_properties(ensure_single_instance_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(ensure_single_instance_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME global_context_test SOURCES global_context_test.cpp)
set_target_properties(global_context_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(global_context_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME handler_test SOURCES handler_test.cpp)
set_target_properties(handler_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(handler_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME launch_test SOURCES launch_test.cpp)
set_target_properties(launch_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(launch_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME myexception_test SOURCES myexception_test.cpp)
set_target_properties(myexception_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(myexception_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME path_aspect_test SOURCES path_aspect_test.cpp)
set_target_properties(path_aspect_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(path_aspect_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME signal_binder_test SOURCES signal_binder_test.cpp)
set_target_properties(signal_binder_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(signal_binder_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME simple_common_application_test SOURCES simple_common_application_test.cpp)
set_target_properties(simple_common_application_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(simple_common_application_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME simple_server_application_test SOURCES simple_server_application_test.cpp)
set_target_properties(simple_server_application_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(simple_server_application_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)

cm_test(NAME tunit_test SOURCES myapp.hpp myapp.cpp tunit_test.cpp)
set_target_properties(tunit_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED TRUE)
target_compile_definitions(tunit_test PRIVATE
                           $<$<STREQUAL:$<UPPER_CASE:$<TARGET_PROPERTY:BUILD_SHARED_LIBS>>,
                           TRUE>:BOOST_TEST_DYN_LINK>)