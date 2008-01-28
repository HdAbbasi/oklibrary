// Oliver Kullmann, 30.11.2007 (Swansea)
/* Copyright 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Satisfiability/Lisp/ClauseSets/plans/general.hpp
  \brief Plans for Maxima-components regarding clause-sets


  \todo Create milestones


  \todo Write tests


  \todo Write docus


  \todo Systematise the use of suffices like "cs" and "cs_f".


  \todo Input and output
  <ul>
   <li> Functions currently in
   ComputerAlgebra/Satisfiability/Lisp/ClauseSets/BasicOperations.mac
   should move to their own file "InputOutput.mac". </li>
   <li> The usage of "print" likely should be replaced by "printf" from
   package "stringproc". </li>
   <li> We should have options for output:
    <ol>
     <li> Instead of for example "php(3,2)" print out "php_3_2". </li>
     <li> DONE And also print it out in strict Dimacs format, optionally
     with the mapping from natural numbers to original variables given
     in the comments. </li>
    </ol>
   </li>
   <li> We need also reading from Dimacs-files. </li>
  </ul>


  \todo General clause-sets
  <ul>
   <li> A "general clause-set" is a triple [V,F,f], where V is a set of
   variables, F a set of clause-labels, and f assigns to each element of
   F a clause over V. </li>
   <li> As we have a promotion from clause-sets to formal clause-sets, we
   also need a promotion from a formal clause-set to a general clause-set.
   </li>
  </ul>


  \todo standardise_fcs (in
  ComputerAlgebra/Satisfiability/Lisp/ClauseSets/BasicOperations.mac)
  <ul>
   <li> DONE The current implementation (using iterated substitution) is
   incorrect in case the clause-set uses already natural numbers as
   variables. </li>
   <li> So ask on maxima-mailing-list whether a parallel substitution
   is available. </li>
   <li> DONE Otherwise, investigate how hash-maps can be made available,
   store the (whole) substitution via a hash-map, and compute
   the new clause-set via transforming clause for clause. </li>
   <li> Perhaps we could establish general renaming functionality. </li>
  </ul>


  \todo Further statistics (for
  ComputerAlgebra/Satisfiability/Lisp/ClauseSets/BasicOperations.mac))
  <ul>
   <li> A map from literals to literal-degrees. </li>
   <li> A map from variables to variable-degrees. </li>
  </ul>

*/

