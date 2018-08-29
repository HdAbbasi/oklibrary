// Oliver Kullmann, 23.7.2018 (Swansea)
/* Copyright 2018 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

#include <iostream>
#include <string>
#include <stdexcept>

#include <cstdlib>

#include "ChessBoard.hpp"

namespace InOut {

  enum class Error {
    missing_argument=1,
    conversion=2,
    too_big=3,
    too_small=4,
    uninterpreted_argument=5
  };
  /* Extracting the underlying code of enum-classes (scoped enums) */
  template <typename EC>
  inline constexpr int code(const EC e) noexcept {return static_cast<int>(e);}

  ChessBoard::coord_t interprete(const int argc, const char* const argv[], const std::string& error) noexcept {
    if (argc == 1) {
      std::cerr << error << "The argument N is needed.\n";
      std::exit(code(Error::missing_argument));
    }
    const std::string arg1 = argv[1];
    unsigned long N;
    try { N = std::stoul(arg1); }
    catch (const std::invalid_argument& e) {
      std::cerr << error << "The argument \"" << arg1 << "\" is not a valid integer.\n";
      std::exit(code(Error::conversion));
    }
    catch (const std::out_of_range& e) {
      std::cerr << error << "The argument \"" << arg1 << "\" is too big for unsigned long.\n";
      std::exit(code(Error::too_big));
    }
    if (N > ChessBoard::max_coord) {
      std::cerr << error << "The argument can be at most " << ChessBoard::max_coord << ", but is " << arg1 << ".\n";
      std::exit(code(Error::too_big));
    }
    if (N == 0) {
      std::cerr << error << "The argument is 0.\n";
      std::exit(code(Error::too_small));
    }
    return N;
  }

}
