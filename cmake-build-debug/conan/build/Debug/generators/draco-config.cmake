########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(draco_FIND_QUIETLY)
    set(draco_MESSAGE_MODE VERBOSE)
else()
    set(draco_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/dracoTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${draco_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(draco_VERSION_STRING "1.5.6")
set(draco_INCLUDE_DIRS ${draco_INCLUDE_DIRS_DEBUG} )
set(draco_INCLUDE_DIR ${draco_INCLUDE_DIRS_DEBUG} )
set(draco_LIBRARIES ${draco_LIBRARIES_DEBUG} )
set(draco_DEFINITIONS ${draco_DEFINITIONS_DEBUG} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${draco_BUILD_MODULES_PATHS_DEBUG} )
    message(${draco_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


