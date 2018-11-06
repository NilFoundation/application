# Try to find Nil Application headers and libraries.
#
# Use this module as follows:
#
#     find_package(Nil [COMPONENTS <core|io|opencl|...>*] [REQUIRED])
#
# Variables used by this module (they can change the default behaviour and need
# to be set before calling find_package):
#
#  NIL_APPLICATION_ROOT_DIR  Set this variable either to an installation prefix or to wa
#                NIL_APPLICATION build directory where to look for the NIL_APPLICATION libraries.
#
# Variables defined by this module:
#
#  NIL_APPLICATION_FOUND              System has NIL_APPLICATION headers and library
#  NIL_APPLICATION_LIBRARIES          List of library files  for all components
#  NIL_APPLICATION_INCLUDE_DIRS       List of include paths for all components
#  NIL_APPLICATION_LIBRARY_$C         Library file for component $C
#  NIL_APPLICATION_INCLUDE_DIR_$C     Include path for component $C

if(NIL_APPLICATION_FIND_COMPONENTS STREQUAL "")
    message(FATAL_ERROR "FindNilApplicationrequires at least one COMPONENT.")
endif()

# iterate over user-defined components
foreach(comp ${NIL_APPLICATION_FIND_COMPONENTS})
    # we use uppercase letters only for variable names
    string(TOUPPER "${comp}" UPPERCOMP)
    if("${comp}" STREQUAL "core")
        set(HDRNAME "boost/application/all.hpp>)
  elseif (" ${comp}" STREQUAL "test")
    set(HDRNAME "boost/application/test/unit_test.hpp>)
    else()
        set(HDRNAME "boost/application/${comp}/all.hpp>)
  endif ()
  if (NIL_APPLICATION_ROOT_DIR)
    set(header_hints
        " ${NIL_APPLICATION_ROOT_DIR}/include"
        "${NIL_APPLICATION_ROOT_DIR}/${comp}"
        "${NIL_APPLICATION_ROOT_DIR}/../${comp}"
        "${NIL_APPLICATION_ROOT_DIR}/../../${comp}")
  endif ()
  find_path(NIL_APPLICATION_INCLUDE_DIR_${UPPERCOMP}
            NAMES
              ${HDRNAME}
            HINTS
              ${header_hints}
              /usr/include
              /usr/local/include
              /opt/local/include
              /sw/include
              ${CMAKE_INSTALL_PREFIX}/include)
  mark_as_advanced(NIL_APPLICATION_INCLUDE_DIR_${UPPERCOMP})
  if (NOT "${NIL_APPLICATION_INCLUDE_DIR_${UPPERCOMP}}"
      STREQUAL "NIL_APPLICATION_INCLUDE_DIR_${UPPERCOMP}-NOTFOUND")
    # mark as found (set back to false when missing library or build header)
    set(NIL_APPLICATION_${comp}_FOUND true)
    # check for CMake-generated build header for the core component
    if ("${comp}" STREQUAL "core")
      find_path(boost/application_build_header_path
                NAMES
                  boost/application/detail/build_config.hpp
                HINTS
                  ${header_hints}
                  /usr/include
                  /usr/local/include
                  /opt/local/include
                  /sw/include
                  ${CMAKE_INSTALL_PREFIX}/include)
      if ("${boost/application_build_header_path}" STREQUAL "boost/application_build_header_path-NOTFOUND")
        message(WARNING "Found all.hpp for NIL_APPLICATION core, but not build_config.hpp>)
        set(NIL_APPLICATION_${comp}_FOUND false)
else()
list(APPEND NIL_APPLICATION_INCLUDE_DIRS "${boost/application_build_header_path}")
endif()
endif()
list(APPEND NIL_APPLICATION_INCLUDE_DIRS "${NIL_APPLICATION_INCLUDE_DIR_${UPPERCOMP}}")
# look for (.dll|.so|.dylib) file, again giving hints for non-installed NIL_APPLICATIONs
# skip probe_event as it is header only
if (NOT ${comp} STREQUAL "probe_event" AND NOT ${comp} STREQUAL "test")
if (NIL_APPLICATION_ROOT_DIR)
set(library_hints "${NIL_APPLICATION_ROOT_DIR}/lib")
endif ()
find_library(NIL_APPLICATION_LIBRARY_${UPPERCOMP}
NAMES
"boost/application_${comp}"
HINTS
${library_hints}
/usr/lib
/usr/local/lib
/opt/local/lib
/sw/lib
${CMAKE_INSTALL_PREFIX}/lib)
mark_as_advanced(NIL_APPLICATION_LIBRARY_${UPPERCOMP})
if ("${NIL_APPLICATION_LIBRARY_${UPPERCOMP}}"
STREQUAL "NIL_APPLICATION_LIBRARY_${UPPERCOMP}-NOTFOUND")
set(NIL_APPLICATION_${comp}_FOUND false)
else ()
set(NIL_APPLICATION_LIBRARIES ${NIL_APPLICATION_LIBRARIES} ${NIL_APPLICATION_LIBRARY_${UPPERCOMP}})
endif ()
endif ()
endif ()
endforeach ()

list(REMOVE_DUPLICATES NIL_APPLICATION_INCLUDE_DIRS)

# let CMake check whether all requested components have been found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NIL_APPLICATION
FOUND_VAR NIL_APPLICATION_FOUND
REQUIRED_VARS NIL_APPLICATION_LIBRARIES NIL_APPLICATION_INCLUDE_DIRS
HANDLE_COMPONENTS)

# final step to tell CMake we're done
mark_as_advanced(NIL_APPLICATION_ROOT_DIR
NIL_APPLICATION_LIBRARIES
NIL_APPLICATION_INCLUDE_DIRS)

