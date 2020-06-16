#----------------------------------------------------------------
# Generated CMake target import file for configuration "Releas".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Upstream::mimiccomm" for configuration "Releas"
set_property(TARGET Upstream::mimiccomm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEAS)
set_target_properties(Upstream::mimiccomm PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEAS "CXX"
  IMPORTED_LOCATION_RELEAS "${_IMPORT_PREFIX}/lib/libmimiccomm.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Upstream::mimiccomm )
list(APPEND _IMPORT_CHECK_FILES_FOR_Upstream::mimiccomm "${_IMPORT_PREFIX}/lib/libmimiccomm.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
