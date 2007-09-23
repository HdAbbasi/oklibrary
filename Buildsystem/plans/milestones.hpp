// Oliver Kullmann, 4.3.2006 (Swansea)
/* Copyright 2006 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/plans/milestones.hpp
  
  \module_version Buildsystem 0.1.6.7 (23.9.2007)


  \par Version 0.2 : THEME is "AVAILABILITY"

  \par Buildsystem/Html version 0.0.6 : DONE
  (see Buildsystem/Html/plans/milestones.hpp)

  \par Buildsystem/ReleaseProcess 0.0.5 : DONE
  (see Buildsystem/ReleaseProcess/plans/milestones.hpp)
  
  \par Buildsystem/ExternalSources version 0.1.1 : DONE
  (see Buildsystem/ExternalSources/plans/milestones.hpp)

  \par Buildsystem/OKlibBuilding 0.2.1 : DONE
  (see Buildsystem/OKlibBuilding/plans/milestones.hpp)

  \par Buildsystem/SourceControl 0.2.1 : DONE
  (see Buildsystem/SourceControl/plans/milestones.hpp)

  \par Buildsystem/MasterScript version 0.0.4 : DONE
  (see Buildsystem/MasterScript/plans/milestones.hpp)

  \par
   In Buildsystem/plans/general.hpp the following topics are handled:
    - Renaming : DONE
    - system_definitions.mak : DONE (moved to Buildsystem/Configuration/plans/milestones.hpp)


  \par Version 0.2.1 : THEME is "PROTO-RELEASE"

  \par Buildsystem/Configuration version 0.0.6
  (see Buildsystem/Configuration/plans/milestones.hpp)

  \par Buildsystem/ReleaseProcess 0.0.7
  (see Buildsystem/ReleaseProcess/plans/milestones.hpp)

  \par Buildsystem/ExternalSources version 0.1.3
  (see Buildsystem/ExternalSources/plans/milestones.hpp)

  \par Buildsystem/Html version 0.0.7
  (see Buildsystem/Html/plans/milestones.hpp)

  \par Buildsystem/OKlibBuilding 0.2.2
  (see Buildsystem/OKlibBuilding/plans/milestones.hpp)

  \par Buildsystem/SourceControl 0.2.3
  (see Buildsystem/SourceControl/plans/milestones.hpp)

  \par
   In Buildsystem/plans/general.hpp the following topics are handled:
    - Further renamings
    - System documentation

  \par
   In Buildsystem/plans/CheckBuildSystem.hpp the following topics are handled:
    - %Test script

  \par
   Update the following milestones.


  \par Version 0.2.2 : THEME is "A specified and testable build system" and "Build system consolidation"

  \par Buildsystem/OKlibBuilding 0.2.4
  (see Buildsystem/OKlibBuilding/plans/milestones.hpp)
  
  \par Buildsystem/MasterScript version 0.0.5
  (see Buildsystem/MasterScript/plans/milestones.hpp)

  \par
   In Buildsystem/plans/MasterScript.hpp the following topics are handled:
    - Further design

  \par
   In Buildsystem/plans/general.hpp the following topics are handled:
    - Renaming module Buildsystem
    - Documentation (Examples and Concepts)
    - Modes of Usage
    - makefile_recursive
    - Source code directory structure
    - Full test
    - Integration testing

  \par
   In Buildsystem/ExternalSources/plans/general.hpp the following topics are handled:
    - Corrections mhash
    - Problems with building Boost


  \par Version 0.2.3 : THEME is "Build system extensions"

  \par
   In Buildsystem/ExternalSources/plans/general.hpp the following topics are handled:
    - Other sources
    - %Tools
    - PostgreSQL
    - General
    - Gcc

  \par
   In Buildsystem/plans/MasterScript.hpp the following topics are handled:
    -  Further enhancements


  \par Version 0.2.4 :
   In Buildsystem/plans/README.hpp the following topics are handled:
    - Supported versions of gcc
    - Update


  \par Version 0.2.5 :
   In Buildsystem/plans/Makefile.hpp the following topics are handled:
    -  Future of this makefile



  \par Version 0.3 : THEME is "Basic functionality for everybody"

    
  \par Version 0.4 : THEME is "Complexity measurements"


  \par Version 0.5 : THEME is "Rounding up"


  
  \par Version 1.0 :
   


  -------------------------------------------------------------------------------------------------------------------------------------

  \par Version history

   - 0.1   : 4.3.2006; initial version number (the build system is under work for around 2 years).
   - 0.1.1 : 3.11.2006; some smaller corrections and modifications regarding naming issues.
   - 0.1.2 : 9.12.2006; systematic naming, placement and decomposition of makefiles; documentation of generic.mak; documentation-building improved.
   - 0.1.3 : 14.1.2007; further improvements on naming and placement of makefiles, improved building of external libraries, improved html-documentation.
   - 0.1.4 : 8.2.2007; steps towards a specified and testable buildsystem. Further documentation of generic.mak; corrections to makefile plans files suffixes; corrections to system-wide variable definitions.
   - 0.1.5 : 31.3.2007; further steps towards a specified and testable buildsystem; started documenting generic.mak in the doxygen-system. Further improvements in the general structure of the documentation-pages.
   - 0.1.6 : 24.6.2007; transition from CVS to Git and investigations into usage of Git, building and using Boost version 1_34_0, building gcc-4.2.0, building CMake and started planning a transition, investigations into mailing lists and the upcoming proto-release in general, overhaul of Buildsystem/plans, planning on configuration, planning on the web pages, doxygen-usage improvements, improvements of generic.mak, started creating user-documentation for the build-system, improved build of Ubcsat and Mhash, streamlining of building of external sources.

*/

