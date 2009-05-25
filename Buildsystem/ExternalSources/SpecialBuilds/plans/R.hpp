// Oliver Kullmann, 27.6.2007 (Swansea)
/* Copyright 2007, 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/R.hpp
  \brief Plans regarding installation of R


  \todo DONE (problem solved by redefining HOME)
  Installing 2.9.0
  <ul>
   <li> We get the error
   \verbatim
begin installing recommended package VR
Error in library(pspline) : there is no package called 'pspline'
Execution halted
   \endverbatim
   </li>
   <li> Apparently the problem was caused by old settings in HOME/.RProfil.
    <ol>
     <li> We need to install R in such a way that it does not interact at all
     with any user configuration files. </li>
     <li> Is "rhome" the appropriate variable here? Unclear what "home" means
     here; it seems not to refer to the users home, and thus perhaps it is
     not appropriate here. </li>
    </ol>
   </li>
   <li> 
  </ul>


  \todo Local installation of gfortran
  <ul>
   <li> Often gfortran is not installed. </li>
   <li> While it shouldn't be a problem to install gfortran locally.
    <ol>
     <li> Just add "fortran" to gcc_enable_languages_okl. </li>
    </ol>
   </li>
   <li> And also employing it for building R shouldn't be a problem. </li>
  </ul>


  \bug Can't output graphics
  <ul>
   <li> For example
   \verbatim
> hist(c(1,2,3,2,1))
Fehler in title(main = main, sub = sub, xlab = xlab, ylab = ylab, ...) :
  X11 Schrift -adobe-helvetica-%s-%s-*-*-%d-*-*-*-*-*-*-*, Typ 2 in Größe 14 konnte nicht geladen werden
   \endverbatim
   on csltok. </li>
   <li> Perhaps this is language-related, or related to the rather old version
   (9.2) of Suse-Linux running on csltok (it works on cs-wsok). </li>
  </ul>


  \todo Packages
  <ul>
   <li> We should supply additional packages. </li>
   <li> DONE (target R_packages)
   And also install them automatically (with documentation). </li>
   <li> Apparently with "library(Rcmdr)" we can open a (useful) graphical user
   interface, and apparently for this package "Rcmdr" is needed.
    <ol>
     <li> On cs-wsok we get the error
     \verbatim
> library(Rcmdr)
Loading required package: tcltk
Error in firstlib(which.lib.loc, package) :
  Tcl/Tk support is not available on this system
Error: package 'tcltk' could not be loaded
     \endverbatim
     though apparently everything is installed? </li>
    </ol>
   </li>
   <li> Of potential interest:
    <ol>
     <li> "SparseM" </li>
     <li> DONE "QCA" (Quine-McCluskey;
     http://cran.r-project.org/src/contrib/Descriptions/QCA.html) </li>
     <li> "boolean" </li>
     <li> "combinat" </li>
     <li> "dyn" </li>
     <li> "gafit" </li>
     <li> "glpk" </li>
     <li> "linprog" </li>
     <li> "pspline" </li>
     <li> "quadprog" </li>
     <li> "randaes" </li>
     <li> "sudoku" </li>
    </ol>
   </li>
  </ul>


  \todo Improving the docus-page
  <ul>
   <li> Prerequisites:
    <ol>
     <li> What precisely is needed from the gcc-suite? </li>
     <li> What is mpfr? We should also add installation-help
     (there is already some installation-make-code). </li>
    </ol>
   </li>
  </ul>


  \todo Building dvi,pdf,info-documentation
  <ul>
   <li> On csltok "make dvi" fails --- is this due to old
   tex-tools? </li>
   <li> Likely "make pdf" sits on top of dvi. </li>
   <li> What can we do with the info-documentation? </li>
   <li> How do we get documentation on the packages? </li>
  </ul>

*/

