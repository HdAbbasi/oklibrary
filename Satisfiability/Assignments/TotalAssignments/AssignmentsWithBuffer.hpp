// Oliver Kullmann, 25.12.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file OKlib/Satisfiability/Assignments/TotalAssignments/AssignmentsWithBuffer.hpp
  \brief Components for assignments with buffers (for processing of single assignments)

*/

#ifndef ASSIGNMENTSWITHBUFFER_nBaLk810
#define ASSIGNMENTSWITHBUFFER_nBaLk810

#include <vector>
#include <stack>
#include <cassert>

#include <OKlib/Satisfiability/ProblemInstances/Variables/traits/index_type.hpp>
#include <OKlib/Satisfiability/ProblemInstances/Literals/traits/var_type.hpp>
#include <OKlib/Satisfiability/ProblemInstances/Literals/traits/cond_type.hpp>
#include <OKlib/Satisfiability/ProblemInstances/Literals/var.hpp>
#include <OKlib/Satisfiability/ProblemInstances/Literals/cond.hpp>
#include <OKlib/Satisfiability/Values/StatusTypes.hpp>

namespace OKlib {
 namespace Satisfiability {
  namespace Assignments {
   namespace TotalAssignments {

     /*!
       \class BAssignmentWithQueue
       \brief Boolean assignments with queue for (elementary) assignments to be processed
     */

     template <typename Lit>
     class BAssignmentWithQueue {
     public :

       typedef Lit literal_type;
       typedef typename OKlib::Literals::traits::var_type<literal_type>::type variable_type;
       typedef typename OKlib::Variables::traits::index_type<variable_type>::type index_type;

       typedef OKlib::Satisfiability::Values::Assignment_status value_type;

       BAssignmentWithQueue() : n(0), next_lit(phi.begin()) {}
       BAssignmentWithQueue(const index_type n_) : n(n_), V(n+1) {
         assert(n >= 0);
         phi.reserve(n);
         next_lit = phi.begin();
       }
       void resize(const index_type n_) {
         assert(n_ >= 0);
         n = n_;
         V.resize(n+1);
         phi.reserve(n);
         next_lit = phi.begin();
       }

       value_type operator[] (const variable_type v) const {
         assert(index_type(v) <= n);
         return V[index_type(v)];
       }
       value_type operator() (const literal_type x) const {
         if (OKlib::Literals::cond(x))
           return V[index_type(OKlib::Literals::var(x))];
         else
           return -V[index_type(OKlib::Literals::var(x))];
       }

       bool push(const literal_type x) {
         switch (operator()(x)) {
         case OKlib::Satisfiability::Values::val0 :
           return false;
         case OKlib::Satisfiability::Values::val1 :
           return true;
         default :
           phi.push_back(x);
           V[index_type(OKlib::Literals::var(x))] = value_type(OKlib::Literals::cond(x));
           return true;
         }
       }

       literal_type top() const {
         assert(not empty());
         return *next_lit;
       }
       void pop() {
        assert(next_lit != phi.end());
         ++next_lit;
       }
       index_type size() const { return phi.end() - next_lit; }
       bool empty() const { return next_lit == phi.end(); }

     private :

       index_type n;
       typedef std::vector<value_type> vector_t;
       vector_t V;
       typedef std::vector<literal_type> pass_t;
       pass_t phi;
       typedef typename pass_t::const_iterator iterator_t;
       iterator_t next_lit;
     };


     /*!
       \class BAssignmentWithRQueue
       \brief Boolean assignments with resettable queue for (elementary) assignments to be processed
     */

     template <typename Lit>
     class BAssignmentWithRQueue : public BAssignmentWithQueue<Lit> {
       typedef BAssignmentWithQueue<Lit> base_class;
     public :

       BAssignmentWithRQueue(const typename base_class::index_type n) : base_class(n) {}

       bool push_forced(const typename base_class::literal_type x) {
         return this -> push(x);
       }
       bool push_free(const typename base_class::literal_type x) {
         if (not this -> push_forced(x)) return false;
         S.push(-- (this -> phi.end()));
         return true;
       }

       void reset() {
         // XXX
       }

     private :

       using typename base_class::iterator_t;
       typedef std::stack<typename base_class::iterator_t> stack_t;
       stack_t S;
     };

    

   } 
  }
 }
}

#endif
