# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Tim Mortsolf
# Creation Date: 05/22/2014
# 

cmake_minimum_required(VERSION 2.8)

add_definitions(-std=gnu99)

##
# Add the given directories to those searched by the compiler for include files
# By default the directories are appended onto the current list of directories
##
include_directories(BEFORE
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwsched/src
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwmsg/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwdts/include)

add_library(rwshell_api SHARED
  rwshell_py.c
  rwshell_pt.c
  rwshell_ct.c

  rwshell_mgmt.c)

target_link_libraries(rwshell_api PRIVATE
  rwshell-1.0
  rwshell-mgmt_yang_gen
  rwlib
  talloc
  ${CMAKE_INSTALL_PREFIX}/usr/lib/libdispatch.so
  rwsched
  CoreFoundation
  rwvcs
  rwdts_api
  rw_vx_plugin
  peas-1.0)

add_dependencies(rwshell_api rwmanifest_yang.headers)

install(TARGETS rwshell_api LIBRARY DESTINATION usr/lib COMPONENT ${PKG_LONG_NAME})

add_subdirectory(rwshell)
