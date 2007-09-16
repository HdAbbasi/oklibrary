// Oliver Kullmann, 18.10.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Combinatorics/Enumeration/plans/Subsets.hpp
  \brief %Tools for enumeration of all subsets of a set.


  \todo Concept of a subset: a set (sequence) of iterators.
  So a general concept of a set (container, sequence) is needed; or perhaps just using
  ranges is enough?!


  \todo An iterator over all subsets (or, for example, over all subsets of size k)
  dereferenced should yield the subset as an in-place-modification of some internal storage.


  \todo Identifying a subset with its characteristic function, we can use the tools
  from GrayCodes.hpp to enumerate all subsets (flipping only one element at a time).
  The iterator should made available the information about the element flipped.


  \todo Refinements:
   - Enumerating all partial hypergraphs of a hypergraph with bipartite edge-vertex graph
     should yield also these bipartite graphs (respectively the corresponding information)
     for the partial hypergraphs.
   - In the same vain, when enumerating all sub-clause-sets of a clause-set (or something
     similar) with such an auxiliary structure, then the enumeration should (possibly)
     make available this structure also for the enumerated objects.


  \todo There should be a general algorithmic framework, allowing to run through all
  subsets (or "sub-structures"), applying an algorithm to each subset, and gathering
  statistics. An application is as follows: For given n, k compute the clause-sets with
  all k-clauses over variables 1, ..., n (there should be generator for this, generalising
  the complete hypergraphs K_n^k). To each sub-clause-set apply the enumeration-SAT-
  algorithm, gathering as much information as possible (at least for each clause-count c
  we need the number of satisfiable clause-sets --- with this we can compute the probability
  that a random clause-sequence is satisfiable).
  See SATAlgorithms/EnumerationSubclausesets.hpp for a generic algorithm for
  clause-sets. Perhaps later this framework might be generalised.

*/

