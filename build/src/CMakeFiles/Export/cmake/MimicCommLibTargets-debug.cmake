#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Upstream::mimiccomm" for configuration "Debug"
set_property(TARGET Upstream::mimiccomm APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Upstream::mimiccomm PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libmimiccomm.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Upstream::mimiccomm )
list(APPEND _IMPORT_CHECK_FILES_FOR_Upstream::mimiccomm "${_IMPORT_PREFIX}/lib/libmimiccomm.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
