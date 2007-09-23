# Oliver Kullmann, 9.9.2007 (Swansea)
# Copyright 2007 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# Build related variables

OKsystem_include := -I$(OKsystem)

oklib_building_log ?= $(log_dir)/OKlibBuilding
external_sources_log ?= $(log_dir)/ExternalSources

rel_path_tool_origin ?= $(bin_dir)/PathDifference-O3-DNDEBUG
rel_path_tool ?= $(tool_dir)/PathDifference-O3-DNDEBUG
rel_path_tool_debug ?= $(tool_dir)/PathDifference

