// Oliver Kullmann, 27.6.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Gcc.hpp
  \brief Plans regarding installation of gcc


  \todo Update our gcc-installation-system to the new standard
  <ul>
   <li> OK: was this done? has this to do with "stubs-32.h not found"?
   As only extension, we install the patch for 4.1.2 as provided
   by MG. </li>
   <li> Regarding this "stubs-32.h"-nonsense (the internet is full
   of noise regarding that, but nobody has a clue): perhaps glibc
   has to be installed (the development library) --- more precisely,
   for a 64-bit machine also the glibc-32-bit version! </li>
   <li> DONE
   Likely it's best for now only to support local installation. </li>
   <li> DONE
   As it is standard now, existing documentation is always overwritten.
   </li>
   <li> DONE
   A problem is how to handle these two lists for the two installation
   modes.
    <ol>
     <li> We need to extend the usual "iseq"-macro. </li>
     <li> Use
     \verbatim
ifneq ($(findstring $(gcc_recommended_version_number_okl), $(gcc_old_installation_okl)),)
     \endverbatim
     to test whether the version to be installed is an old installation. </li>
    </ol>
   </li>
   <li> DONE
   Another problem is the target "gcc_all":
    <ol>
     <li> In this way all support versions of gcc are installed. </li>
     <li> In the new model, where always (only) the "recommended version" is
     installed, this needs several calls of make (from oklib). </li>
     <li> So well, seems alright to me. </li>
    </ol>
   </li>
   <li> DONE
   The current installation creates timestamps: Shall we take over
   this, or shall we first drop it?
    <ol>
     <li> Doesn't seem to be a big problem to keep it. </li>
     <li> On the other hand, is it really useful? </li>
     <li> It might create trouble, and for all recent installations
     it was not done (forgotten; but likely also not needed?). </li>
     <li> So we drop it (at least for now). </li>
    </ol>
   </li>
   <li> DONE
   We should introduce make-variables for the configuration options. </li>
  </ul>


  \todo Providing gcc 4.1.2
  <ul>
   <li> Motivated by "GRASP cannot be compiled with gcc version 4.3" (see
   Buildsystem/ExternalSources/SpecialBuilds/plans/SAT.hpp), we should provide
   a permanent installation of version 4.1.2. </li>
   <li> Perhaps we should provide in general build-variables supporting
   usage of gcc (i.e., calling the compiler, and providing the instructions
   for fixing the shared libraries in the binaries. </li>
  </ul>


  \todo Install GCC 4.2.4
  <ul>
   <li> First only as an alternative (since yet code doesn't compile with
   versions 4.2 or later). </li>
   <li> It seems best to proceed in stages, first installing the latest
   4.2.x and updating our code, and then installing the latest 4.3.x. </li>
  </ul>
  

  \todo Installation in general
  <ul>
   <li> Documentation:
    <ol>
     <li> Linking to the gcc-documentation (main info-page) should be checked
     for completeness. </li>
     <li> We could offer also to show the man-page (just open it into a
     browser); however then it should be said that likely the html-documentation
     is more complete. </li>
     <li> We should also move the info-pages to the doc-directory. How to view
     them? The least is just to open them into a browser. </li>
    </ol>
   </li>
   <li> If variable "gcc_version_okl" is set, then it should have one of the
   allowed values (while otherwise we get an error). </li>
   <li> We must understand, how gcc interacts with 32- and 64-bit
   environments, and how to take control of this. </li>
   <li> There should be make-variables, which allow control over
   some settings for the build of gcc. </li>
   <li> texti2pdf is a script, which can be put into ~/bin for example,
   and is needed for building the gcc-documentation --- how to provide it?
   Such small utilities could be put under version control (OKlibrary) ? </li>
   <li> Installation of R requires a Fortran compiler. Therefore the 
    system-installation of Gcc should allow for enabling of Fortran
    language support. </li>
   <li> Enabling Fortran language support in Gcc requires that the MPFR
    and GMP libraries are installed. Should we install these also locally?
    <ol>
     <li> GMP is also of interest to us regarding big-number-types, so we need
     full control about it, and perhaps a local installation is warranted
     (ignoring the system installation). UPDATE NEEDED </li>
    </ol>
   </li>
   <li> Shouldn't file external_sources_versions.mak be placed in
   subdirectory Buildsystem/ExternalSources ? DONE (placed in
   Buildsystem/Configuration) </li>
   <li> If the filestamp does already exist, then we want nothing to happen ---
   however yet the build-directory will be rebuilt if not existent, since
   it is a prerequisite of the rule for the "tag-paths". So it seems
   necessary to remove the build-directory from the prerequisite-list,
   however then it seems impossible to create the build-directory, if actually
   gcc *is* to be build, via the target-mechanism. DONE (it seems reasonable
   to remove the build-directory from the prerequisite-list and to build it
   "manually") </li>
   <li> DONE (now just "oklib gcc", and potentially setting 
  gcc_recommended_version_number_okl)
   Instead of, %e.g., "make gcc-4.1.2", wouldn't it be more consistent with
   building Boost to also have "make gcc gcc-version=4.1.2" ? </li>
  </ul>

*/
