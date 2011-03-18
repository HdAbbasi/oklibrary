// Oliver Kullmann, 5.3.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/4-k/10.hpp
  \brief On investigations into vdw_2(4,10) > 328


  \todo Best ubcsat-solver
  <ul>
   <li> We need to find the best algorithm from the ubcsat-1-2-0 suite. </li>
  </ul>


  \todo vanderwaerden_2(4,10) > 328
  <ul>
   <li> We don't have a nice prediction, except of that it's greater (or 
   equal) than 309. </li>
   <li> Evaluating
   \verbatim
> E = run_ubcsat("VanDerWaerden_2-4-10_350.cnf", runs=100,cutoff=100000,monitor=TRUE)
   \endverbatim
   by plot(E$alg,E$best): It seems that gsat_tabu, rots and samd are best,
   where samd reached the best min=37, but this might be just an outlier, and
   perhaps rots is best. </li>
   <li> Using cutoff=10^6: the two best min-values are reached by rnovelty
   (twice min=8) and rots (twice min=9), while otherwise the best min=34.
   Considering the success of rnovelty as just luck, rots would again be best 
   here. </li>
   <li> Evaluating
   \verbatim
E = run_ubcsat("VanDerWaerden_2-4-10_330.cnf", runs=100,cutoff=100000,monitor=TRUE)
   \endverbatim
   again rots seems best (reaching min=26). </li>
   <li> The same, but with cutoff=10^6: three algorithms, each with one run,
   reached min=3, namely rots, rsaps and sapsnr, while otherwise the best min 
   is 26. Again rots seems best. </li>
   <li> The same, but with cutoff=4*10^6: the three best algorithms seem now
   adaptnovelty+, rnovelty+ and saps (the best is min=2; perhaps adapnovelty+ 
   is best):
   \verbatim
> table(E$best[E$alg=="adaptnoveltyp"])

 3  4  5 28 29 30 31 32 33 34 35
 1  1  1  5  5 11 14 22 20 14  6
> table(E$best[E$alg=="rnoveltyp"])

 2  4 28 30 31 32 33 34 35 36 37 38 39 40 41 42
 1  2  1  2  1  1  7  3 11 15 15 17 13  8  2  1
> table(E$best[E$alg=="saps"])

 2 28 31 33 34 35 36 37 38
 1  1  2  8 14 19 36 18  1
> table(E$best[E$alg=="irots"])

 5 30 31 32 33 34 35 36 37
 1  2  7 10 18 23 25 11  3
   \endverbatim
   </li>
   <li> Evaluating (cutoff=10^5)
   \verbatim
>  E = run_ubcsat("VanDerWaerden_2-4-10_320.cnf", runs=100,cutoff=100000,monitor=TRUE)
   \endverbatim
   gsat-tabu and samd appear best (both reaching min=23).
   </li>
   <li> Now using cutoff=10^6: Three solver reached min=1:
   \verbatim
 table(E$best[E$alg=="novelty"])
 1 42 44 45 46 47 48 49 50 51 52
 1  1  7  6  9 17 21 14 19  3  2
> table(E$best[E$alg=="rnovelty"])
 1 26 29 30 31 32 33 34 35 36 37 38
 1  1  9  7 11 12 17 16 13  7  5  1
> table(E$best[E$alg=="rots"])
 1 23 24 25 26 27 28 29
 1  2  7 24 39 20  6  1
   \endverbatim
   but these could well be outliers. Unclear situation. </li>
   <li> cutoff=10^7: four solvers found solutions:
   \verbatim
> table(E$best[E$alg=="adaptnoveltyp"])
 0  2  3 20 21 22 23 24 25 26 27 28
 2  1  2  2  2  6 16 21 26 17  4  1
> table(E$best[E$alg=="rnoveltyp"])
 0  1 24 25 26 27 28 29 30 31 32 33
 1  2  3  3  4  6 17 25 21 10  7  1
> table(E$best[E$alg=="rsaps"])
 0  3  4 26 27 28 29 30 31 32
 1  1  1  3  5 12 23 32 20  2
> table(E$best[E$alg=="noveltyp"])
 0 39 40 41 42 43 44 45 46 47 48
 1  2  4  4  6 11 18 23 15 15  1
   \endverbatim
   where the above order seems to be appropriate for their ranking.
   So perhaps for now we should assume that adaptnovelty+ is best. </li>
   <li> n=321 with adaptnovelty+
    <ol>
     <li> cutoff=10^7:
     \verbatim
> nohup ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 10000000 -i VanDerWaerden_2-4-10_321.cnf | tee VanDerWaerden_2-4-10_321.cnf_OUT &
> E=read_ubcsat("VanDerWaerden_2-4-10_321.cnf_OUT")
 0  1  2 21 22 23 24 25 26 27
 1  2  2  1  6 12 24 25 18  9
100
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  36040 1817000 3963000 4553000 7101000 9987000
     \endverbatim
     </li>
    </ol>
   </li>
   <li> n=322, cutoff=10^7: a solution was found in run 51 (seed=3424017434,
   osteps=2557765). </li>
   <li> n=323, cutoff=10^7: a solution was found in run 22 (seed=420342374,
   osteps=9743243). </li>
   <li> n=324
    <ol>
     <li> cutoff=10^7 found one solution in 1000 runs:
     \verbatim
> nohup ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i VanDerWaerden_2-4-10_324.cnf | tee VanDerWaerden_2-4-10_324.cnf_OUT &
> E=read_ubcsat("VanDerWaerden_2-4-10_324.cnf_OUT")
  0   1   2   3   4   5  18  21  22  23  24  25  26  27  28  29  30  31
  1  11  19   9   4   2   1   2   9  29  69 143 193 254 178  66   9   1
1000
> E[E$min==0,]
    sat min  osteps  msteps       seed
993   1   0 2065594 2065594 2579089101
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   8842 1877000 4370000 4471000 6848000 9996000
     \endverbatim
     </li>
     <li> cutoff=10^8 found three solution:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 100000000 -i VanDerWaerden_2-4-10_324.cnf | tee VanDerWaerden_2-4-10_324.cnf_OUT2
> E = read_ubcsat("VanDerWaerden_2-4-10_324.cnf_OUT2")
 0  1  2  3  4  5 21 22 23 24 25 26
 3  7 13  4  6  2  1  6 12 20 12  4
90
> E[E$min==0,]
   sat min   osteps   msteps       seed
38   1   0 67111454 67111454 3357914690
48   1   0 37435932 37435932 3595047384
62   1   0 68099425 68099425  748374078
     \endverbatim
     </li>
     <li> So it seems one needs to use cutoff=10^8 now. </li>
    </ol>
   </li>
   <li> n = 325, cutoff=10^8: found one solution (seed=1755037834,
   osteps=38900247):
   \verbatim
> E=read_ubcsat("VanDerWaerden_2-4-10_325.cnf_OUT2")
 1  2  3  4  5 21 22 23 24 25 26 27
10 17  7  6  2  2  6 11 15 16  7  1
100
> E = read_ubcsat("VanDerWaerden_2-4-10_325.cnf_OUT")
 0  1  2  3  5 20 21 22 23 24 25 26
 1  6 18  4  4  1  2  4  9 13 16  3
81
   \endverbatim
   </li>
   <li> n = 326, cutoff=10^8: found one solution (seed=64752191,
   osteps=96247637) in 162 runs:
   \verbatim
> E = read_ubcsat("VanDerWaerden_2-4-10_326.cnf_OUT")
 0  1  2  3  4  5 21 22 23 24 25 26 27
 1  6 33 18  6  4  4  4  9 18 36 15  8
162
   \endverbatim
   So we should use cutoff=2*10^8 now. </li>
   <li> n=327, cutoff=2*10^8: In 81 runs one solution was found 
   (seed=403939055, osteps=23019617):
   \verbatim
> E = read_ubcsat("VanDerWaerden_2-4-10_327.cnf_OUT")
 0  1  2  3  4  5 22 23 24 25 26 27
 1  1 28 12  5  3  2  5  9  8  6  1
81
   \endverbatim
   And in another 112 runs also one solution was found:
   \verbatim
> nohup ubcsat-okl -alg adaptnovelty+ -runs 200 -cutoff 200000000 -i VanDerWaerden_2-4-10_327.cnf > VanDerWaerden_2-4-10_327.cnf_OUT &
 0  1  2  3  4  5 21 22 23 24 25 26
 1  3 33 11 11  3  1  3  5  9 17 15
112
> summary(E$osteps)
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
   525600  32000000  91600000  89860000 138000000 199800000
   \endverbatim
   </li>
   <li> n=328
    <ol>
     <li> cutoff=2*10^8:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 200 -cutoff 200000000 -i VanDerWaerden_2-4-10_328.cnf | tee VanDerWaerden_2-4-10_328.cnf_OUT
> E = read_ubcsat("VanDerWaerden_2-4-10_328.cnf_OUT")
 1  2  3  4  5 21 22 23 24 25 26 27 28
 2 51 45 28  9  1  7  3 12 17 19  4  2
200
> summary(E$osteps)
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
   599500  40370000  84970000  92870000 141000000 198300000
     \endverbatim
     </li> 
     <li> cutoff=4*10^8:
     \verbatim
> nohup ubcsat-okl -alg adaptnovelty+ -runs 200 -cutoff 400000000 -i VanDerWaerden_2-4-10_328.cnf > VanDerWaerden_2-4-10_328.cnf_OUT &
> E=read_ubcsat("VanDerWaerden_2-4-10_328.cnf_OUT")
 0  1  2  3  4  5 23 24 25 26
 1  1 29 17  4  2  1  1  1  1
58
> summary(E$osteps)
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
  1000000  36620000 124200000 146200000 228000000 397700000
     \endverbatim
     So cutoff=4*10^8 seems needed now.
     </li>
    </ol>
   </li>
   <li> n=329
    <ol>
     <li>cutoff=4*10^8:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 200 -cutoff 400000000 -i VanDerWaerden_2-4-10_329.cnf | tee VanDerWaerden_2-4-10_329.cnf_OUT
> E = read_ubcsat("VanDerWaerden_2-4-10_329.cnf_OUT")
 1  2  3  4  5  6 21 23 24 25 26 27
 7 75 53 26 12  2  2  2  9  6  5  1
200
> summary(E$osteps)
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
  4042000  78170000 166600000 178900000 260800000 397600000

> E=read_ubcsat("VanDerWaerden_2-4-10_329.cnf_OUT2")
 1  2  3  4  5  6 22 23 24 25 26 27
 3 47 31 17  4  3  1  2  5  5  6  2
126
> summary(E$osteps)
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
  1242000  67280000 164600000 174800000 284900000 394100000
     \endverbatim
     </li>
     <li> cutoff=5*10^8:
     \verbatim
  1   2   3   4   5   6  23  24  25  26
  5 103  59  31  10   3   2   7  12   8
240
     \endverbatim
     </li>
    </ol>
   </li>
   <li> n=330 with adaptnovelty+
    <ol>
     <li> cutoff=10^7 
     \verbatim
 2  4 23 26 28 29 30 31 32 33 34
 5  3  2  3 11 17 24 19  9  5  2
100
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  11110 1841000 4807000 4775000 7835000 9856000
     \endverbatim
     </li>
     <li> cutoff=10^8:
     \verbatim
 2  3  4  5  6 22 23 24 25 26 27 28 29 30
33 50 39 22  3  1  1  9 23 40 43 53 11  4
332
  2   3   4   5   6  21  22  23  24  25  26  27  28  29  30
 84 113 112  48  18   2   3  13  19  62 117 189 162  51   7
1000
     \endverbatim
     </li>
    </ol>
   </li>
  </ul>


  \todo vdw_2^pd(4,10) = (320,329)
  <ul>
   <li> Established by minisat-2.2.0. </li>
   <li> Do we have an easy-hard pattern based on parity? </li>
  </ul>

*/