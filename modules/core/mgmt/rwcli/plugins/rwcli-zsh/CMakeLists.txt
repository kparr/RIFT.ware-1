# 
# (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
#
# Author(s): Tim Mortsolf
# Creation Date: 3/20/2014
# 

cmake_minimum_required(VERSION 2.8)

set(PKG_NAME rwcli_zsh)
set(PKG_VERSION 1.0)
set(PKG_RELEASE 1)
set(PKG_LONG_NAME ${PKG_NAME}-${PKG_VERSION})

##
# Add flags to the compiler command line for sources in the 
# current directory and below
##
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DMODULE)

##
# Add the given directories to those searched by the compiler for include files
# By default the directories are appended onto the current list of directories
##
include_directories(BEFORE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_INSTALL_PREFIX}/usr/include/zsh
  ${CMAKE_INSTALL_PREFIX}/usr/include/zsh/Src
  ${CMAKE_INSTALL_PREFIX}/usr/include/zsh/Src/Zle
  )

set(C_SOURCES rift.c)
add_library(rift_zsh SHARED ${C_SOURCES})
add_dependencies(rift_zsh zsh rwcli)
# For ZSH plugin the lib prefix should not be present 
set_target_properties(rift_zsh
  PROPERTIES 
    PREFIX ""
    OUTPUT_NAME "rift"
    LINK_FLAGS "-lcrypto -ldl -lncursesw -lrt -lm  -lc")
target_link_libraries(rift_zsh
  ${RIFT_SUBMODULE_BINARY_ROOT}/rwcli/src/librwcli.so)
install(TARGETS rift_zsh
  LIBRARY DESTINATION usr/lib/zsh/5.0.7/zsh 
  COMPONENT ${PKG_LONG_NAME})

set(C_SOURCES rwmsg_agent.c)
add_library(rwmsg_agent SHARED ${C_SOURCES})
add_dependencies(rwmsg_agent zsh rwcli)
# For ZSH plugin the lib prefix should not be present 
set_target_properties(rwmsg_agent
  PROPERTIES 
    PREFIX ""
    LINK_FLAGS "-L${RIFT_SUBMODULE_BINARY_ROOT}/rwcli/plugins/rwcli-zsh -ldl -lncursesw -lrt -lm  -lc")
target_link_libraries(rwmsg_agent
  ${RIFT_SUBMODULE_BINARY_ROOT}/rwcli/src/librwcli.so rwlogdproto)
install(TARGETS rwmsg_agent 
  LIBRARY DESTINATION usr/lib/zsh/5.0.7/zsh 
  COMPONENT ${PKG_LONG_NAME})

set(C_SOURCES rwnetconf_agent.c)
add_library(rwnetconf_agent SHARED ${C_SOURCES})
add_dependencies(rwnetconf_agent zsh rwcli)
# For ZSH plugin the lib prefix should not be present 
set_target_properties(rwnetconf_agent
  PROPERTIES 
    PREFIX ""
    LINK_FLAGS "-L${RIFT_SUBMODULE_BINARY_ROOT}/rwcli/plugins/rwcli-zsh -ldl -lncursesw -lrt -lm  -lc")
target_link_libraries(rwnetconf_agent
  ${RIFT_SUBMODULE_BINARY_ROOT}/rwcli/src/librwcli.so)
install(TARGETS rwnetconf_agent 
  LIBRARY DESTINATION usr/lib/zsh/5.0.7/zsh 
  COMPONENT ${PKG_LONG_NAME})

install(FILES rwnetconf_agent.py
  PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  DESTINATION usr/bin
  COMPONENT ${PKG_LONG_NAME})
