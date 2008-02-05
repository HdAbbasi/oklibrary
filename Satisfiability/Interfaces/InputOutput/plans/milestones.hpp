// Oliver Kullmann, 10.9.2006 (Swansea)
/* Copyright 2006 - 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Interfaces/InputOutput/plans/milestones.hpp

  \module_version Interfaces/InputOutput 0.0.9 (5.2.2008)


  \par Version 0.0.10 :

  \par
   In Interfaces/InputOutput/plans/general.hpp the following topics are handled:
    - Rewrite code for the new namespaces.
    - Update
    - See Transitional/Satisfiability/ProofSystems/DPv/Input_output.hpp

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Complete the doxygen-documentation.


  \par Version 0.0.11 :

  \par
   In InputOutput/plans/general.hpp the following topics are handled:
    - Write docus.

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Write docus


  \par Version 0.0.12 :

  \par
   In Interfaces/InputOutput/plans/general.hpp the following topics are handled:
    - Move to the new test system
    - Write demos

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Write demos


  \par Version 0.0.13:

  \par
   In Interfaces/InputOutput/plans/general.hpp the following topics are handled:
    - Complete the tests

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - What happens if the integers from the file are too big?
    - It must also be tested, whether the integers can be safely negated
    - Consider the code-comments regarding checking


  \par Version 0.1 :

  \par
   In Interfaces/InputOutput/plans/general.hpp the following topics are handled:
    - Improve application InputOutput/ExtendedToStrictDimacs.cpp
    - Complete the functionality


  \par Version 0.1.1 :

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Improve class InputOutput::StandardDIMACSInput
    - Use Messages for messages.
    

  \par Version 0.1.2 :

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Exceptions


  \par Version 0.1.3 :

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Improving class InputOutput::LiteralReadingExtended
    - Error handling


  \par Version 0.2 :

  \par
   In Interfaces/InputOutput/plans/general.hpp the following topics are handled:
    - Move InputOutput/ExtendedToStrictDimacs.cpp
    - Input and output of partial assignments


  \par Version 0.3 :

  \par
   In Interfaces/InputOutput/plans/Dimacs.hpp the following topics are handled:
    - Write extended Dimacs-parser for clause-sets with non-boolean variables


  \par Version 0.4 :

  \par
   In Interfaces/InputOutput/plans/general.hpp the following topics are handled:
    - General propositional formulas and circuits



  -------------------------------------------------------------------------------------------------------------------------------------

  \par Version history

   - 0.0.7 : 7.11.2006; initial version number (several implementations).
   - 0.0.8 : 26.9.2007; moved to new place in part Satisfiability, and related updates.
   - 0.0.9 : 5.2.2008; created facilities to read extended Dimacs, and to translate it to standard Dimacs, and extensions and updates of plans.

*/

