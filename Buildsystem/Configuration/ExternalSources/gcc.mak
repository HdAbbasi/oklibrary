# Oliver Kullmann, 26.7.2007 (Swansea)
# Copyright 2007, 2008, 2009, 2010 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Settings for building and using gcc

gcc_recommended_version_number_okl ?= 4.5.2
gcc_other_versions_okl ?= 

gcc_prefix_okl ?= gcc

gcc_recommended_package_name_okl ?= $(gcc_prefix_okl)-$(gcc_recommended_version_number_okl)

gcc_html_template_okl ?= $(OKbuildsystem)/ExternalSources/SpecialBuilds/Documentation/Gcc.html
gcc_html_output_okl ?= $(local_html_dir)/Gcc.html
gcc_html_documentation_index_location_okl ?= Gcc.html

gcc_base_installation_dir_okl ?= $(ExternalSources_installations)/Gcc
gcc_installation_dir_okl ?= $(gcc_base_installation_dir_okl)/$(gcc_recommended_version_number_okl)
gcc_base_build_dir_okl ?= $(ExternalSources_builds)/Gcc
gcc_unarchived_source_okl ?= $(gcc_base_build_dir_okl)/$(gcc_recommended_package_name_okl)
# Since gcc doesn't like very much installation into the extracted source
# directory (as it is normal otherwise), we have the distinction between
# "unarchived_source" and "build_dir".
gcc_build_dir_okl ?= $(gcc_base_build_dir_okl)/$(gcc_recommended_package_name_okl)_build
gcc_base_doc_dir_okl ?= $(ExternalSources_doc)/Gcc
gcc_doc_dir_okl ?= $(gcc_base_doc_dir_okl)/$(gcc_recommended_version_number_okl)

gcc_main_index_okl ?= $(gcc_doc_dir_okl)/html/gcc/index.html
gcc_main_dvi_okl ?= $(gcc_doc_dir_okl)/doc/gcc.dvi
gcc_cpp_index_okl ?= $(gcc_doc_dir_okl)/html/cpp/index.html
gcc_cpp_dvi_okl ?= $(gcc_doc_dir_okl)/doc/cpp.dvi
gcc_install_index_okl ?= $(gcc_doc_dir_okl)/html/gccinstall/index.html
gcc_install_dvi_okl ?= $(gcc_doc_dir_okl)/doc/gccinstall.dvi
gcc_internals_index_okl ?= $(gcc_doc_dir_okl)/html/gccint/index.html
gcc_internals_dvi_okl ?= $(gcc_doc_dir_okl)/doc/gccint.dvi
gcc_libiberty_index_okl ?= $(gcc_doc_dir_okl)/html/libiberty.html

gcc_call_okl ?= $(gcc_installation_dir_okl)/bin/gcc
gpp_call_okl ?= $(gcc_installation_dir_okl)/bin/g++
gcj_call_okl ?= $(gcc_installation_dir_okl)/bin/gcj
gfortran_call_okl ?= $(gcc_installation_dir_okl)/bin/gfortran
gcc_lib_okl ?= $(gcc_installation_dir_okl)/lib
gcc_lib64_okl ?= $(gcc_installation_dir_okl)/lib64

gcc_docu_page_okl ?= $(doc_dir)/doxygen_html/d4/dfb/docus_2Gcc_8hpp.html

gcc_homepage_url_okl := http://gcc.gnu.org/
gcc_documentation_url_okl := http://gcc.gnu.org/onlinedocs/

gcc_source_okl := $(ExternalSources)/sources/Gcc/$(gcc_recommended_package_name_okl)

gcc_enable_languages_okl ?= c,c++,fortran#,java
# disabled java due to build-problems with 4.5.2
gcc_threads_okl ?= posix
gcc_other_options_okl ?= --enable-shared --disable-multilib

# Special handling for gcc-4.1.2

gcc412_unarchived_source_okl ?= $(gcc_base_build_dir_okl)/gcc-4.1.2
gcc412_installation_dir_okl ?= $(gcc_base_installation_dir_okl)/4.1.2
gcc412_build_dir_okl ?= $(gcc_base_build_dir_okl)/gcc-4.1.2_build
gcc412_doc_dir_okl ?= $(gcc_base_doc_dir_okl)/4.1.2
gcc412_source_okl := $(ExternalSources)/sources/Gcc/gcc-4.1.2
gcc412_enable_languages_okl ?= c,c++
gcc412_threads_okl ?= posix
gcc412_other_options_okl ?= --enable-shared
gcc412_corrected_dir_okl := $(OKsystem)/OKlib/Programming/SystemSpecifics/Gcc/412/corrected/
gcc412_patched_dir_okl := $(OKsystem)/OKlib/Programming/SystemSpecifics/Gcc/412/patched/

gcc412_call_okl ?= $(gcc412_installation_dir_okl)/bin/gcc
gpp412_call_okl ?= $(gcc412_installation_dir_okl)/bin/g++
gcc412_lib_okl ?= $(gcc412_installation_dir_okl)/lib
gcc412_lib64_okl ?= $(gcc412_installation_dir_okl)/lib64
