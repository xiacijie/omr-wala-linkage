# Install script for directory: /Users/cijiexia/Project/lljb/third_party/omr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr/OmrTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr/OmrTargets.cmake"
         "/Users/cijiexia/Project/lljb/build_1/third_party/omr/CMakeFiles/Export/lib/cmake/Omr/OmrTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr/OmrTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr/OmrTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr" TYPE FILE FILES "/Users/cijiexia/Project/lljb/build_1/third_party/omr/CMakeFiles/Export/lib/cmake/Omr/OmrTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr" TYPE FILE FILES "/Users/cijiexia/Project/lljb/build_1/third_party/omr/CMakeFiles/Export/lib/cmake/Omr/OmrTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Omr" TYPE FILE FILES "/Users/cijiexia/Project/lljb/build_1/third_party/omr/OmrConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/tools/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/example/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/thread/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/port/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/omr/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/third_party/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/omrsigcompat/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/omrtrace/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/compiler/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/jitbuilder/cmake_install.cmake")

endif()

