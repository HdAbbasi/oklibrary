# Oliver Kullmann, 25.3.2009 (Swansea)
# Copyright 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# ##################################
# Directory Structure
# ################################## 

minisat1_directories_okl := $(minisat_base_installation_dir_okl) $(minisat_base_build_dir_okl) $(minisat1_installation_dir_okl)
minisat2_directories_okl := $(minisat_base_installation_dir_okl) $(minisat_base_build_dir_okl) $(minisat2_installation_dir_okl)
minisatp_directories_okl := $(minisat_base_installation_dir_okl) $(minisat_base_build_dir_okl) $(minisatp_installation_dir_okl)
minisat_directories_okl := $(minisat_base_installation_dir_okl) $(minisat_base_build_dir_okl) $(minisat1_installation_dir_okl) $(minisat2_installation_dir_okl) $(minisatp_installation_dir_okl)

$(minisat_directories_okl) : % : 
	mkdir -p $@


# #################################
# Main Minisat targets
# #################################

.PHONY : minisat minisat1 minisat2 minisatp cleanminisat cleanallminisat

minisat : minisat1 minisat2 minisatp

minisat1 : $(minisat1_directories_okl)
	$(call unarchive,$(minisat1_source_okl),$(minisat_base_build_dir_okl)) $(postcondition) \
	cd $(minisat1_build_dir_okl); $(postcondition) \
	make rs; $(postcondition) \
	cp minisat_static $(minisat1_installation_dir_okl); $(postcondition) \
	ln -s --force $(minisat1_call_okl) $(public_bin_dir_okl)/minisat1; $(postcondition)

minisat2 : $(minisat2_directories_okl)
	$(call unarchive,$(minisat2_source_okl),$(minisat_base_build_dir_okl)) $(postcondition) \
	cd $(minisat2_build_dir_okl)/simp; $(postcondition) \
	make rs; $(postcondition) \
	cp minisat_static $(minisat2_installation_dir_okl); $(postcondition) \
	ln -s --force $(minisat2_call_okl) $(public_bin_dir_okl)/minisat2; $(postcondition)

minisatp : $(minisatp_directories_okl)
	$(call unarchive,$(minisatp_source_okl),$(minisat_base_build_dir_okl)) $(postcondition) \
	cd $(minisatp_build_dir_okl); $(postcondition) \
	make rx; $(postcondition) \
	make rs; $(postcondition) \
	cp minisat+_64-bit_static minisat+_bignum_static $(minisatp_installation_dir_okl); $(postcondition) \
	ln -s --force $(minisatp_call_okl) $(public_bin_dir_okl)/minisat+; $(postcondition) \
	ln -s --force $(minisatpb_call_okl) $(public_bin_dir_okl)/minisat+b; $(postcondition)


# #################################
# Cleaning
# #################################

cleanminisat : 
	-rm -rf $(minisat_base_build_dir_okl)

cleanallminisat : cleanminisat
	-rm -rf $(minisat_base_installation_dir_okl)
