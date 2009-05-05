// Oliver Kullmann, 26.11.2008 (Swansea)
/* Copyright 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/RamseyTheory/Lisp/Ramsey/plans/Numbers.hpp
  \brief Plans regarding %Ramsey numbers


  \todo %Ramsey numbers
  <ul>
   <li> The following needs to be updated according to the general naming
   conventions discussed in "Systematic notations for the numbers in %Ramsey
   theory" in ComputerAlgebra/RamseyTheory/plans/general.hpp.
    <ol>
     <li> For a "Ramsey parameter tuple" as below, the number of "colours" is
     not mentioned, while the size of the hyperedges comes last. </li>
     <li> Perhaps we should just put the size of the hyperedges as
     first component, but leave it otherwise. </li>
     <li> So the tuple of clique-sizes is always written out (while
     the redundant information on the number of colours then is not
     needed). </li>
     <li> Or should be provide the (redundant) number of colours?
     Then it would use the same conventions as the function-arguments? </li>
     <li> Should we then also allow the hyperedge-size to be left out
     (which implies the value 2)? </li>
     <li> The current tuple [[3,3,3],2] would then become [3,2,[3,3,3]]
     or [3,[3,3,3]]. But there such defaults seem useless, so perhaps
     we should just use the full version. </li>
     <li> Leaving out the number of colours yields [2,[3,3,3]]; perhaps
     this is best. </li>
    </ol>
   </li>
   <li> A "Ramsey parameter tuple" is a tuple [[q_1,...,q_s],r], where s
   is the number of colours (all q_i and r are natural numbers). </li>
   <li> The function ramsey(r, par_tuple) computes a pair, consisting of
   a lower and an upper bound on the %Ramsey number for this tuple. </li>
   <li> This function is now available, but needs 
    <ul>
     <li> More bounds added:
      <ol>
       <li> See the running report of [Radziszowski, Small %Ramsey Numbers].
       </li>
       <li> Also in the eis-database we should find Ramsey-numbers. </li>
      </ol>
     </li>
     <li> References for the bounds; compare "Bibtex-database" in
     OKlib/plans/Annotations.hpp. </li>
     <li> The known general upper and lower bounds need to be integrated:
      <ol>
       <li> The system must be extensible. </li>
       <li> Perhaps one "bound function" delivers:
        <ul>
         <li> the function which from the given parameter tuple computes
         the other parameter tuple for which bounds are needed </li>
         <li> and the function which from these other bounds computes
         the bounds. </li>
        </ul>
        Then ramsey recursively invokes all registered bound functions,
        and uses minimum resp. maximum.
       </li>
       <li> Either we provide pairs [lower bound, upper bound], or precise
       values (just integers). </li>
       <li> The system needs to general enough, so that also the values given
       by ramsey_hm can be checked (possibly improved).
        <ol>
         <li> It might be good to extend the hash-map ramsey_hm to contain
         information on how currently the best bounds are obtained. </li>
         <li> One possibility is for the interesting small parameter values
         just to use comments. </li>
        </ol>
       </li>
      </ol>
     </li>
    </ul>
   </li>
   <li> Important that the system developed here can later be generalised to
   yield bounds on all sorts of combinatorial parameters.
    <ol>
     <li> Compare
     ComputerAlgebra/Satisfiability/Lisp/MinimalUnsatisfiability/plans/uhit_def.hpp
     for another catalogue of data (and instances). </li>
    </ol>
   </li>
  </ul>

*/

