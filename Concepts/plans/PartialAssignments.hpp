// Oliver Kullmann, 28.11.2006 (Swansea)
/* Copyright 2006 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Concepts/plans/PartialAssignments.hpp
  \brief Plans for concepts for partial assignments

  \todo See OKsolver/Experimental/AllgKlassen200203/PartialAssignments.hpp
  for older concepts of partial assignments.

  \todo See PartialAssignments/plans/PartialAssignments.hpp for further design studies.

  \todo Generalisations:
  With generalised literals we have more than one variable per literal.
  <ul>
   <li> Do we still speak of "partial assignments" ??? One could use:
    <ol>
     <li> "partial assignments" for partial maps v -> value </li>
     <li> "partial multiassignments" for partial maps v -> set-of-values </li>
     <li> "partial specifications" for arbitrary sets of literals </li>
    </ol>
   </li>
   <li> "Partial assignments" are some form of normalised constraints. These normalisation
   conditions need to be discussed (they are especially critical for non-unary literals). </li>
   <li> Consider equality-literals: Here substitutions can be performed! And in general
   we could have eliminated variables, which depend in arbitrary ways on other variables.
   How to handle this? And what if some active clause-sets perform the substitutions, some
   don't ?! </li>
   <li> Partial assignments in general contain several types of literals. So a partial assignment
   is a tuple or a sequence of mono-typed partial assignments ?! </li>
  </ul>

  \todo Development of the fundamental concept of a partial specification phi:
  <ol>
   <li> Partial specifications are the mediators between alliances of active clause-sets
   and the backtracking-style SAT algorithm. They record the decisions (for example branching
   literals), derived informations (e.g. unit-clause-eliminations) and other (SAT-equivalent)
   specifications (like autarkies), and they enable conflict analysis and backtracking. </li>
   <li> A partial specification is the central "communication bus": New derived conditions
   can only be communicated via phi. </li>
   <li> A partial specification is a special constraint with certain normalisation procedures
   especially for unary constraints, and is given as a conjunction of "literals", where literals
   represent certain "atomic constraints" (so a partial specification is a generalised DNF-clause,
   and negating it yields a generalised CNF-clause, which can be learned). </li>
   <li> Branching specifies a sequence of literals x_1, ..., x_m (m is the width of the branching),
   such that in branch i the literal x_i is added to the partial specification. The SAT algorithm
   then connects the alliances of active clause-sets F with phi, where F first up-dates its
   internal state so that it becomes aware of the full partial specification,
   and then possibly adds inferred literals to the partial specification. This process is repeated
   until either the problem was solved or a further decision is needed. </li>
   <li> In case of backtracking, phi contains the information for conflict analysis and backtracking.
   </li>
   <li> More precisely, phi contains a tuple of sequences of literals, where the order of the sequences
   is specified by the order in which the literals arrived. Better we have not just literals, but they
   are embedded into structures which contain information
   <ul>
    <li> whether the literal is a decision literal, a derived literal (in which case at least the
    responsible active clause-set is referenced), or some form of a "safe" literal, </li>
    <li> whether the literal eliminates a variable or not, and if yes, then whether the elimination
    shall be performed "eagerly" (so that the variables cannot be mentioned afterwards) or "lazily"
    (using the variable elimination information only if needed), </li>
    <li> and whether the literal is treated to by a "long-term" constraint (like when actually
    branching), or as a "short-term" constraint (like in look-ahead). </li>
   </ul>
   <li> Functional variable eliminations are of the forms
    <ol>
     <li> v = value </li>
     <li> v = w (another variable) </li>
     <li> v = f(w_1, ..., w_k) (generalising the two forms above) </li>
     <li> "{v_1, ..., v_k} = w", meaning v_1, ..., v_k are to be replaced by w (this is more efficient
     than v_1=w, ..., v_k=w; is this case of importance?). </li>
    </ol>
   </li>
   <li> And then there is for example DP_v, which is a "non-constructive" variable elimination (but in the
   special cases typically considered one can "constructivise" it). Likely such an operation is not
   connected to partial specifications, but is left to the discretion of the (single) active clause-set
   involved. DP_v(F) is equivalent to the existential quantification of F on v (and as such is a global
   process). </li>
   <li> Of special importance are the mono-literals (unary constraints), which are treated separately
   and collected into the current running assignment, which for every variable (at all) states whether
   it is restricted (some values are not available), set (restricted to one value) or unaffected.
   How much this running assignment takes into account the non-mono-literals (like variable-equations
   or disequalities) depends on the normalisation power. </li>
   <li> If an active clause-set(s) F connects to phi, then the running assignments gives
   the current "accumulated" situation, while the sequences of mono-literals
   (there might be several, of distinct types) show the "differential" situation, what has changed
   since the last contact (here F needs to store memory-markers, which inform phi about the last contact).
   The other sequences of (non-mono) literals give further constraints (which
   might not be comprised by the running assignment), again in the differential form. </li>
   <li> If F then derives further literals, these are added to phi.
   After this addition, the SAT algorithm might call normalisation of phi (there might be several
   possibilities for normalisation, and possibly the solver waits until it seems rewarding). </li>
   <li> In the boolean case we have the special situation that all mono-literals eliminate a variable.
   So in this case there is no need at all to distinguish between a differential mono-literal (just telling
   the eliminated values) and ordinary literals. </li>
  </ol>

  \todo How to do the updates in an alliance of active clause-sets (perhaps each active clause-set
     can be registered?). One idea:

     With phi.update_iterator() an active clause-set F can obtain an input iterator i_F
     from phi (specifically to be used by F).
     With phi.new_end(i_F) one gets the current past-the-end iterator (of the same type
     as i_F), so that from i_F to this iterator the update-literals can be found; two models:
     <ol>
      <li> i_F is independent of F, and is just the end-iterator of the list of all update-literals
      (for boolean clause-sets this is fully enough, since here this sequence is just a
      standardised partial assignment); </li>
      <li> phi processes all the update-literals from i_F to the current end, and maintains a
      compressed form of the corresponding partial assignment (which should be just the
      standardisation). </li>
     </ol>
     We see that effectively phi maintains *views* for every active clause-set F, providing
     partial assignments which show F the "difference" between the last state of phi
     and the new state.

  \todo Refinements of partial assignments offer access to a variable container.

  \todo Relation to the notion of clauses:
  Are partial assignments just "DNF-clauses" ("positive clauses")? Likely not --- there
  are the special normalisation conditions, and then all the interaction with active
  clause-sets.

*/
