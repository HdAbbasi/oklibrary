# Oliver Kullmann, 24.12.2007 (Swansea)
# Copyright 2007, 2008 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# This installation possibly has to be performed by hand, since apparently the
# configure-script of the clisp-installation cannot handle correctly
# the bash-shell.

# The clisp-configure-script apparently cannot handle correctly bash in the
# context of make.

# ##################################
# Directory Structure
# ################################## 

clisp_directories_okl := $(clisp_base_installation_dir_okl) $(clisp_base_build_dir_okl) $(clisp_base_doc_dir_okl) $(clisp_doc_dir_okl)

$(clisp_directories_okl) : % : 
	mkdir -p $@

# #################################
# Main clisp targets
# #################################

.PHONY : clisp

ifeq ($(clisp_recommended_version_number_okl),2.45)
clisp : $(clisp_directories_okl)
	$(call unarchive,$(clisp_source_okl),$(clisp_base_build_dir_okl))
	cd $(clisp_build_dir_okl); $(postcondition) \
	./configure --prefix=$(clisp_installation_dir_okl) --with-libsigsegv-prefix=$(libsigsegv_installation_dir_okl) --with-libffcall-prefix=$(libffcall_installation_dir_okl) --cbc $(clisp_build_dir_okl)/oklib-build; $(postcondition) \
	cd $(clisp_build_dir_okl)/oklib-build; $(postcondition) \
	make install; $(postcondition)
	cp -f $(clisp_installation_dir_okl)/share/doc/doc/* $(clisp_doc_dir_okl)
else
clisp : $(clisp_directories_okl)
	$(call unarchive,$(clisp_source_okl),$(clisp_base_build_dir_okl))
	cd $(clisp_build_dir_okl); $(postcondition) \
	./configure --prefix=$(clisp_installation_dir_okl) --with-libsigsegv-prefix=$(libsigsegv_installation_dir_okl) --build $(clisp_build_dir_okl)/oklib-build; $(postcondition) \
	cd $(clisp_build_dir_okl)/oklib-build; $(postcondition) \
	make; $(postcondition) \
        make check; $(postcondition) \
	make install; $(postcondition)
	cp -f $(clisp_installation_dir_okl)/share/doc/doc/* $(clisp_doc_dir_okl)
endif


# #################################
# Cleaning
# #################################

cleanallclisp : 
	-rm -rf $(clisp_base_installation_dir_okl) $(clisp_base_build_dir_okl) $(clisp_base_doc_dir_okl)


# #################################
# Tool libsigsegv
###################################

libsigsegv_directories_okl := $(libsigsegv_base_build_dir_okl) $(libsigsegv_base_installation_dir_okl)

.PHONY : libsigsegv

$(libsigsegv_directories_okl) : % : 
	mkdir -p $@

libsigsegv : $(libsigsegv_directories_okl)
	$(call unarchive,$(libsigsegv_source_okl),$(libsigsegv_base_build_dir_okl))
	cd $(libsigsegv_build_dir_okl); $(postcondition) \
	./configure --prefix=$(libsigsegv_installation_dir_okl); $(postcondition) \
	make; $(postcondition) \
	make check; $(postcondition) \
	make install; $(postcondition)

cleanalllibsigsegv : 
	-rm -rf $(libsigsegv_base_build_dir_okl) $(libsigsegv_base_installation_dir_okl) 


# #################################
# Tool libffcall
###################################

libffcall_directories_okl := $(libffcall_base_build_dir_okl) $(libffcall_base_installation_dir_okl)

.PHONY : libffcall

$(libffcall_directories_okl) : % : 
	mkdir -p $@

libffcall : $(libffcall_directories_okl)
	$(call unarchive,$(libffcall_source_okl),$(libffcall_base_build_dir_okl))
	cd $(libffcall_build_dir_okl); $(postcondition) \
	./configure --prefix=$(libffcall_installation_dir_okl); $(postcondition) \
	make; $(postcondition) \
	make check; $(postcondition) \
	make install; $(postcondition)

cleanalllibffcall : 
	-rm -rf $(libffcall_base_build_dir_okl) $(libffcall_base_installation_dir_okl) 
