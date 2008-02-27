// Oliver Kullmann, 23.9.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Satisfiability/Algorithms/Autarkies/plans/general.hpp
  \brief General plans on autarkies.


  \todo Update namespaces : DONE


  \todo Move Transitional/AutarkySearch here. DONE


  \todo Lean kernel
  <ul>
   <li> Create module with algorithms performing iterated SAT-search with
   variable-cross-out (see [Kullmann, Lynce, Marques-Silva 2006]). </li>
   <li> Should this module also contain other methods for computing the
   (full) lean kernel ? Looks reasonable. </li>
   <li> Also generic methods for computing lean kernels for arbitrary autarky
   systems should be included. </li>>
  </ul>

*/

/*!
  \namespace OKlib::Satisfiability::Algorithms::Autarkies
  \brief Components for autarky handling

  Alias "Aut".
*/

namespace OKlib {
  namespace Satisfiability {
    namespace Algorithms {
      namespace Autarkies {
      }
      namespace Aut = Autarkies;
    }
  }
}

