// Oliver Kullmann, 8.7.2007 (Swansea)
/* Copyright 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ReleaseProcess/plans/general.hpp
  \brief Plans regarding the release process in general

  The different aspects of the release process (including the "continuous
  releases" via source-control access) are considered in:
  <ul>
   <li> Buildsystem/ReleaseProcess/plans/Release.hpp looks at the overall
   process for preparing a (special) release. </li>
   <li> Buildsystem/ReleaseProcess/plans/MailingLists.hpp treats all different
   aspects regarding e-mail communication. </li>
   <li> Buildsystem/ReleaseProcess/plans/PackageBuilding.hpp considers building
   the packages for the releases. </li>
   <li> Buildsystem/ReleaseProcess/plans/README.hpp looks at the README-file
   in the package. </li>
  </ul>


  \todo DONE (there is only a permanent release process via packages
  created every few days or so; to the outside
  world it matters which functionality is provided, which is regulated
  by the milestones, however this does not affect the release processj
  yet no experience with access to git-repositories by users)
  Plans-structure review:
  The plans-structure in Buildsystem/ReleaseProcess/plans/ needs review.
  <ul>
   <li> Should we make a distinction between "special releases" and
   "continuous releases" ? </li>
  </ul>


  \todo Packages history
  <ul>
   <li> A policy is needed which packages to be kept. </li>
   <li> Somewhere there should be already some discussion on
   that? </li>
   <li> In any case only the minimal packages are kept. </li>
   <li> Perhaps the packages created with every advance in the
   version number (disregarding the fourth digit). </li>
   <li> There could be months between advances in the version number,
   but otherwise we have too much to store, and there should be enough
   clones floating around in case of a dispute regarding the recent
   history would show up (which seems unlikely). </li>
   <li> However the policy about archiving packages should ask for
   additional archiving of packages in case for a long time no advance
   happened while there is activity (this should be prevented by
   reasonable milestones). </li>
   <li> Compare "Backups and archives" in Transitional/plans/general.hpp
   for the "official history". </li>
   <li> DONE (the "official history" is handled by "Backups and archives"
   in Transitional/plans/general.hpp)
   Can we make the OKlibrary "officially" available? Or "more
   official"?? Perhaps we need a Sourceforge-account??? The Git-history should
   be well-secured. </li>
  </ul>

*/

