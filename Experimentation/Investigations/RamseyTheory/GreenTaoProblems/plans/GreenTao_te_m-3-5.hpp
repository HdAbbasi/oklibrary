// Oliver Kullmann, 7.11.2009 (Swansea)
/* Copyright 2009, 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_te_m-3-5.hpp
  \brief Investigations regarding the "transversal extension" numbers greentao_{m+2}([2,...,2,3,5])

  The aloamo-translation is generated by
  output_greentao_stdname(append(create_list(2,i,1,m),[3,5]),n)
  and output_greentao_sb_stdname(append(create_list(2,i,1,m),[3,5]),n) at
  Maxima-level, and by "GTSat 2 ... 2 3 5 n" at C++ level.

  The nested translation is generated by
  output_greentao_standnest_stdname(append(create_list(2,i,1,m),[3,5]),n) and
  output_greentao_standnest_strong_stdname(append(create_list(2,i,1,m),[3,5]),n).

  The logarithmic translation is generated by
  output_greentao_logarithmic_stdname(append(create_list(2,i,1,m),[3,5]),n).

  The reduced translation is created by
  output_greentao_reduced_stdname(append(create_list(2,i,1,m),[3,5]),n) resp.
  output_greentao_reduced_strong_stdname(append(create_list(2,i,1,m),[3,5]),n).


  \todo greentao_3(2,3,5) = 581
  <ul>
   <li> n=550
    <ol>
     <li> OKsolver_2002 without preprocessing: the instance allows many
     autarkies and single-nodes, but full processing on csltok seems to take
     roughly a day, and after have processed roughly 25% of the monitoring
     nodes no solution was found:
     \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D16 GreenTao_3-2-3-5_550.cnf
 15167:    330     97.85  6.41E+06     3.23s     1.08s     0y   0d 15h  7m  8s     0   116   44

s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         5
c initial_number_of_variables           1650
c initial_number_of_clauses             166883
c initial_number_of_literal_occurrences 348728
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   152625
c running_time(sec)                     16392.5
c number_of_nodes                       1484482
c number_of_single_nodes                41131
c number_of_quasi_single_nodes          0
c number_of_2-reductions                16689392
c number_of_pure_literals               0
c number_of_autarkies                   496261
c number_of_missed_single_nodes         6
c max_tree_depth                        44
c number_of_table_enlargements          0
c number_of_1-autarkies                 157064664
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_3-2-3-5_550.cnf
     \endverbatim
     </li>
     <li> OKsolver_2002 with preprocessing: seems much worse (very
     slow processing of nodes); autarkies and single nodes apparently
     disappeared (while some pure literals showed up):
     \verbatim
> OKsolver_2002-m2pp -M -D16 GreenTao_3-2-3-5_550.cnf
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         27
c initial_number_of_variables           956
c initial_number_of_clauses             144252
c initial_number_of_literal_occurrences 333179
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   132796
c running_time(sec)                     1004.4
c number_of_nodes                       177
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                9193
c number_of_pure_literals               68
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        43
c number_of_table_enlargements          0
c number_of_1-autarkies                 4925
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_3-2-3-5_550.cnf_m2pp_9474
     \endverbatim
     (three monitoring nodes were processed). One should find out what kind of
     disaster here happened through preprocessing (is it that OKsolver_2002
     can't handle long clauses, since its heuristics is insensitive to them?
     but why is processing so slow? perhaps because of the tree-pruning?).
     </li>
     <li> march_pl: aborted after 30m (csltok), where some "progress" was
     achieved (according to the star-output), but no assignment was found.
     </li>
     <li> minisat2 </li>
     <li> ubcsat: saps determined satisfiability with cutoff=10^5 in run 17.
     </li>
    </ol>
   </li>
   <li> n=556: cutoff=10^6 and novelty+ found a solution in run 3
   (seed=695982803, osteps=675537). </li>
   <li> n=557: cutoff=10^6 and novelty+ found a solution in run 12
   (seed=1721874736, osteps=723073). </li>
   <li> n=558:
    <ol>
     <li> cutoff=10^6 and novelty+:
     \verbatim
  1   2
188  12
200
     \endverbatim
     </li>
     <li> cutoff=10^7 and novelty+: 100 runs yield constantly min=1. </li>
     <li> OKsolver_2002-O3-DNDEBUG with monitoring-depth 16 made good
     progress, until in the very last part a steep increase in the number
     of nodes (and in the depth) happened, culminating with the very last
     node, which was far harder than everything else:
     \verbatim
> tail GreenTao_3-2-3-5_558.cnf.mo
    65526  28603   324.692   306.370     3.510      0 13524    55    10.88
    65527  49012   325.435   577.380     3.519      0 23320    55    11.09
    65528  27549   325.850   331.270     3.524      0 13835    55    10.91
    65529 562334   334.427  6488.950     3.623   5378 191960    55    11.79
    65530 837667   347.205  9069.920     3.761  17668 251517    56    11.42
    65531 138580   349.314  1507.570     3.784      0 62472    56    10.89
    65532  80440   350.536   831.820     3.797      7 39280    56    11.08
    65533 1269559   369.904 13897.170     4.009  26180 410500    57    11.42
    65534 220228   373.258  2424.560     4.045      7 103785    57    10.93
    65535 1614247   397.885 17704.900     4.316  18279 543185    58    11.52
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         5
c initial_number_of_variables           1674
c initial_number_of_clauses             171716
c initial_number_of_literal_occurrences 358797
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   157077
c running_time(sec)                     511654.4
c number_of_nodes                       46513164
c number_of_single_nodes                685702
c number_of_quasi_single_nodes          0
c number_of_2-reductions                533093485
c number_of_pure_literals               0
c number_of_autarkies                   15720875
c number_of_missed_single_nodes         332
c max_tree_depth                        72
c number_of_table_enlargements          0
c number_of_1-autarkies                 663956927
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_3-2-3-5_558.cnf
> plot_oksolver_mon_nodes(E)
ldstep= 13 step= 8192 left= 128 right= 65535
obs/count= 1.172691 nodes-range= 0 1614247 ave-nodes-range= 12.391 397.885
> summary_oksolver(E)
Nodes:
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
      0.0       5.0      19.0     466.7      87.0 1614000.0
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   0.25   10.36   11.51   12.30   12.99   68.00
Single nodes:
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
    0.000     0.000     0.000     6.968     0.000 26180.000
Autarkies:
    Min.  1st Qu.   Median     Mean  3rd Qu.     Max.
     0.0      2.0      9.0    157.5     34.0 543200.0
Time ~ nodes:
[1] 0.997862
(Intercept)     E$nodes
-0.04139706  0.01093504
Single nodes ~ nodes:
[1] 0.8307606
(Intercept)     E$nodes
-0.29176246  0.01555560
Autarkies ~ nodes:
[1] 0.9936747
(Intercept)     E$nodes
  5.1898732   0.3263478
> hist_oksolver_mon_nodes(E)
Median= 4.247928
Mean= 8.866372

> plot(E$nodes,E$ave_reductions)

> invest =function(lb) {
 S = E$nodes >= lb
 N = E$nodes[S]
 R = E$ave_reductions[S]
 plot(N,R)
 cat("Nodes:\n")
 print(summary(N))
 cat("Reductions:\n")
 print(summary(R))
 length(N)
}

> invest(1)
Nodes:
     Min.   1st Qu.    Median      Mean   3rd Qu.      Max.
      1.0       5.0      20.0     469.2      87.0 1614000.0
Reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   0.25   10.36   11.51   12.30   12.99   68.00
[1] 55575
> invest(100)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
    100     163     307    1957     770 1614000
Reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   8.11   10.88   11.42   11.45   11.97   15.83
[1] 12869
> invest(1000)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   1000    1418    2214    8408    4508 1614000
Reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   9.26   11.02   11.45   11.45   11.87   14.17
[1] 2610
> invest(2000)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   2002    2751    4194   14300    8294 1614000
Reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   9.59   11.03   11.46   11.44   11.84   12.96
[1] 1417
     \endverbatim
     (computation aborted). Subdividing the monitoring-range into 1024
     intervals, an explosion happened in interval 1024. </li>
     <li> The last plot and its investigation is interesting, suggesting that
     there are two types of observation-nodes: One with low node-count and a
     wide range of 2-red-averages (from 0 to 70), while from, say, a node
     count of 100 on the range of 2-red-averages is very restricted (around
     11.45). So perhaps 2-reductions are very much responsible for the node
     count? </li>
     <li> While autarkies here seem just to occur with a very stable
     frequency, and don't have much influence (regarding the given numbers ---
     but possibly the numbers would be much bigger without them). This needs 
     further investigation. </li>
     <li> Perhaps QCA could be applicable?! </li>
     <li> Regarding the branching, perhaps the variables are all those about
     the first colour, since once we set one node to the first colour, all
     other nodes don't get this colour (a large number of 2-clauses). What
     then happens very late (interval 1024)? </li>
     <li> Also using -D20 doesn't bring more inside: Again doesn't complete
     the last monitoring node. </li>
     \verbatim
csoliver@cs-oksvr:~/OKplatform> tail nohup.out
1048575:1617278     30.85  3.23E+07 21846.88s     0.42s     0y   0d  0h  0m  0s 21310 544482   62

s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         5
c initial_number_of_variables           1674
c initial_number_of_clauses             171716
c initial_number_of_literal_occurrences 358797
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   157077
c running_time(sec)                     515655.7
c number_of_nodes                       38185392
c number_of_single_nodes                568919
c number_of_quasi_single_nodes          0
c number_of_2-reductions                437581299
c number_of_pure_literals               0
c number_of_autarkies                   12878659
c number_of_missed_single_nodes         265
c max_tree_depth                        66
c number_of_table_enlargements          0
c number_of_1-autarkies                 4066478903
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_3-2-3-5_558.cnf
     \endverbatim
     so again it fall into a deep hole at the last monitoring node, and after
     8590 m no progress visible --- interestingly the rather slow 32-bit
     machine csltok (see above) seems faster than this 64-bit machine!. </li>
     <li> minisat2 actually finds a satisfying assignment:
     \verbatim
> minisat2 GreenTao_3-2-3-5_558.cnf
|  25566627 |     978   150454   346323 |   795555   412549     33 |  0.000 % |
===============================================================================
restarts              : 30
conflicts             : 30829712       (236 /sec)
decisions             : 40539158       (1.70 % random) (310 /sec)
propagations          : 3289905696     (25191 /sec)
conflict literals     : 1175934931     (26.30 % deleted)
Memory used           : 576.89 MB
CPU time              : 130600 s

SATISFIABLE
     \endverbatim
     Hopefully this can be verified for example by the OKsolver. </li>
    </ol>
   </li>
   <li> n=559:
    <ol>
     <li> cutoff=10^6 and novelty+:
     \verbatim
> E=read_ubcsat("GreenTao_3-2-3-5_559.cnf_OUT")
  1   2   3
172  27   1
200
     \endverbatim
     </li>
     <li>
     In a second try one solution was found quickly:
     \verbatim
> ubcsat-okl -alg novelty+ -cutoff 1000000 -runs 10000 -i GreenTao_3-2-3-5_559.cnf | tee GreenTao_3-2-3-5_559.cnf_OUT
       sat  min     osteps     msteps       seed
    39 1     0     925169     925169  270520321
     \endverbatim
     </li>
     <li> minisat2: abort after nearly 26 days (csltok):
     \verbatim
============================[ Search Statistics ]==============================
| Conflicts |          ORIGINAL         |          LEARNT          | Progress |
|           |    Vars  Clauses Literals |    Limit  Clauses Lit/Cl |          |
===============================================================================
| 291221740 |     982   151637   348951 |  1420456   492530     29 |  0.000 % |
*** INTERRUPTED ***
restarts              : 36
conflicts             : 312341917      (140 /sec)
decisions             : 407597722      (1.75 % random) (182 /sec)
propagations          : 32165890883    (14369 /sec)
conflict literals     : 10963422073    (26.69 % deleted)
Memory used           : 794.32 MB
CPU time              : 2.23859e+06 s
     \endverbatim
     </li>
     <li> OKsolver_2002 </li>
    </ol>
   </li>
   <li> n=560, cutoff=10^6 (novelty+) finds in 1074 runs one solution
   (seed=449744216, osteps=402793). </li>
   <li> n=561, cutoff=10^6 (novelty+) finds in 256 runs one solution
   (seed=4223011878, osteps=161530). </li>
   <li> n=562
    <ol>
     <li> adaptnovelty+ with cutoff=10^6:
     \verbatim
> E=read_ubcsat("GreenTao_3-2-3-5_562.cnf_OUT")
  1   2   3
 91 104   5
200
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 122700  262800  352800  413600  529700  996600
     \endverbatim
     (looks worse than for n=575 ?!)
     </li>
     <li> Evaluation of all ubcsat-algorithms:
     \verbatim
> E = eval_ubcsat("GreenTao_3-2-3-5_562.cnf", params=list(cutoff=1000000,runs=100))
plot(E$alg,E$best)
min(E$best)
 1
E$alg[E$best==1]
> table(E$best[E$alg=="noveltyp"])
 1  2
84 16
> table(E$best[E$alg=="novelty"])
 1  2
70 30
> table(E$best[E$alg=="adaptnoveltyp"])
 1  2
46 54
> table(E$best[E$alg=="sapsnr"])
 1  2  3  4  5  6
34 35  5  9 12  5
> table(E$best[E$alg=="gwsat"])
 1  2  3  4
30 61  8  1
> table(E$best[E$alg=="saps"])
 1  2  3  4  5  6  7
29 29  1 19 19  2  1
> table(E$best[E$alg=="gsat_tabu"])
 1  2  3  4  5
 7 18 52 21  2
> table(E$best[E$alg=="samd"])
 1  2  3  4  5
 3 22 49 25  1
> table(E$best[E$alg=="walksat_tabu"])
 1  2  3  4  5  6  7  8
 1  8 16 16 24 21 13  1
> table(E$best[E$alg=="rnoveltyp"])
 1  2  3  4  5  6  7  8  9 10 11 12
 1  3  3 10  3  5  7 15 11 19 21  2
     \endverbatim
     so noveltyp seems clearly best. </li>
     <li> cutoff=10^6 (novelty+) finds in 5486 runs two solutions
     (seed=665936935, osteps=541019):
     \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_562.cnf_OUT")
   0    1    2    3
   2 4663  815    6
5486
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   8586  157900  302600  362300  524300  999700
     \endverbatim
     </li>
     <li> The osteps-summary doesn't necessarily indicate that the cutoff
     should be increased? </li>
    </ol>
   </li>
   <li> n=563, cutoff=10^6 (novelty+):
   \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_563.cnf_OUT")
   0    1    2    3
   2 4893  822   13
5730
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   8135  155800  300200  358900  523700 1000000
   \endverbatim
   (seed=3852946212,osteps=842014).
   And with cutoff=2*10^6
   \verbatim
> E2 = read_ubcsat("GreenTao_3-2-3-5_563.cnf_OUT2")
   0    1    2
   2 1734   45
1781
> summary(E2$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  11080  189400  358900  508400  710900 1996000
   \endverbatim
   </li>
   <li> n=564, cutoff=2*10^6 (novelty+): a solution found in run 269
   (seed=547643513, osteps=1980136). </li>
   <li> n=565, cutoff=2*10^6 (novelty+): two solutions found in 3390 runs
   (seed=1584156557, osteps=555457). </li>
   <li> n=566, cutoff=2*10^6 (novelty+): one solution found in 523 runs
   (seed=1418552292, osteps=1384572). </li>
   <li> n=575
    <ol>
     <li> adaptnovelty+ with cutoff=10^6:
     \verbatim
> E=read_ubcsat("GreenTao_3-2-3-5_575.cnf_OUT")
  1   2   3
108  91   1
200
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 130900  331500  452000  506100  677500  992900
     \endverbatim
     </li>
     <li> cutoff=2*10^6 (novelty+): one solution found in 1012 runs
     \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_575.cnf_OUT")
  0   1   2
  1 996  15
1012
> E[E$min==0,]
    sat min  osteps  msteps       seed
151   1   0 1480941 1480941 1122654540
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  19260  177300  317000  416600  541600 1976000
     \endverbatim
     </li>
    </ol>
   </li>
   <li> n=580
    <ol>
     <li> cutoff=2*10^6 (novelty+) found one solution in 2482 runs:
     \verbatim
 E = read_ubcsat("GreenTao_3-2-3-5_580.cnf_OUT")
   0    1    2    3
   1  110 2145  226
2482
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   8632  253800  545900  673000 1010000 2000000
> E[E$min==0,]
     sat min osteps msteps       seed
1934   1   0 715931 715931 2205549087
     \endverbatim
     We see quite a change: min=2 is now the overwhelming majority; one might
     need to check whether under these changed circumstances perhaps now
     adaptnovelty+ is better. </li>
     <li> Weak standard nested translation, sapsnr, cutoff=10^6:
     \verbatim
 0  1  2  3
 1 33 53 13
100
     \endverbatim
     So it seems clear that this translation with sapsnr is superior over
     the aloamo-translation. </li>
    </ol>
   </li>
   <li> n=581
    <ol>
     <li> cutoff=2*10^6 (novelty+):
     \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_581.cnf_OUT")
   1    2    3    4
 508 8495  995    2
10000
> summary(E$osteps[E$min==1])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  17010  665400 1075000 1087000 1577000 1999000
> summary(E$osteps[E$min==2])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  10870  284400  578000  697400 1031000 1998000
> summary(E$osteps[E$min==3])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   7201  115200  259800  349500  467900 1975000
     \endverbatim
     </li>
     <li> cutoff=2*10^6 (adaptnovelty+):
     \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_581.cnf_OUT2")
   1    2    3
 244 9631  125
10000
> summary(E$osteps[E$min==1])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 181600  702500 1126000 1139000 1587000 1979000
> summary(E$osteps[E$min==2])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 113000  351000  516700  612800  781300 1999000
> summary(E$osteps[E$min==3])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 121300  237900  305300  342600  405900 1131000
     \endverbatim
     Apparently adaptnovelty+ is better than novelty+ in avoiding the worst
     cases, but worse in achieving the best cases (and this should be what
     counts). </li>
     <li> cutoff=4*10^6 (novelty+):
     \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_581.cnf_OUT3")
   1    2    3
1013 8900   87
10000
> summary(E$osteps[E$min==1])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  66300 1097000 1981000 2026000 2981000 3990000
> summary(E$osteps[E$min==2])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   9536  295200  634300  853200 1178000 3991000
> summary(E$osteps[E$min==3])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  14180  104300  239200  270900  404300  904300
     \endverbatim
     </li>
     <li> cutoff=4*10^6 (adaptnovelty+):
     \verbatim
> E2 = read_ubcsat("GreenTao_3-2-3-5_581.cnf_OUT4")
   1    2    3
 516 9483    1
10000
> summary(E$osteps[E$min==1])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  66300 1097000 1981000 2026000 2981000 3990000
> summary(E$osteps[E$min==2])
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   9536  295200  634300  853200 1178000 3991000
     \endverbatim
     </li>
     <li> Until now here only the aloamo-translation has been considered;
     now we consider the weak standard nested translation. </li>
     <li> Finding the best Ubcsat-algorithm:
     \verbatim
> E = eval_ubcsat("GreenTao_N_3-2-3-5_581.cnf")
> plot(E$alg,E$best)
> eval_ubcsat_dataframe(E)

sapsnr :
 1  2  3  4  5  6
 5  9 27 33 22  4
gwsat :
 1  2  3  4  5  6
 1  9 23 34 28  5
saps :
 1  2  3  4  5  6
 1  5 29 35 24  6
     \endverbatim
     </li>
     <li> Weak standard nested translation, sapsnr, cutoff=10^6:
     \verbatim
 1  2  3
33 40 27
100
  1   2   3   4
460 589 397   7
1453
     \endverbatim
     </li>
     <li> minisat2 determines unsatisfiability:
     \verbatim
> minisat2 GreenTao_N_3-2-3-5_581.cnf
| 194147745 |     988   150528   381538 |  1366664   312117     92 |  1.980 % |
===============================================================================
restarts              : 35
conflicts             : 205723929      (154 /sec)
decisions             : 218415159      (1.18 % random) (164 /sec)
propagations          : 13406735824    (10053 /sec)
conflict literals     : 17789955664    (17.80 % deleted)
Memory used           : 1129.76 MB
CPU time              : 1.33355e+06 s
UNSATISFIABLE
     \endverbatim
     </li>
    </ol>
   </li>
   <li> n=585, cutoff=2*10^6 (novelty+):
   \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_585.cnf_OUT")
   2    3    4
1026 2809  113
3948
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   8295  251200  561200  690300 1041000 1999000
   \endverbatim
   Either this needs much higher cutoff/runs, or it is unsatisfiable. </li>
   <li> n=600
    <ol>
     <li> saps with cutoff=10^5:
     \verbatim
> ubcsat-okl -alg saps -runs 100 -cutoff 100000 -i GreenTao_3-2-3-5_600.cnf | tee GreenTao_3-2-3-5_600.cnf_OUT1
> E=read_ubcsat("GreenTao_3-2-3-5_600.cnf_OUT1")
 8  9 10 11 12 13 14 15 16 17 18
 2  2  6 13 11 16 26 15  5  3  1
100
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   3693   19490   41420   45090   66360   98940
     \endverbatim
     </li>
     <li> Checking all ubcsat-algorithms via
     \verbatim
> E = eval_ubcsat("GreenTao_3-2-3-5_600.cnf")
plot(E$alg,E$best)
> min(E$best)
[1] 3
> E$alg[E$best==3]
[1] novelty  novelty  novelty  noveltyp
> table(E$best[E$alg=="novelty"])
 3  4  5  6  7  8  9 10
 3  5 12 15 22 19 16  8
> table(E$best[E$alg=="noveltyp"])
 3  4  5  6  7  8  9 10 11 12
 1  2 12 14 17 24 12 13  4  1
     \endverbatim
     shows novelty as best. </li>
     <li> novelty with cutoff=10^6:
     \verbatim
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  37450  255200  485000  496100  746300  996700
> E=read_ubcsat("GreenTao_3-2-3-5_600.cnf_OUT2")
 2  3  4  5  6
 2 22 44 25  7
100
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  23310  215500  431000  464800  727800  996700
     \endverbatim
     </li>
     <li> Checking saps with cutoff=10^6: Seems worse. </li>
     <li> Checking adaptnovelty+ with cutoff=10^6:
     \verbatim
> E=read_ubcsat("GreenTao_3-2-3-5_600.cnf_OUT2")
 2  3  4
 5 58 37
100
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 167100  305900  432400  466300  606600  972000
     \endverbatim
     There seems to be a general tendency that adaptnovelty+ gets better than
     other algorithms with higher cutoffs (while it's not good with lower
     cutoffs). 
     </li>
     <li> cutoff=2*10^6, novelty+:
     \verbatim
> E = read_ubcsat("GreenTao_3-2-3-5_600.cnf_OUT")
  2   3   4   5   6
 11 109 106  42   3
271
> summary(E$osteps)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  32740  483000  907800  921700 1312000 1999000
     \endverbatim
     </li>
     <li> Let's consider n=600 for now as unsatisfiable. </li>
    </ol>
   </li>
  </ul>


  \todo greentao_4(2,2,3,5) > 581
  <ul>
   <li> Using weak standard nested translation with sapsnr. </li>
   <li> Created by
   output_greentao_standnest_stdname(append(create_list(2,i,1,2),[3,5]),n).
   </li>
   <li> n=581:
    <ol>
     <li> cutoff=10^5 in 100 runs didn't find a solution. </li>
     <li> cutoff=10^6 in 100 runs yields min=1 97 times and 3 times min=2.
     </li>
     <li> Finding the best Ubcsat-algorithm:
     \verbatim
> E = eval_ubcsat("GreenTao_N_4-2-2-3-5_581.cnf", params=list(runs=100,cutoff=1000000))
> plot(E$alg,E$best)
> eval_ubcsat_dataframe(E)

saps :
 0  1  2
 5 93  2
gwsat
 0  1  2
 3 66 31
walksat :
 0  1  2
 2 73 25
sapsnr :
 0  1  2
 1 91  8
walksat_tabu :
 0  1  2
 1 58 41
hwsat :
 0  1  2  3  4  5
 1 23 40 28  4  4
     \endverbatim
     So here saps seems best. </li>
    </ol>
   </li>
   <li> n=582, cutoff=10^6, saps: 100 runs yield all min=1. </li>
   <li> Considering the logarithmic translation:
    <ol>
     <li> Finding the best Ubcsat-algorithm:
     \verbatim
> E = eval_ubcsat("GreenTao_L_4-2-2-3-5_582.cnf", params=list(runs=100,cutoff=1000000))
> plot(E$alg,E$best)
> eval_ubcsat_dataframe(E)

     \endverbatim
     </li>
    </ol>
   </li>
  </ul>

*/
