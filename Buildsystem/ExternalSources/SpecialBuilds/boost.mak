# Matthew Henderson, 19.7.2006 (Paderborn)
# Copyright 2006-2007, 2008, 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# ##################################
# Directory Structure
# ################################## 

boost_directories_okl := $(boost_base_installation_dir_okl) $(boost_base_build_dir_okl) $(boost_base_doc_dir_okl) $(boost_doc_dir_okl) $(boost_build_dir_okl)

$(boost_directories_okl) : % : 
	mkdir -p $@

# #################################
# Main boost targets
# #################################

.PHONY : boost cleanboost cleanallboost

boost : $(boost_directories_okl)
	$(call unarchive,$(boost_source_dir_okl),$(boost_base_build_dir_okl)) $(postcondition) \
	cd $(boost_extracted_package_okl); $(postcondition) \
	cd tools/jam/src; $(postcondition) \
	CC="$(gcc_call_okl)" CFLAGS="-fno-strict-aliasing" ./build.sh cc; $(postcondition) \
	cp bin.*/bjam $(boost_base_build_dir_okl); $(postcondition) \
	cd ../../..; $(postcondition) \
	echo "using gcc : $(gcc_recommended_version_number_okl) : $(gcc_call_okl) : ;" > $(boost_base_build_dir_okl)/bjam_config; $(postcondition) \
	$(boost_base_build_dir_okl)/bjam --user-config=$(boost_base_build_dir_okl)/bjam_config --prefix=$(boost_installation_dir_okl) --build-dir=$(boost_build_dir_okl) install --without-python --without-wave --without-graph; $(postcondition) \
	cd $(boost_link_library_okl); for F in $$(ls | awk '/.*gcc[0-9][0-9].*/'); do ln -s $${F} $$(echo $${F} | sed 's/gcc[0-9][0-9]/gcc/'); done; cd -; $(postcondition) \
	cp -r boost.png boost.css index.htm more libs doc tools $(boost_doc_dir_okl); $(postcondition)



# ####################################
# Cleaning
# ####################################

cleanboost : 
	-rm -rf $(boost_base_build_dir_okl)

cleanallboost : cleanboost
	-rm -rf $(boost_base_installation_dir_okl) $(boost_base_doc_dir_okl)

