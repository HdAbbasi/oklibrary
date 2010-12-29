# Matthew Henderson, 25.6.2007 (Swansea)
# Copyright 2007, 2008, 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# ##################################
# Directory Structure
# ################################## 

R_directories_okl := $(R_base_installation_dir_okl) $(R_base_build_dir_okl) $(R_base_doc_dir_okl) $(R_doc_dir_okl)

$(R_directories_okl) : % : 
	mkdir -p $@


# #################################
# Main R targets
# #################################

.PHONY : R R_base R_packages cleanR cleanallR

R : R_base R_packages

R_base : $(R_directories_okl)
	$(call unarchive,$(R_source_package_okl),$(R_base_build_dir_okl)) $(postcondition) \
	cd $(R_build_dir_okl); $(postcondition) \
	echo > $(R_site_profile_okl); $(postcondition) \
	F77=$(gfortran_call_okl) FC=$${F77} CC=$(gcc_call_okl) CXX=$(gpp_call_okl) LDFLAGS="-L $(gcc_lib_okl)" ./configure --prefix=$(R_install_directory_okl); $(postcondition) \
	R_PROFILE=$(R_site_profile_okl) make; $(postcondition) \
	R_PROFILE=$(R_site_profile_okl) make check; $(postcondition) \
	make info; $(postcondition) \
	$(R_install_command_okl) install-info; $(postcondition)
	cp -r $(R_build_dir_okl)/doc $(R_doc_dir_okl); $(postcondition)
	cp -r $(R_build_dir_okl)/library $(R_doc_dir_okl)

R_packages :
	cd $(R_source_dir_okl)/packages; $(postcondition) \
	R_PROFILE=$(R_site_profile_okl) $(R_call_okl) CMD INSTALL $(R_packages_okl); $(postcondition) \
	cp *.pdf $(R_doc_dir_okl); $(postcondition)


# #################################
# Cleaning
# #################################

cleanR : 
	-rm -rf $(R_base_build_dir_okl)

cleanallR : cleanR
	-rm -rf $(R_base_installation_dir_okl) $(R_base_doc_dir_okl)
