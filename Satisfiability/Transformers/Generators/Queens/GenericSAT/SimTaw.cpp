// Oliver Kullmann, 23.7.2018 (Swansea)
/* Copyright 2018 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

#include <iostream>
#include <string>

#include "ChessBoard.hpp"
#include "Backtracking.hpp"
#include "NQueens.hpp"
#include "InOut.hpp"

namespace {

const std::string version = "0.4.2";
const std::string date = "1.9.2018";
const std::string program = "SimTaw"
#ifndef NDEBUG
  "_debug"
#endif
;
const std::string error = "ERROR[" + program + "]: ";

}

int main(const int argc, const char* const argv[]) {

  using namespace ChessBoard;
  using namespace NQueens;

  const coord_t N = InOut::interprete(argc, argv, error);
  if (argc == 2) {
    typedef AmoAlo_board AmoAlo;
    AmoAlo Fq(N);
    Backtracking::CountSat<AmoAlo, TawHeuristics<AmoAlo>> B;
    const auto rFq = B(Fq);
    std::cout << rFq.solutions << " " << rFq.nodes << "\n";
    return 0;
  } else {
    typedef PhasedAmoAlo_board AmoAlo;
    AmoAlo Fq(N);
    Backtracking::CountSat<AmoAlo, TawHeuristics<AmoAlo>> B;
    const auto rFq = B(Fq);
    std::cout << rFq.solutions << " " << rFq.nodes << "\n";
    return 0;
  }
}
