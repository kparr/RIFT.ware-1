# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Tim Mortsolf
# Creation Date: 2014/03/20
# 

cmake_minimum_required(VERSION 2.8)

set(subdirs yang ${PKG_NAME}-c rwdtsperfmgrtasklet rwdtsperftasklet)
rift_add_subdirs(SUBDIR_LIST ${subdirs})
