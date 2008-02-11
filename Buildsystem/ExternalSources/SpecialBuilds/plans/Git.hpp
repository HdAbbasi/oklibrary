// Oliver Kullmann, 9.7.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Git.hpp
  \brief Plans regarding installation of Git


  \todo Update the installation process : DONE
  <ul>
   <li> Use new naming-conventions. </li>
   <li> Use only target "git". </li>
   <li> Support also local installation. </li>
  </ul>


  \todo Prerequisites
  <ul>
   <li> The build system can install asciidoc if needed; put it into
   the documentation. (Is it available in recent distributions?) </li>
   <li> What to do about xmlto --- is this available in recent
   distributions, so that we don't need to provide an installation
   ourselves (only documentation)?
    <ol>
     <li> Suse 10.0 has it. </li>
    </ol>
   </li>
   <li> What about
   \verbatim
/bin/sh: curl-config: command not found
   \endverbatim
   ??? Is this another missing prerequisite? </li>
  </ul>


  \todo Info- and man-pages
  <ul>
   <li> Using system-wide installation, are man-pages provided by our
   installation? </li>
   <li> And how to use these pages with a local installation? </li>
  </ul>


  \todo Installation process
  <ul>
   <li> There are several build-possibilities (listed in the INSTALL-file
   of the git-package); the one we used was the only one working: Is this
   still true? What are the reasons? </li>
  </ul>


*/

