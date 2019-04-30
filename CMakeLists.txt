cmake_minimum_required(VERSION 3.12)

# Project name and version
project(merseburg LANGUAGES CXX)

# define library version (update: apparently you can also do it in project()!)
set(MERSEBERG_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(MERSEBERG_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(MERSEBERG_VERSION ${MERSEBERG_VERSION_MAJOR}.${MERSEBERG_VERSION_MINOR} CACHE STRING "version" FORCE)

option(ENABLE_TESTS "Enable testing" OFF)
option(ENABLE_EXAMPLES "Enable examples" ON)
option(ENABLE_DOCS "Enable documentation" OFF)

set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for include library")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/merseberg)
endif()

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}"   # to find foo/foo.h
  "${PROJECT_BINARY_DIR}")  # to find foo/config.h

include(CTest)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

# Define GNU standard installation directories
include(GNUInstallDirs)

# Add feature summary
include(FeatureSummary)

# C++ compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})

add_subdirectory(include)

if (ENABLE_DOCS)
  add_subdirectory(docs)
endif()

if (ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ------ export -----
# Add all targets to the build-tree export set
export(TARGETS merseberg
  FILE "${PROJECT_BINARY_DIR}/MersebergTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE Merseberg)

# Create the MersebergConfig.cmake and MersebergConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(MersebergConfig.cmake.in
  "${PROJECT_BINARY_DIR}/MersebergConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${MERSEBERG_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(MersebergConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MersebergConfig.cmake" @ONLY)
# ... for both
configure_file(MersebergConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/MersebergConfigVersion.cmake" @ONLY)

# Install the MersebergConfig.cmake and MersebergConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MersebergConfig.cmake"
  "${PROJECT_BINARY_DIR}/MersebergConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT MersebergTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
