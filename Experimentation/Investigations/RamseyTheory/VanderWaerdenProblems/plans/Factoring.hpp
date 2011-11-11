// Oliver Kullmann, 4.11.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/Factoring.hpp
  \brief Lower bounds for van-der-Waerden problems via simplifying homomorphisms

  Generalising the approaches from [Rabung 1979] and Heule et al, aiming at
  finding an m-colouring of a hypergraph G as a composition of hypergraph-
  morphisms, where the final one has as target a hypergraph with at most m
  vertices and without 1-hyperedges (this yields an m-colouring of G).


  \todo vdw_2(6,6)=1132
  <ul>
   <li> First considering random creation of equivalence classes of size 5
   (resp. 2 for the last one):
   \verbatim
G66:arithprog_hg(6,1132)$
ncl_list_fcs(G66);
  [[6,127577]]
set_random(1);
G66p5 : random_projection_hg(G66,5)$
ncl_list_fcs(G66p5);
  [[4,91],[5,6560],[6,120533]]
G66p5m : min_hg(G66p5)$
ncl_list_fcs(G66p5m);
  [[4,91],[5,6460],[6,116949]]

F66p5 : tcol2sat_stdhg2stdfcs(G66p5)$
outputext_fcs("set_random(1),random_projection_hg(arithprog_hg(6,1132),5)",F66p5,"VanDerWaerden_p5_1132.cnf");
F66p5m : tcol2sat_stdhg2stdfcs(G66p5m)$
outputext_fcs("set_random(1),random_projection_min_hg(arithprog_hg(6,1132),5)",F66p5m,"VanDerWaerden_p5m_1132.cnf");

for s : 1 thru 20 do block([G], set_random(s), G : random_projection_hg(G66,5), print(s, ncl_list_fcs(G), ncl_list_fcs(min_hg(G))));
1 [[4,91],[5,6560],[6,120533]] [[4,91],[5,6460],[6,116949]]
2 [[4,100],[5,6300],[6,120777]] [[4,100],[5,6201],[6,117309]]
3 [[4,79],[5,6643],[6,120460]] [[4,79],[5,6558],[6,116795]]
4 [[4,92],[5,6613],[6,120476]] [[4,92],[5,6510],[6,116888]]
5 [[4,93],[5,6446],[6,120631]] [[4,93],[5,6343],[6,117128]]
6 [[4,106],[5,6442],[6,120602]] [[4,106],[5,6339],[6,117098]]
7 [[4,87],[5,6492],[6,120579]] [[4,87],[5,6403],[6,116973]]
8 [[4,78],[5,6391],[6,120695]] [[4,78],[5,6313],[6,117243]]
9 [[3,1],[4,120],[5,6420],[6,120626]] [[3,1],[4,118],[5,6312],[6,117028]]
10 [[4,89],[5,6351],[6,120755]] [[4,89],[5,6256],[6,117225]]
11 [[4,91],[5,6426],[6,120639]] [[4,91],[5,6343],[6,117098]]
12 [[4,97],[5,6390],[6,120689]] [[4,97],[5,6293],[6,117154]]
13 [[3,1],[4,53],[5,6554],[6,120566]] [[3,1],[4,52],[5,6498],[6,116962]]
14 [[3,1],[4,108],[5,6425],[6,120641]] [[3,1],[4,108],[5,6329],[6,117084]]
15 [[4,94],[5,6550],[6,120533]] [[4,94],[5,6463],[6,116918]]
16 [[4,100],[5,6290],[6,120795]] [[4,100],[5,6176],[6,117412]]
17 [[3,2],[4,115],[5,6539],[6,120512]] [[3,2],[4,111],[5,6425],[6,116965]]
18 [[4,102],[5,6445],[6,120622]] [[4,102],[5,6339],[6,117084]]
19 [[3,1],[4,72],[5,6506],[6,120645]] [[3,1],[4,70],[5,6413],[6,117062]]
20 [[3,2],[4,99],[5,6798],[6,120279]] [[3,2],[4,97],[5,6684],[6,116558]]

> E=run_ubcsat("VanDerWaerden_p5m_1132.cnf",runs=100,cutoff=1000000)
# computation not successfully completed, however it looks hopeless
# all minimums around 2700 - 3000

   \endverbatim
   </li>
   <li> The longer the clauses the better, one would guess? </li>
   <li> Partitioning into classes with 10 elements:
   \verbatim
for s : 1 thru 20 do block([G], set_random(s), G : random_projection_hg(G66,10), print(s, ncl_list_fcs(G), ncl_list_fcs(min_hg(G))));
1 [[3,8],[4,518],[5,13881],[6,112214]] [[3,8],[4,507],[5,13348],[6,104508]]
2 [[3,5],[4,499],[5,13600],[6,112516]] [[3,5],[4,494],[5,13101],[6,104915]]
3 [[3,7],[4,490],[5,13672],[6,112459]] [[3,7],[4,477],[5,13174],[6,104894]]
4 [[3,4],[4,496],[5,13718],[6,112420]] [[3,4],[4,491],[5,13231],[6,104821]]
5 [[3,5],[4,506],[5,13728],[6,112338]] [[3,5],[4,498],[5,13209],[6,104811]]
6 [[3,14],[4,449],[5,13973],[6,112129]] [[3,14],[4,437],[5,13506],[6,104378]]
7 [[3,3],[4,464],[5,14038],[6,112058]] [[3,3],[4,458],[5,13548],[6,104298]]
8 [[3,7],[4,490],[5,13760],[6,112343]] [[3,7],[4,476],[5,13265],[6,104756]]
9 [[3,6],[4,482],[5,14035],[6,112039]] [[3,6],[4,472],[5,13545],[6,104238]]
10 [[3,9],[4,469],[5,13909],[6,112224]] [[3,9],[4,458],[5,13412],[6,104397]]
11 [[3,3],[4,462],[5,14062],[6,112054]] [[3,3],[4,458],[5,13587],[6,104293]]
12 [[3,1],[4,509],[5,13752],[6,112325]] [[3,1],[4,507],[5,13225],[6,104758]]
13 [[3,8],[4,458],[5,13703],[6,112437]] [[3,8],[4,450],[5,13243],[6,104868]]
14 [[3,4],[4,466],[5,13640],[6,112517]] [[3,4],[4,464],[5,13184],[6,104945]]
15 [[3,6],[4,472],[5,14370],[6,111735]] [[3,6],[4,465],[5,13888],[6,103884]]
16 [[3,2],[4,498],[5,13477],[6,112666]] [[3,2],[4,494],[5,12951],[6,105320]]
17 [[3,8],[4,542],[5,13892],[6,112129]] [[3,8],[4,532],[5,13367],[6,104395]]
18 [[3,2],[4,431],[5,13898],[6,112256]] [[3,2],[4,428],[5,13439],[6,104652]]
19 [[3,5],[4,448],[5,14077],[6,112079]] [[3,5],[4,443],[5,13587],[6,104340]]
20 [[3,10],[4,487],[5,14044],[6,112069]] [[3,10],[4,475],[5,13504],[6,104266]]

set_random(1);
outputext_fcs("set_random(1),random_projection_min_hg(arithprog_hg(6,1132),10)",tcol2sat_stdhg2stdfcs(random_projection_min_hg(G66,10)),"VanDerWaerden_p10m_1132.cnf");
> OKsolver_2002-O3-DNDEBUG VanDerWaerden_p10m_1132.cnf
s UNSATISFIABLE
c sat_status                            0
c initial_maximal_clause_length         6
c initial_number_of_variables           114
c initial_number_of_clauses             236742
c initial_number_of_literal_occurrences 1391680
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     88.2
c number_of_nodes                       319
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                758
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        12
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_p10m_1132.cnf

> minisat-2.2.0 VanDerWaerden_p10m_1132.cnf
Simplification time:         51.85 s
conflicts             : 2966
CPU time              : 54.2827 s

set_random(18);
outputext_fcs("set_random(1),random_projection_min_hg(arithprog_hg(6,1132),10)",tcol2sat_stdhg2stdfcs(random_projection_min_hg(G66,10)),"VanDerWaerden_p10m18_1132.cnf");
> minisat-2.2.0 VanDerWaerden_p10m18_1132.cnf
Simplification time:         50.32 s
conflicts             : 5788
CPU time              : 55.0556 s
UNSATISFIABLE
   \endverbatim
   Looks highly unsatisfiable. </li>
   <li> One should write a variation, which multicolours the hyperedges, that
   is, chooses the equivalence classes to avoid intersecting any hyperedge
   in more than one element (doing it greedily, possibly failing). </li>
   <li> One could do this more greedily, trying to minimise the number
   of equivalence classes (the number of vertices in the image)?
    <ol>
     <li> One needs to inspect the literature on greedy hypergraph colouring
     (with as few colours as possible, but not fixed in advance) and on
     greedy hypergraph multicolouring. </li>
     <li> The simplest approach perhaps is to make every independent set
     (equivalence class) as large as possible, one after another. </li>
     <li> "As large as possible" just means avoiding that a unit-hyperedge
     is obtained, or, stronger, that any hyperedge gets shortened. </li>
    </ol>
   </li>
   <li> Now using projection via the modulo-operation:
   \verbatim
m : ceiling(1132/5);
  227
G66m5 : modulo_projection_hg(G66, m)$
ncl_list_fcs(G66m5);
  [[6,25651]]
F66m5 : tcol2sat_stdhg2stdfcs(G66m5)$
outputext_fcs("modulo_projection_hg(arithprog_hg(6,1132),227)",F66m5,"VanDerWaerden_m5_1132.cnf");

> E=run_ubcsat("VanDerWaerden_m5_1132.cnf",runs=100,cutoff=1000000)
# segmentation fault for sapsnr
1. rots:
358 364 365 366 368 369 370 371 372 373
 14   8  27   6  16  17   2   8   1   1
fps: 61118
5. g2wsat:
358 359 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384
  3   3   1   2   2   2   1   5   4   6  13   8   8  10  11   8   8   2   3
fps: 41672
6. ddfw:
358 359 360 365 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384
  1   4   3   2   2   1   1   5   2   1   8  13  13  13  12   6   6   4   1   2
fps: 3803
14. anovp:
391 409 413 415 417 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433
  1   1   3   1   1   1   5   6   5   5   9   6  10  11  10   6   8   1   5   4
434
  1
fps: 49414
35. uwalk:
627 628 629 630 631 632 633 634 635 636 637 638 640 641 642 643 644 645 646 647
  1   1   1   3   1   3   2   4   4   5   9   6   6   4   9   5   3   6   5   5
648 649 650 651 652 653 654
  5   3   1   1   2   2   3
fps: 180326
# sapsnr:
374 375 376 377 378 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394
  1   1   1   1   1   1   1   2   1   4   3   7  16  10   8   9   9   7  14   3

# on cs-oksvr:
> ubcsat-okl -alg rots -runs 100 -cutoff 10000000 -i VanDerWaerden_m5_1132.cnf | tee VanDerWaerden_m5_1132.cnf_OUT
> E=read_ubcsat("VanDerWaerden_m5_1132.cnf_OUT")
358 364 365
 83   4  10
97
# on csltok:
> ubcsat-okl -alg adaptg2wsat -runs 100 -cutoff 10000000 -i VanDerWaerden_m5_1132.cnf | tee VanDerWaerden_m5_1132.cnf_OUT
> E=read_ubcsat("VanDerWaerden_m5_1132.cnf_OUT",nrows=100)
358 364 365 366 368 369
 74   4  12   3   4   3
100
   \endverbatim
   Very little achieved (and rots might be a bit "better"; these instances are
   very hard for the ubcsat-algorithms (or they are unsatisfiable --- what is
   the real min? Is there a meaning to 358?) </li>
   <li> Using a complete solver seems hopeless:
   \verbatim
> minisat-2.2.0 VanDerWaerden_m5_1132.cnf
# aborted after apparently making no progress:
|   86287761 |     227    51302   307812 |   361059    75919     40 |  0.002 %
restarts              : 131070
conflicts             : 103554002      (1407 /sec)
CPU time              : 73592.2 s
> cryptominisat VanDerWaerden_m5_1132.cnf
# aborted after apparently making no progress:
c conflicts                : 39040336    (565.34    / sec)
c CPU time                 : 69056.95    s
> march_pl VanDerWaerden_m5_1132.cnf
# aborted after 2232m, apparently making no progress.
   \endverbatim
   Seems much harder than the palindromic problem. </li>
   <li> Can one create a certificate for n=1132 by Rabung's method or
   variations?:
   \verbatim
primep(227);
  true
5*227;
  1135
rabung_valid_param(2,6,1136);
  true
rabung_derived_parameters(2,6,1136);
  [227,2]
rabung_checkcriterion(2,6,1136);
  false
cm : rabung_colouring_map(2,6,1136);
L : map(cm,create_list(i,i,1,226));
C : seq2certificatevdw(L);
certificate_vdw_p([6,6],226,C);
  false
# First part contains 25,26,27,28,29,30.

ifactors(226);
  [[2,1],[113,1]]
smallest_primitive_modular_root(226);
  3
totient(226);
  112
ifactors(112);
  [[2,4],[7,1]]
XXX
   \endverbatim
   </li>
   <li> Perhaps these parameter values are difficult for these methods. </li>
  </ul>

*/
