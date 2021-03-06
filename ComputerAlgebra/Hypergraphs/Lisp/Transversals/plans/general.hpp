// Oliver Kullmann, 23.3.2008 (Swansea)
/* Copyright 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Hypergraphs/Lisp/Transversals/plans/general.hpp
  \brief Plans regarding hypergraphs transversals (in Maxima/Lisp)


  \todo Connections
  <ul>
   <li> See
   Combinatorics/Hypergraphs/Transversals/Minimal/plans/DirectTransversalEnumeration.hpp
   for computing the transversal hypergraph via recursive splitting. </li>
   <li> See
   Combinatorics/Hypergraphs/Transversals/Bounded/plans/general.hpp
   for the use of a parameter bounding the size of the transversals. </li>
   <li> See especially Transversals/Bounded/BoundedTransversals_bv.cpp and
   Transversals/Bounded/VertexBranching.hpp for implementations of
   transversals_bv(s). </li>
   <li> And, more generally, see
   Combinatorics/Hypergraphs/Transversals/plans/general.hpp. </li>
   <li> See "dual_cs" in
   ComputerAlgebra/Satisfiability/Lisp/ClauseSets/Constructions.mac, and see
   ComputerAlgebra/Satisfiability/Lisp/ClauseSets/plans/Constructions.hpp.
   </li>
  </ul>


  \todo Organisation
  <ul>
   <li> Split Transversals/Transversals.mac into several files. </li>
   <li> Perhaps Transversals/Basics.mac, Transversals/Minimal.mac,
   Transversals/Bounded.mac, and Transversals/Greedy.mac. </li>
  </ul>


  \todo The triangle of the three possibilities
  <ul>
   <li> The complementary problem is about maximal independent sets,
   the dual problem is about hyperedge coverings. </li>
   <li> Likely these problems have each at least one natural algorithm,
   different from the translations of the others. </li>
   <li> So we need to provide a general scheme for translations. </li>
  </ul>


  \todo ind_hg(G)
  <ul>
   <li> See Combinatorics/Hypergraphs/IndependentSets/plans/general.hpp. </li>
   <li> The test-function okltest_ind_hg should be a generic test-function,
   applicable to any function for computing the hypergraph of (maximal)
   independent subsets (the "independence hypergraph"). </li>
   <li> So, as with transversals, we must distinguish between the (many)
   possible algorithms for ind_hg. </li>
   <li> An alternative method for computing ind_hg is by direct
   construction:
    <ol>
     <li> Bottom-up: Start with all independent subsets of size 0.
     Then for k=0, 1, ... take the sets of size k and consider all
     possibilities to a vertex, obtain so level k+1. Those which
     cannot be extended go to the final result, while otherwise
     the processed level is removed. </li>
     <li> This algorithm is for example efficient for complete graphs. </li>
     <li> Top-down: We start with the full vertex-set at level n.
     Then for k = n,n-1, ... all subsets which are independent are
     moved to the final result, while otherwise all possible (k-1)-subsets
     are formed, which makes level k-1, and level k is removed. </li>
     <li> This algorithm is efficient for hypergraphs with no
     hyperedges. </li>
    </ol>
   </li>
   <li> Of course, a question is whether independence hypergraphs are
   really on its own, or we should standardise all considerations by
   considering transversals? Just taking the edgewise-complement is not
   a big step? But it's a step, and also the literature is different. </li>
  </ul>

*/

