// Oliver Kullmann, 18.8.2007 (Swansea)
/* Copyright 2007, 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Gmp.hpp
  \brief Plans regarding installation of gmp


  \todo Application RankPrimes is slower with version 4.3.0/4.3.1
  <ul>
   <li> The Gmp webpage says that mpz_nextprime is now "much faster". </li>
   <li> However, running RankPrimes-O3-DNDEBUG with parameter "unrank"
   and with input 999999, version 4.2.4 needs stably ~25 seconds (on
   csltok), while it needs ~37 seconds with 4.3.0. </li>
   <li> Notify the Gmp mailing list! </li>
   <li> At this occassion one could also ask that they provide
   functions for ranking and unranking (applying sieves for larger
   intervals seems to be much faster than running it again and
   again). </li>
   <li> On csltok (32-bit), first with current Gmp-default (4.3.1):
   \verbatim
kullmann-0:PrimeNumbers> oklib cleanall 
kullmann-0:PrimeNumbers> all
kullmann-0:PrimeNumbers> time RankPrimes-O3-DNDEBUG data/PrimeRanks.txt rank
10000000
664580
user    0m26.539s
kullmann-0:PrimeNumbers> time RankPrimes-O3-DNDEBUG data/PrimeRanks.txt rank
10000000
664580
user    0m26.615s
kullmann-0:PrimeNumbers> oklib cleanall 
kullmann-0:PrimeNumbers> oklib all gmp_recommended_version_number_okl=4.2.4
kullmann-0:PrimeNumbers> time RankPrimes-O3-DNDEBUG data/PrimeRanks.txt rank
10000000
664580
user    0m17.143s
kullmann-0:PrimeNumbers> time RankPrimes-O3-DNDEBUG data/PrimeRanks.txt rank
10000000
664580
user    0m17.071s
kullmann-0:PrimeNumbers> oklib cleanall 
kullmann-0:PrimeNumbers> oklib all gmp_recommended_version_number_okl=4.3.0
kullmann-0:PrimeNumbers> time RankPrimes-O3-DNDEBUG data/PrimeRanks.txt rank
10000000
664580
user    0m26.592s
kullmann-0:PrimeNumbers> time RankPrimes-O3-DNDEBUG data/PrimeRanks.txt rank
10000000
664580
user    0m26.546s
   \endverbatim
   So 4.2.4 needs only about %65 of the time needed by 4.3.0 or 4.3.1. </li>
  </ul>


  \todo Installation of Mpfr
  <ul>
   <li> Since apparently mpfr belongs to gmp, could it be automatically
   installed with gmp? </li>
   <li> Update mpfr-version. </li>
   <li> Update the mpfr-installation to the new standard. </li>
   <li> We should now by default provide local installation:
    <ol>
     <li> First we need to find out who needs mpfr. </li>
     <li> R needs it (see "Prerequisites" in
     Buildsystem/ExternalSources/SpecialBuilds/plans/R.hpp). </li>
     <li> Also the gcc Fortran compiler need it (see "Installation in general"
     in Buildsystem/ExternalSources/SpecialBuilds/plans/Gcc.hpp). </li>
    </ol>
   </li>
  </ul>


*/

