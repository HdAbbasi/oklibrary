// Oliver Kullmann, 25.12.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

// rename to TestTestExecutionTools.cpp

#include <iostream>

#include <Transitional/TestSystem/TestBaseClass.hpp>

#include <Transitional/TestExecutionTools/TestAlgorithms_Testobjects.hpp>
#include <Transitional/TestExecutionTools/SecondOrderTestTools_Testobjects.hpp>
#include <Transitional/TestExecutionTools/RelationTests_Testobjects.hpp>
#include <Transitional/TestExecutionTools/ExampleRelations_Testobjects.hpp>

int main() {
  return OKlib::TestSystem::TestBase::run_tests_default(std::cerr);
} 
