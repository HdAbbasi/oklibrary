// Oliver Kullmann, 9.4.2007 (Swansea)
/* Copyright 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/docus/general.hpp
  \brief General documentation for the makefile "Buildsystem/ExternalSources/Makefile", responsible for external builds
  
  <h1> General overview </h1>


  <h2> Basic ideas </h2>

  <ul>
   <li> The <strong>recommended version</strong> is the version installed by default;
   using other versions might or might not work. </li>
   <li> Two basic types of installations:
    <ol>
     <li> <strong>System-wide installation</strong>: installation in directories like
     <code>/usr/local</code> (depending on the package's own build system); requires
     at the end of the installation to enter the appropriate super-user password
     (if this was missed, then just re-run the build, which should quickly arrive
     at the entry-point again). </li>
     <li> <strong>Local installation</strong>: installation to directory
     <code>$(ExternalSources_installations)</code>. </li>
    </ol>
    In both case, if possible, we will extract documentation to the local documentation
     directory <code>$(ExternalSources_doc)</code>.
   </li>
   <li> The build system provides access to the results of the builds:
    <ol>
     <li> executable programs </li>
     <li> source-code libraries </li>
     <li> link-libraries </li>
     <li> documentation </li>
     <li> other resources. </li>
    </ol>
   </li>
   <li> As part of a "holistic" or "active" library, the part of the build system
   responsible for building external sources is highly configurable and extensible;
   details are explained in Buildsystem/ExternalSources/docus/Internals.hpp. </li>
   <li> The OKlibrary (and its support "staff") can offer only very restricted
   installation support (especially for general-purpose tools like web servers).
   For more information on the internal build process see
   Buildsystem/ExternalSources/docus/Internals.hpp. </li>
  </ul>


  <h2> Configuration </h2>

  Enter into <code>$(OKoverrideconfig)</code> the overriding definitions, for example
  \code
ocaml_bin_dir := /usr/local/bin
  \endcode
  to use the system-wide ocaml-installation instead of the local installation.
  (These definitions prevent the involved variables from being (re-)defined by the configuration system.)

  
  <h2> Installations </h2>

  User documentation on how to install supported software and basic usage
  (sorted alphabetically):

  <ol>
   <li> Boost (Buildsystem/ExternalSources/SpecialBuilds/docus/Boost.hpp) </li>
   <li> CLisp (Buildsystem/ExternalSources/SpecialBuilds/docus/CLisp.hpp) </li>
   <li> Coq (Buildsystem/ExternalSources/SpecialBuilds/docus/Coq.hpp) </li>
   <li> Doxygen (Buildsystem/ExternalSources/SpecialBuilds/docus/Doxygen.hpp) </li>
   <li> Gcc (Buildsystem/ExternalSources/SpecialBuilds/docus/Gcc.hpp) </li>
   <li> Git (Buildsystem/ExternalSources/SpecialBuilds/docus/Git.hpp) </li>
   <li> Gmp (Buildsystem/ExternalSources/SpecialBuilds/docus/Gmp.hpp) </li>
   <li> Maxima (Buildsystem/ExternalSources/SpecialBuilds/docus/Maxima.hpp) </li>
   <li> Mhash (Buildsystem/ExternalSources/SpecialBuilds/docus/Mhash.hpp) </li>
   <li> Ocaml (Buildsystem/ExternalSources/SpecialBuilds/docus/Ocaml.hpp) </li>
   <li> Postgresql (Buildsystem/ExternalSources/SpecialBuilds/docus/Postgresql.hpp) </li>
   <li> R (Buildsystem/ExternalSources/SpecialBuilds/docus/R.hpp) </li>
   <li> Sage (Buildsystem/ExternalSources/SpecialBuilds/docus/Sage.hpp) </li>
   <li> Ubcsat (Buildsystem/ExternalSources/SpecialBuilds/docus/Ubcsat.hpp) </li>
   <li> Valgrind (Buildsystem/ExternalSources/SpecialBuilds/docus/Valgrind.hpp) </li>
  </ol>
  
*/

