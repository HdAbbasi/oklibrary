// Oliver Kullmann, 27.6.2007 (Swansea)

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Coq.hpp
  \brief Plans regarding installation of Coq
  
  
  \todo Improve Coq installation
  <ul>
   <li> Download documentation and make it available. </li>
   <li> How to make the man-pages available? </li>
   <li> What about
   <code>LablGtk2 not found: CoqIde will not be available</code>:
   This library comes normally with ocaml ?! </li>
   <li> Tell the Coq-people about the incompatibility with Ocaml 3.10.0
   (that is, the usage of the deprecated "pa_ifdef.cmo", removed in
   Ocaml 3.10.0). </li>
   <li> The manual says
    \verbatim
   If you wish to write tactics (and that really means that you belong
   to advanced users !) you *must* keep the Coq sources, without cleaning
   them.
    \endverbatim
    Now what does it %mean to "keep the sources" --- they recommend
    not to use "make install", but then the manual etc. won't
    be installed? We ignore this first, since writing tactics
    will only come later, and we can reinstall Coq anytime. </li>
  </ul>


  \todo Improve ocaml installation
  <ul>
   <li> Where do we get lablgtk2 (the problems seems to be version 2) ??
   (The Coq installation claims it's not there, but it should
   have been build by the Ocaml installation.) </li>
   <li> Target "make cleanocaml" for removing the build-directory. </li>
   <li> What about (after "configure")
   \verbatim
NDBM not found, the "dbm" library will not be supported.
   \endverbatim
   </li>
  </ul>

*/

