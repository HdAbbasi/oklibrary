// Oliver Kullmann, 16.2.2007 (Swansea)
/* Copyright 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */


/*!
  \file ProofSystems/Resolution/plans/Search.hpp
  \brief Plans for the sub-module providing components for resolution proof search


  \todo Exact tree resolution complexity:
  <ul>
   <li> Implement the dynamic-programming algorithm for computing
   the tree resolution complexity for all possible clauses
   over var(F) for a given clause-set F:
    <ol>
     <li> Let trc(C) be the tree-resolution complexity of C w.r.t. F,
     that is, the minimal number of nodes in a tree resolution
     derivation of (exactly) C from F. </li>
     <li> So trc(C) is an odd natural number. </li>
     <li> At the beginning trc(C) is "open" for
     all C over F. </li>
     <li> Then in round i = 1, 2, ... we determine
     all clauses C with trc(C) = 2i-1 (by marking exactly those
     clauses with 2i-1). </li>
     <li> In round 1 exactly the clauses of F are marked with 1. </li>
     <li> In round i > 1 for a yet unmarked clause C one checks whether
     it is the resolvent of marked clauses C',C'' such that
     trc(C') + trc(C'') + 1 = 2i-1 in which case clause C gets marked. </li>
    </ol>
   </li>
   <li> For extracting an optimal tree resolution refutation for the
   empty clause, when marking a clause one should also store
   pointers to the parent clauses. </li>
   <li> Can further restrictions be handled for boolean resolution? </li>
   <li> For non-boolean clause-sets there is still only one form
   of resolution, however if signed literals are allowed, then
   more forms are possible. </li>
   <li> If only interested in the empty clause, then we can stop
   as soon as we found it (and the reached level then is
   exactly the tree-resolution complexity of F). </li>
   <li> Are there other strategies to make the procedure a bit more
   efficient?
    <ol>
     <li> One possibility is to restrict the maximal clause-size
     considered (for 2-CNF it is actually sufficient to consider
     only clauses of length at most 2). </li>
    </ol>
   </li>
  </ul>


  \todo How to compute the minimal regular-resolution complexity?


  \todo How to compute the minimal DP-resolution complexity?


  \todo How to compute the minimal resolution complexity?


  \todo Implement the Buresh-Oppenheim/Mitchell algorithm
  for computing the minimal resolution complexity of F in
  boolean 2-CNF in polynomial time.
  
*/

