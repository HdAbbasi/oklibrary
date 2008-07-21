// Oliver Kullmann, 20.7.2008 (Swansea)
/* Copyright 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Cryptology/Lisp/CryptoSystems/Rijndael/plans/AdvancedEncryptionStandard.hpp
  \brief Plans on the AES implementation


  \todo Auxiliary functions
  <ul>
   <li> See TermSystems/Lisp/Conversions.mac. </li>
   <li> What is the meaning of
   \verbatim
load("functs")$ Bug Here atm  For logxor
   \endverbatim
   If there is a Maxima bug, then it needs to submitted to Maxima,
   and we provide a correction. </li>
   <li> What about the section "Helper Functions" ?
    <ol>
     <li>  We shouldn't have a section with "useless stuff":
     Auxiliary functions either directly accompany their main user, or are
     not just "helper functions". </li>
     <li> intToPoly and polyToInt should (besides the bad naming (see below))
     be replaced by the gf-functions poly2num and num2poly. </li>
    </ol>
   </li>


  \todo Naming Conventions
  <ul>
   <li> We don't use "camels", so names like GF2t8PolyToInt needs to be
   replaced. </li>
   <li> To avoid clashes with other modules and to make clear which functions
   are specific to AES and which aren't, functions in this module should 
   perhaps have the prefix "aes_". </li>
   <li> Should this perhaps instead be "rijndael_" or "rijn_" or similar? </li>
  </ul>

*/

