#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "j9avl" for configuration ""
set_property(TARGET j9avl APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(j9avl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libj9avl.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS j9avl )
list(APPEND _IMPORT_CHECK_FILES_FOR_j9avl "${_IMPORT_PREFIX}/lib/libj9avl.a" )

# Import target "omrsig" for configuration ""
set_property(TARGET omrsig APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(omrsig PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libomrsig.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libomrsig.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS omrsig )
list(APPEND _IMPORT_CHECK_FILES_FOR_omrsig "${_IMPORT_PREFIX}/lib/libomrsig.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
