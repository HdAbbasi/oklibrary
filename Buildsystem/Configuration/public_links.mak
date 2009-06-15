# Oliver Kullmann, 16.1.2008 (Swansea)
# Copyright 2008, 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.

# The list of links to be established to programs from the OKlibrary.

oksolver2002_okl ?= $(bin_dir)/OKsolver_2002-O3-DNDEBUG

ramsey_generator_okl ?= $(bin_dir)/Ramsey-O3-DNDEBUG
vanderwaerden_generator_okl ?= $(bin_dir)/VanderWaerden-O3-DNDEBUG

vdw_minimumtransversals_okl ?= $(bin_dir)/MinimumTransversals_VanderWaerden-O3-DNDEBUG
vdwtransversals_okl ?= $(OKlib)/Satisfiability/Transformers/Generators/VdWTransversals
vdwtransversalspb_okl ?= $(OKlib)/Satisfiability/Transformers/Generators/VdWTransversalsPB
vdwtransversalsinc_okl ?= $(OKlib)/Satisfiability/Transformers/Generators/VdWTransversalsInc
vdwtransversalsincpb_okl ?= $(OKlib)/Satisfiability/Transformers/Generators/VdWTransversalsIncPB
gttransversals_okl ?= $(OKlib)/Satisfiability/Transformers/Generators/GTTransversals
gttransversalsinc_okl ?= $(OKlib)/Satisfiability/Transformers/Generators/GTTransversalsInc

lininequal_trans_okl ?= $(bin_dir)/LinInequal-O3-DNDEBUG
boundones_okl ?=  $(OKlib)/Satisfiability/Transformers/Generators/BoundOnes
oksolver_2002_m2pp_okl ?= $(OKlib)/Satisfiability/Solvers/OKsolver/SAT2002/OKsolver_2002-m2pp
satz215_m2pp_okl ?= $(OKlib)/Satisfiability/Solvers/Satz/satz215-m2pp

extdimacs2dimacs_okl ?= $(bin_dir)/ExtendedToStrictDimacs-O3-DNDEBUG
extdimacsstatistics_okl ?= $(bin_dir)/ExtendedDimacsStatistics-O3-DNDEBUG

boundedtransversalsbv_okl ?= $(bin_dir)/BoundedTransversals_bv-O3-DNDEBUG

rankprimes_okl ?= $(bin_dir)/RankPrimes-O3-DNDEBUG

quinemccluskey_okl ?= $(bin_dir)/QuineMcCluskey-n16-O3-DNDEBUG

public_link_list_okl ?= $(oksolver2002_okl) $(ramsey_generator_okl) $(vanderwaerden_generator_okl) $(lininequal_trans_okl) $(boundones_okl) $(vdwtransversals_okl) $(vdwtransversalspb_okl) $(vdwtransversalsinc_okl) $(vdwtransversalsincpb_okl) $(gttransversals_okl) $(gttransversalsinc_okl) $(oksolver_2002_m2pp_okl) $(satz215_m2pp_okl) $(extdimacs2dimacs_okl) $(extdimacsstatistics_okl) $(boundedtransversalsbv_okl) $(rankprimes_okl) $(quinemccluskey_okl) $(vdw_minimumtransversals_okl) $(oklib_call)

