// Oliver Kullmann, 6.6.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Interfaces/InputOutput/plans/ClauseSetAdaptors.hpp
  \brief Plans for adaptors (transferring clause-sets in streams to data structures)


  \todo Document the basic concept CLSAdaptor
  <ul>
   <li> See Interfaces/InputOutput/ClauseSetAdaptors.hpp. </li>
  </ul>


  \todo Discussing the basic concept CLSAdaptor
  <ul>
   <li> Perhaps the adaptor should perform cleaning-up the input (regarding
   tautological clauses and multiple literal occurrences) ? </li>
   <li> But perhaps this is better done by some other component, while the
   adaptor is only responsible for the data transfer. </li>
  </ul>


  \todo Write concept for Statistics class
  <ul>
   <li> See Interfaces/InputOutput/ClauseSetAdaptors.hpp. </li>
  </ul>


  \todo Write tests!


  \todo RawDimacsCLSAdaptor
  <ul>
   <li> What are the precise assumptions on template parameter Lit? </li>
   <li> Handling of the additional information: Perhaps we have
   (optionally?) an embedded object of type CLSAdaptorStatistics ?! </li>
   <li> Should there be policies for checking n and c (or should this
   go into a more complex adaptor?)? </li>
  </ul>


  \todo Create "base class" for "raw adaptors"
  <ul>
   <li> Yet we have InputOutput::RawDimacsCLSAdaptor and
   InputOutput::RawDimacsCLSAdaptorSets, which are very similar. </li>
   <li> Creating std::vector<std::vector<int>> or std::set<std::set<int>>
   only differs in the one line where a clause is transferred ("insert"
   instead of "push_back"). </li>
  </ul>

*/

