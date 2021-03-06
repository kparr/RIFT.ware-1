

PACKAGE_VERSION := 2.0.0
RPM_REVISION := 4
# Where do we install our files.
installdir := ""

# Various commands we need.
MKDIR_P := mkdir -p
CP_P := cp -p
# In some environment this command can be called `gsha1sum' or `digest'.
SHA1SUM := sha1sum
ZIP := zip -9

# Our "source tree" is in the parent directory, always.
VPATH := ..

# What files to put in the RPM.
FILES := 
    
git_version := \
  `git rev-list --pretty=format:%h HEAD --max-count=1 | sed 1d || echo unknown`
git_fullsha1 := \
  `git rev-list --pretty=format:%H HEAD --max-count=1 | sed 1d || echo unknown`
# What / where do we build.
DESTDIR := destdir
RPM_TARGET := noarch
BASENAME := dpdk_tools-$(PACKAGE_VERSION)-$(RPM_REVISION)
RPM := $(BASENAME).$(RPM_TARGET).rpm
RWREPO_ROOT := /net/charm/localdisk/jenkins/rwrepo
RWREPO_BASE := $(RWREPO_ROOT)/releases/20/Everything/x86_64/os

all: rpm 
rpm: $(RPM)

.spec.rpm:
	rpmbuild --target=$(RPM_TARGET) --buildroot=`pwd`/$(DESTDIR) -bb $<
	mv noarch/$(RPM) ./
	rm -rf noarch

update-repo: .update-repo
.update-repo: $(RPM)
	if test -f "$(RWREPO_BASE)/Packages/$(RPM)"; then \
	  echo "Same version of rpm already on repo" && exit 1; \
	fi
	$(CP_P) $(RPM) $(RWREPO_BASE)/Packages/ || exit 1
	createrepo --update --database $(RWREPO_BASE) || exit 1
	echo "updating cobbler....."
	ssh root@cobbler cobbler reposync --only=riftware
	@touch $@

.dist-stamp: $(FILES) Makefile
	rm -rf $(DESTDIR)
	$(MKDIR_P) "$(DESTDIR)"
	@: >filelist 
	for file in $(FILES); do \
          d=`dirname "$$file"`;  \
          if test ! -d "$(DESTDIR)/$(installdir)/$$d"; then \
            echo "%dir \"$(installdir)/$$d\"" >>filelist; \
            echo $(MKDIR_P) "'$(DESTDIR)/$(installdir)/$$d'"; \
            $(MKDIR_P) "$(DESTDIR)/$(installdir)/$$d" || exit $$?; \
          fi; \
          echo "\"$(installdir)/$$file\"" >>filelist; \
          case $$file in \
            (*.py) echo "\"$(installdir)/$${file}c\"" >>filelist;; \
          esac; \
          echo $(CP_P) "$(VPATH)/$$file" "'$(DESTDIR)/$(installdir)/$$file'"; \
          $(CP_P) "$(VPATH)/$$file" "$(DESTDIR)/$(installdir)/$$file" || exit $$?; \
        done
	chmod -R a+rX "$(DESTDIR)"
	@touch $@

common.spec: .dist-stamp dpdk_tools.spec ChangeLog Makefile
	set -e; { \
          echo "# File generated by Makefile, do not edit"; \
          sed \
            -e 's/@PACKAGE_VERSION@/$(PACKAGE_VERSION)/' \
            -e "s/@GIT_SHORTSHA1@/$(git_version)/" \
            -e "s/@GIT_FULLSHA1@/$(git_fullsha1)/" \
            -e 's/@RPM_REVISION@/$(RPM_REVISION)/' \
            dpdk_tools.spec; \
        } >$@-t
	mv $@-t $@

RPM_SPEC := $(RPM:.rpm=.spec)
$(RPM_SPEC): common.spec linux.spec
	# Note: $^ is common.spec linux.spec, $@ is the target itself
	mkdir -p $(DESTDIR)/usr/bin
	cp $(VPATH)/dpdk_nic_bind.py $(DESTDIR)/usr/bin
	{ \
          cat $^; \
          echo %files; \
          cat filelist; \
	  echo '%attr(755, -, -) "/usr/bin/dpdk_nic_bind.py"'; \
          echo %changelog; \
          cat ChangeLog; \
          echo %description; \
	} >$@-t
	mv $@-t $@

clean: 
	#rm -rf "$(DESTDIR)/$(installdir)"
	rm -rf "$(DESTDIR)"
	@test -d "$(DESTDIR)" || exit 0; \
        find "$(DESTDIR)" -depth -type d \
        | while read dir; do \
          echo rmdir "'$$dir'"; \
          rmdir "$$dir" || exit $$?; \
        done
	rm -f common.spec $(RPM_SPEC) filelist manifest.txt 
	rm *.rpm
	@rm -f .dist-stamp

help:
	@echo "Usage:"
	@echo "  make help:  		This message"
	@echo "  make:  		Create the target rpm"
	@echo "  make update-repo:  	Update the rpm to repo"
	@echo "  make clean:  		Clean up.(Do so before push this code to git)"


.PHONY: all rpm clean help
.SUFFIXES: .spec .rpm
