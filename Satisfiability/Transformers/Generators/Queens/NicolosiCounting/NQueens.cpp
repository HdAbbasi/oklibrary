// Oliver Kullmann 25.5.2018 (Swansea)
/*
  Copyright Alessandro Nicolosi 2016, 2017
  Copyright Oliver Kullmann 2018

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

  Started as copy from
  https://github.com/alenic/nqueens/commits/master
  ID f50264291093fe8529d143995ae9784f097d7ebf.

The basic idea is the same as explained at
  https://helloacm.com/n-queen-problem-in-back-tracing-bit-logics/
and indeed the same as the program from 2002 by Jeff Somers
  http://users.rcn.com/liusomers/nqueen_demo/nqueens.html

Variable numrows there is our size, lsb is next, bitfield is avail, mask
is all_columns. The array aQueenBitCol contains the values of our variable
column, aQueenBitPosDiag of fdiag, aQueenBitNegDiag of fantid.
An array is used there to simulate the recursion.
The additional aQueenBitRes there just represents the solution for printing.

  Version 1.0, 28.5.2018.

  Usage:

> ./qcount N

Output of the solution count and the number of nodes; e.g.

> ./qcount 8
92 615

That is, 92 solutions (nonattacking placements of 8 queens on the 8x8 board),
using 615 nodes in the backtracking tree.

For compilation the Makefile in the same directory as this file can be used.
It produces also the debugging-version "qcount_debug".
To set NMAX (maximal allowed value of N; default 64), use e.g.
> CXXFLAGS="-DNMAX=32" make

For timing-output, the gnu-tool /usr/bin/time is recommended.
For example, output to file Out, first current date and time, then the output
of this program, then the command itself, then the time measurements,
first user-time (most important), then total-time, then system-time,
always appending to Out:
> date >> Out; /usr/bin/time -ao Out -f "%C\n%U %e %S" ./qcount 16 >>Out
> cat Out
Mon May 28 21:07:52 BST 2018
14772512 355451208
./qcount 16
5.41 5.43 0.00

A simple experiment in Bash then, running N=0,...,20, and collecting the data
in file NQ_out:

> OUT="NQ_out"; for ((N=0; N<=20; ++N)); do echo "N=$N" | tee -a $OUT;
   date >> $OUT; /usr/bin/time -ao $OUT -f "%C\n%U %e %S" ./qcount $N >> $OUT;
   done

TODOS:

1. Use signals (like the tawSolver), to show current counts.
2. Use futures for parallelisation.
3. Simulate the recursion by a stack (as done in Jeff Somers's original
   program, whose runtime is very similar to the runtime of this program
   (version 1.0)). OK doesn't expect a speed-up, but one can try.

*/

#include <cstdint>
#include <iostream>
#include <string>
#include <cassert>
#include <limits>

namespace {

typedef std::uint8_t input_t; // type of N
typedef std::uint_fast64_t count_t; // counting solutions

// Definition of queen_t, the bits representing the N columns:
#ifndef NMAX
# define NMAX 64
#endif
constexpr input_t maxN = NMAX;
static_assert(maxN == 32 or maxN == 64, "Max value for N: 32 or 64.");
#if maxN == 32
  typedef std::uint_fast32_t queen_t;
#else
 typedef std::uint_fast64_t queen_t;
#endif
static_assert(std::numeric_limits<queen_t>::digits >= maxN, "Problem with queen_t.");
// For 64 < N <= 128, use queen_t = std::uint_fast128_t (and appropriate count_t).

// Three helper functions for bit-operations:

// N 1's from the right, the rest 0:
constexpr queen_t setrightmostbits(const input_t N) noexcept {
  return (N>=maxN) ? queen_t(-1) : (queen_t(1) << N) - 1;
}
// 1 at position+1 (from right), the rest 0:
constexpr queen_t one(const input_t position) noexcept {
  return queen_t(1) << position;
}
// Set all bits in x to 0 except of rightmost one (if exists):
inline constexpr queen_t keeprightmostbit(const queen_t x) noexcept {
  return -x & x;
}

// The recursive counting-function;
// using bit-positions 0, ..., N-1 for the columns 1, ..., N:

count_t count = 0, nodes = 0;
queen_t all_columns; // the first N bits 1, the rest 0
input_t N;
// Idea: size-many rows (from bottom) have been processed, now consider the
// next row, and try to place the next queen in some column.
inline void backtracking(queen_t avail,
  const queen_t columns, const queen_t fdiag, const queen_t fantid,
  const input_t size) noexcept {
  // avail: columns available (set to 1) for this invocation (only)
  // columns: the current placement of queens
  // fdiag: forbidden columns due to diagonal constraints
  // fantid: forbidden columns due to antidiagonal constraints
  assert(size == 0 or avail == (~(columns|fdiag|fantid) & all_columns));
  //assert(std::bitset<maxN>(columns).count() == size);
  ++nodes;
  assert(avail);
  const queen_t sdiag = fdiag>>1, santid = fantid<<1;
  const queen_t newavail0 = ~(columns | sdiag | santid) & all_columns;
  if (not newavail0) return;
  queen_t next = keeprightmostbit(avail); // could be any bit, but that seems fastest
  const input_t sp1 = size+1; // due to the placement of next
  assert(sp1 < N);
  if (sp1+1 == N) {
    do
      count += bool(newavail0 & ~(next | next>>1 | next<<1));
    while (next = keeprightmostbit(avail^=next));
  }
  else
    do {const queen_t newcolumns = columns|next,
          nextrs = next>>1, nextls = next<<1,
          newdiag = sdiag | nextrs, newantid = santid | nextls,
          newavail = newavail0 & ~(next | nextrs | nextls);
      if (newavail) backtracking(newavail,newcolumns,newdiag,newantid,sp1);
    } while (next = keeprightmostbit(avail^=next));
}
}

int main(const int argc, const char* const argv[]) {
  if (argc != 2) { std::cout << "Usage[qcount]: N\n"; return 0; }
  const unsigned long arg1 = std::stoul(argv[1]);
  if (arg1 <= 1) { std::cout << 1 << " " << nodes << "\n"; return 0; }
  if (arg1 > maxN) { std::cerr << " N <= " << int(maxN) << " required.\n"; return 1; }
  N = arg1;
  all_columns = setrightmostbits(N);
  // Using rotation-symmetry around vertical axis:
  if (N % 2 == 0) {
    backtracking(setrightmostbits(N/2), 0, 0, 0, 0);
    std::cout << 2*count << " " << nodes << "\n";
  } else {
    backtracking(setrightmostbits(N/2), 0, 0, 0, 0);
    const count_t half = count; count = 0;
    backtracking(one(N/2), 0, 0, 0, 0);
    std::cout << 2*half + count << " " << nodes << "\n";
  }
}
