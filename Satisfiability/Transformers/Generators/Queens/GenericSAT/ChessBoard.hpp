// Oliver Kullmann, 6.7.2018 (Swansea)
/* Copyright 2018 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */


#ifndef CHESSBOARD_PjPxE
#define CHESSBOARD_PjPxE

#include <limits>
#include <type_traits>
#include <ostream>
#include <vector>

#include <cassert>
#include <cstdint>
#include <cmath>

namespace ChessBoard {

  // The coordinates of the field, with valid values >= 1:
  typedef std::uint32_t coord_t;
  typedef std::int32_t scoord_t;
  constexpr coord_t max_coord = std::numeric_limits<coord_t>::max() / 2 - 1;

  /*
     Var{i,j} for i, j >= 1 refers to a valid field, while i=0 or j=0
     are "singular" variables.
  */
  struct Var {
    coord_t first;
    coord_t second;
  };
  static_assert(std::is_pod<Var>::value, "Var is not POD.");
  inline constexpr bool operator ==(const Var lhs, const Var rhs) {
    return lhs.first == rhs.first and lhs.second == rhs.second;
  }
  inline constexpr bool operator !=(const Var lhs, const Var rhs) {
    return not (lhs == rhs);
  }
  inline constexpr bool singular(const Var v) noexcept {
    return v.first == 0 or v.second == 0;
  }
  std::ostream& operator <<(std::ostream& out, const Var v) noexcept {
    return out << "(" << v.first << "," << v.second << ")";
  }

  // Values related to encoding the 2-dimensional variables:
  typedef std::uint64_t Var_uint;
  typedef std::int64_t Var_int;

  // Counting solutions:
  typedef std::uint_fast64_t Count_t;

  /*
    The decomposition of the NxN field into diagonals (fields with equal
     difference) and antidiagonals (fields with equal sum), where each
     such line is specified by a value of class Diagonal:
  */
  struct Diagonal {
    Var s; // start field
    Var_uint l; // length
    Var_uint i;
    /* Field (variable) (x,y) has abstract diagonal-index x-y, which ranges
       from 1-N to N-1, and then we set i = (x-y) + (N-1) with
       0 <= i <= 2N-2.
    */
  };
  struct AntiDiagonal {
    Var s; // start field
    Var_uint l; // length
    Var_uint i;
    /* (x,y) has abstract antidiagonal-index x+y, which ranges from 1+1 to
       N+N, and then we set i = (x+y) - 2.
    */
  };
  static_assert(std::is_pod<Diagonal>::value, "Diagonal is not POD.");
  static_assert(std::is_pod<AntiDiagonal>::value, "AntiDiagonal is not POD.");

  inline constexpr Diagonal diagonal(const Var v, const coord_t N) noexcept {
    assert(v.first >= 1 and v.second >= 1);
    assert(v.first <= N and v.second <= N);
    const scoord_t diff = scoord_t(v.first) - scoord_t(v.second);
    if (diff >= 0) {
      const coord_t cd = diff;
      return {{cd+1,1}, N-cd, (N-1)-cd};
    }
    else {
      const coord_t cd = -diff;
      return {{1,cd+1}, N-cd, (N-1)+cd};
    }
  }
  inline constexpr AntiDiagonal anti_diagonal(const Var v, const coord_t N) noexcept {
    assert(v.first >= 1 and v.second >= 1);
    assert(v.first <= N and v.second <= N);
    const coord_t sum = v.first + v.second;
    if (sum <= N) return {{1,sum-1}, sum-1, sum-2};
    else return {{sum-N,N}, 2*N-(sum-1), sum-2};
  }

  // The number of open, placed and forbidden fields for any line, that is, any
  // row, column, diagonal or antidiagonal:
  struct Rank {
    Var_uint o;
    Var_uint p;
    Var_uint f;
  };
  static_assert(std::is_pod<Rank>::value, "Rank is not POD.");
  inline constexpr bool operator ==(const Rank& r1, const Rank& r2) noexcept {
    return r1.o==r2.o and r1.p==r2.p and r1.f==r2.f;
  }
  inline constexpr bool operator !=(const Rank& r1, const Rank& r2) noexcept {
    return not (r1 == r2);
  }

  // The same numbers as with Rank, but now for the whole board:
  struct TotalRank {
    Var_uint o;
    Var_uint p;
    Var_uint f;
  };
  static_assert(std::is_pod<TotalRank>::value, "TotalRank is not POD.");
  inline constexpr bool operator ==(const TotalRank& r1, const TotalRank& r2) noexcept {
    return r1.o==r2.o and r1.p==r2.p and r1.f==r2.f;
  }
  inline constexpr bool operator !=(const TotalRank& r1, const TotalRank& r2) noexcept {
    return not (r1 == r2);
  }

  enum class State { open=0, placed, forbidden };

  // As in ComputerAlgebra/NumberTheory/Lisp/Numbering.mac, the enumeration of
  // all non-singular variables:
  inline constexpr Var enum_squarenumbering(const Var_uint n) noexcept {
#ifndef NDEBUG
    {const Var_uint two64m1 = std::numeric_limits<Var_uint>::max();
     const Var_uint two32m1 = std::numeric_limits<coord_t>::max();
     assert(n <=  two64m1 - 2*two32m1);}
#endif
    const coord_t r = std::ceil(std::sqrt(n));
    const coord_t d = Var_uint(r) * r - n;
    return (d < r) ? Var{d+1, r} : Var{r, 2*r-d-1};
  }
  typedef std::vector<Var> varvec_t;
  varvec_t enum_square(const coord_t N) {
    varvec_t v;
    const Var_uint NS = Var_uint(N) * N;
    v.reserve(NS);
    for (Var_uint i = 1; i <= NS; ++i) v.push_back(enum_squarenumbering(i));
    return v;
  }

}

#endif
