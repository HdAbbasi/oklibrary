# Matthew Henderson, 30.10.2006 (Swansea)
# Copyright 2006-2007, 2008, 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Configuration variables regarding installation and documentation of external sources

global_targets_extsrc_okl ?= all clean cleanall update math buildsystem libraries compilers sat

sat_targets_extsrc_okl ?= ubcsat minisat march satz sp grasp
math_targets_extsrc_okl ?= allmaxima gap R # sage
buildsystem_targets_extsrc_okl ?= git doxygen
compiler_targets_extsrc_okl ?= gcc
library_targets_extsrc_okl ?= bzip2 boost mhash gmp
# Dependencies between these external sources:
# minisat needs gmp
# march, grasp need gcc-4.1.2
# boost needs bzip2
# bzip2, boost, mhash, gmp need gcc


ExternalSources_sources ?= $(ExternalSources)/sources

ExternalSources_installations ?= $(ExternalSources)/Installations
ExternalSources_doc ?= $(ExternalSources)/doc
ExternalSources_builds ?= $(ExternalSources)/builds

ext_src_checksum := md5sum

include $(OKconfiguration)/ExternalSources/coq.mak
include $(OKconfiguration)/ExternalSources/doxygen.mak
include $(OKconfiguration)/ExternalSources/gcc.mak
include $(OKconfiguration)/ExternalSources/git.mak
include $(OKconfiguration)/ExternalSources/gmp.mak
include $(OKconfiguration)/ExternalSources/ocaml.mak
include $(OKconfiguration)/ExternalSources/postgresql.mak
include $(OKconfiguration)/ExternalSources/r.mak
include $(OKconfiguration)/ExternalSources/sage.mak
include $(OKconfiguration)/ExternalSources/ubcsat.mak
include $(OKconfiguration)/ExternalSources/valgrind.mak
include $(OKconfiguration)/ExternalSources/clisp.mak
include $(OKconfiguration)/ExternalSources/ecl.mak
include $(OKconfiguration)/ExternalSources/maxima.mak
include $(OKconfiguration)/ExternalSources/asciidoc.mak
include $(OKconfiguration)/ExternalSources/gap.mak
include $(OKconfiguration)/ExternalSources/grasp.mak
include $(OKconfiguration)/ExternalSources/minisat.mak
include $(OKconfiguration)/ExternalSources/march.mak
include $(OKconfiguration)/ExternalSources/satz.mak
include $(OKconfiguration)/ExternalSources/sp.mak
include $(OKconfiguration)/ExternalSources/cmake.mak
include $(OKconfiguration)/ExternalSources/bzip2.mak
include $(OKconfiguration)/ExternalSources/boost.mak
include $(OKconfiguration)/ExternalSources/mhash.mak


# ################################
# mpfr
# ###############################

# NEEDS UPDATE

mpfr_recommended_version_number ?= 2.3.0
mpfr_supported_version_numbers ?= $(mpfr_recommended_version_number)

mpfr_prefix ?= mpfr

mpfr_homepage_url := http://www.mpfr.org/

mpfr_targets_prefix := $(mpfr_prefix)-
mpfr_targets := $(addprefix $(mpfr_targets_prefix), $(mpfr_supported_version_numbers))
mpfr_recommended := $(mpfr_targets_prefix)$(mpfr_recommended_version_number)

