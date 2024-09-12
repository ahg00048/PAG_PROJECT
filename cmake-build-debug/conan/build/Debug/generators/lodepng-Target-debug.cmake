# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(lodepng_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(lodepng_FRAMEWORKS_FOUND_DEBUG "${lodepng_FRAMEWORKS_DEBUG}" "${lodepng_FRAMEWORK_DIRS_DEBUG}")

set(lodepng_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET lodepng_DEPS_TARGET)
    add_library(lodepng_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET lodepng_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${lodepng_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${lodepng_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### lodepng_DEPS_TARGET to all of them
conan_package_library_targets("${lodepng_LIBS_DEBUG}"    # libraries
                              "${lodepng_LIB_DIRS_DEBUG}" # package_libdir
                              "${lodepng_BIN_DIRS_DEBUG}" # package_bindir
                              "${lodepng_LIBRARY_TYPE_DEBUG}"
                              "${lodepng_IS_HOST_WINDOWS_DEBUG}"
                              lodepng_DEPS_TARGET
                              lodepng_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "lodepng"    # package_name
                              "${lodepng_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${lodepng_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET lodepng::lodepng
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${lodepng_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${lodepng_LIBRARIES_TARGETS}>
                 )

    if("${lodepng_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET lodepng::lodepng
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     lodepng_DEPS_TARGET)
    endif()

    set_property(TARGET lodepng::lodepng
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${lodepng_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET lodepng::lodepng
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${lodepng_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET lodepng::lodepng
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${lodepng_LIB_DIRS_DEBUG}>)
    set_property(TARGET lodepng::lodepng
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${lodepng_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET lodepng::lodepng
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${lodepng_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(lodepng_LIBRARIES_DEBUG lodepng::lodepng)
