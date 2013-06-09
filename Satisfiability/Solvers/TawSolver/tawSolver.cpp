/**************************************************************************************************
tawSolver -- Copyright (c) 2007-2013, Tanbir Ahmed
http://users.encs.concordia.ca/~ta_ahmed/

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/

// Compile with
// g++ -Wall -Ofast tawSolver.cpp -o tawSolver

#include <limits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <sys/time.h>
#include <sys/resource.h>


constexpr int POS = 1;
constexpr int NEG = 0;
constexpr int MAX_CLAUSES = 300000;
constexpr int MAX_VARS = 4096;

enum Error_codes {
  missing_file_error=1, file_reading_error=2, clause_length_error=3 };

typedef unsigned int Clause_content;
constexpr int MAX_CLAUSE_LENGTH {std::numeric_limits<Clause_content>::digits};
// If longer clauses are needed, replace Clause_content with bigger uint type.

struct clause_info {
  int* literals;
  Clause_content value;
  int number;
  int length;
  int c_ucl;
  bool status;
};

clause_info* clauses;

// Defining "special logarithm" log2s(v)=k, where v=2^k, k natural number:
constexpr Clause_content pow2(const unsigned e) {return (e==0)?1:2*pow2(e-1);}
constexpr Clause_content pow22(const unsigned e) {return pow2(pow2(e));}
constexpr int log2(const Clause_content n) {return (n <= 1)?0:1+log2(n/2);}
inline constexpr Clause_content bp(const unsigned N, const unsigned i) {
  return (i < N-1) ? bp(N-1,i) * (1 + pow22(N-1)) : pow22(N) - pow22(N-1);
}
constexpr int N = log2(MAX_CLAUSE_LENGTH);
static_assert(pow2(N) == (unsigned) MAX_CLAUSE_LENGTH, "Number of bits in \"Clause_content\" not a power of 2.");
static_assert(N==5 or N==6, "Unexpected size of type \"Clause_content\".");
const Clause_content b[6] {bp(N,0),bp(N,1),bp(N,2),bp(N,3),bp(N,4), (N==6)?bp(N,5):0}; // Unfortunately there is no reasonable way in C++ to just define b[N].
inline int log2s(const Clause_content v) {
  assert(exp2(log2(v)) == v);
  Clause_content r = (v & b[0]) != 0;
  for (int i = 1; i < N; ++i) r |= ((v & b[i]) != 0) << i;
  return r;
}

struct var_info {
  int* var_in_clauses;
  int* var_in_clause_locs;
  unsigned int n_occur;
  int is_ucl;
  bool status;
};


struct change_info {
  int clause_number;
  int literal_index;
};

change_info changes[MAX_CLAUSES];
int n_changes[MAX_VARS][2], changes_index = 0;

var_info vars[MAX_VARS][2];

unsigned int n_clauses, r_clauses, n_init_clauses, n_vars, depth = 0;
int current_working_clause[MAX_CLAUSE_LENGTH], cwc_length;
int gucl_stack[MAX_VARS], n_gucl = 0;

int contradictory_unit_clauses = false;
unsigned long long int n_branches = 0, n_units = 0;
unsigned int max_clause_len = 0;
unsigned long long int n_backtracks = 0;

FILE* open_formula_file(const char* const file_name) {
  FILE* const f = fopen(file_name, "r");
  if(!f) {
    printf("Invalid file name.\n");
    exit(file_reading_error);
  }
  else return f;
}

void read_formula_header(FILE* const f) {
  char str[256], p[2], cnf[4];
  while(1) {
    fgets(str, 256, f);
    if(str[0] == 'p') break;
  }
  sscanf(str, "%s %s %u %u", p, cnf, &n_vars, &n_clauses);
  clauses = (clause_info*) realloc(clauses, (n_clauses+1)*sizeof(clause_info));
  n_clauses = r_clauses = 0;
}

void close_formula_file(FILE* const f) { if (f) fclose(f); }

bool read_a_clause_from_file(FILE* const f) {
  bool trivial_clause = false;
  cwc_length = 0;
  int* const checker = (int*) calloc((n_vars+1), sizeof(int));
  while (true) {
    int x;
    if (fscanf(f, "%d", &x) == EOF) return false;
    if (x == 0) break;
    if (checker[abs(x)]==0) {
      if (cwc_length >= MAX_CLAUSE_LENGTH) {
        printf("Clauses can have at most %u elements.\n", MAX_CLAUSE_LENGTH);
        exit(clause_length_error);
      }
      current_working_clause[cwc_length++] = x;
      checker[abs(x)] = x;
    }
    else if (checker[abs(x)] + x == 0) trivial_clause = true;
  }
  if (trivial_clause) {
    cwc_length = 0;
    return true;
  }
  free(checker);
  if(cwc_length == 0) return false;
  return true;
}

void add_a_clause_to_formula(const int A[], const unsigned int n) {
  if (n == 0) return;
  clauses[n_clauses].number = n_clauses;
  clauses[n_clauses].status = true;
  clauses[n_clauses].length = n;
  clauses[n_clauses].value = ((1<<n)-1);
  clauses[n_clauses].c_ucl = 0;
  clauses[n_clauses].literals = (int *) malloc((n + 1) * sizeof(int));

  if (n>max_clause_len) max_clause_len = n;

  for (unsigned int i=0; i<n; ++i) {
    int p = abs(A[i]), q = A[i]>0 ? POS : NEG;
    vars[p][q].var_in_clauses = (int*) realloc(vars[p][q].var_in_clauses,
                                (vars[p][q].n_occur+1) * sizeof(int));
    vars[p][q].var_in_clause_locs = (int*) realloc(vars[p][q].var_in_clause_locs,
                                (vars[p][q].n_occur+1) * sizeof(int));
    vars[p][q].var_in_clauses[vars[p][q].n_occur] = n_clauses;
    vars[p][q].var_in_clause_locs[vars[p][q].n_occur] = i;
    ++vars[p][q].n_occur;
    vars[p][q].status = true;
    vars[p][q].is_ucl = false;
    clauses[n_clauses].literals[i] = A[i];
  }
  ++n_clauses;
  ++r_clauses;
}

void read_formula(const char* const filename) {
  FILE* const f = open_formula_file(filename);
  read_formula_header(f);
  n_init_clauses = 0;
  while(read_a_clause_from_file(f)) {
    add_a_clause_to_formula(current_working_clause, cwc_length);
    ++n_init_clauses;
  }
  close_formula_file(f);
}

int checker[MAX_VARS];

void reduce(const int v) {
  const int p = abs(v);
  const int q = (v>0) ? POS : NEG;
  for (unsigned int i=0; i<vars[p][q].n_occur; ++i) {
    const int m = vars[p][q].var_in_clauses[i];
    if(!clauses[m].status) continue;
    clauses[m].status = false;
    --r_clauses;
    changes[changes_index++].clause_number = m;
    ++n_changes[depth][POS];
  }
  const int nq = !q;
  for (unsigned int i=0; i<vars[p][nq].n_occur; ++i) {
    const int m = vars[p][nq].var_in_clauses[i];
    if (!clauses[m].status) continue;
    const int n = vars[p][nq].var_in_clause_locs[i];
    --clauses[m].length;
    clauses[m].value -= ((1 << n));

    changes[changes_index].clause_number = m;
    changes[changes_index++].literal_index = n;
    ++n_changes[depth][NEG];

    if (clauses[m].length == 1) {
      const int ucl = clauses[m].literals[int(log2s(clauses[m].value))];
      const int aucl = abs(ucl);
      if (checker[aucl] == 0) {
        gucl_stack[n_gucl++] = ucl;
        checker[aucl] = ucl;
        clauses[m].c_ucl = ucl;
      }
      if (checker[aucl]+ucl == 0) {
        contradictory_unit_clauses = true;
        checker[aucl] = 0;
      }
    }
  }
  ++depth;
  vars[p][POS].status = false;
  vars[p][NEG].status = false;
}

void reverse(const int v) {
  const int p = abs(v);
  --depth;
  while (n_changes[depth][NEG]) {
    --n_changes[depth][NEG];
    const int m = changes[--changes_index].clause_number;
    const int n = changes[changes_index].literal_index;
    ++clauses[m].length;
    if(clauses[m].length == 2) {
      checker[abs(clauses[m].c_ucl)] = 0;
      clauses[m].c_ucl = 0;
    }
    clauses[m].value += ((1 << n));
  }

  while (n_changes[depth][POS]) {
    --n_changes[depth][POS];
    const int m = changes[--changes_index].clause_number;
    clauses[m].status = true;
    ++r_clauses;
  }
  vars[p][POS].status = true;
  vars[p][NEG].status = true;
}

inline int get_variable_2sjw() {
  const unsigned int mlen = max_clause_len;
  unsigned int max = 0;
  int v = 0;

  for (unsigned int i=1; i<=n_vars; ++i) {
    if (vars[i][POS].status or vars[i][NEG].status) {
      unsigned int pz = 0, nz = 0;
      for(unsigned int k=0; k<vars[i][POS].n_occur; ++k) {
        const unsigned int ell = vars[i][POS].var_in_clauses[k];
        pz += clauses[ell].status << (mlen - clauses[ell].length);
      }
      for (unsigned int k=0; k<vars[i][NEG].n_occur; ++k) {
        const unsigned int ell = vars[i][NEG].var_in_clauses[k];
        nz += clauses[ell].status << (mlen - clauses[ell].length);
      }
      const unsigned int s = pz + nz;
      if (s > max) {
        max = s;
        if (pz >= nz) v = i; else v = -i;
      }
    }
  }
  return v;
}

int out[MAX_VARS];

bool dpll() {
  ++n_branches;
  unsigned int n_lucl = 0;
  int* lucl_stack = nullptr;
  while (true) {
    if (contradictory_unit_clauses) {
      while(n_lucl) {
        reverse(lucl_stack[--n_lucl]);
        out[depth] = 0;
      }
      contradictory_unit_clauses = false;
      free(lucl_stack);
      n_gucl = 0;
      return false;
    }
    else if (n_gucl) {
      lucl_stack = (int*) realloc(lucl_stack, (n_lucl + 1) * sizeof(int));
      const int implied_literal = gucl_stack[--n_gucl];
      out[depth] = lucl_stack[n_lucl++] = implied_literal;
      reduce(implied_literal);
      ++n_units;
    }
    else break;
  }
  if (!r_clauses) return true;
  const int v = get_variable_2sjw();
  out[depth] = v;
  reduce(v);
  if (dpll()) return true;
  reverse(v);
  ++n_backtracks;

  const int nv = -v;
  out[depth] = nv;
  reduce(nv);
  if (dpll()) return true;
  reverse(nv);
  out[depth] = 0;

  while (n_lucl) {
    reverse(lucl_stack[--n_lucl]);
    out[depth] = 0;
  }
  free(lucl_stack);
  contradictory_unit_clauses = false;
  return false;
}

void output(const char* const file, const bool result, const long int timediff) {
  printf("s ");
  if (result) printf("SATISFIABLE\n"); else printf("UNSATISFIABLE\n");
  printf("c number_of_variables                   %u\n"
         "c number_of_clauses                     %u\n"
         "c running_time(sec)                     %1.2f\n"
         "c number_of_nodes                       %llu\n"
         "c number_of_binary_nodes                %llu\n"
         "c number_of_1-reductions                %llu\n"
         "c file_name                             %s\n",
       n_vars, n_init_clauses, double(timediff)/100, n_branches, n_backtracks, n_units, file);
  if (result) {
    int order[MAX_VARS];
    for (unsigned int i=0; i<n_vars; i++) {
      const auto val = out[i];
      const auto index = std::abs(val)-1;
      if (val > 0) order[index] = 1;
      else if (val < 0) order[index] = -1;
      else order[index] = 0;
    }
    printf("v ");
    for (unsigned int i=0; i<n_vars; ++i)
     if (order[i]) printf("%d ", order[i]*(i+1));
    printf("0\n");
  }
}


int main(const int argc, const char* const argv[]) {
  if (argc < 2) {
    printf("Missing file name.\n");
    return missing_file_error;
  }
  read_formula(argv[1]);
  struct rusage runtime;
  getrusage(RUSAGE_SELF, &runtime);
  const long int t1 = (100*runtime.ru_utime.tv_sec)+(runtime.ru_utime.tv_usec/10000);
  const bool result = dpll();
  getrusage(RUSAGE_SELF, &runtime);
  const long int t2 = (100*runtime.ru_utime.tv_sec)+(runtime.ru_utime.tv_usec/10000);
  output(argv[1], result, t2-t1);
  return (result) ? 10 : 20;
}
