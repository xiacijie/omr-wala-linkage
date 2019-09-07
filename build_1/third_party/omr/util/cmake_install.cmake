# Install script for directory: /Users/cijiexia/Project/lljb/third_party/omr/util

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/avl/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/hashtable/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/hookable/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/main_function/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/omrutil/cmake_install.cmake")
  include("/Users/cijiexia/Project/lljb/build_1/third_party/omr/util/pool/cmake_install.cmake")

endif()

