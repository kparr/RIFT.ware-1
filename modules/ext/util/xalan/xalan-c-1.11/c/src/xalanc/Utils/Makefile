#
# Copyright 1999-2004 The Apache Software Foundation.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Output directory
OUTDIR := ../../..

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}

include $(XALANCROOT)/version.incl
include ../../../Makefile.incl


## ----------------------------------------------------------------------------

XSL_NLS_SRC_DIR=$(XALANCROOT)/src/xalanc/NLS

MSGFILENAME=XalanMsg_

CATALOG_NAME=$(MSGFILENAME)$(LOCALE)

ifeq ($(PLATFORM), CYGWIN)
XLIFF_FILE_NAME=$(shell cygpath -u $(XSL_NLS_SRC_DIR)/$(LOCALE)/$(MSGFILENAME)$(LOCALE).xlf)
else
XLIFF_FILE_NAME=$(XSL_NLS_SRC_DIR)/$(LOCALE)/$(MSGFILENAME)$(LOCALE).xlf
endif

MOVE= mv
COPY=cp



INCLUDE_DIR = $(XALANCROOT)/src/xalanc/Include

.PHONY: locale doClean prepare install doCommonInstall doCommonPrepare


	
	
##=================== End of Common for all localization systems area =====
## ----------------------------------------------------------------------------
ifeq ($(MESSAGELOADER),inmem)



locale: $(MESSAGELIB)

$(MESSAGELIB): $(XSL_NLS_DIR)/include/LocalMsgData.hpp
	$(MAKE) -C XalanMsgLib 
ifeq ($(PLATFORM), OS390)
ifneq (${OS390BATCH},1)
	@$(MOVE) XalanMsgLib/*.x ../../../lib
endif
endif

$(XSL_NLS_DIR)/include/LocalMsgData.hpp : $(XSL_BIN_DIR)/MsgCreator $(XLIFF_FILE_NAME)
	$(XSL_BIN_DIR)/MsgCreator $(XLIFF_FILE_NAME) -TYPE $(MESSAGELOADER) -LOCALE $(LOCALE)
	@$(MOVE) LocalMsgIndex.hpp $(XSL_NLS_DIR)/include
	@$(MOVE) LocalMsgData.hpp  $(XSL_NLS_DIR)/include		

install: doCommonInstall
	$(MAKE) -C XalanMsgLib $@



prepare: doCommonPrepare
	
	
endif  # end of ($(MESSAGELOADER),inmem))

## ----------------------------------------------------------------------------

ifeq ($(MESSAGELOADER),icu)
##=============================== Specific for ICU variables ================================

GENRB    = $(ICUROOT)/bin/genrb

PKGDATA  = $(ICUROOT)/bin/pkgdata



##=============================== End of Specific for ICU variables ================================

locale:  $(XSL_NLS_DIR)/icu/$(LOCALE).txt $(MESSAGELIB)

$(MESSAGELIB) : $(XSL_NLS_DIR)/icu/$(LOCALE).txt
	$(GENRB) -p $(LOC_PROJECT_NAME) -d $(XSL_NLS_DIR)/icu -i $(XSL_NLS_DIR)/icu $(XSL_NLS_DIR)/icu/$(LOCALE).txt
	echo $(XSL_NLS_DIR)/icu/$(LOC_PROJECT_NAME)_$(LOCALE).res > $(XSL_NLS_DIR)/icu/res-file-list.txt
	$(PKGDATA) --name $(LOC_PROJECT_NAME) -T $(XSL_NLS_DIR)/icu -v -O $(ICUROOT)/lib/icu/Makefile.inc  --mode dll -d $(XSL_LIB_DIR) $(XSL_NLS_DIR)/icu/res-file-list.txt -M "prefix=$(ICUROOT) TARGET=$(LOC_LIB)"   
	$(LN) -fs $(LOC_LIB) $(XSL_LIB_DIR)/$(LOC_LIBNAME)$(SHLIBSUFFIX)
ifeq ($(PLATFORM), AIX)
	$(LN) -fs $(LOC_LIB) $(XSL_LIB_DIR)/$(LOC_LIBNAME)$(LIB_MAJOR_VER)$(SHLIBSUFFIX)
else	
	$(LN) -fs $(LOC_LIB) $(XSL_LIB_DIR)/$(LOC_LIBNAME)$(SHLIBSUFFIX).$(LIB_MAJOR_VER)
endif ## AIX

$(XSL_NLS_DIR)/icu/$(LOCALE).txt : $(XLIFF_FILE_NAME) $(XSL_BIN_DIR)/MsgCreator
	$(XSL_BIN_DIR)/MsgCreator $(XLIFF_FILE_NAME) -TYPE $(MESSAGELOADER) -LOCALE $(LOCALE)
	$(MOVE) LocalMsgIndex.hpp $(XSL_NLS_DIR)/include
	$(MOVE) $(LOCALE).txt $(XSL_NLS_DIR)/icu
	
prepare: doCommonPrepare
	-${MKDIR} -p $(XSL_NLS_DIR)/icu

install: doCommonInstall
	$(MKINSTALLDIRS) $(DESTDIR)/$(libdir)
	$(INSTALL_PROGRAM) $(XSL_LIB_DIR)/$(LOC_LIB) $(DESTDIR)/$(libdir)
ifneq ($(PLATFORM), OS390)
	$(LN) -fs $(LOC_LIB) $(DESTDIR)/$(libdir)/$(LOC_LIBNAME)$(SHLIBSUFFIX)
ifeq ($(PLATFORM), AIX)
	$(LN) -fs $(LOC_LIB) $(DESTDIR)/$(libdir)/$(LOC_LIBNAME)$(LIB_MAJOR_VER)$(SHLIBSUFFIX)
else	
	$(LN) -fs $(LOC_LIB) $(DESTDIR)/$(libdir)/$(LOC_LIBNAME)$(SHLIBSUFFIX).$(LIB_MAJOR_VER)
endif ## AIX	

endif ## OS390

	
endif # end of ($(MESSAGELOADER),icu)

##=============================== NLS SYSTEM =====================================================
ifeq ($(MESSAGELOADER),nls)


locale:  $(XSL_NLS_DIR)/$(LOCALE)/$(CATALOG_NAME).cat 

$(XSL_NLS_DIR)/$(LOCALE)/$(CATALOG_NAME).cat : $(XLIFF_FILE_NAME) $(XSL_BIN_DIR)/MsgCreator
	$(XSL_BIN_DIR)/MsgCreator $(XLIFF_FILE_NAME) -TYPE $(MESSAGELOADER) -LOCALE $(LOCALE)
	$(MOVE) LocalMsgIndex.hpp $(XSL_NLS_DIR)/include
	$(MOVE) $(CATALOG_NAME).msg $(XSL_NLS_DIR)/nls
	-rm -f $(CATALOG_NAME).cat
	gencat  $(CATALOG_NAME).cat $(XSL_NLS_DIR)/nls/$(CATALOG_NAME).msg
	$(MOVE)	$(CATALOG_NAME).cat $(XSL_NLS_DIR)/nls
	
install: doCommonInstall
	$(MKINSTALLDIRS) $(DESTDIR)/$(libdir)
	$(MKINSTALLDIRS) $(DESTDIR)/$(libdir)/nls
	$(MKINSTALLDIRS) $(DESTDIR)/$(libdir)/nls/msg
	$(MKINSTALLDIRS) $(DESTDIR)/$(libdir)/nls/msg/$(LOCALE)
	$(COPY) $(XSL_NLS_DIR)/nls/$(CATALOG_NAME).cat $(DESTDIR)/$(libdir)/nls/msg/$(LOCALE)	
	
prepare: doCommonPrepare
	-${MKDIR} -p $(XSL_NLS_DIR)/nls
endif
##=============================== END OF NLS SYSTEM ==================================================


##=================== Common for all localization systems area ============

$(XSL_BIN_DIR)/MsgCreator:
	$(MAKE) -C MsgCreator 



doCommonPrepare:
	-${MKDIR} -p $(XSL_NLS_DIR)
	-${MKDIR} -p $(XSL_NLS_DIR)/include

doCommonInstall:
	$(INSTALL_DATA) $(XSL_NLS_DIR)/include/LocalMsgIndex.hpp $(XALANCROOT)/src/xalanc/PlatformSupport

doClean:
	$(MAKE) -C XalanMsgLib $@
	$(MAKE) -C MsgCreator $@
	rm -f	$(XSL_NLS_DIR)/nls/*
	rm -f   $(XSL_NLS_DIR)/icu/*
	rm -f	$(XSL_LIB_DIR)/$(LOC_LIBNAME)*
	rm -f   $(XSL_NLS_DIR)/include/LocalMsgData.hpp
	rm -f 	$(XSL_NLS_DIR)/include/LocalMsgIndex.hpp
	rm -f   $(MESSAGELIB)
	
	

