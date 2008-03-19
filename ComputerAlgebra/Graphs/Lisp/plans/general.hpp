// Oliver Kullmann, 24.11.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Graphs/Lisp/plans/general.hpp
  \brief Plans for graphs via computer-algebra-systems in general


  \todo Create milestones


  \todo Graph concepts
  <ul>
   <li> A "graph" is just a 2-element list, consisting of the set of
   vertices, and a set of 2-element vertex sets. </li>
   <li> A "graph with loops" also allows 1-element vertex sets. </li>
   <li> A "general graph" is a triple [V,E,f], where V, E are sets and
   f is a map from E to 1-2-element subsets of V. </li>
   <li> The same with directed graphs, only that this time we have
   vertex lists instead of vertex sets. </li>
   <li> There is also the (cryptomorphic) notion of a "precategory",
   which is a 4-tuple [V,E,source,target]. </li>
   <li> Since also for general graphs the edge set needs to be given, we don't
   have the possibility of "lazy graph representations". Seems unavoidable. /li>
   <li> Given a vertex, we need the set of edges incident to the vertex;
   this can be handled via the dual hypergraph, but we should provide some
   more convenient methods. </li>
   <li> Likely, our graph-etc-concepts are conceptually, but when using or
   implementing algorithms then we should, if possible, use the maxima-graphs. </li>
   <li> How to handle "properties" ? DONE (these shall just be maps) </li>
   <li> Can we tag such objects as being "graphs" ? DONE (we are living
   type-free) </li>
  </ul>


  \todo Maxima package "graphs"
  <ul>
   <li> We need to find out whether for example the colouring function computes an
   exact value or an approximation! See my e-mail to the maxima-mailing-list (yet,
   18.3.2008, without answer). </li>
   <li> We need conversions between graphs and maxima-graphs.
    <ol>
     <li> DONE (the vertex names become vertex labels)
     Given a graph, we can either just forget the vertex names, or use
     them as vertex labels. </li>
     <li> DONE And given a maxima-graph, we can use the standard-vertex-names
     0, ... </li>
     <li> Or we can use the vertex-labels (assuming they are present). </li>
    </ol>
   </li>
   <li> And we need conversions between directed graphs and maxima-digraphs. </li>
   <li> Find out about the output-formats for maxima-graphs. </li>
   <li> Bug:
   \verbatim
draw_graph(complete_graph(3))$
gnuplot> plot '/home/kullmann/data.gnuplot' index 0 t '' w lp ps 1 pt 0 lw 1 lt 1 lc rgb 'black', '/home/kullmann/data.gnuplot' index 1 t '' w lp ps 1 pt 0 lw 1 lt 1 lc rgb 'black', '/home/kullmann/data.gnuplot' index 2 t '' w lp ps 1 pt 0 lw 1 lt 1 lc rgb 'black', '/home/kullmann/data.gnuplot' index 3 t '' w p ps 2 pt 7 lc rgb 'red'
         "/home/kullmann/maxout.gnuplot", line 22: ';' expected
   \endverbatim
   Notify maxima mailing-list. </li>
  </ul>


  \todo InputOutput.mac
  <ul>
   <li> Extend the documentation. </li>
   <li> Write documentation. </li>
   <li> Output :
    <ol>
     <li> Can we add comments to the graph-output? </li>
     <li> Should we give the graphs in the dot-output a dedicated name? </li>
     <li> Generalise the graph output, so that arbitrary graphs
     can be output (making function "string_vertex" a parameter). </li>
     <li> DONE Move graph output to dedicated "InputOutput.mac". </li>
    </ol>
   </li>


  \todo Generators.mac
  <ul>
   <li> Create complete graphs. DONE (already in package "graphs") </li>
   <li> Create complete bipartite graphs. DONE (already in package "graphs") </li>
   <li> Generalisations of the Kneser graphs:
    <ol>
     <li> The Johnson graphs J(n,k,i), consisting like the Kneser
     graphs of all k-subsets of n, while we have an edge joining
     two vertices if the intersection has exactly size i. </li>
     <li> The generalised Kneser graph K(n,k,t), the union
     of J(n,k,i) for 0 <= i < t. </li>
     <li> The Kneser graph K(G) of a hypergraph G, with vertices
     the hyperedges, joined by an edge if disjoint. </li>
    </ol>
   </li>
  </ul>


  \todo Graph traversal
  <ul>
   <li> Implement the generic graph traversal from module CS-232. </li>
   <li> This is likely best done with the maxima-graphs. </li>
   <li> Compute connected components and strong connected components. </li>
  </ul>


  \todo Treewidth
  <ul>
   <li> Implement all basic methods for computing the treewidth of a graph. </li>
   <li> See Combinatorics/Graphs/TreeDecompositions/EliminationSequences.hpp for
   one algorithm, and
   Combinatorics/Graphs/TreeDecompositions/plans/EliminationSequences.hpp for
   plans. </li>
   <li> See also Combinatorics/Graphs/TreeDecompositions/plans/general.hpp.
   </li>
  </ul>


  \todo Primitive directed graphs etc.
  <ul>
   <li> Compute the index of imprimitivity of a directed graph (with loops).
   </li>
   <li> And for primitive directed graphs (with loops) compute the index of
   primitivity. </li>
   <li> Again, perhaps best done with the maxima-graph-package. But then loops
   need to be handled specially (is this reasonable?). </li>
  </ul>

*/

