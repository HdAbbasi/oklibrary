// Oliver Kullmann, 2.5.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file OKlib/Satisfiability/Assignments/PartialAssignments/Boolean.hpp
  \brief Partial assignments for boolean literals
*/

#ifndef BOOLEAN_gB5eSpoao7Y
#define BOOLEAN_gB5eSpoao7Y

#include <map>
#include <utility>
#include <cassert>

#include <OKlib/Satisfiability/ProblemInstances/Literals/var.hpp>
#include <OKlib/Satisfiability/ProblemInstances/Literals/cond.hpp>
#include <OKlib/Satisfiability/ProblemInstances/Literals/Basics.hpp>
#include <OKlib/Satisfiability/Values/StatusTypes.hpp>

namespace OKlib {
  namespace Satisfiability {
    namespace Assignments {
      namespace PartialAssignments {

        /*!
          \class BPass0
          \brief An immutable boolean partial assignment in the simplest form
        */

        template <typename Lit>
        class BPass0 {
        public :
          typedef Lit literal_type;
        private :
          typedef OKlib::Satisfiability::ProblemInstances::Literals::Literal2pair<Lit> lit2pair_functor;
        public :
          typedef typename lit2pair_functor::litaspair_type litaspair_type;
          typedef typename lit2pair_functor::var_type var_type;
          typedef typename lit2pair_functor::cond_type cond_type;
        private :
          typedef std::map<var_type,bool> map_type;
          typedef typename map_type::const_iterator iterator;
          const map_type map;
        public :
          typedef typename map_type::size_type size_type;
          typedef OKlib::Satisfiability::Values::Assignment_status status_type;

          BPass0() {}
          template <class LitIterator>
          BPass0(const LitIterator begin, const LitIterator end) : map(fill_map(begin,end)) {}
          BPass0(const literal_type x) : map(map_type()) {
            if (not x) return;
            map[OKlib::Literals::var(x)] = OKlib::Literals::cond(x);
          }

          size_type size() const { return map.size(); }
          bool empty() const { return map.empty(); }

          friend bool operator ==(const BPass0& lhs, const BPass0& rhs) {
            return lhs.map == rhs.map;
          }

          status_type operator()(const literal_type x) const {
            const var_type v = OKlib::Literals::var(x);
            const iterator it = map.find(v);
            if (it == map.end()) return OKlib::Satisfiability::Values::unassigned;
            assert(v);
            return it->second;
          }

        private :
          template <class LitIterator>
          map_type fill_map(const LitIterator begin, const LitIterator end) {
            const lit2pair_functor l2p;
            map_type result;
            for (LitIterator i = begin; i != end; ++i) {
              const literal_type x = *i;
              if (not x) return result;
              const litaspair_type p = l2p(x);
              result.insert(p);
            }
            return result;
          }
        };
      }
    }
  }
}

#endif
