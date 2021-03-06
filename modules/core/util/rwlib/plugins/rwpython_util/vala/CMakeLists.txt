# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Anil Gunturu
# Creation Date: 8/26/2013
# 

##
# rwpython_util.vala
#
# Set some RIFT specific VALA variables for this cmake project
##
set(VALA_NAME rwpython_util)
set(VALA_FILES ${VALA_NAME}.vala)
set(VALA_VERSION 1.0)
set(VALA_RELEASE 1)
set(VALA_LONG_NAME ${VALA_NAME}-${VALA_VERSION})
set(VALA_TYPELIB_PREFIX rwpython_util-${VALA_VERSION})

##
# This function compiles all the vala sources
# Generates the package .h/.c sources, .gir file, .vapi file, and the .so
##
rift_add_vala(
  ${VALA_LONG_NAME}
  VALA_FILES ${VALA_FILES}
  VALA_PACKAGES rw_types-1.0
  VAPI_DIRS ${RIFT_SUBMODULE_BINARY_ROOT}/rwtypes/src
  GIR_PATHS ${RIFT_SUBMODULE_BINARY_ROOT}/rwtypes/src
  GENERATE_HEADER_FILE ${VALA_NAME}.h
  GENERATE_SO_FILE lib${VALA_LONG_NAME}.so
  GENERATE_VAPI_FILE ${VALA_LONG_NAME}.vapi
  GENERATE_GIR_FILE ${VALA_TYPELIB_PREFIX}.gir
  GENERATE_TYPELIB_FILE ${VALA_TYPELIB_PREFIX}.typelib
  DEPENDS rwtypes_gi
  )

##
# This function creates an install target for artifacts generated from the vala files
##
rift_install_vala_artifacts(
  HEADER_FILES ${VALA_NAME}.h
  SO_FILES lib${VALA_LONG_NAME}.so
  VAPI_FILES ${VALA_LONG_NAME}.vapi
  GIR_FILES ${VALA_TYPELIB_PREFIX}.gir
  TYPELIB_FILES ${VALA_TYPELIB_PREFIX}.typelib
  COMPONENT ${PKG_LONG_NAME}
  DEST_PREFIX .
  )

rift_make_pc(rwpython_util
  LIBS -lrwpython_util-1.0
  LIBDIR ${RIFT_LIBDIR}/rift/plugins
  COMPONENT rwpython_util-1.0)

# Recurse into the subdirectories 
# This does not actually cause another cmake executable to run
# The same process will walk through the project's entire directory structure
set(subdirs ${VALA_NAME}-python)
rift_add_subdirs(SUBDIR_LIST ${subdirs})

