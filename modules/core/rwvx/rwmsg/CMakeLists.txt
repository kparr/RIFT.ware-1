# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Anil Gunturu
# Creation Date: 8/29/2013
# 

cmake_minimum_required(VERSION 2.8)

set(PKG_NAME rwmsg)
set(PKG_VERSION 1.0)
set(PKG_RELEASE 1)
set(PKG_LONG_NAME ${PKG_NAME}-${PKG_VERSION})

# IMHO this should just be the default
rift_werror()

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")

##
# This appends to the list of directories to search for
# header files. INCLUDE_DIRECTORIES is a DIRECTORY property and
# is inherited from the parent directory.
#
include_directories(BEFORE
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwmsg/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwdts/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwmemlogdts/include/riftware
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwsched/src
  ${CMAKE_CURRENT_BINARY_DIR}
  /usr/include/libxml2)

set(LIB_SOURCES
  src/rwmsg_endpoint.c
  src/rwmsg_destination.c
  src/rwmsg_signature.c
  src/rwmsg_method.c
  src/rwmsg_queue.c
  src/rwmsg_notify.c
  src/rwmsg_srvchan.c
  src/rwmsg_clichan.c
  src/rwmsg_sockset.c
  src/rwmsg_request.c
  src/rwmsg_channel.c
  )
add_library(rwmsg SHARED ${LIB_SOURCES})
target_link_libraries(rwmsg PRIVATE
  rwlib
  ck
  CoreFoundation
  dispatch
  glib-2.0
  nanomsg
  protobuf-c
  pthread
  talloc

  rwcal_api
  rwsched
  rwmsg_yang_gen
  rwlog
  rwtrace)

# Broker, a tasklet in a library.  Probably to be a plugin .do in the end
set(BROKER_SOURCES
  src/rwmsg_broker.c
  src/rwmsg_broker_acceptor.c
  src/rwmsg_broker_clichan.c
  src/rwmsg_broker_srvchan.c
  src/rwmsg_broker_channel.c
  src/rwmsg_broker_main.c
  )
add_library(rwmsgbroker SHARED ${BROKER_SOURCES})
target_link_libraries(rwmsgbroker PRIVATE
  rwcal_api
  rwlib
  rwmsg
  rwsched
  rwtrace
  rwvcs
  rwtasklet
  rwmemlog
  rwmemlog_yang_gen

  CoreFoundation
  ck
  dispatch
  glib-2.0
  protobuf-c
  rwmsg_yang_gen
  rwlog
  talloc)

##
# Add the target for the rwmsg-uagent static library
##
set(BROKERUAGENT_SOURCES
  src/rwmsg_broker_dts.c
  src/rwmsg_broker_mgmt.c)

add_library(rwmsgbrokeruagent STATIC ${BROKERUAGENT_SOURCES})

# link with all the libraries that brokeruagent depends on
target_link_libraries(rwmsgbrokeruagent PRIVATE
  rwmsg
  rwyang
  rwdts_api
  rwsched
  CoreFoundation
  ck
  dispatch)

# add the dependencies for rwmsgbrokeruagent
add_dependencies(rwmsgbrokeruagent rwmsgbroker rwmsg rwmsg_yang.headers rw_tasklet_plugin-1.0 rwdts_api)

# Compile protobuf files
rift_add_proto_target(
  TARGET rwmsg_test_proto
  SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto
  PROTO_FILES test1.proto
  OUT_C_FILES_VAR proto_c_files
)

# Linkage testing executable
set(C_SOURCES src/test_rwmsg_api.c ${proto_c_files})
set(rwmsg_link_libs
  rwlib
  rwlog
  rwmsg
  rwsched
  rwtrace

  BlocksRuntime
  ck
  dispatch
  event
  glib-2.0
  nanomsg
  protobuf-c
  talloc
  unwind)
add_executable(rwmsg_testlink ${C_SOURCES})
target_link_libraries(rwmsg_testlink ${rwmsg_link_libs})
add_dependencies(rwmsg_testlink rwmsg_test_proto)

# Experiment vehicle for nanomsg threaded, dethreaded, and event-driven.
# Toy scheduler to support the experiment.
set(C_SOURCES rwmsg_experiment.c rwmsg_toysched.c)
add_executable(rwmsg_exp ${C_SOURCES})
add_dependencies(rwmsg_exp rwmsg rwsched rwlog)
target_link_libraries(rwmsg_exp ${rwmsg_link_libs})

# Same vehicle linked against libdispatch-based scheduler's toy api instead
set(SCHED_C_SOURCES rwmsg_experiment.c)
add_executable(rwmsg_rwsched_exp ${SCHED_C_SOURCES})
target_link_libraries(rwmsg_rwsched_exp ${rwmsg_link_libs})
add_dependencies(rwmsg_rwsched_exp rwmsg rwsched rwlog)

set(C_SOURCES rwmsg_experiment.c)
add_executable(rwmsg_cf_exp ${C_SOURCES})
target_link_libraries(rwmsg_cf_exp ${rwmsg_link_libs})
add_dependencies(rwmsg_cf_exp rwmsg rwsched rwlog)
set_target_properties(rwmsg_cf_exp PROPERTIES COMPILE_DEFINITIONS "_CF_")

##
# The following code installs the targets to
# ${CMAKE_INSTALL_PREFIX}/usr/bin.
# Always use relative path for destination.
#
# NOTE: In some examples the install command may also be called
# with COMPONENT label. This is for CPACK component based
# installation.
##
set(INSTALL_HFILES
  include/rwmsg.h
  include/rwmsg_api.h
  include/rwmsg_endpoint.h
  include/rwmsg_destination.h
  include/rwmsg_signature.h
  include/rwmsg_method.h
  include/rwmsg_queue.h
  include/rwmsg_notify.h
  include/rwmsg_srvchan.h
  include/rwmsg_clichan.h
  include/rwmsg_request.h
  include/rwmsg_sockset.h
  )
install(FILES ${INSTALL_HFILES} DESTINATION usr/include COMPONENT ${PKG_LONG_NAME})
install(TARGETS rwmsg LIBRARY DESTINATION usr/lib COMPONENT ${PKG_LONG_NAME})
install(TARGETS rwmsgbroker LIBRARY DESTINATION usr/lib COMPONENT ${PKG_LONG_NAME})

##
# Add the subdirectories
##
set(subdirs
  plugins/rwmsgbroker-c
  plugins/yang
  test)
rift_add_subdirs(SUBDIR_LIST ${subdirs})

##
# documentation target
##
rift_add_doxygen_target(${PKG_NAME}_doxygen
  DEST_DIR ${PKG_NAME}
  DOXY_FILES ${INSTALL_HFILES}
  DOXY_NAME "RWMsg QuickStart and API Reference")

