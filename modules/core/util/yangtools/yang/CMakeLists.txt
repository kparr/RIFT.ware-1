# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Tom Seidenberg
# Creation Date: 2014/02/13
# 

set(yang_install_dir ${CMAKE_INSTALL_PREFIX}/usr/data/yang)

##
# Parse the IETF yang files.
##
set(ietf_yang_sources
  ietf-inet-types.yang 
  ietf-yang-types.yang
  ietf-netconf.yang
  ietf-netconf-notifications.yang
)

rift_add_yang_target(
  TARGET ietf_yang
  YANG_FILES ${ietf_yang_sources}
  WITHOUT_CONFD 
  COMPONENT ${PKG_LONG_NAME}
  DEPENDS RwYang_gi RwKeyspec_gi RwSchemaProto_gi
)

##
# Parse the Yuma yang files.
##
rift_files_prepend_path(yuma_yang_sources ${yang_install_dir}
  yuma-types.yang 
  yuma-app-common.yang 
  yangdump.yang
)

rift_add_yang_target(
  TARGET yuma_yang
  YANG_FILES ${yuma_yang_sources}
  WITHOUT_CONFD 
  WITHOUT_PROTO 
  WITHOUT_LIB 
  WITHOUT_GI
  NO_INSTALL_YANG
  COMPONENT ${PKG_LONG_NAME}
  EXCLUDE_RWYANG_PB_LIBRARY
  DEPENDS ietf_yang.headers
)

##
# Build our yang files
##
set(rwext_yang_files
  rw-cli-ext.yang
  rw-pb-ext.yang
  rw-notify-ext.yang
  rw-yang-types.yang
  rw-3gpp-types.yang
  rw-c-types.yang
  rw-netconf.yang
  rw-keyspec-stats.yang
  rw-pbc-stats.yang
)

rift_add_yang_target(
  TARGET rwext_yang
  YANG_FILES ${rwext_yang_files}
  COMPONENT ${PKG_LONG_NAME}
  LIBRARIES ietf_yang_gen
  DEPENDS ietf_yang.headers
)

add_custom_target(yangtools_yang DEPENDS ietf_yang rwext_yang)
add_custom_target(yangtools_yang.headers
  DEPENDS ietf_yang.headers yuma_yang.headers rwext_yang.headers)
add_custom_target(yangtools_yang.schema
  DEPENDS ietf_yang.schema yuma_yang.schema rwext_yang.schema)

