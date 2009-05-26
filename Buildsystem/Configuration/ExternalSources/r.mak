# Oliver Kullmann, 26.7.2007 (Swansea)
# Copyright 2007, 2008, 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Settings for building and using R

R_recommended_version_number_okl ?= 2.9.0
R_supported_not_recommended_version_numbers_okl ?= 2.8.1

R_prefix_okl ?= R

R_targets_prefix_okl := $(R_prefix_okl)-
R_recommended_okl := $(R_targets_prefix_okl)$(R_recommended_version_number_okl)
R_source_dir_okl := $(ExternalSources)/sources/R
R_source_package_okl := $(R_source_dir_okl)/$(R_recommended_okl)

R_base_build_dir_okl ?= $(ExternalSources_builds)/R
R_build_dir_okl ?= $(R_base_build_dir_okl)/$(R_recommended_okl)

R_default_install_okl ?= local
# other possibility: system

R_base_installation_dir_okl ?= $(ExternalSources_installations)/R
R_installation_dir_okl ?= $(R_base_installation_dir_okl)/$(R_recommended_version_number_okl)
R_system_install_directory_okl ?= /usr/local
ifeq ($(R_default_install_okl),local)
  R_install_directory_okl ?= $(R_installation_dir_okl)
  R_install_command_okl ?= make install
  R_call_okl ?= $(R_installation_dir_okl)/bin/R
else
  R_install_directory_okl ?= $(R_system_install_directory)
  R_install_command_okl ?= sudo make install
  R_call_okl ?= R
endif
R_call_parameters ?= --no-environ --no-restore-data --save

R_base_doc_dir_okl ?= $(ExternalSources_doc)/R
R_doc_dir_okl ?= $(R_base_doc_dir_okl)/$(R_recommended_version_number_okl)
R_html_documentation_index_location_okl ?= $(R_doc_dir_okl)/doc/html/index.html
R_dvi_documentation_index_location_okl ?= 
R_pdf_documentation_index_location_okl ?= 
R_docu_page_okl ?= $(doc_dir)/doxygen_html/da/d4d/docus_2R_8hpp.html

R_homepage_url_okl := http://www.r-project.org/
R_documentation_url_okl := http://www.r-project.org/

R_packages_okl := lpSolve_5.6.4.tar.gz QCA_0.5-3.tar.gz Rcmdr_1.4-10.tar.gz
