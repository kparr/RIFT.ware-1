# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Anil Gunturu
# Creation Date: 8/29/2013
# 

cmake_minimum_required(VERSION 2.8)

set(subdirs yang)
rift_add_subdirs(SUBDIR_LIST ${subdirs})

install(FILES packet.pkt DESTINATION usr/bin/ COMPONENT ${PKG_NAME})
install(FILES inbound_gtp.pkt DESTINATION usr/bin/ COMPONENT ${PKG_NAME})
install(FILES outbound_gtp.pkt DESTINATION usr/bin/ COMPONENT ${PKG_NAME})

include_directories(BEFORE
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwsched/src
  ${RIFT_ROOT}/module/core/mgmt/rwcli/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwmsg/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwlog/rwlogd/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwlog/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwlog/rwlogd/sinkapi/include
  ${RIFT_SUBMODULE_SOURCE_ROOT}/rwdts/include)

# RIFT-5033
rift_gtest(rwlogd_gtest
  TEST_SRCS rwlogd_gtest.cc
  TEST_LIBS
    rwlog
    log_test_yang_gen
    dynschema_log_test_yang_gen
    rwlib
    rwlogd-c
    rwlogdproto
    uuid
    dl
  DEPENDS rwlogd_api
)

