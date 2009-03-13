// Oliver Kullmann, 15.1.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Graphs/Lisp/Bicliques/plans/Consensus.hpp
  \brief Plans regarding implementing the "consensus algorithm" from [XXX] for computing all maximal bicliques
  
  
  \todo Notions and notations
  <ul>
   <li> A kind of dictionary is needed. </li>
   <li> Compare with the functions for resolution. </li>
  </ul>


  \todo The basic "consensus" operation
  <ul>
   <li> Discuss the basic forms. </li>
   <li> Provide all basic definitions in
   ComputerAlgebra/Graphs/Lisp/Bicliques/Consensus.mac (avoiding "similar").
   </li>
  </ul>


  \todo Maximisation functions
  <ul>
   <li> It appears that the various maximisation functions should better
   be placed somewhere else. </li>
   <li> maximal_bc_gl belongs to general biclique functionality. </li>
   <li> For aux_con_alg1_abs compare
   max_elements in ComputerAlgebra/Hypergraphs/Lisp/SetSystems.mac. </li>
  </ul>


  \todo The consensus iteration
  <ul>
   <li> Discuss the basic forms. </li>
   <li> Provide all basic definitions in
   ComputerAlgebra/Graphs/Lisp/Bicliques/Consensus.mac (avoiding "similar").
   </li>
  </ul>


  \todo Handling general graphs
  <ul>
   <li> Can the algorithms be generalised to  handle general graphs? </li>
   <li> Regarding vertex bicliques: the bicliques of a general graph are
   exactly the bicliques of the underlying graph (with loops). </li>
   <li> Regarding edge bicliques, we can simply obtain them from the vertex
   bicliques by using all combinations of underlying edges. </li>
  </ul>


  \todo Improving the implementations
  <ul>
   <li> "con_adj_gl_b1_1_b2_1_p" looks confusing; perhaps all these functions
   can be captured by a single function. </li>
  </ul>


  \todo Compute all maximal bicliques
  <ul>
   <li> "con_alg1/2" should likely use "consensus". </li>
   <li> We need also these algorithms without the argument C.
    <ol>
     <li> The trivial choice is just to take the edges on their own. </li>
     <li> Does the running time depend on C (strongly)? </li>
     <li> If yes, then some heuristics is needed. </li>
     <li> Likely, we need some reasonable algorithm for finding a biclique
     cover of small size.
      <ol>
       <li> One possibility is to chose some yet uncovered edge, find a maximal
       biclique (in the original graph) covering this edge, and repeating this
       process. </li>
      <ol>
     </li>
    </ol>
   </li>
   <li> Perhaps "C" should be called "LB". </li>
  </ul>

*/

