// Oliver Kullmann, 23.7.2008 (Swansea)
/* Copyright 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/docus/CourseCombinatorics_LintWilson/Chapter03.hpp
  \brief Chapter "Colorings of graphs and Ramsey's theorem" from [A Course in %Combinatorics]


  <h1> Brook's theorem </h1>

  <h2> Greedy colouring </h2>

  <ul>
   <li> See "Greedy colouring" in
   ComputerAlgebra/Hypergraphs/Lisp/plans/Colouring.hpp. </li>
   <li> Greedy graph colouring will always find a colouring using at most
   d + 1 many colours, where d is the maxima degree. </li>
   <li> Likely it does not automatically yield a d-colouring if no component
   is an odd cycle or the graph does not contain a (d+1)-clique --- example?
   </li>
   <li> Can this be repaired? </li>
   <li> Or with other algorithms? Is it possible at all? </li>
  </ul>


  <h1> Ramsey's theorem </h1>


  <h2> On the automorphism group of %Ramsey hypergraphs </h2>

  <h2> Finding %Ramsey numbers via SAT </h2>

  <ul>
   <li> Some experimentation has been started in this area at 
   Experimentation/Investigations/RamseyTheory/plans/RamseyProblems.hpp . 
   </li>
  </ul>

  <h2> On the automorphism group of %Ramsey clause-sets </h2>

  <ul>
   <li> Some initial discussions on the symmetries of the %Ramsey problems are
   at ComputerAlgebra/Satisfiability/Lisp/Generators/RamseyTheory/plans/RamseyProblems.hpp . 
   </li>
  </ul>

  <h2> Tournaments and transitive tournaments </h2>

  <ul>
   <li> See [%Ramsey numbers for tournaments] by Y.Mannoussakis and Z.Tuza, and 
   originally [A problem on tournaments] by P.Erdos and L.Moser, for work on 
   treating tournaments and transitive subtournaments as a Ramsey-type problem,
   as well as other Ramsey-type problems of directed graphs. </li>
  </ul>

  <h1> The Lovasz local lemma </h1>

*/

