# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Anil Gunturu
# Creation Date: 8/29/2013
# 

cmake_minimum_required(VERSION 2.8)


# this block should be at the top of every CMakleLists.txt
# this sets up project root dir and module path
get_filename_component(PROJECT_TOP_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
message("PROJECT_TOP_DIR = ${PROJECT_TOP_DIR}")
set(CMAKE_MODULE_PATH ${PROJECT_TOP_DIR}/cmake/modules)
include(rift_globals)
include(rift_build_utils)
include(rift_externalproject)
cmake_policy(SET CMP0017 NEW)


##
# Fetch the module dependencies
# For each submodule that is checked out, this target will determine the 
# dependencies. For each dependency, this target tries to populate the cache.
# If the cache doesn't exist for the dependency, the submodule is checkedout
# to build locally.
##
configure_file(
  ${PROJECT_TOP_DIR}/cmake/modules/rift_fetch_dependencies.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/rift_fetch_dependencies.cmake
  ESCAPE_QUOTES @ONLY
  )

# Custom target for fetching the dependencies
add_custom_target(fetch-dependencies
  ${CMAKE_COMMAND}
  -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
  -DPROJECT_TOP_DIR=${PROJECT_TOP_DIR}
  -P ${CMAKE_CURRENT_BINARY_DIR}/rift_fetch_dependencies.cmake
  )

# Fetch the dependencies
# This would eliminate the "make fetch_dependencies" step during the build process
execute_process(
  COMMAND
  ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
  -DPROJECT_TOP_DIR=${PROJECT_TOP_DIR}
  -P ${CMAKE_CURRENT_BINARY_DIR}/rift_fetch_dependencies.cmake
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

if(result)
  message("Failed to get dependencies for submodule ${submodule}")
  message(FATAL_ERROR "Error: ${result}")
endif(result)

##
# function to create a target to generate rw-composite.yang from dir of .yangs
# rift_gen_composite_yang(<TARGET>
#   OUTPUT_FILE <output file path>          # composite output file path
#   INPUT_YANG_DIR <yang_install_directory) # directory to scan for .yang files
# )
##
function(rift_gen_composite_yang TARGET)
  set(parse_options )
  set(parse_onevalargs OUTPUT_FILE INPUT_YANG_DIR)
  set(parse_multivalueargs DEPENDS)
  cmake_parse_arguments(ARGS "${parse_options}" "${parse_onevalargs}" "${parse_multivalueargs}" ${ARGN})

  add_custom_command(
    OUTPUT ${ARGS_OUTPUT_FILE}
    COMMAND
      if ls ${ARGS_INPUT_YANG_DIR}\; then
        ${PROJECT_TOP_DIR}/scripts/util/generate_composite_yang.py
        --yang-dir ${ARGS_INPUT_YANG_DIR}
        --output-file ${ARGS_OUTPUT_FILE}\;
      fi
    DEPENDS
      ${ARGS_DEPENDS}
      ${PROJECT_TOP_DIR}/scripts/util/generate_composite_yang.py
    )

  add_custom_target(${TARGET} ALL
    DEPENDS ${ARGS_OUTPUT_FILE}
    )
endfunction(rift_gen_composite_yang)

##
# function to convert the submodule relative path into a target name
# rift_submodule_to_target_name(<var> <submodule>)
#
# Example: rift_submodule_to_target_name(var modules/core/fpath)
#
# Result: $(var) == core_fpath
##
function(rift_submodule_to_target_name var submodule)
      set(retval)
      string(REPLACE "/" "_" retval ${submodule})
      string(REPLACE "modules_" "" retval ${retval})
      set(${var} "${retval}" PARENT_SCOPE)

endfunction(rift_submodule_to_target_name)


function(add_submodule_targets
    submodule
    submodule_target
    clean_targets
    unittest_targets
    unittest_long_targets
    systemtest_targets
    coverage_targets
    doxygen_targets
    package_targets
    bcache_targets)
  ##
  # Wipe out the external project and build it again
  ##
  list(APPEND clean_targets clean_${submodule_target})
  add_custom_target(clean_${submodule_target}
    rm -rf ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/
    )

  ##
  # Add custom targets for running quick unittests in each submodule
  ##
  list(APPEND unittest_targets rw.unittest.${submodule_target})
  add_custom_target(rw.unittest.${submodule_target}
    $(MAKE) rw.unittest
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )

  ##
  # Add custom targets for running long unittests in each submodule
  ##
  list(APPEND unittest_long_targets rw.unittest_long.${submodule_target})
  add_custom_target(rw.unittest_long.${submodule_target}
    $(MAKE) rw.unittest_long
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )

  ##
  # Add custom targets for running systemtests in each submodule
  ##
  list(APPEND systemtest_targets rw.systemtest.${submodule_target})
  add_custom_target(rw.systemtest.${submodule_target}
    $(MAKE) rw.systemtest
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )


  ##
  # Add custom targets for running coverage analysis in each submodule
  ##
  list(APPEND coverage_targets rw.coverage.${submodule_target})
  add_custom_target(rw.coverage.${submodule_target}
    $(MAKE) rw.coverage
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )

  ##
  # Add custom targets for generating doxygen documentation in each submodule
  ##
  list(APPEND doxygen_targets rw.doxygen.${submodule_target})
  add_custom_target(rw.doxygen.${submodule_target}
    $(MAKE) rw.doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )

  ##
  # Add custom targets for generating packages in each submodule
  ##
  list(APPEND package_targets rw.package.${submodule_target})
  add_custom_target(rw.package.${submodule_target}
    $(MAKE) rw.package
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )

  ##
  # Add custom targets for caching packages in each submodule
  ##
  list(APPEND bcache_targets rw.bcache.${submodule_target})
  add_custom_target(rw.bcache.${submodule_target}
    $(MAKE) rw.bcache
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    DEPENDS ${submodule_target}
    )

  set(clean_targets "${clean_targets}" PARENT_SCOPE)
  set(unittest_targets "${unittest_targets}" PARENT_SCOPE)
  set(unittest_long_targets "${unittest_long_targets}" PARENT_SCOPE)
  set(systemtest_targets "${systemtest_targets}" PARENT_SCOPE)
  set(coverage_targets "${coverage_targets}" PARENT_SCOPE)
  set(doxygen_targets "${doxygen_targets}" PARENT_SCOPE)
  set(package_targets "${package_targets}" PARENT_SCOPE)
  set(bcache_targets "${bcache_targets}" PARENT_SCOPE)
endfunction()

##
# rwbase is a special project which sets up the environment for
# the rest of Riftware to build.  As such, every other project
# will depend on rwbase.  As this will never change, rather than
# use .gitmodules.deps, we can just create this special project
# here and set the dependency for the rest of the projects below.
#
# This also allows us to have rwbase be directly included in this
# git tree rather than in a submodule which is preferable as
# rwbase is tiny.
##
externalproject_add(
  rwbase
  DOWNLOAD_COMMAND ""
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rwbase
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rwbase
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"
    -DNOT_DEVELOPER_BUILD="${NOT_DEVELOPER_BUILD}"
    -DCOVERAGE_BUILD="${COVERAGE_BUILD}"
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DRIFT_AGENT_BUILD=${RIFT_AGENT_BUILD}
  INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
)

rift_externalproject_sha_check(rwbase
  BINARY_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/rwbase/src/rwbase-build
  SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/rwbase
  STAMP_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/rwbase/src/rwbase-stamp)

set(clean_targets)
set(unittest_targets)
set(unittest_long_targets)
set(systemtest_targets)
set(coverage_targets)
set(doxygen_targets)
set(package_targets)
set(bcache_targets)

add_submodule_targets(rwbase rwbase
  "${clean_targets}"
  "${unittest_targets}"
  "${unittest_long_targets}"
  "${systemtest_targets}"
  "${coverage_targets}"
  "${doxygen_targets}"
  "${package_targets}"
  "${bcache_targets}")

set(package_targets)
set(bcache_targets)

##
# Find the list of checked out submodules
# The user may check out one or more submodules to build
# For example user may check out modules/core/schema using
# - git submodule init modules/core/schema
# - git submodule update modules/core/schema
# - cd modules/core/schema && git checkout master
# Missing cache for submodule dependencies will also cause the submodule
# to be checked-out
##
rift_find_checkedout_submodules(
  PROJECT_TOP_DIR ${PROJECT_TOP_DIR}
  OUT_SUBMODULES submodules)

##
# Add external project for building individual submodules
##
foreach(submodule ${submodules})
  rift_submodule_to_target_name(submodule_target ${submodule})

  ##
  # Add the externalproject targets for each submodule
  ##

  # RIFT-3266 - Prevent docs from running too much in parallel
  # due to out of memory situation with "fop".
  set (submodule_build_cmd $(MAKE))
  if(submodule_target MATCHES "(.*)docs(.*)")
    set (submodule_build_cmd $(MAKE) -j1)
  endif()

  externalproject_add(
    ${submodule_target}
    DOWNLOAD_COMMAND ""
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${submodule}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${submodule}
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"
    -DNOT_DEVELOPER_BUILD="${NOT_DEVELOPER_BUILD}"
    -DCOVERAGE_BUILD="${COVERAGE_BUILD}"
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DRIFT_AGENT_BUILD=${RIFT_AGENT_BUILD}
    BUILD_COMMAND ${submodule_build_cmd}
    DEPENDS rwbase
    )

  # Get the submodule dependents instead of its dependencies
  rift_find_submodule_deps(
    PROJECT_TOP_DIR ${PROJECT_TOP_DIR}
    SUBMODULE ${submodule}
    OUT_DEPS dep_submodules
    GET_DEPENDENTS
    )

  # Calculate all dependent submodule targets
  set(dep_submodule_targets)
  foreach(dep_submodule ${dep_submodules})
    rift_submodule_to_target_name(dep_submodule_target ${dep_submodule})
    list(APPEND dep_submodule_targets ${dep_submodule_target})
  endforeach(dep_submodule)

  rift_externalproject_sha_check(${submodule_target}
    BINARY_DIR
      ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-build
    SOURCE_DIR
      ${CMAKE_CURRENT_SOURCE_DIR}/${submodule}
    STAMP_DIR
      ${CMAKE_CURRENT_BINARY_DIR}/${submodule}/src/${submodule_target}-stamp
    GIT_DIR
      ${CMAKE_CURRENT_SOURCE_DIR}/${submodule}/.git
    DEPENDENT_EXTERNAL_TARGETS
      ${dep_submodule_targets}
    )

  add_submodule_targets(${submodule} ${submodule_target}
    "${clean_targets}"
    "${unittest_targets}"
    "${unittest_long_targets}"
    "${systemtest_targets}"
    "${coverage_targets}"
    "${doxygen_targets}"
    "${package_targets}"
    "${bcache_targets}")
endforeach(submodule)

##
# Create a list which contains all submodule targets
##
set(submodule_targets)
foreach(submodule ${submodules})
  rift_submodule_to_target_name(submodule_target ${submodule})
  list(APPEND submodule_targets ${submodule_target})
endforeach(submodule)

##
# Each submodule may be dependent on other submodules
# Add dependencies for each submodule target
##
foreach(submodule ${submodules})
  rift_submodule_to_target_name(submodule_target ${submodule})

  # create a list of targets for dependent submodules
  unset(dep_targets)
  rift_find_submodule_deps(
    PROJECT_TOP_DIR     ${PROJECT_TOP_DIR}
    SUBMODULE ${submodule}
    OUT_DEPS deps)
  if(deps)
    foreach(dep ${deps})
      rift_submodule_to_target_name(dep_target ${dep})
      add_dependencies(${submodule_target} ${dep_target})
      #add_dependencies(externalproject_${submodule_target}_sha externalproject_${dep_target}_sha)
    endforeach(dep)
  endif(deps)
endforeach(submodule)

##
# A target which writes solib search path configuration for gdb into a file
#
if(NOT "${submodules}" STREQUAL "")
  add_custom_target(rw.gdbinit ALL
    COMMAND ${PROJECT_TOP_DIR}/scripts/util/generate_gdbinit.sh ${CMAKE_INSTALL_PREFIX}
    # This is an utter hack, the gdbinit ends up not included in rpm installs.  For bcache rpms we
    # don't mind; for real rpm installs there may well not be symbols anyway so it'll do for now
    )
endif()

##
# Create a target which combines all installed foss.txt files into a single
# output
##
add_custom_target(rw.foss ALL
  COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/foss/foss.html
  COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX}/foss
  COMMAND ${PROJECT_TOP_DIR}/scripts/util/generate_foss.py
    --foss-dir ${CMAKE_INSTALL_PREFIX}/foss
    --output-file ${CMAKE_INSTALL_PREFIX}/foss/foss.html
  DEPENDS ${submodule_targets}
  )

##
# Add a top level target for forcing the clean on all submodules
##
#??this doesn't work as clean isn't a target it's a freebie from the Makefile generator: add_dependencies(clean ${clean_targets})
#??this doesn't work as two cleans come out?? add_custom_target(clean
#  DEPENDS ${clean_targets}
#  )

##
# Add a top level target for running quick unittests
##
add_custom_target(rw.unittest_long
  DEPENDS ${unittest_long_targets}
  )

##
# Add a top level target for running unittests
##
add_custom_target(rw.unittest 
  DEPENDS ${unittest_targets}
  )

##
# Add a top level target for running systemtests
##
add_custom_target(rw.systemtest
  DEPENDS ${systemtest_targets}
  )

##
# Add a top level target for running coverage
##
add_custom_target(rw.coverage 
  DEPENDS ${coverage_targets}
  )

##
# Add a top level target for generating doxygen documentation
##
add_custom_target(rw.doxygen 
  DEPENDS ${doxygen_targets}
  )

##
# Add a top level target for generating packages
##
add_custom_target(rw.package
  DEPENDS ${package_targets}
  )

##
# Add a top level target for creating build cache
##
add_custom_target(rw.bcache
  DEPENDS ${bcache_targets}
  )

if(NOT submodules)
  message("No submodules are checked out")
endif()

##
# Generate the dependency graph for pictorial viewing
##
add_custom_target(rw.dependency_graph
  COMMAND
  sed s,modules/,,g ${PROJECT_TOP_DIR}/.gitmodules.deps | dot -Tpng -odependency.png
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

##
# Generate cscope sysmbols
##
add_custom_target(rw.cscope
  cscope-indexer -r
  WORKING_DIRECTORY ${PROJECT_TOP_DIR}
  )

##
# Generate pycscope sysmbols
##
add_custom_target(rw.pycscope
  ./scripts/cloud/pycscope-indexer  -v
  WORKING_DIRECTORY ${PROJECT_TOP_DIR}
  )

##
# Perform compilation check on python scripts
##
add_custom_target(rw.pycheck
  COMMAND python ./bin/rift-lint.py -c -t modules -verbose
  WORKING_DIRECTORY ${PROJECT_TOP_DIR}
  )

add_subdirectory(scripts)
