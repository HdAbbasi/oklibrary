// Oliver Kullmann, 17.5.2008 (Swansea)
/* Copyright 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Satisfiability/Lisp/MinimalUnsatisfiability/plans/uhit_def.hpp
  \brief Plans regarding the catalogue of unsatisfiable non-singular hitting clause-sets


  \todo Organisation
  <ul>
   <li> Rename this file to Uhit_def.hpp, and move data/uhit_def.hpp to
   MinimalUnsatisfiabilility/Uhit_def.hpp. </li>
  </ul>


  \todo Connections to other modules
  <ul>
   <li> See ComputerAlgebra/Satisfiability/Lisp/ConflictCombinatorics/plans/HittingClauseSets.hpp
   </li>
  </ul>


  \todo Tests
  <ul>
   <li> Write tests for all functions.
    <ol>
     <li> uhit_def : DONE </li>
     <li> uhit_n : started </li>
     <li> apply_uhit </li>
     <li> collect_uhit_n </li>
     <li> classify_candidates_uhit_def </li>
     <li> isotype_uhit_def </li>
     <li> closure_uhit_def_pass </li>
    </ol>
   </li>
   <li> Testing functions which evaluate uhit_def:
    <ol>
     <li> Create mock-variations of uhit_def using dynamic binding. </li>
     <li> Perhaps we create a list of such mock-variations. </li>
    </ol>
   </li>
   <li> At level basic, the test for uhit_def takes too long. </li>
  </ul>


  \todo uhit_n
  <ul>
   <li> info_data should be computed. </li>
   <li> def_data should be computed. </li>
   <li> Run through all deficiencies in uhit_def and check whether
   the given n is contained. </li>
   <li> To determine whether the classification is complete, use
   two functions which compute lower and upper bounds on possible
   deficiencies for a given n, and then check whether for all these
   deficiencies the corresponding entries are complete. </li>
  </ul>


  \todo New entries
  <ul>
   <li> For n=5 add deficiencies delta = 14, ..., 27. </li>
   <li> It seems unlikely that we can get all for n=5. Nevertheless
   we should get a good variety, and for that we need a version of
   all_unsinghitting which starts from a different (random) path. </li>
   <li> The general policy about new entries should be that in case
   there is a large number of entries, and so we cannot have them all,
   then we should enter "interesting" examples:
    <ol>
     <li> Since we are investigating the maximal min-var-degree for a given
     deficiency (see "Maximal min-var-degrees" in
     ComputerAlgebra/Satisfiability/Lisp/MinimalUnsatisfiability/plans/general.hpp),
     examples where the bound is attained are interesting. </li>
     <li> Also of interest are ABDs. </li>
     <li> And examples for minimal and maximal n. </li>
    </ol>
   </li>
   <li> We should provide a mechanism for lazy evaluation.
    <ol>
     <li> Entries like max_var_hitting_def(58)[2] are just too big
     to compute every time with oklib_load. </li>
     <li> We could just store the terms, and by some function then trigger
     the evaluation. </li>
     <li> Ask on the Maxima mailing list about "lazy evaluation". </li>
    </ol>
   </li>
  </ul>


  \todo ExternalSources for larger data-sets
  <ul>
   <li> Larger data-sets should be made available as uhit_def*.mac
   data-sets under ExternalSources, loadable on demand.
    <ol>
     <li> These files, as ".tar.bz2"-files, are to be found under
     ExternalSources/data. </li>
     <li> What ending for these files? They are created by save, so
     apparently ".lisp" is appropriate? </li>
     <li> It is the responsibility of the user to unpack these packages. </li>
     <li> The path to the directory is known to our Maxima-system. </li>
     <li> Perhaps we provide some special load-functions. </li>
     <li> Single data sets can be specified, and also all of them. </li>
    </ol>
   </li>
   <li> Which data is already provided in uhit_def.mac ? </li>
   <li> Process n=5,6,7,8.
    <ol>
     <li> For n=5 add at least deficiencies delta = 4,5. </li>
     <li> For n=6 add at least deficiencies delta = 5,6,7. </li>
     <li> For n=7 add at least deficiencies delta = 5,6,7. </li>
     <li> For n=8 add at least deficiencies delta = 5,6,7. </li>
    </ol>
   </li>
  </ul>


  \todo Reduction by 2-subsumption resolution
  <ul>
   <li> A second catalogue should be created, which contains only
   those unsatisfiable hitting clause-sets for which
   no 2-subsumption resolution is possible. </li>
   <li> The structure of this catalogue is the same as of uhit_def. </li>
   <li> The subset of uhit_def is of interest (here we are also asking
   for non-singularity). Call it uhit_def_nsn2s.
    <ol>
     <li> Via
     \verbatim
sublist(apply_uhit(lambda([k,n,i,F],[k,n,i,redtsrp(F)])),lambda([T],T[4]));
     \endverbatim
     we obtain the current examples. </li>
     <li> We should get much smaller numbers. </li>
    </ol>
   </li>
   <li> And also the bigger catalogue uhit_def_n2s, where non-singularity
   is dropped, is of interest.
    <ol>
     <li> The question is whether for given deficiency there are only
     finitely many cases in uhit_def_n2s?! </li>
     <li> From this catalogue all of uhit_def can be created by inverse
     2-subsumption resolution. </li>
     <li> A representation involves an element F of uhit_def_n2s, a
     clause-list, and then a partial map from clause-indices to variable-sets,
     where the latter specify the expansion. </li>
     <li> The process of reduction by 2-subsumption-resolution
     is not confluent, and for a given (non-singular) hitting clause-set
     F there can exist 2 non-isomorphic hitting clause-sets reduces w.r.t.
     2-subsumption-resolution which can be expanded to F.
      <ol>
       <li> Obvious examples are given by reducing full_fcs(n). </li>
       <li> For full_fcs(n) there exist many representations, the optimal
       representing full_fcs(n) as the expansion of {{}} by setn(n). </li>
       <li> One could use shortest representations. </li>
      </ol>
     </li>
    </ol>
   </li>
  </ul>

*/

