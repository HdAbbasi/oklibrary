# Oliver Kullmann, 9.8.2007 (Swansea)
# Copyright 2007, 2008, 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Settings for building and using Sage

sage_recommended_version_number_okl ?= 2.7.2
sage_supported_not_recommended_version_numbers_okl ?= 2.6
sage_supported_version_numbers_okl ?= $(sage_supported_not_recommended_version_numbers_okl) $(sage_recommended_version_number_okl)

sage_prefix_okl ?= sage

sage_html_template_okl ?= $(OKbuildsystem)/ExternalSources/SpecialBuilds/Documentation/Sage.html
sage_html_output_okl ?= $(local_html_dir)/Sage.html
sage_html_documentation_index_location_okl ?= Sage.html

sage_base_installation_dir_okl ?= $(ExternalSources_installations)/Sage
sage_recommended_package_name_okl ?= $(sage_prefix_okl)-$(sage_recommended_version_number_okl)
sage_installation_dir_okl ?= $(sage_base_installation_dir_okl)/$(sage_recommended_package_name_okl)
sage_base_doc_dir_okl ?= $(ExternalSources_doc)/Sage
sage_doc_dir_okl ?= $(sage_base_doc_dir_okl)/$(sage_recommended_version_number_okl)

sage_call_okl ?= $(sage_installation_dir_okl)/sage

sage_main_index_okl ?= $(sage_installation_dir_okl)/doc/index.html

sage_docu_page_okl ?= $(doc_dir)/doxygen_html/d9/dc3/docus_2Sage_8hpp.html

sage_homepage_url_okl := http://www.sagemath.org/
sage_documentation_url_okl := http://modular.math.washington.edu/sage/documentation.html

sage_targets_prefix_okl := $(sage_prefix_okl)-
sage_recommended_okl := $(sage_targets_prefix_okl)$(sage_recommended_version_number_okl)
sage_source_okl := $(ExternalSources)/sources/Sage/$(sage_recommended_okl)

