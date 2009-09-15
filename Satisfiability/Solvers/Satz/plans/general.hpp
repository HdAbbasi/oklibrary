// Oliver Kullmann, 19.4.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Satisfiability/Solvers/Satz/plans/general.hpp
  \brief Plans for maintaining solvers from the Satz family

  Yet only satz215 is considered.


  \todo Improve the statistics output
  <ul>
   <li> The output should confirm to the Dimacs-output form. </li>
   <li> The labels for the various numbers should be improved resp.
   introduced at all:
    <ol>
     <li> "NB_BRANCHE" should mean the number of branches, that is,
     the number of nodes - 1; but what then is NB_BACK? It is always
     a bit more than half of NB_BRANCHE. </li>
    </ol>
   </li>
   <li> And we need additional documentation on these numbers. </li>
  </ul>


  \todo Improve range of statistic measurements
  <ul>
   <li> Yet for the four basic statistics variables, <code> NB_UNIT, NB_MONO,
   NB_BRANCHE, NB_BACK </code> just type <code>long</code> is used. </li>
   <li> A typedef should be introduced. </li>
   <li> The type should become unsigned. </li>
   <li> And it should be a 64-bit type. </li>
  </ul>


  \todo Improve time measurement
  <ul>
   <li> Adapt the method of OKsolver_2002, to use the Unix time system for
   32-bit machines. </li>
   <li> The time measurement is also faulty:
   \verbatim
> time satz215 VanDerWaerden_2-4-6_73.cnf
**** The instance is unsatisfiable. *****
NB_MONO= 39, NB_UNIT= 788138, NB_BRANCHE= 78809, NB_BACK= 39800
Program terminated in 0.002 seconds.
satz215 VanDerWaerden_2-4-6_73.cnf 0.002 78809 39800 4882931 207876 0 73 1349 0 190588 62376

real    1m20.445s
user    0m24.296s
sys     0m0.058s
   \endverbatim
   </li>
  </ul>


  \todo Improve file output
  <ul>
   <li> We should use the same conventions as with the OKsolver_2002. </li>
  </ul>


  \todo Use signals as with OKsolver_2002
  <ul>
   <li> The solver should react as OKsolver_2002 to the signals SIGINT and
   SIGUSR1. </li>
  </ul>


  \todo Provide application tests


  \todo Update to C99
  <ul>
   <li> Improve naming (functions, variables, types, macros). </li>
   <li> Improve comments. </li>
   <li> Introduce const. </li>
   <li> Make variables more local. </li>
   <li> Use type bool. </li>
   <li> Add least some macros can be replaced by constants. </li>
  </ul>


  \todo Add Doxygen documentation


  \todo DONE
  Add a licence text


  \todo DONE
  Updating the exit codes for Satz215
  <ul>
   <li> According to Buildsystem/ExternalSources/SpecialBuilds/plans/SAT.hpp
   the exit codes need to be updated to the DIMACS standard. </li>
   <li> In order to follow the given style, we just introduce new
   exit-code macros
    <ol>
     <li> EXITCODE_PARAMETER_FAILURE </li>
     <li> EXITCODE_INPUT_ERROR </li>
     <li> EXITCODE_VERIFICATION_FAILED </li>
     <li> EXITCODE_SAT </li>
     <li> EXITCODE_UNSAT </li>
    </ol>
   </li>
   <li> And the exit-status must be stored, so that it can be returned
   at the end of the main program.
    <ol>
     <li> In order to stay with the pre-C99 style, we just declare an
     additional variable at the beginning of the main-block, called
     exit_value and of type int. </li>
    </ol>
   </li>

*/

