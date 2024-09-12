########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(lodepng_COMPONENT_NAMES "")
if(DEFINED lodepng_FIND_DEPENDENCY_NAMES)
  list(APPEND lodepng_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES lodepng_FIND_DEPENDENCY_NAMES)
else()
  set(lodepng_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(lodepng_PACKAGE_FOLDER_DEBUG "C:/Users/ahues/.conan2/p/b/lodep355371ed66db3/p")
set(lodepng_BUILD_MODULES_PATHS_DEBUG )


set(lodepng_INCLUDE_DIRS_DEBUG "${lodepng_PACKAGE_FOLDER_DEBUG}/include")
set(lodepng_RES_DIRS_DEBUG )
set(lodepng_DEFINITIONS_DEBUG )
set(lodepng_SHARED_LINK_FLAGS_DEBUG )
set(lodepng_EXE_LINK_FLAGS_DEBUG )
set(lodepng_OBJECTS_DEBUG )
set(lodepng_COMPILE_DEFINITIONS_DEBUG )
set(lodepng_COMPILE_OPTIONS_C_DEBUG )
set(lodepng_COMPILE_OPTIONS_CXX_DEBUG )
set(lodepng_LIB_DIRS_DEBUG "${lodepng_PACKAGE_FOLDER_DEBUG}/lib")
set(lodepng_BIN_DIRS_DEBUG )
set(lodepng_LIBRARY_TYPE_DEBUG STATIC)
set(lodepng_IS_HOST_WINDOWS_DEBUG 1)
set(lodepng_LIBS_DEBUG lodepng)
set(lodepng_SYSTEM_LIBS_DEBUG )
set(lodepng_FRAMEWORK_DIRS_DEBUG )
set(lodepng_FRAMEWORKS_DEBUG )
set(lodepng_BUILD_DIRS_DEBUG )
set(lodepng_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(lodepng_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${lodepng_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${lodepng_COMPILE_OPTIONS_C_DEBUG}>")
set(lodepng_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${lodepng_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${lodepng_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${lodepng_EXE_LINK_FLAGS_DEBUG}>")


set(lodepng_COMPONENTS_DEBUG )