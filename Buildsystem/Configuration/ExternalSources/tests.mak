# Oliver Kullmann, 1.8.2007 (Swansea)
# Copyright 2007, 2008 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Tests for external sources.
# To be executed *after* the configuration variables have been set.

# New variables for the configuration of building gcc (to be designed 
# and implemented):

gpp_system_call ?= g++
gcc_system_call ?= gcc

gcc_version_number_extraction := awk '/[0-9]\.[0-9]\.[0-9]/{print $$3}'
# assumes that the output of "gcc --version" contains a line of the form
# (for example) "gcc (GCC) 3.4.3"
# Perhaps all such calls should be replaced by the use of shell pattern matching
# as shown in the setting of version_gpp_system_call (as opposed to
# the setting of version_gcc_system_call) ?

location_gpp_system_call ?= $(shell (type -P $(gpp_system_call)))
ifeq ($(location_gpp_system_call),)
  gpp_system_call_ready ?= NO
else
  version_gpp_system_call ?= $(shell if [[ "$$($(gpp_system_call) --version)" =~ ".*([0-9]\.[0-9]\.[0-9]).*" ]]; then echo $${BASH_REMATCH[1]}; else echo "Unknown"; fi)
# $(shell $(gpp_system_call) --version | $(gcc_version_number_extraction))
  ifeq ($(version_gpp_system_call),$(gcc_recommended_version_number))
    gpp_system_call_ready ?= YES
  else
    gpp_system_call_ready ?= MAYBE
  endif
endif
location_gcc_system_call ?= $(shell (type -P $(gcc_system_call)))
ifeq ($(location_gcc_system_call),)
  gcc_system_call_ready ?= NO
else
  version_gcc_system_call ?= $(shell $(gcc_system_call) --version| $(gcc_version_number_extraction))
  ifeq ($(version_gcc_system_call),$(gcc_recommended_version_number))
    gcc_system_call_ready ?= YES
  else
    gcc_system_call_ready ?= MAYBE
  endif
endif

gpp_local_call ?= $(ExternalSources)/Gcc/$(gcc_recommended_version_number)/bin/g++
gcc_local_call ?= $(ExternalSources)/Gcc/$(gcc_recommended_version_number)/bin/gcc

location_gpp_local_call ?= $(shell (type -P $(gpp_local_call)))
ifeq ($(location_gpp_local_call),)
  gpp_local_call_ready ?= NO
else
  version_gpp_local_call ?= $(shell $(gpp_local_call) --version | $(gcc_version_number_extraction))
  ifeq ($(version_gpp_local_call),$(gcc_recommended_version_number))
    gpp_local_call_ready ?= YES
  else
    gpp_local_call_ready ?= ERROR
  endif
endif
location_gcc_local_call ?= $(shell (type -P $(gcc_local_call)))
ifeq ($(location_gcc_local_call),)
  gcc_local_call_ready ?= NO
else
  version_gcc_local_call ?= $(shell $(gcc_local_call) --version | $(gcc_version_number_extraction))
  ifeq ($(version_gcc_local_call),$(gcc_recommended_version_number))
    gcc_local_call_ready ?= YES
  else
    gcc_local_call_ready ?= ERROR
  endif
endif

# the following construction needs to be generalised by some function
gcc_html_documentation_index_location_tag ?= <a href="$(gcc_html_documentation_index_location)">$(gcc_html_documentation_index_location)</a>

# New variables for the configuration of building doxygen (to be designed 
# and implemented):

location_doxygen_call_okl ?= $(shell (type -P $(doxygen_call_okl)))
ifeq ($(location_doxygen_call_okl),)
  doxygen_call_ready_okl ?= NO
else
  version_doxygen_call_okl ?= $(shell $(doxygen_call_okl) --version)
  ifeq ($(version_doxygen_call_okl),$(doxygen_recommended_version_number_okl))
    doxygen_call_ready_okl ?= YES
  else
    doxygen_call_ready_okl ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
doxygen_html_documentation_index_location_tag_okl ?= <a href="$(doxygen_html_documentation_index_location_okl)">$(doxygen_html_documentation_index_location_okl)</a>

# New variables for the configuration of building ocaml (to be designed 
# and implemented):

ocaml_call ?= $(ocaml_bin_dir)/ocaml

ocaml_version_number_extraction := awk '/ [0-9]+\.[0-9]+(\.[0-9]+)?/{print $$6}'
# assumes that the output of "ocaml -version" contains a line of the form
# (for example) "The Objective Caml toplevel, version 3.10.0"

location_ocaml_call ?= $(shell (type -P $(ocaml_call)))
ifeq ($(location_ocaml_call),)
  ocaml_call_ready ?= NO
else
  version_ocaml_call ?= $(shell $(ocaml_call) -version | $(ocaml_version_number_extraction))
  ifeq ($(version_ocaml_call),$(ocaml_recommended_version_number))
    ocaml_call_ready ?= YES
  else
    ocaml_call_ready ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
ocaml_docu_page_tag ?= <a href="$(ocaml_docu_page)">Ocaml installation page</a>


# New variables for the configuration of building coq (to be designed 
# and implemented):

coq_call ?= $(ExternalSources)/Coq/$(coq_recommended_version_number)/bin/coqtop

coq_version_number_extraction := awk '/ [0-9]\.[0-9] /{print $$6}'
# assumes that the output of "coq --version" contains a line of the form
# (for example) "The Coq Proof Assistant, version 8.1 (Feb. 2007)"

location_coq_call ?= $(shell (type -P $(coq_call)))
ifeq ($(location_coq_call),)
  coq_call_ready ?= NO
else
  version_coq_call ?= $(shell $(coq_call) --version | $(coq_version_number_extraction))
  ifeq ($(version_coq_call),$(coq_recommended_version_number))
    coq_call_ready ?= YES
  else
    coq_call_ready ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
coq_html_documentation_index_location_tag ?= <a href="$(coq_html_output)">$(coq_html_output)</a>


# New variables for the configuration of building sage (to be designed 
# and implemented):

sage_call ?= $(sage_installation_dir)/sage

sage_version_number_extraction := > /dev/null; echo $$?
# sage doesn't allow to ask for the version number

location_sage_call ?= $(shell (type -P $(sage_call)))
ifeq ($(location_sage_call),)
  sage_call_ready ?= NO
else
  output_sage_call ?=  $(shell $(sage_call) -h $(sage_version_number_extraction))
  ifeq ($(output_sage_call),1)
    version_sage_call ?= $(sage_recommended_version_number)
  else
    version_sage_call ?= UNKNOWN
  endif
  ifeq ($(version_sage_call),$(sage_recommended_version_number))
    sage_call_ready ?= YES
  else
    sage_call_ready ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
sage_html_documentation_index_location_tag ?= <a href="$(sage_html_output)">$(sage_html_output)</a>


# New variables for the configuration of building git (to be designed 
# and implemented):

git_version_number_extraction_okl := awk '/ [0-9]\.[0-9](\.[0-9])+/{print $$3}'
# assumes that the output of "git --version" contains a line of the form
# (for example) "git version 1.5.2.4" or "git version 1.5.4"

location_git_call_okl ?= $(shell (type -P $(git_call_okl)))
ifeq ($(location_git_call_okl),)
  git_call_ready_okl ?= NO
else
  version_git_call_okl ?= $(shell $(git_call_okl) --version | $(git_version_number_extraction_okl))
  ifeq ($(version_git_call_okl),$(git_recommended_version_number_okl))
    git_call_ready_okl ?= YES
  else
    git_call_ready_okl ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
git_html_documentation_index_location_tag_okl ?= <a href="$(git_html_documentation_index_location_okl)">$(git_html_documentation_index_location_okl)</a>


# New variables for the configuration of building gmp (to be designed 
# and implemented):

check_gmp_header_okl ?= $(shell [[ -f $(gmp_source_library_okl)/gmp.h ]]; echo $$?)
ifneq ($(check_gmp_header_okl),0)
  gmp_ready_okl ?= NO
else
  version_gmp_okl ?= $(shell basename $$(dirname $(gmp_source_library_okl)))
  ifeq ($(version_gmp_okl),$(gmp_recommended_version_number_okl))
    gmp_ready_okl ?= YES
  else
    gmp_ready_okl ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
gmp_html_documentation_index_location_tag_okl ?= <a href="$(gmp_html_documentation_index_location_okl)">$(gmp_html_documentation_index_location_okl)</a>

# New variables for the configuration of building valgrind (to be designed 
# and implemented):

valgrind_call_okl ?= valgrind

valgrind_version_number_extraction_okl := sed 's/valgrind-\([0-9]\.[0-9]\.[0-9]\)/\1/'
# assumes that the output of "valgrind --version" is a line of the form
# (for example) "valgrind-3.2.3"

location_valgrind_call_okl ?= $(shell (type -P $(valgrind_call_okl)))
ifeq ($(location_valgrind_call_okl),)
  valgrind_call_ready_okl ?= NO
else
  version_valgrind_call_okl ?= $(shell $(valgrind_call_okl) --version | $(valgrind_version_number_extraction_okl))
  ifeq ($(version_valgrind_call_okl),$(valgrind_recommended_version_number_okl))
    valgrind_call_ready_okl ?= YES
  else
    valgrind_call_ready_okl ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
valgrind_html_documentation_index_location_tag_okl ?= <a href="$(valgrind_html_documentation_index_location_okl)">$(valgrind_html_documentation_index_location_okl)</a>

# New variables for the configuration of building postgresql (to be designed 
# and implemented):

postgresql_call ?= psql

postgresql_version_number_extraction := awk '/ [0-9]\.[0-9]\.[0-9]+/{print $$3}'
# assumes that the output of "postgresql --version" contains a line of the form
# (for example) "psql (PostgreSQL) 7.4.13"

location_postgresql_call ?= $(shell (type -P $(postgresql_call)))
ifeq ($(location_postgresql_call),)
  postgresql_call_ready ?= NO
else
  version_postgresql_call ?= $(shell $(postgresql_call) --version | $(postgresql_version_number_extraction))
  ifeq ($(version_postgresql_call),$(postgresql_recommended_version_number))
    postgresql_call_ready ?= YES
  else
    postgresql_call_ready ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
postgresql_html_documentation_index_location_tag ?= <a href="$(postgresql_html_documentation_index_location)">$(postgresql_html_documentation_index_location)</a>

# New variables for the configuration of building R (to be designed 
# and implemented):

R_version_number_extraction_okl := awk '/ [0-9]\.[0-9]\.[0-9]/{print $$3}'
# assumes that the output of "R --version" contains a line of the form
# (for example) "R version 2.5.0 (2007-04-23)"

location_R_call_okl ?= $(shell (type -P $(R_call_okl)))
ifeq ($(location_R_call_okl),)
  R_call_ready_okl ?= NO
else
  version_R_call_okl ?= $(shell $(R_call_okl) --version | $(R_version_number_extraction_okl))
  ifeq ($(version_R_call_okl),$(R_recommended_version_number_okl))
    R_call_ready_okl ?= YES
  else
    R_call_ready_okl ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
R_html_documentation_index_location_tag_okl ?= <a href="$(R_html_documentation_index_location_okl)">$(R_html_documentation_index_location_okl)</a>


# New variables for the configuration of building clisp (to be designed 
# and implemented):

clisp_version_number_extraction_okl := awk '/ CLISP [0-9]+\.[0-9]+/{print $$3}'
# assumes that the output of "clisp -version" contains a line of the form
# (for example) "GNU CLISP 2.43 (2007-11-18) (built 3407616533) (memory 3407616899)"

location_clisp_call_okl ?= $(shell (type -P $(clisp_call_okl)))
ifeq ($(location_clisp_call_okl),)
  clisp_call_ready_okl ?= NO
else
  version_clisp_call_okl ?= $(shell $(clisp_call_okl) --version | $(clisp_version_number_extraction_okl))
  ifeq ($(version_clisp_call_okl),$(clisp_recommended_version_number_okl))
    clisp_call_ready_okl ?= YES
  else
    clisp_call_ready_okl ?= MAYBE
  endif
endif



# New variables for the configuration of building maxima (to be designed 
# and implemented):

maxima_version_number_extraction_okl := awk '/Maxima [0-9]+\.[0-9]+\.[0-9]+/{print $$2}'
# assumes that the output of "maxima --version" contains a line of the form
# (for example) "Maxima 5.14.0"

location_maxima_call_okl ?= $(shell (type -P $(maxima_call_okl)))
ifeq ($(location_maxima_call_okl),)
  maxima_call_ready_okl ?= NO
else
  version_maxima_call_okl ?= $(shell $(maxima_call_okl) --version | $(maxima_version_number_extraction_okl))
  ifeq ($(version_maxima_call_okl),$(maxima_recommended_version_number_okl))
    maxima_call_ready_okl ?= YES
  else
    maxima_call_ready_okl ?= MAYBE
  endif
endif

# the following construction needs to be generalised by some function
maxima_html_documentation_index_location_tag_okl ?= <a href="$(maxima_html_output_okl)">$(maxima_html_output_okl)</a>



# New variables for the configuration of building ubcsat (to be designed 
# and implemented):

ubcsat_version_number_extraction_okl := awk '/UBCSAT version [0-9]+\.[0-9]+\.[0-9]+/{print $$4}'
# assumes that the output of "ubcsat --version" contains a line of the form
# (for example) "# UBCSAT version 1.0.0 (Grouse Mountain Release)"

location_ubcsat_call_okl ?= $(shell (type -P $(ubcsat_call_okl)))
ifeq ($(location_ubcsat_call_okl),)
  ubcsat_call_ready_okl ?= NO
else
  version_ubcsat_call_okl ?= $(shell $(ubcsat_call_okl) -hc | $(ubcsat_version_number_extraction_okl))
  ifeq ($(version_ubcsat_call_okl),$(subst -,.,$(ubcsat_recommended_version_number_okl)))
    ubcsat_call_ready_okl ?= YES
  else
    ubcsat_call_ready_okl ?= MAYBE
  endif
endif

