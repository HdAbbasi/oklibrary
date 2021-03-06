// Oliver Kullmann, 13.9.2010 (Swansea)
/* Copyright 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/CategoriesCls/plans/general.hpp
  \brief On investigations regarding categories of clause-sets


  \todo Links
  <ul>
   <li> See ComputerAlgebra/Satisfiability/Lisp/Categories/plans/general.hpp.
   </li>
  </ul>


  \todo Satisfiability of products
  <ul>
   <li> The first form of the conjecture (falsified below) is that for a 
   finite family of unsatisfiable flcls's, none of them containing the empty
   clause, their product is unsatisfiable as well. </li>
   <li> Considering the product of full clause-sets V_n:
   \verbatim
prl(L) := product_flcls(map(fcls2flcls, map(full_fcs,L)))$
prlfcs(L) := flcls2fcls(prl(L))$
testl(L) := current_satsolver(prlfcs(L))$

testl([0,0]);
  false;
testl([0,1]);
  true;
testl([1,1]);
  false;
testl([1,2]);
  true;
testl([1,3]);
  true;
testl([1,4]);
  true;
testl([1,5]);
  true;
testl([1,6]);
  true;

prl([1,2]);
[
  [{[-1,-2],[-1,-1],[-1,1],[-1,2],[1,-2],[1,-1],[1,1],[1,2]},
   lambda([x],map('apply,[lambda([x],-x),lambda([x],-x)],map("[",x)))],
  {{[-1,-2],[-1,-1]},{[-1,-2],[-1,1]},{[-1,-1],[-1,2]},{[-1,1],[-1,2]},
  {[1,-2],[1,-1]},{[1,-2],[1,1]},{[1,-1],[1,2]},{[1,1],[1,2]}}
]
flcls2fcls(prl([1,2]));
  [{1,2,3,4},{{-4,-3},{-4,-2},{-3,-1},{-2,-1},{1,2},{1,3},{2,4},{3,4}}]
all_sat_fcs(flcls2fcls(prl([1,2])));
  {{-4,-1,2,3},{-3,-2,1,4}}
% Solutions interpreted:
[1,1],[1,-1],[-1,2],[-1,-2]
-2,-3,4,1
[-1,-1],[-1,1],[1,-2],[1,2]
2,3,-4,-1

length(all_sat_fcs(flcls2fcls(prl([1,2]))));
  2
length(all_sat_fcs(flcls2fcls(prl([1,3]))));
  18
length(all_sat_fcs(flcls2fcls(prl([1,4]))));
  110
length(all_sat_fcs(flcls2fcls(prl([1,5]))));
  570
length(all_sat_fcs(flcls2fcls(prl([1,6]))));
  2702
length(all_sat_fcs(flcls2fcls(prl([1,7]))));
  12138

map(factor,[2,18,110,570,2702]);
  [2, 2*3^2, 2*5*11, 2*3*5*19, 2*7*193]
eis_search(2,18,110,570,2702);
  ["A038721"]
eis_search_name(2,18,110,570,2702);
  A038721 - k=2 column of A038719.
eis_search(1,9,55,285,1351);
  ["A016269"]
eis_search_name(1,9,55,285,1351);
A016269 - Number of monotone Boolean functions of n variables with 2 mincuts. 
Also number of Sperner systems with 2 blocks.

eis_details(A016269);

A016269 - Number of monotone Boolean functions of n variables with 2 mincuts. 
Also number of Sperner systems with 2 blocks.

UNSIGNED TERMS
  1, 9, 55, 285, 1351, 6069, 26335, 111645, 465751, 1921029, 7859215, 
  31964205, 129442951,522538389, 2104469695, 8460859965, 33972448951, 
  136276954149, 546269553775, 2188563950925, 8764714059751

OFFSET
  0, 2

FORMULA
  G.f.: 1/((1-2x)(1-3x)(1-4x)). a(n) = (2^n)*(2^n - 1)/2 - 3^n + 2^n.
  a(n)=sum{0<=i,j,k,<=n, i+j+k=n, 2^i*3^j*4^k}. - Hieronymus Fischer 
   (Hieronymus.Fischer(AT)gmx.de), Jun 25 2007
  a(n)=2^(n+1)*(1+2^(n+2))-3^(n+2). - Hieronymus Fischer 
   (Hieronymus.Fischer(AT)gmx.de), Jun 25 2007
  a(n) = 3*StirlingS2(n+1,4) + StirlingS2(n+1,3). - Ross La Haye 
   (rlahaye(AT)new.rr.com), Jan 10 2008

MAPLE PROGRAM
  with(combinat):a:=n->stirling2(n,4)-stirling2(n-1,4): seq(a(n), n=4..24); 
  - Zerinvary Lajos (zerinvarylajos(AT)yahoo.com), Oct 05 2007

CROSS-REFERENCES
  Equals (1/2) A038721(n+1). First differences of A000453. 
  Partial sums of A027650.
  Pairwise sums of A099110.
  Odd part of A019333. Cf. A000392, A032263.
  Adjacent sequences: A016266 A016267 A016268 this_sequence A016270 A016271 
    A016272
  Sequence in context: A058852 A068970 A141530 this_sequence A005770 A030053 
    A072844

REFERENCES
  L. Comtet, Advanced Combinatorics, Reidel, 1974, p. 292, #8, s(n,2).

HYPERLINKS
  K. S. Brown, Dedekind's problem [http://www.mathpages.com/home/kmath030.htm]
  Vladeta Jovovic, Illustration for A016269, A047707, A051112-A051118
[http://www.research.att.com/~njas/sequences/a047707.pdf]
  Index entries for sequences related to Boolean functions
[http://www.research.att.com/~njas/sequences/Sindx_Bo.html#Boolean]
  Goran Kilibarda and Vladeta Jovovic, Antichains of Multisets
[http://www.cs.uwaterloo.ca/journals/JIS/index.html], J. Integer Seqs., 
  Vol. 7, 2004.

COMMENTS
  Half the number of 2 X (n+2) binary arrays with both a path of adjacent 1's 
  and a path of adjacent 0's from top row to bottom row. 
    - Ron Hardin (rhh(AT)cadence.com), Mar 21 2002
  As (0,0,1,9,55,...) this is the third binomial transform of cosh(x)-1. 
  It is the binomial transform of A000392, when this has two leading zeros. 
  Its e.g.f. is then exp(3x)cosh(x)-exp(3x) and a(n)=(4^n-2*3^n+2^n)/2. 
    - Paul Barry (pbarry(AT)wit.ie), May 13 2003
  Let P(A) be the power set of an n-element set A. Then a(n-2) = the number of
  pairs of elements {x,y} of P(A) for which either 
   0) x and y are disjoint and for which x is not a subset of y and y is
      not a subset of x, or 
   1) x and y are intersecting but for which x is not a subset of y and y is 
      not a subset of x. - Ross La Haye (rlahaye(AT)new.rr.com), Jan 10 2008

testl(2,2);
  false;
testl(2,3);
  false;
testl(3,3);
  false;

testl([2,2,2]);
  false;
testl([2,2,3]);
  false;

testl([2,2,2,2]);

   \endverbatim
   Below we will see that a(n) should start with 0 (for n=1), that is, the
   sequence should be right-shifted, with a 0 added at the beginning. </li>
   <li> Investigation of prl([1,n]):
    <ol>
     <li> Let F_n := prl([1,n]) = V_1 x V_n and s_n := 
     length(all_sat_fcs(flcls2fcls(prl([1,n])))) the number of satisfying
     assignments of F_n. </li>
     <li> And let a(n) be sequence A016269, and thus s_n = 2*a(n-1). </li>
     <li> F_n is complementation-invariant (as a product of complementation-
     invariant clause-sets) and bipartite (as every product V_1 x V is: one
     part is given by {1} x V_n, the other by {-1} x V_n):
     \verbatim
map(bipartite_fcs_p,create_list(prlfcs([1,n]),n,1,5));
  [true,true,true,true,true]

map(lambda([FF], is(comp_fcs(FF) = FF)), create_list(prlfcs([1,n]),n,1,5));
  [true,true,true,true,true]
     \endverbatim
     </li>
     <li> Thus we actually have a hypergraph 2-colouring problem, namely the
     problem of 2-colouring the hypergraph G_n := cls2hg(V_n) (with the 2n
     literals as vertices).
     \verbatim
is_isomorphic_btr_fcs(tcol2sat_hg2fcs(fcs2hg(full_fcs(1))), prlfcs([1,1]));
  true
is_isomorphic_btr_fcs(tcol2sat_hg2fcs(fcs2hg(full_fcs(2))), prlfcs([1,2]));
  true
is_isomorphic_btr_fcs(tcol2sat_hg2fcs(fcs2hg(full_fcs(3))), prlfcs([1,3]));
  true
is_isomorphic_btr_fcs(tcol2sat_hg2fcs(fcs2hg(full_fcs(4))), prlfcs([1,4]));
  true
is_isomorphic_btr_fcs(tcol2sat_hg2fcs(fcs2hg(full_fcs(5))), prlfcs([1,5]));
  true
     \endverbatim
     </li>
     <li> Now it is easy to see that F_n for n >= 2 is satisfiable, since
     G_n is obviously 2-colourable: Give the vertices -1,+1 colour 1, and
     give vertices -2,+2 colour 2 --- every hyperedge contains -1 or +1,
     and every hyperedge contains -2 or +2. </li>
     <li> It remains to determine s_n, the number of 2-colourings of G_n. </li>
     <li> The 2-colourings of G_n are the partitions of {-n,...,n} - {0} such
     that no part contains a hyperedge of G_n; these are exactly the partitions
     such that each part contains both i,-i for some i. </li>
     <li> So the 2-colourings of G_n correspond to triples (A,B,x), where A,B
     are disjoint subsets of {1,...,n}, while x is a vector with entries -1,+1
     of length n - |A| - |B| : for i in A the vertices i,-i get colour 1, for
     i in B the vertices i,-i get colour 2, and x determines for the remaining
     vertices whether the positive or the negative vertex gets colour 1 resp.
     colour 2.
     \verbatim
alldisjnepairs(n) := second(kneser_g_hg(ses2hg(disjoin({},powerset(setn(n))))));
an_v1(n) := sum_l(map(
  lambda([P], 2^(n-length(first(P))-length(second(P)))),
  listify(alldisjnepairs(n))));

create_list(an_v1(n),n,1,6);
  [0,1,9,55,285,1351]
     \endverbatim
     an_v1(n) = a(n-1) = 1/2 s_n; note that an_v1(n) computes only half of the
     assignments, since only one form of a pair (A,B) is considered. </li>
     <li> "Also number of Sperner systems with 2 blocks." in A016269 means the
     number of subsumption-free hypergraphs with n+1 vertices not containing
     the empty hyperedge:
     \verbatim 
all_Sp_2bl(n) := subset(powerset(powerset(setn(n)), 2), lambda([S], 
    is(length(S)=2) and not elementp({},S) and is_antichain(S)))$
an_v2(n) := length(all_Sp_2bl(n))$

create_list(an_v2(n),n,1,6);
  [0,1,9,55,285,1351]
     \endverbatim
     </li>
     <li> So s_n = 1/2 * number of Sperner systems with n vertices and 2
     blocks. </li>
     <li> This is proven as follows:
      <ol>
       <li> We have to show an_v2(n) = an_v1(n). </li>
       <li> This is done be constructing a bijection between all triples
       (A,B,x) as specified above and the two-element subsumption-free pairs
       (X,Y) of the powerset of {1,..,n}. </li>
       <li> To (A,B,X) we assign (X,Y), where X := A + C, Y := B + C, and where
       C is the set of i in X - (A+B) with value +1 at the corresponding
       position in x. </li>
      </ol>
     </li>
     <li> A formula for s_n/2 is as follows:
     \verbatim
an_v3(n) := binomial(2^n,1) + binomial(2^n,2) - 3^n;
create_list(an_v3(n),n,1,10);
  [0,1,9,55,285,1351,6069,26335,111645,465751]
     \endverbatim
     which is shown as follows:
      <ol>
       <li> The number of all anti-chains {A,B}, where A,B are subsets of
       {1,...,n}, is to be computed. </li>
       <li> The number of all subsets {A,B} (possibly A=B) is
       binomial(2^n,1) + binomial(2^n,2). </li>
       <li> From this we have to subtract the number of all {A,B} where
       A <= B or B <= A. </li>
       <li> These sets can be mapped bijectively to all pairs (A,B) with
       A <= B <= {1,...,n} by sorting. </li>
       <li> Now these pairs exactly represent the partial assignment over
       {1,...,n}, where elements in A are unassigned, elements in B-A are
       positive, elements in {1,...,n}-B are negative. </li>
      </ol>
     </li>
    </ol>
   </li>
   <li> So perhaps unit-clauses are also problematic, not just
   empty clauses? </li>
   <li> For the special case of products of full clauses, the conjecture is
   that testl(L) yields true iff L contains a 0 and a non-0 or a 1 and a non-1.
   </li>
   <li> The new conjecture for the general case then could be: A product of
   literal-based formal clause-sets, where all clauses are of length at least
   2, is unsatisfiable iff at least one part is unsatisfiable. </li>
  </ul>

*/
