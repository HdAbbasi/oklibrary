// Matthew Gwynne, 29.7.2010 (Swansea)
/* Copyright 2010, 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Structures/Sets/SetAlgorithms/SubsumptionHypergraph.hpp
  \brief Module, which implements a subsumption hypergraph generator

  Given two set systems F and G, the subsumption hypergraph of F with
  respect to G is the hypergraph (F,E) where
    
    * F is the vertex set,
    * E is the set of hyperedges H such that for every set S in G, H is the 
      largest subset of F where every T in H subsumes (i.e. is a subset of) S.

  One typically doesn't need the original sets from G and wants standardised
  vertex names, rather than sets as vertices. For reproducibility one also 
  wants an ordered version rather than using sets.

  Therefore assuming an order on F and G, one considers the standardised 
  ordered subsumption hypergraph of F and G with vertex list (1,...,|F|) and
  hyperedge list (H_1,...,H_|G|) where for all 1 <= j <= |G|, we have that H_j
  is a subset of (1,...,|F|) and, for all  1 <= i <= |F|, i is in H_j if F_i 
  subsumes G_j.

  The class implemented here implements the generation of such an ordered
  subsumption hypergraph given (ordered) set systems F and G.
  

  \todo Improve code quality
  <ul>
   <li> Specification of Subsumption_hypergraph needs more explanations, and
   it needs the concept! </li>
   <li> DONE All member functions need a specification. </li>
   <li> DONE Every class and function needs documentation! </li>
   <li> DONE In cases of larger arguments the argument-types of functions 
   should be const-references. </li>
   <li> DONE Everything not used by the user must be private. </li>
   <li> DONE Adopt the new for-loop-style. </li>
   <li> DONE Proper constructor: The two data members should be const, and so 
   their construction must take place in the initialiser list. </li>
   <li> DONE "Brief" should speak in intuitive words about the functionality
   provided. </li>
   <li> DONE Then the paragraph must specify it more precisely, *in words*. </li>
   <li> DONE So the reference to the Maxima-level is misplaced there. </li>
   <li> DONE And it needs more precision. </li>
  </ul>


  \todo Organisation
  <ul>
   <li> This submodule must go to Combinatorics/Hypergraphs, since it does not
   provide general set-operations. </li>
  </ul>


  \todo More unit tests

*/

#ifndef SUBSUMPTION_HYPERGRAPH_yhgBBv567
#define SUBSUMPTION_HYPERGRAPH_yhgBBv567

#include <algorithm>
#include <map>
#include <vector>

#include <boost/range.hpp>
#include <boost/iterator/counting_iterator.hpp>


namespace OKlib {
  namespace SetAlgorithms {

    // ############################################

    /*!
      \class Subsumption_hypergraph
      \brief Constructing the subsumption hypergraph

      Given two set systems F and G, as ranges of ranges (of type RangeF
      and RangeG respectively) of type Int, constructs the 
      standardised ordered subsumption hypergraph.

      The subsumption hypergraph is available as the object constructed
      by this class, with the vertex set (vertex_set) as the list 
      (1,...,length(F)) and the hyperedge set as the list (H_1,...,H_|G|)
      where for all 1 <= j <= |G| we have that H_j is the sublist of
      (1,...,|F|), i is in H_j if F_i subsumes G_j and H_j is a list of Int.

      The Maxima-specification is subsumption_std_ohg(F,G) (see
      ComputerAlgebra/Hypergraphs/Lisp/Basics.mac).
    */

    template <class RangeF,
	      class RangeG,
              typename Int = typename boost::range_difference<RangeF>::type>
    class Subsumption_hypergraph {

    public :

      //! The type of vertices associated with the subsumption hypergraph.
      //! Note here that these are index/integral types as the hypergraph
      //! is standardised.
      typedef Int vertex_type;
      //! The type of container for hyperedges associated with the subsumption
      //! hypergraph.
      typedef std::vector<vertex_type> hyperedge_type;
      //! The type of the set system corresponding to the subsumption 
      //! hypergraph itself, and specifically the container of it's
      //! hyperedges (see Subsumption_hypergraph::hyperedges).
      typedef std::vector<hyperedge_type> set_system_type;
      
      //! The list of vertices in the subsumption hypergraph, one for
      //! every set in F.
      //! Note here that these are index/integral types as the hypergraph
      //! is standardised. 
      const hyperedge_type vertex_set;
      //! The hyperedges of the subsumption hypergraph, one for each set in G 
      //! and a vertex in each edge H for each set in F which subsumes the 
      //! set in G corresponding to H.
      const set_system_type hyperedges;

      Subsumption_hypergraph(const RangeF& f_range, 
                             const RangeG& g_range):
        vertex_set(fill_vertex_set(boost::distance(f_range))), 
        hyperedges(subsumption_hypergraph(f_range, g_range)) {}

    private:

      //! Iterator type used for iterating over F (set systems) types
      typedef typename boost::range_const_iterator<RangeF>::type f_iterator_type;
      //! Iterator type used for iterating over G (set systems) types
      typedef typename boost::range_const_iterator<RangeG>::type g_iterator_type;
      //! Type of the values in F.
      typedef typename boost::range_value<RangeF>::type f_value_type;
      //! Type of std::map from elements of F to their index in F.
      typedef std::map<f_value_type, Int> hyperedge_map_type;
      //! Type of a non-standardised hyperedge in the subsumption hypergraph, 
      //! i.e., a set system with with subsumed sets as elements of each set.
      typedef std::vector<f_value_type> hyperedge_nonstd_type;
      //! Size type of F.
      typedef typename boost::range_size<RangeF>::type f_size_type;

      //! Given a maximum value returns a list of vertices 0 to size_f,
      //! intended for use as the vertex set of the subsumption hypergraph.
      static const hyperedge_type fill_vertex_set(const f_size_type size_f) {
        hyperedge_type vertex_set;
        const boost::counting_iterator<Int> v_begin(0);
        const boost::counting_iterator<Int> v_end(size_f);
        vertex_set.assign(v_begin, v_end);
        return(vertex_set);
      }

      //! Takes an ordered set system and returns a map which maps each
      //! set in the set system to the index of the set in the set system
      //! starting at 0.
      static hyperedge_map_type fill_hyperedge_map(const RangeF& f_range) {
        hyperedge_map_type hyperedge_map;
        for(
            struct {
              f_iterator_type it;
              Int count;
              const f_iterator_type f_end;
            } l = {boost::begin(f_range), 0, boost::end(f_range)};
            l.it != l.f_end;
            ++l.it)
          hyperedge_map[*l.it] = ++l.count;
        return(hyperedge_map);
      }

      //! Takes a set system with sets contained in RangeF and a map
      //! from all such sets to an integral type, returning a set of
      //! integral type elements having mapped each set to the element
      //! assigned to it by the given map.
      static
      hyperedge_type standardise_hyperedge(const hyperedge_nonstd_type& edge, 
                                           const hyperedge_map_type& hmap) {
        typedef typename boost::range_const_iterator<hyperedge_nonstd_type>::type
          hyperedge_nonstd_const_iterator_type;

        hyperedge_type new_edge;
        for(
            struct {
              hyperedge_nonstd_const_iterator_type it;
              const hyperedge_nonstd_const_iterator_type end;
            } l = {boost::begin(edge),boost::end(edge)};
            l.it != l.end; 
            ++l.it)
          new_edge.push_back(hmap.find(*l.it)->second);
        return(new_edge);
      }

      //! Takes a set c_range and a set system f_range and returns
      //! the set system containing all sets in f_range which subsume
      //! (i.e. are a subset of) c_range.
      template <class RangeC>
      static
      hyperedge_nonstd_type all_subsuming(const RangeC c_range, 
                                          const RangeF& f_range) {
        hyperedge_nonstd_type subsumes_set;
        for (
             struct {
               f_iterator_type it;
               const f_iterator_type end;
             } f = { boost::begin(f_range), boost::end(f_range) };
             f.it != f.end; ++f.it) 
          if (std::includes(boost::begin(c_range), boost::end(c_range), 
                            boost::begin(*f.it),boost::end(*f.it)))
            subsumes_set.push_back(*f.it);
        return(subsumes_set);
      }

      //! Given the input ranges computes the hyperedges of the subsumption 
      //! hypergraph.
      static const set_system_type subsumption_hypergraph(const RangeF& f_range,
                                                          const RangeG& g_range) {
        set_system_type hyperedges;
        for (
             struct {
               g_iterator_type it;
               const g_iterator_type end;
               const hyperedge_map_type map;
             } g = {boost::begin(g_range), boost::end(g_range), 
                    fill_hyperedge_map(f_range)};
             g.it != g.end; ++g.it)
          hyperedges.push_back(standardise_hyperedge(all_subsuming(*g.it, f_range), g.map));
        return hyperedges;
      }
    };


    /*!
      \brief Computes the subsumption hypergraph

      Given two ordered set system as ranges f_range and g_range (of type 
      RangeF and RangeG respectively), yielding hypergraphs F and G,
      constructs the standardised ordered subsumption hypergraph.

      The subsumption hypergraph is returned as the hyperedge list 
      (H_1,...,H_|G|) where for all 1 <= j <= |G| we have that H_j is the
      sublist of (1,...,|F|) of those i where F_i contained in G_j, while H_j
      is a list of Ints where Int is the size type of f_range.

      The Maxima-specification is subsumption_std_ohg(F,G) (see
      ComputerAlgebra/Hypergraphs/Lisp/Basics.mac).

      @param f_range the conceptual vertices of the subsumption hypergraph, 
                     i.e., the list of sets which subsumes elements of g_range.
      @param g_range the list of sets which are mapped to hyperedges, i.e., 
                      the sets which are subsumed by elements of f_range.
      @return the std::vector of hyperedges in the subsumption hypergraph of 
              f_range (subsuming sets) w.r.t g_range (subsumed sets).
    */

    template<class RangeF, class RangeG>
    typename Subsumption_hypergraph<RangeF, RangeG>::set_system_type
    subsumption_hypergraph(const RangeF& f_range, const RangeG& g_range) {
      Subsumption_hypergraph<RangeF, RangeG> sub_hyp(f_range,g_range);
      return sub_hyp.hyperedges;
    }

  }
}

#endif
