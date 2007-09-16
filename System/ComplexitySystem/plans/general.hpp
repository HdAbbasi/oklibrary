// Oliver Kullmann, 3.12.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComplexitySystem/plans/general.hpp
  \brief Plans for the complexity system


  \todo Update namespaces.


  \todo Designing the file structure
  <ul>
   <li> In principle similar to the (new) test system. </li>
   <li> For every Module as we have now sub-directories
   "tests" and "testobjects", we get sub-directories
   "measurements" and "measurementobjects", and for
   every Submodule we get measurements/Submodule.hpp
   and measurementobjects/Submodule.hpp. </li>
   <li> In measurements/Submodule.hpp for every class X
   as we have now the class template tests::X we get
   the class template measurements::X. </li>
   <li> There is a measure function in measurements::X which returns
   an event description and the time measured (time in seconds). </li>
   <li> What is measured is actually a simple test (so that something
   is computed, and the action to be timed is not optimised away;
   repetitions of the same computations should be avoided). </li>
  </ul>


  \todo Designing the level system

  Also the (new) level system is the same as for
  the test system.


  \todo Designing the makefile

  There is a timestamp-file "measurement" for each
  of the three levels.
 

  \todo Designing measurement classes
  <ul>
   <li> Measurements are instances of a wrapper class
   around boost::timer objects but with extra data members for
    <ol>
     <li> compiler version, </li>
     <li> %boost version, </li>
     <li> time and date. </li>
    </ol>
   OK: I think that this information should be global (for the
   whole container of measurement objects), not just for
   one measurement.
   </li>
   <li> To test a function f in SubmoduleClass of Submodule,
   create a class, derived from ComplexityBaseClass, with a private
   member function take_measurements. (Also with public measure_type
   and constructor providing self insertion.)
   OK: self insertion has been replaced for the test system (or will be),
   and perhaps also here we should not mix the functionalities of measuring
   and storing the measure objects. So look at the new test system for the role model.
   </li>
   <li> Measurement classes have an end() public member function
   which gets the elapsed time from the boost::timer and passes
   this to the measurement handling policy.
   OK: Don't call it "end()" (because of "begin() + end()").
   And actually we might not need such a function, or?
   </li>
   <li> For example, to test f in SubmoduleClass of Submodule
   do something like the following:
   \code
class Measure_SubmoduleClass : public ::OKlib::ComplexitySystem::ComplexityBase {
  public :
    typedef Measure_SubmoduleClass measure_type;
    Measure_SubmoduleClass() {
      insert(this); // OK: obsolete
    }
  private :
    void take_measurements() {
      measurement<SaveToFile> timer; // OK: see below (we should do it globally)
      for (int i=0; i<100; ++i) { // OK: such repetitions are dangerous (optimised away)
        f();  // Function to be measured
      }
      measurement.end(); // Measurement finished. Handling of
                         // measurement by policy begun. // OK: not needed (return value)
    }
   };
   \endcode
   OK: As said above, we should avoid calling a function repeatedly without
   doing something. And it seems reasonable to me that take_measurements
   returns the results. </li>
   <li> It seems that the idea of MH is, that every measurement object can place
   its results where it wants to, while I think that a simpler design is
   enough, where we have a container of measurement objects, the measurement
   objects deliver their individual results, and then a container with all
   results and all additional information is dumped to a file. (Like with the
   test system, but this time we need to store it.) </li>
  </ul>


  \todo Designing measurement accumulation
  <ul>
   <li> Here the results of measurements are accumulated, and output
   (to a file, and/or other streams). </li>
   <li> How do we specify a filename for the measurements to be saved to?
   OK: All this kind of information should be input to the measurement
   *program* and stored in the measurement *container* (which is serialised
   to a file). It's like the (new) test system: We have the information at the
   makefile-level, then at the measurement-program-level, then at the level
   of the files in directories measurements and measurementsobjects, then
   at the level of the single measurement classes, and finally at the level of
   the single measurement objects. </li>
  </ul>

*/

/*!
  \namespace OKlib::ComplexitySystem
  \brief Module for (persistent) complexity measurements
*/

namespace OKlib {
  namespace ComplexitySystem {
  }
}

