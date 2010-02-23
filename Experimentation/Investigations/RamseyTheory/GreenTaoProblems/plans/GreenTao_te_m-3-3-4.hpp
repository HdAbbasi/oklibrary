// Oliver Kullmann, 11.2.2010 (Swansea)
/* Copyright 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_te_m-3-3-4.hpp
  \brief Investigations regarding the "transversal extension" numbers greentao_{m+2}([2,...,2,3,3,4])

  The aloamo-translation is generated by
  output_greentao_stdname(append(create_list(2,i,1,m),[3,3,4]),n)
  and output_greentao_sb_stdname(append(create_list(2,i,1,m),[3,3,4]),n) at
  Maxima-level, and by "GTSat 2 ... 2 3 3 4 n" at C++ level.

  The nested translation is generated by
  output_greentao_standnest_stdname(append(create_list(2,i,1,m),[3,3,4]),n) and
  output_greentao_standnest_strong_stdname(append(create_list(2,i,1,m),[3,3,4]),n).

  The logarithmic translation is generated by
  output_greentao_logarithmic_stdname(append(create_list(2,i,1,m),[3,3,4]),n).

  The reduced translation is created by
  output_greentao_reduced_stdname(append(create_list(2,i,1,m),[3,3,4]),n) resp.
  output_greentao_reduced_strong_stdname(append(create_list(2,i,1,m),[3,3,4]),n).


  \todo greentao_4(2,3,3,4) >= 453
  <ul>
   <li> The conjecture is greentao_4(2,3,3,4) = 453. </li>
   <li> First considering the weak standard nested translation with rnovelty+.
   </li>
   <li> n=442, cutoff=10^6: finds one solution in 15 runs (seed=2776413455,
   osteps=327557). </li>
   <li> n=443
    <ol>
     <li> cutoff=10^6: in 100 runs no solutions was found. </li>
     <li> cutoff=2*10^6: finds in run 78 one solution (seed=3773007564,
     osteps=1936809). </li>
    </ol>
   </li>
   <li> n=444, cutoff=4*10^6: finds a solution in run 10 (seed=2050602575,
   osteps=2112736). </li>
   <li> n=445, cutoff=4*10^6: finds a solution in run 7 (seed=4168291728,
   osteps=2670307). </li>
   <li> n=446, cutoff=4*10^6: finds a solution in run 2 (seed=3913893840,
   osteps=3235502). </li>
   <li> n=447, cutoff=4*10^6: in 332 runs 13 solutions were found
   (seed=1711609145, osteps=865779). </li>
   <li> n=448, cutoff=4*10^6: in run 131 a solution was found
   (seed=4208191351, osteps=3277920). </li>
   <li> n=449, cutoff=6*10^6: in run 54 a solution was found
   (seed=3969099878, osteps=2013315). </li>
   <li> n=450, cutoff=6*10^6: in run 162 a solution was found
   (seed=1486592823, osteps=2486421). </li>
   <li> n=451, cutoff=6*10^6: in run 13 a solution was found
   (seed=3091775367, osteps=5018123). </li>
   <li> n=452 cutoff=6*10^6
    <ol>
     <li> cutoff=6*10^6: In run 11 a solution was found (seed=592938116,
     osteps=3809907). </li>
     <li> cutoff=10^7:
     \verbatim
 0  1  2
 4 75 21
100
     \endverbatim
     So perhaps actually walksat-tabu-nonull is better (for higher cutoffs).
     </li>
     <li> walksat-tabu-nonull, cutoff=10^7:
     \verbatim
 0  1  2
 5 84 11
100
     \endverbatim
     </li>
     <li> rnovelty, cutoff=10^7:
     \verbatim
 1  2
70 30
100
     \endverbatim
     So here we have a case where an algorithms seem good, because it finds
     reasonably many cases with min=1, but actually it fails to realise
     min=0 ! </li>
     <li> walksat-tabu, cutoff=10^7:
     \verbatim
 0  1  2  3
 3 68 12  1
84
     \endverbatim
     So walksat-tabu-nonull seems better. </li>
    </ol>
   </li>
   <li> n=453
    <ol>
     <li> cutoff=6*10^6:
     \verbatim
  1   2   3
214 169  17
400
     \endverbatim
     </li>
     <li> cutoff=10^7:
     \verbatim
  1   2   3
310 151   5
466
     \endverbatim
     </li>
     <li> Best local search algorithm from Ubcsat-suite:
     \verbatim
> E = eval_ubcsat("GreenTao_N_4-2-3-3-4_453.cnf", params=list(runs=100,cutoff=1000000))
     \endverbatim
     evaluated by plot(E$alg,E$best) and eval_ubcsat_dataframe(E):
     \verbatim
rnovelty :
 1  2  3  4  5
 7 34 44 14  1
rnoveltyp :
 1  2  3  4
 7 29 41 23
walksat_tabu_nonull :
 1  2  3  4  5  6
 5 18 33 29 10  5
noveltyp :
 1  2  3  4  5
 2 27 54 15  2
walksat_tabu :
 1  2  3  4  5  6
 2 15 25 33 22  3
novelty :
 1  2  3  4  5
 1  5 53 38  3
gwsat :
 1  3  4  5  6  7  8  9
 1  5 14 28 30 15  6  1
     \endverbatim
     </li>
     <li> walksat-tabu-nonull with cutoff=10^7
     \verbatim
  1   2   3
323  74   3
400
     \endverbatim
     Since it's faster than rnovelty+, it seems to be superior. </li>
     <li> walksat-tabu, cutoff=10^7:
     \verbatim
 1  2  3
65 32  3
100
     \endverbatim
     So it seems that the nonull-option improves performance (though at the
     cost of running time). </li>
    </ol>
   </li>
  </ul>


  \todo greentao_5(2,2,3,3,4) > 465
  <ul>
   <li> First considering the weak standard nested translation with
   rnovelty+. </li>
   <li> n=460, cutoff=10^7: found a solution in run 100 (seed=689351359,
   osteps=6436295). </li>
   <li> n=461
    <ol>
     <li> cutoff=2*10^7:
     \verbatim
 1  2
40 60
100
     \endverbatim
     </li>
     <li> walksat-tabu-nonull, cutoff=2*10^7 finds a solution in run 22
     (seed=164496226, osteps=16042190). </li>
    </ol>
   </li>
   <li> n=462, cutoff=2*10^7, walksat-tabu-nonull: found a solution in the
   first run (seed=89229228, osteps=8204248). </li>
   <li> n=463, cutoff=2*10^7, walksat-tabu-nonull: found a solution in run 88
   (seed=3466211155, osteps=17673628). </li>
   <li> n=464
    <ol>
     <li> cutoff=2*10^7, walksat-tabu-nonull:
     \verbatim
 1  2  3
21 65 14
100
     \endverbatim
     </li>
     <li> cutoff=4*10^7, walksat-tabu-nonull: in run 18 a solution was found
     (seed=3466303736, osteps=17253883). </li>
    </ol>
   </li>
   <li> n=465, cutoff=4*10^7, walksat-tabu-nonull: found a solution in run 63
   (seed=3647398344, osteps=32380993). </li>
   <li> n=466, cutoff=4*10^7, walksat-tabu-nonull </li>
  </ul>

*/

