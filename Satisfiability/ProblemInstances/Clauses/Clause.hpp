// Oliver Kullmann, 27.2.2002 (Swansea)
/* Copyright 2002 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

// Clause.hpp

#ifndef WAECHTERCLAUSE

#include <set>
#include <algorithm>
// #include <limits> not yet in gcc (2.9.5)
#include <climits> // instead of <limits>

#include "VarSet.hpp"
#include "Literal.hpp"

namespace Clauses {

  using namespace Variables;
  using namespace Literals;

  typedef size_t set_length; // should by "size_type"
  const set_length max_length = INT_MAX;
  // should be:
  // const set_length max_length = numeric_limits<size_type>::max();

  inline const set<Var> operator + (const set<Var>& A, const set<Var>& B) {
    set<Var> result;
    insert_iterator< set<Var> > res_ins(result, result.begin());
    set_union(A.begin(), A.end(), B.begin(), B.end(), res_ins);
    return result;
  }

  
  class Litset {

  public :

    Litset () {}
    Litset (const set<Lit>&);

    bool is_tautological() const;
    bool is_empty() const;

    set_length length() const;

    bool contains(Lit) const;

    Litset comp() const;
    set<Var> var() const;

    Litset& add(Lit);
    Litset& remove(Lit);

    Litset& add_ls(const Litset&);
    Litset& remove_ls(const Litset&);

    bool operator == (const Litset&) const;
    bool operator < (const Litset&) const;

    const Litset operator + (const Litset&) const;
    const Litset operator - (const Litset&) const;
    const Litset operator & (const Litset&) const;
    
    set<Lit> ls;

  };

  inline Litset::Litset(const set<Lit>& L) {
    ls = set<Lit>(L);
  }

  inline bool Litset::is_tautological() const {
    // uses the special order of literals
    set<Lit>::iterator a0 = ls.begin(), a = a0;
    if (a0 == ls.end())
      return false;
    a++;
    while (a != ls.end()) {
      if (a -> comp() == *a0)
	return true;
      a++; a0++;
    }
    return false;
  }

  inline bool Litset::is_empty() const {
    return ls.empty();
  }
  
  inline set_length Litset::length() const {
    return ls.size();
  }

  inline bool Litset::contains(const Lit x) const {
    return ! (ls.find(x) == ls.end());
  }

  inline Lit comp(const Lit x) {
    return x.comp();
  }

  inline Litset Litset::comp() const {
    set<Lit> result;
    insert_iterator< set<Lit> > res_ins(result, result.begin());
    transform(ls.begin(), ls.end(), res_ins, Clauses::comp);
    return Litset(result);
  }

  inline Var var(const Lit x) {
    return x.var();
  }

  inline set<Var> Litset::var() const {
    set<Var> result;
    insert_iterator< set<Var> > res_ins(result, result.begin());
    transform(ls.begin(), ls.end(), res_ins, Clauses::var);
    return result;
  }

  inline Litset& Litset::add(Lit x) {
    ls.insert(x);
    return *this;
  }

  inline Litset& Litset::remove(Lit x) {
    ls.erase(x);
    return *this;
  }

  inline Litset& Litset::add_ls(const Litset& L) {
    ls.insert(L.ls.begin(), L.ls.end());
    return *this;
  }

  inline Litset& Litset::remove_ls(const Litset& L) {
    ls.erase(L.ls.begin(), L.ls.end());
    return *this;
  }

  inline bool Litset::operator == (const Litset& L) const {
    return ls == L.ls;
  }

  inline bool Litset::operator < (const Litset& L) const {
    return ls < L.ls;
  }

  inline const Litset Litset::operator + (const Litset& L) const {
    set<Lit> result;
    insert_iterator< set<Lit> > res_ins(result, result.begin());
    set_union(ls.begin(), ls.end(), L.ls.begin(), L.ls.end(), res_ins);
    return Litset(result);
  }

  inline const Litset Litset::operator - (const Litset& L) const {
    set<Lit> result;
    insert_iterator< set<Lit> > res_ins(result, result.begin());
    set_difference(ls.begin(), ls.end(), L.ls.begin(), L.ls.end(), res_ins);
    return Litset(result);
  }

  inline const Litset Litset::operator & (const Litset& L) const {
    set<Lit> result;
    insert_iterator< set<Lit> > res_ins(result, result.begin());
    set_intersection(ls.begin(), ls.end(), L.ls.begin(), L.ls.end(), res_ins);
    return Litset(result);
  }


  namespace Error {

    struct not_a_clause {};

  }


  class Cl : public Litset {

    // for objects x of type Cl we must have ! x.is_tautological()

  public :

    Cl () {};
    Cl (const set<Lit>&);
    Cl (const Litset&);

    Cl& add(Lit);

    const Cl operator + (const Cl&) const;
    
  };

  inline Cl::Cl(const set<Lit>& L)
    : Litset(L)
  {
    if (this -> Litset::is_tautological())
      throw Error::not_a_clause();
  }

  inline Cl::Cl(const Litset& L)
    : Litset(L)
  {
    if (this -> Litset::is_tautological())
      throw Error::not_a_clause();
  }

  inline Cl& Cl::add(Lit x) {
    if (this -> contains(x.comp()))
      throw Error::not_a_clause();
    this -> Litset::add(x);
    return *this;
  }

  inline const Cl Cl::operator + (const Cl& C) const {
    Cl D = Litset(*this) + Litset(C);
    if (D.is_tautological())
      throw Error::not_a_clause();
    return D;
  }

}


#endif

#define WAECHTERCLAUSE


