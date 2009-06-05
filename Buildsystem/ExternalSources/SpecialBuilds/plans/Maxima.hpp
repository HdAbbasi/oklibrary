// Oliver Kullmann, 7.10.2007 (Swansea)
/* Copyright 2007, 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Maxima.hpp
  \brief Plans regarding installation of Maxima


  \bug Inappropriate command-extension on certain machines
  <ul>
   <li> Using the tab-key on csltok (32-bit, Suse 9.2), command-line extension
   happens using the existing Maxima- symbols. </li>
   <li> But including our own symbols does not happen after they have been
   included, but oklib_load_all(). </li>
   <li> On the other hand, once we used oklib_batch with a testobjects-file,
   then the included symbols are used! </li>
   <li> Is this related to "load" versus "batch"?
    <ol>
     <li> Considering for example "ohg". The extension "ohg_p" should be found.
     </li>
     <li> After oklib_load_all() this is not the case. </li>
     <li> Neither after
     oklib_load("OKlib/ComputerAlgebra/Hypergraphs/Lisp/Basics.mac"). </li>
     <li> But after
     oklib_batch("OKlib/ComputerAlgebra/Hypergraphs/Lisp/testobjects/Basics.mac")
     it works! </li>
     <li> And considering "sgn" ("sgnv2c" and "sgnvs2cs" should be found),
     still after
     oklib_load("OKlib/ComputerAlgebra/Matroids/Lisp/OrientedMatroids/SignVectors.mac")
     it is not available, though when using oklib_batch instead of oklib_load
     it works! </li>
     <li> So there appears to be something works when using the Maxima
     function "batch", but not with "load". </li>
    </ol>
   </li>
   <li> The above is with Ecl. With CLisp we get the behaviour, that only
   Lisp-symbols are considered, no Maxima-symbols, and no user-defined
   ones. So here something more fundamental seems to go wrong. </li>
  </ul>


  \bug DONE
  Gnuplot not working anymore
  <ul>
   <li>
   \verbatim
(%i1) plot2d(sin(x),[x,-5,5])$
Xlib: connection to ":0.0" refused by server
Xlib: No protocol specified
gnuplot: unable to open display ':0.0'
gnuplot: X11 aborted.
   \endverbatim
   </li>
   <li> If the (currently introduced) redefinition of HOME (when calling
   Maxima) to the Maxima-installation-directory is removed, then it works
   again. </li>
   <li> Those two files apparently establishing that "gnuplot-pipe" are
   stored in the installation directory --- perhaps gnuplot can't find
   them? </li>
   <li> Setting plot_format to "gnuplot" (not "gnuplot_pipes", as it is
   the default) doesn't help (apparently with that no files are used?). </li>
   <li> And also "openmath" doesn't work anymore. </li>
   <li> Without HOME-resetting both alternative formats work (though with
   gnuplot the window doesn't stay open, but this seems to be "normal"). </li>
  </ul>


  \todo Install xgettext
  <ul>
   <li> To create new Maxima packages, xgettext, available at
   http://www.gnu.org/software/gettext/ , is needed </li>
  </ul>

  
  \todo Communicate with Maxima/Ecl to fix load behaviour with symlinks on path
  <ul>
   <li> The issue is that load-command fails (%e.g., "load(descriptive)").
   </li>
   <li> The problem occurs if one has a symbolic link on the path during the
   building of maxima and ecl. </li>
   <li> MG is communicating with the Maxima mailing list on the issue and
   hopefully this will be resolved in the next Maxima. </li>
   <li> For now, the symlink to OKplatform can simply be removed, as it is
   only a convenience. </li>
   <li> Additionally, if one wishes to use a symlink on the build path,
   the "file_search_maxima" variable may be "fixed" at runtime by using an
   old "hard-coded" version of a particular lisp function for listing the
   directories (Thanks to Robert Dodier):
   \verbatim
:lisp (setf (symbol-function 'share-subdirs-list) (symbol-function 'default-share-subdirs-list))
:lisp (set-pathnames)
   \endverbatim
   and then load functionality works fine. </li>
  </ul>


  \todo Database of integer sequences
  <ul>
   <li> We have to see whether the sequences are becoming (publically)
   available. </li>
   <li> If this is not the case, then likely we shouldn't contribute to
   that database. </li>
  </ul>


  \todo Additional packages
  <ul>
   <li> Real algebraic geometry
    <ol>
     <li> The book [Algorithms in Real Algebraic Geometry; Basu, Pollack, Roy]
     is available at http://www.math.gatech.edu/~saugata/bpr-posted1.html.
     </li>
     <li> Also maxima-code for various chapters is available. </li>
    </ol>
   </li>
  </ul>


  \todo System-wide installation
  <ul>
   <li> The build-system should be extended, taking for example the
   Gmp-installation as an example, so that we can also produce/use in the
   standard way system-wide installations of Libsigsegv, CLisp and Maxima.
   </li>
  </ul>


  \todo Handling of redefined load-function
  <ul>
   <li> See "How to eliminate the annotation of lists" in
   ComputerAlgebra/plans/Maxima.hpp. </li>
   <li> And see the e-mail thread (May 2008)
   "how to stop the annotation of lists by filenames?" on the Maxima
   mailing list. </li>
   <li> We need documentation on this regarding the build-system:
    <ol>
     <li> We need to watch the Maxima distribution, whether the
     two functions involved, "load" and "add-lineinfo", ever are
     changed, and then we need to incorporate these changes. </li>
     <li> Hopefully, this is not a big thing, since these functions
     are rather small. </li>
     <li> The good point about this solution is its non-intrusiveness:
     The Maxima system doesn't know about these changes. </li>
    </ol>
   </li>
  </ul>

*/
