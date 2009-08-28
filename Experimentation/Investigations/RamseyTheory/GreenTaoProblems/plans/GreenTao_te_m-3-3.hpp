// Oliver Kullmann, 3.5.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_te_m-3-3.hpp
  \brief Investigations regarding the "transversal extension" numbers greentao_{m+2}([2,...,2,3,3])

  Generated by output_greentao_stdname(append(create_list(2,i,1,m),[3,3]),n)
  and output_greentao_sb_stdname(append(create_list(2,i,1,m),[3,3]),n).


  \todo greentao_3(2,3,3) = 31
  <ul>
   <li> n=30 trivially satisfiable by adaptnovelty+. </li>
   <li> Also trivial for the OKsolver_2002, which also determines that n=31
   is unsatisfiable with 171 nodes. </li>
  </ul>


  \todo greentao_4(2,2,3,3) = 39
  <ul>
   <li> Very easy for OKsolver_2002. </li>
  </ul>


  \todo greentao_5(2,2,2,3,3) = 41
  <ul>
   <li> n=40 trivially satisfiable by adaptnovelty+. </li>
   <li> Also still easy for OKsolver_2002. </li>
   <li> And n=41 needs 163846 nodes (less than a minute) with the OKsolver.
   </li>
   <li> minisat2 needs only less than a second. </li>
   <li> While satz215 seems to have some bigger problems. </li>
   <li> And also march_pl seems to have some problems. </li>
  </ul>

  
  \todo greentao_6(2,2,2,2,3,3) = 47
  <ul>
   <li> Created by
   output_greentao_stdname(append(create_list(2,i,1,4),[3,3]),47) resp.
   output_greentao_sb_stdname(append(create_list(2,i,1,4),[3,3]),47). </li>
   <li> n=46 trivially satisfiable by adaptnovelty+. </li>
   <li> n=47 found easily unsatisfiable by minisat2:
    <ol>
     <li> Without symmetry breaking: 19 restarts, 335241 conflicts, 77s
     (csltok). </li>
     <li> With symmetry breaking: 20 restarts, 544888 conflict. As usual,
     symmetry breaking impairs performance. </li>
     <li> Without preprocessing and without symmetry breaking: 18 restarts,
     259250 conflicts. So also minisat2 seems hurt by the preprocessing! </li>
     <li> Without preprocessing and with symmetry breaking: 20 restarts,
     645974 conflict. Again symmetry breaking impairs performance, and this
     quite a bit, compared to without it (and also without preprocessing).
     In absolute terms for this combination the performance is worst. </li>
     <li> Since the node-count is lower, minisat2 seems to do here something
     better than OKsolver_2002: dynamic heuristics? locality? full resolution
     versus tree resolution? </li>
    </ol>
   </li>
   <li> OKsolver_2002:
    <ol>
     <li> Without preprocessing and without symmetry breaking:
     \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D10 -F GreenTao_6-2-2-2-2-3-3_47.cnf
s UNSATISFIABLE
c sat_status                            0
c initial_maximal_clause_length         6
c initial_number_of_variables           282
c initial_number_of_clauses             5372
c initial_number_of_literal_occurrences 11228
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   5029
c running_time(sec)                     2269.3
c number_of_nodes                       4266000
c number_of_single_nodes                2217
c number_of_quasi_single_nodes          0
c number_of_2-reductions                20413272
c number_of_pure_literals               0
c number_of_autarkies                   63449
c number_of_missed_single_nodes         392532
c max_tree_depth                        60
c number_of_table_enlargements          0
c number_of_1-autarkies                 236133359
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_6-2-2-2-2-3-3_47.cnf

> E = read_oksolver_mon("GreenTao_6-2-2-2-2-3-3_47.cnf.mo")
1024
> plot_oksolver_mon_nodes(E,left=1)
ldstep= 7 step= 128 left= 1 right= 1024
obs/count= 1 nodes-range= 5 75068 ave-nodes-range= 980.6 4937.533
> summary_oksolver(E)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      5     614    1450    4166    4209   75070
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  0.500   3.710   4.270   4.663   5.115  33.600
Single nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  0.000   0.000   0.000   2.165   1.000 120.000
Autarkies:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   0.00    3.00   12.00   61.96   40.00 1911.00
Time ~ nodes:
[1] 0.9626347
 (Intercept)      E$nodes
0.0292801246 0.0005249267
Single nodes ~ nodes:
[1] 0.03070471
 (Intercept)      E$nodes
1.3807603513 0.0001882563
Autarkies ~ nodes:
[1] 0.7590312
 (Intercept)      E$nodes
-14.99220801   0.01847188

> hist_oksolver_mon_nodes(E)
     \endverbatim
     average 2-reductions ~ 4.79, 282 / 4.79 ~ 59, speed ~ 1880 nodes per 
     second. The distribution of log2-node-counts looks rather "normally
     distributed" (with a long tail; with center around 10.5, that is, around 
     the median). </li>
     <li> One should flip the first-branch decisions, to see whether we get
     more single nodes. </li>
     <li> With preprocessing and without symmetry breaking:
     \verbatim
> OKsolver_2002-m2pp -M -D10 -F GreenTao_6-2-2-2-2-3-3_47.cnf
s UNSATISFIABLE
c sat_status                            0
c initial_maximal_clause_length         24
c initial_number_of_variables           229
c initial_number_of_clauses             4892
c initial_number_of_literal_occurrences 11898
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   4596
c running_time(sec)                     4716.8
c number_of_nodes                       5175647
c number_of_single_nodes                216
c number_of_quasi_single_nodes          68
c number_of_2-reductions                43341558
c number_of_pure_literals               137406
c number_of_autarkies                   57622
c number_of_missed_single_nodes         133433
c max_tree_depth                        121
c number_of_table_enlargements          0
c number_of_1-autarkies                 6498689
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_6-2-2-2-2-3-3_47.cnf_m2pp_6916

> E = read_oksolver_mon("GreenTao_6-2-2-2-2-3-3_47.cnf_m2pp_6916.mo")
1012
> plot_oksolver_mon_nodes(E,left=1)
ldstep= 7 step= 128 left= 1 right= 1024
obs/count= 1.011858 nodes-range= 1 216013 ave-nodes-range= 2532.398 7640.75
> summary_oksolver(E)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      1      51     382    5114    2094  216000
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  0.100   5.058   7.245   7.005   9.052  19.840
Single nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 0.0000  0.0000  0.0000  0.2134  0.0000 25.0000
Autarkies:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   0.00    0.00    0.00   56.94   11.00 6168.00
Time ~ nodes:
[1] 0.9898389
 (Intercept)      E$nodes
0.0882628069 0.0008940907
Single nodes ~ nodes:
[1] 0.3890737
  (Intercept)       E$nodes
-0.0560472614  0.0000526929
Autarkies ~ nodes:
[1] 0.7921343
 (Intercept)      E$nodes
-23.69363369   0.01576614

> hist_oksolver_mon_nodes(E)
     \endverbatim
     average 2-reduction ~ 8.37, 229 / 8.37 ~ 27.4, speed ~ 1097 nds/sec.
     Distribution of log2-node-counts might show a separation into two
     "different distributions", one centered around 5, the other around 10
     but this might be misleading (one could also see three distributions,
     one with centre 2, one with 5 and one with 10). </li>
     <li> As with greentao_7(2,...,2,3,3) (see below), here preprocessing
     impairs performance (more nodes, and considerably fewer nds/sec), and we 
     also get the enormous depth of the tree (relative to the number of 
     variables); and also one observes the periodic patterns. I (OK) would 
     guess, that also here in principle the reduction helps, but something 
     "goes wrong", and one obtains the bad outliers; and/or perhaps the added
     long clauses cause problems. </li>
     <li> Without preprocessing and with symmetry breaking:
     \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D10 -F GreenTao_sb_6-2-2-2-2-3-3_47.cnf
s UNSATISFIABLE
c sat_status                            0
c initial_maximal_clause_length         6
c initial_number_of_variables           282
c initial_number_of_clauses             5373
c initial_number_of_literal_occurrences 11230
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   5030
c running_time(sec)                     1105.8
c number_of_nodes                       2101403
c number_of_single_nodes                948
c number_of_quasi_single_nodes          0
c number_of_2-reductions                9937291
c number_of_pure_literals               0
c number_of_autarkies                   31209
c number_of_missed_single_nodes         194102
c max_tree_depth                        59
c number_of_table_enlargements          0
c number_of_1-autarkies                 115924859
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_sb_6-2-2-2-2-3-3_47.cnf

> E = read_oksolver_mon("GreenTao_sb_6-2-2-2-2-3-3_47.cnf.mo")
1021
> plot_oksolver_mon_nodes(E,left=1)
ldstep= 7 step= 128 left= 1 right= 1024
obs/count= 1.002938 nodes-range= 1 58477 ave-nodes-range= 49.333 2052.151
> summary_oksolver(E)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      1     125     377    2058    1511   58480
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  0.200   3.260   4.050   4.358   5.220  34.670
Single nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
 0.0000  0.0000  0.0000  0.9285  0.0000 90.0000
Autarkies:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   0.00    0.00    3.00   30.57   12.00 1300.00
Time ~ nodes:
[1] 0.9658678
 (Intercept)      E$nodes
0.0083875413 0.0005221542
Single nodes ~ nodes:
[1] 0.04710342
 (Intercept)      E$nodes
0.4988707647 0.0002087429
Autarkies ~ nodes:
[1] 0.7357201
(Intercept)     E$nodes
-5.82921479  0.01768372

> hist_oksolver_mon_nodes(E)
     \endverbatim
     4.73 2red/nds, 282 / 4.73 ~ 59.6, 1900 nds/sec.
     The distribution seems to be divided into two sub-distributions, the first
     small one centered around 2, while the main distribution is centered
     around the median 8.5. </li>
     <li> With preprocessing and with symmetry breaking:
     \verbatim
> OKsolver_2002-m2pp -M -D10 -F GreenTao_sb_6-2-2-2-2-3-3_47.cnf
s UNSATISFIABLE
c sat_status                            0
c initial_maximal_clause_length         16
c initial_number_of_variables           225
c initial_number_of_clauses             4730
c initial_number_of_literal_occurrences 11353
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   4451
c running_time(sec)                     216028.4
c number_of_nodes                       215434556
c number_of_single_nodes                431683
c number_of_quasi_single_nodes          0
c number_of_2-reductions                1878685678
c number_of_pure_literals               18025739
c number_of_autarkies                   6866623
c number_of_missed_single_nodes         3724945
c max_tree_depth                        82
c number_of_table_enlargements          0
c number_of_1-autarkies                 726406714
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_sb_6-2-2-2-2-3-3_47.cnf_m2pp_7718
> plot_oksolver_mon_nodes(E,left=1,ldstep=5)
ldstep= 5 step= 32 left= 1 right= 1024
obs/count= 1.026052 nodes-range= 0 5536056 ave-nodes-range= 1.286 210385.3
> summary_oksolver(E)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      0      26    2169  215900  206800 5536000
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   1.22    8.51    9.29   11.46   13.48   66.00
Single nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
    0.0     0.0     5.0   432.5   389.5  9657.0
Autarkies:
    Min.  1st Qu.   Median     Mean  3rd Qu.     Max.
     0.0      0.0     47.5   6880.0   6212.0 151500.0
Time ~ nodes:
[1] 0.9951324
 (Intercept)      E$nodes
-6.621237389  0.001033429
Single nodes ~ nodes:
[1] 0.6542652
 (Intercept)      E$nodes
80.026281984  0.001633056
Autarkies ~ nodes:
[1] 0.835877
 (Intercept)      E$nodes
434.35530177   0.02986121
> hist_oksolver_mon_nodes(E)
Median= 11.08281
Mean= 17.71978
     \endverbatim
     </li>
     8.72 2red/nds, 225 / 8.72 ~ 25.8, 997 nds/sec.
     The distribution has two peaks, one around 5, followed by a slow descend
     until before 15, and then a sharp ascend to the second peak around 20, 
     followed by a very steep descend. </li>
     <li> This is an interesting disaster! Using preprocessing alone impairs
     performance somewhat, using symmetry breaking alone improves performance
     quite a bit, while both together has a disastrous effect (compared with
     the best case the node-count is multiplied by 100, the running time by
     200)! </li>
     <li> Using the subdivision of the nodes-plots into 32 segments, there
     are roughly two parts, both with roughly linear increase of the average 
     node count: Until the end of segment 23 there is a continous basis of easy
     problems with occasional much harder problems, but then the harder 
     problems become much more frequent. </li>
     <li> Due to the constant increase in the average node count, at any time
     the prediction is far too good; the hardest monitoring node is the last
     one. </li>
     <li> The above data doesn't give much clue what happened (perhaps it is
     important that the depth increased, but this itself is only an effect,
     and doesn't explain much). </li>
     <li> The easy problems have a lot 2-reductions, the hard ones much less.
     </li>
    </ol>
   </li>
   <li> satz215
   <ol>
    <li> Without preprocessing and without symmetry breaking:
    aborted after 3 1/2 hours (csltok). </li>
    <li> Without preprocessing and with symmetry breaking:
    </li>
   </ol>
  </li>
   <li> march_pl </li>
  </ul>


  \todo greentao_7(2,...,2,3,3) = 53
  <ul>
   <li> Generated by 
   output_greentao_stdname(append(create_list(2,i,1,5),[3,3]),n)
   and output_greentao_sb_stdname(append(create_list(2,i,1,5),[3,3]),n).
   </li>
   <li> n=52 trivially satisfiable by adaptnovelty+. </li>
   <li> n=53 poses some difficulties for minisat2 (learning
   very long clauses), but in ~ 70m and 11222376 conflicts (27 restarts)
   unsatisfiability was confirmed. </li>
   <li> Using symmetry breaking
   ("output_greentao_sb_stdname([2,2,2,2,2,3,3],53)"): It's actually harder
   for minisat2, 15589496 conflicts and 28 restarts. It is understandable
   that minisat2 is hard to steer, and thus can't exploit the additional
   symmetry breaking rule, but again it gets a bit harder? </li>
   <li> Without preprocessing: </li>
   <li> OKsolver_2002 can solve it in 3.8 days (without preprocessing and
   with symmetry breaking):
   \verbatim
s UNSATISFIABLE
c sat_status=0 initial_maximal_clause_length=7 initial_number_of_variables=371 initial_number_of_clauses=8415 initial_number_of_literal_occurrences=17453 running_time(s)=331416.7 number_of_nodes=176784736 number_of_single_nodes=1480233 number_of_quasi_single_nodes=0 number_of_2-reductions=2961445595 number_of_pure_literals=0 number_of_autarkies=1108523 number_of_missed_single_nodes=3399131 max_tree_depth=63 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=15885525871 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=8004 file_name=GreenTao_sb_7-2-2-2-2-2-3-3_53.cnf
   \endverbatim
   16.75 2red/nds, 371 / 16.75 ~ 22.1, 533 nds/sec (csltok).
   Interesting to understand the autarkies and the single nodes. </li>
   <li> The number of nodes is definitely worse than with minisat2, so
   something is achieved here by minisat2 (or badly done by OKsolver_2002).
   </li>
   <li> With preprocessing and without symmetry breaking:
   \verbatim
> OKsolver_2002-m2pp -M -D15 -F GreenTao_7-2-2-2-2-2-3-3_53.cnf
GreenTao_7-2-2-2-2-2-3-3_53.cnf_m2pp_15229,   15,      32768

 16255:4017096  14922.59  4.89E+08  4529.56s    17.95s     0y   3d 10h 21m 18s  1470 116746  153
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         29
c initial_number_of_variables           310
c initial_number_of_clauses             7764
c initial_number_of_literal_occurrences 18809
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   7400
c running_time(sec)                     293581.0
c number_of_nodes                       243777417
c number_of_single_nodes                78417
c number_of_quasi_single_nodes          840
c number_of_2-reductions                2133168434
c number_of_pure_literals               14320249
c number_of_autarkies                   5574285
c number_of_missed_single_nodes         14682434
c max_tree_depth                        153
c number_of_table_enlargements          0
c number_of_1-autarkies                 464218661
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_7-2-2-2-2-2-3-3_53.cnf_m2pp_15229

> E = read_oksolver_mon("GreenTao_7-2-2-2-2-2-3-3_53.cnf_m2pp_15229.mo")
14724
> plot_oksolver_mon_nodes(E)
ldstep= 11 step= 2048 left= 128 right= 16255
obs/count= 1.104355 nodes-range= 1 4626650 ave-nodes-range= 699.985 14922.59
> summary_oksolver(E)
Nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      1      13     102   16470    1265 4627000
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  0.100   5.750   8.860   8.824  11.200  90.000
Single nodes:
    Min.  1st Qu.   Median     Mean  3rd Qu.     Max.
   0.000    0.000    0.000    5.312    0.000 2609.000
Autarkies:
    Min.  1st Qu.   Median     Mean  3rd Qu.     Max.
     0.0      0.0      0.0    375.3     11.0 124100.0
Time ~ nodes:
[1] 0.9886211
(Intercept)     E$nodes
1.092014523 0.001136873
Single nodes ~ nodes:
[1] 0.7498523
  (Intercept)       E$nodes
-0.1662990797  0.0003325131
Autarkies ~ nodes:
[1] 0.8931323
 (Intercept)      E$nodes
-21.11046739   0.02406468
> hist_oksolver_mon_nodes(E)
Median= 6.672425
Mean= 14.00792
   \endverbatim
   8.75 2red/nds, 310 / 8.75 ~ 35.4, 830 nds/sec (csltok).
   </li>
   <li> As above, preprocessing impairs performance quite a bit; especially
   interesting seems (again) the large tree-depth. The average node-count
   slowly but constantly goes up; the histogram shows perhaps two peaks,
   one at around 2, the other around 5, but we have a heavy tail. </li>
   <li> Remark: Having a look into the monitoring output, especially the
   autarky-counts looks strangely structured (some kind of periodic
   behaviour), for example many kind of (exact) doublings and repetitions,
   or arithmetic progressions --- and this somehow periodic. </li>
   <li> Without preprocessing and with symmetry breaking: </li>
  </ul>


  \todo greentao_8(2,...,2,3,3) = 55
  <ul>
   <li> n=53 trivially satisfiable with cutoff=10000. </li>
   <li> For n=54 however a cutoff=10^6 is needed (still easy). </li>
   <li> n=55 yields constantly min=1 in 10 runs with cutoff=10^6 and
   with cutoff=10*10^6. </li>
   <li> The jump in minisat2's run time experienced above (from m=4 to
   m=5) seems to indicate a factor of 100; so roughly 5 days.
    <ol>
     <li> We should give minisat2 10 days. </li>
     <li> Determined unsatisfiability with 37 restarts, 645336350 conflicts,
     and 817059 s (~ 9.5 days). </li>
    </ol>
   </li>
   <li> We should also try the alternative encoding as discussed in
   "Alternative handling of parameter-values 2" in
   ComputerAlgebra/Satisfiability/Lisp/Generators/RamseyTheory/plans/VanderWaerdenProblems.hpp.
   </li>
  </ul>


  \todo greentao_9(2,...,2,3,3) >= 60
  <ul>
   <li> n=55, cutoff=10^6: trivially satisfiable. </li>
   <li> n=56, cutoff=10^6: trivially satisfiable. </li>
   <li> n=57, cutoff=10^6: still 100% success (always with 10 runs). </li>
   <li> n=58, cutoff=10^6: now 30% success. </li>
   <li> n=59, cutoff=10^6: 70% success. </li>
   <li> n=60, cutoff=10^6: 0% success, also with cutoff=10*10^6. </li>
  </ul>


  \todo greentao_10(2,...,2,3,3) >= 62
  <ul>
   <li> n=60, cutoff=10^6: 100% success. </li>
   <li> n=61, cutoff=10^6: 100% success. </li>
   <li> n=62, cutoff=10^6: 0% success, also with cutoff=10*10^6. </li>
  </ul>


  \todo greentao_11(2,...,2,3,3) >= 67
  <ul>
   <li> n=62, cutoff=10^6: 100% success. </li>
   <li> n=63, cutoff=10^6: 100% success. </li>
   <li> n=64, cutoff=10^6: 100% success. </li>
   <li> n=65, cutoff=10^6: 80% success. </li>
   <li> n=66, cutoff=10^6: 0% success, but 80% success with cutoff=10*10^6.
   </li>
   <li> n=67, cutoff=10*10^6: 0% success, also with cutoff=100*10^6. </li>
  </ul>


  \todo greentao_12(2,...,2,3,3) >= 71
  <ul>
   <li> n=67, cutoff=10*10^6: 100% success. </li>
   <li> n=68, cutoff=10*10^6: 100% success. </li>
   <li> n=69, cutoff=10*10^6: 100% success. </li>
   <li> n=70, cutoff=10*10^6: 90% success. </li>
   <li> n=71, cutoff=10*10^6: 0% success; 100 runs, cutoff=50*10^6:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 50000000 -i GreenTao_12-2-2-2-2-2-2-2-2-2-2-3-3_71.cnf
Clauses = 30221
Variables = 852
TotalLiterals = 61766
FlipsPerSecond = 347739
BestStep_Mean = 387364.340000
Steps_Mean = 50000000.000000
Steps_Max = 50000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
   \endverbatim
   </li>
  </ul>

*/

