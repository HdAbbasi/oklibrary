// Oliver Kullmann, 13.9.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/RandomGenerator/plans/general.hpp
  \brief Plans regarding the random generation of problem instances


  \todo Update namespaces.


  \todo Basic revision:
  The first thing is to make the OKgenerator and accompanying tools
  compiling and running correctly again. This should proceed in the
  following stages:
  <ol>
   <li> Creating the basic concept for BigIntegers
   (see BigIntegers/concepts/plans/general.hpp), together with the wrapper for GMP
   (see BigIntegers/plans/GMPWrapper.hpp). </li>
   <li> Replacing the current big-integer implementation in OKgenerator
   (files flint*; they are sub-standard, introducing macros like "isxdigit",
   many(!) others written with small letter and additional "_I", and even
   "ggT", "xggT", "kgV", "chinrest" and "zweianteil"; perhaps one could have
   a look, whether there is a web page of Michael Welschenbach with improved code). </li>
   <li> Creating the concept for AES in the module Cryptology (see
   Cryptology/plans/general.hpp). </li>
   <li> Replacing the current AES implementation (Cryptology/aes*)
   by Cryptology/rijndael*). </li>
   <li> Correct General/Kommandozeile.hpp (there are input-errors,
   likely undefined behaviour). </li>
  </ol>
  Regarding testing we should link to the computer-algebra implementation of
  the generator (see "Random generator" in
  ComputerAlgebra/Satisfiability/Lisp/ClauseSets/plans/general.hpp). </li>


  \todo Improvements
  <ul>
   <li> Replacing General/Kommandozeile (see General/Kommandozeile.hpp)
   by module Transitional/ProgramOptions. </li>
  </ul>


  \todo Other tools
  <ul>
   <li> All other tools for experiment creation, processing and transfer shall
   move to Experimentation/ExperimentSystem. </li>
  </ul>

*/

/*!
  \namespace OKlib::RandomGenerator
  \brief Components for the generation of random problems
*/

namespace OKlib {
  namespace RandomGenerator {
  }
}

