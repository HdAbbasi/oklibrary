// Oliver Kullmann, 24.7.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Concepts/plans/Clauses.hpp
  \brief Plans for concepts for clauses.


  \todo The following needs to be updated.
  <ul>
   <li> See supermodule Satisfiability/ProblemInstances. </li>
   <li> See supermodule ComputerAlgebra/Satisfiability. </li>
   <li> This file shall be partially moved to
   Satisfiability/ProblemInstances/ActiveClauses/concepts/plans
   and partially to
   Satisfiability/ProblemInstances/Clauses/concepts/plans.
   </li>
  </ul>


  \todo Concepts for and-clauses, or-clauses, etc.


  \todo Shall there be also "active clauses" ?! Seems reasonable;
  perhaps there is actually not a big difference, since the literals
  need not to be there anyway --- however with regard to active
  clauses more care is needed for the concept, and this might be
  quite right. An active clause perhaps is something like
  a "small active clause-set" (see Concepts/plans/ActiveClauseSets.hpp),
  in which we can also grasp into. The hierarchy then would be
  <ol>
   <li> (generalised) literals </li>
   <li> active clauses </li>
   <li> active clause-sets </li>
   <li> alliances of active clause-sets </li>
  </ol>


  \todo The relations to
  <ul>
   <li> Concepts/plans/ClauseSets.hpp </li>
   <li> Concepts/plans/ActiveClauseSets.hpp </li>
  </ul>
  needs to be determined.


  \todo Watched literals
  <ul>
   <li> Motivated by the submission of Armin Biere to SAT2007, for the look-ahead
   the clause could manage the two watched literals in them (inclusive the two
   pointers to the respective next clauses). </li>
   <li> The main point here is to find out (as easily as possible) when possibly
   a clause became unit. </li>
   <li> Also interesting here to find out when possibly a clause became binary
   (here we would need three watched literals per clause). </li>
   <li> Taking care of those special literals in a clause would be the
   responsibility of the clause (not some higher-level mechanism). </li>
  </ul>


  \todo For an earlier attempt see
  OKsolver/Experimental/AllgKlassen200203/Clauses.hpp.


  \todo A fundamental issue here is the relation to the concept of
  partial assignments (see Concepts/plans/PartialAssignments.hpp):
  <ul>
   <li> It should be possible to easily switch between
   the concepts of partial assignments and clauses; perhaps the only
   difference is in the complexity of the operations: while clauses correspond
   to sets (using space proportionally to their size), partial assignments
   correspond to total maps (using a special value "unassigned"; supporting
   constant time access).
   </li>
   <li> As set-objects partial assignments and clause-sets
   are identical (for standard literals), namely they are sets of pairs of variables
   and (forbidden) values, interpreted as constituting the assignment or as
   literals. </li>
   <li> Regarding the operations considered above, from the concept-side (the
   operations and their complexity) there is quite some difference between clauses
   and partial assignments (for example regarding watched literals). So turning a
   partial assignment into a clause (and vice versa) must be possible (lossless),
   but might be more costly. </li>
   <li> The CNF(DNF)-representation of some condition is just a representation of
   those assignments we realised as falsifying (satisfying).
   </li>
  </ul>

*/

