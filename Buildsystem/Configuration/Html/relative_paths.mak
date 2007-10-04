# Oliver Kullmann, 9.9.2007 (Swansea)
# Copyright 2007 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Here all relative paths, to be used in html pages (except in case of
# links between doxygen pages, which are handled by doxygen itself),
# are defined.

# It is assumed here that all relevant make-variables got their values now.

# From the local home page:
rel_lindex_OKlibrary_html_documentation_index_location := $(shell $(rel_path_tool) $(OKlibrary_html_documentation_index_location) $(local_home_page_output))
rel_lindex_OKlibrary_full_documentation_dvi_location := $(shell $(rel_path_tool) $(OKlibrary_full_documentation_dvi_location) $(local_home_page_output))
rel_lindex_main_docu_page := $(shell $(rel_path_tool) $(main_docu_page) $(local_home_page_output))
rel_lindex_main_demo_page := $(shell $(rel_path_tool) $(main_demo_page) $(local_home_page_output))

# From the Aims-page:
rel_aims_accu2006_talk_location := $(shell $(rel_path_tool) $(accu2006_talk_location) $(aims_page_output))

# From the History-page:
rel_history_epsrc_faststream_pdf_location := $(shell $(rel_path_tool) $(epsrc_faststream_pdf_location) $(history_page_output))
rel_history_epsrc_6finalreport_pdf_location := $(shell $(rel_path_tool) $(epsrc_6finalreport_pdf_location) $(history_page_output))
rel_history_epsrc_finalreport_pdf_location := $(shell $(rel_path_tool) $(epsrc_finalreport_pdf_location) $(history_page_output))
rel_history_release_history_output := $(shell $(rel_path_tool) $(release_history_output) $(history_page_output))

# From the external sources page:
rel_les_boost_docu_page := $(shell $(rel_path_tool) $(boost_docu_page) $(externalsources_page_output))
rel_les_mhash_docu_page := $(shell $(rel_path_tool) $(mhash_docu_page) $(externalsources_page_output))
rel_les_gcc_docu_page := $(shell $(rel_path_tool) $(gcc_docu_page) $(externalsources_page_output))
rel_les_ocaml_docu_page := $(shell $(rel_path_tool) $(ocaml_docu_page) $(externalsources_page_output))
rel_les_valgrind_docu_page := $(shell $(rel_path_tool) $(valgrind_docu_page) $(externalsources_page_output))
rel_les_git_docu_page := $(shell $(rel_path_tool) $(git_docu_page) $(externalsources_page_output))
rel_les_doxygen_docu_page := $(shell $(rel_path_tool) $(doxygen_docu_page) $(externalsources_page_output))
rel_les_cmake_docu_page := $(shell $(rel_path_tool) $(cmake_docu_page) $(externalsources_page_output))
rel_les_postgresql_docu_page := $(shell $(rel_path_tool) $(postgresql_docu_page) $(externalsources_page_output))
rel_les_R_docu_page := $(shell $(rel_path_tool) $(R_docu_page) $(externalsources_page_output))
rel_les_gmp_docu_page := $(shell $(rel_path_tool) $(gmp_docu_page) $(externalsources_page_output))
rel_les_sage_docu_page := $(shell $(rel_path_tool) $(sage_docu_page) $(externalsources_page_output))
rel_les_coq_docu_page := $(shell $(rel_path_tool) $(coq_docu_page) $(externalsources_page_output))
rel_les_ubcsat_docu_page := $(shell $(rel_path_tool) $(ubcsat_docu_page) $(externalsources_page_output))
ifeq ($(extsrc_relative),)
  rel_les_boost_html_documentation_index_location := $(boost_html_documentation_index_location)
  rel_les_mhash_html_documentation_index_location := $(mhash_html_documentation_index_location)
  rel_les_gcc_html_documentation_index_location := $(gcc_html_documentation_index_location)
  rel_les_valgrind_html_documentation_index_location := $(valgrind_html_documentation_index_location)
  rel_les_git_html_documentation_index_location := $(git_html_documentation_index_location)
  rel_les_doxygen_html_documentation_index_location := $(doxygen_html_documentation_index_location)
  rel_les_cmake_html_documentation_index_location := $(cmake_html_documentation_index_location)
  rel_les_pgsql_html_documentation_index_location := $(pgsql_html_documentation_index_location)
  rel_les_R_html_documentation_index_location := $(R_html_documentation_index_location)
  rel_les_gmp_html_documentation_index_location := $(gmp_html_documentation_index_location)
  rel_les_ubcsat_html_documentation_index_location := $(ubcsat_html_documentation_index_location)
else
  rel_les_boost_html_documentation_index_location := $(shell $(rel_path_tool) $(boost_html_documentation_index_location) $(externalsources_page_output))
  rel_les_mhash_html_documentation_index_location := $(shell $(rel_path_tool) $(mhash_html_documentation_index_location) $(externalsources_page_output))
  rel_les_gcc_html_documentation_index_location := $(shell $(rel_path_tool) $(gcc_html_documentation_index_location) $(externalsources_page_output))
  rel_les_valgrind_html_documentation_index_location := $(shell $(rel_path_tool) $(valgrind_html_documentation_index_location) $(externalsources_page_output))
  rel_les_git_html_documentation_index_location := $(shell $(rel_path_tool) $(git_html_documentation_index_location) $(externalsources_page_output))
  rel_les_doxygen_html_documentation_index_location := $(shell $(rel_path_tool) $(doxygen_html_documentation_index_location) $(externalsources_page_output))
  rel_les_cmake_html_documentation_index_location := $(shell $(rel_path_tool) $(cmake_html_documentation_index_location) $(externalsources_page_output))
  rel_les_pgsql_html_documentation_index_location := $(shell $(rel_path_tool) $(pgsql_html_documentation_index_location) $(externalsources_page_output))
  rel_les_R_html_documentation_index_location := $(shell $(rel_path_tool) $(R_html_documentation_index_location) $(externalsources_page_output))
  rel_les_gmp_html_documentation_index_location := $(shell $(rel_path_tool) $(gmp_html_documentation_index_location) $(externalsources_page_output))
  rel_les_ubcsat_html_documentation_index_location := $(shell $(rel_path_tool) $(ubcsat_html_documentation_index_location) $(externalsources_page_output))
endif

# to be completed XXX

# From the Internet home page:
rel_ihp_local_home_page_output := $(shell $(rel_path_tool) $(local_home_page_output) $(internet_home_page_output))

