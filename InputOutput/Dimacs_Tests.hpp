// Oliver Kullmann, 24.7.2005 (Swansea)

/*!
  \file InputOutput/Dimacs_Tests.hpp
  \brief Tests for tools concerning DIMACS input and output
  \deprecated Move to the new test system.
*/

#ifndef DIMACSTESTS_0jbmnr
#define DIMACSTESTS_0jbmnr

#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <limits>
#include <cassert>

#include <boost/assign/std/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

#include <Transitional/TestSystem/TestBaseClass.hpp>
#include <Transitional/TestSystem/TestExceptions.hpp>

#include <Transitional/InputOutput/Exceptions.hpp>
#include <Transitional/InputOutput/ClauseSetAdaptors.hpp>

namespace OKlib {
  namespace InputOutput {

    /*!
      \class Test_StandardDIMACSInput
      \brief Test the standard DIMACS cnf reader.

      \todo Extending the tests (not just checking whether the statistics are right).
      \todo Test with the archetype of a CLSAdaptor.
      \todo For the negative tests:
       - catch all exceptions thrown
       - test the specific exceptions thrown.
      \todo For the positive tests:
        - catch all exceptions thrown.
      \todo Test for errors where the numbers read-in are too large to be represented.
    */

    template <template <class CLSAdaptor> class StandardDIMACSInput>
    class Test_StandardDIMACSInput : public ::OKlib::TestSystem::TestBase {
    public :
      typedef Test_StandardDIMACSInput test_type;
      Test_StandardDIMACSInput() {
        insert(this);
      }
    private :
      void perform_test_trivial() {
        {
          typedef CLSAdaptorStatistics<> cls_adaptor_type_stat;
          typedef StandardDIMACSInput<cls_adaptor_type_stat> dimacs_input_type_stat;

          typedef CLSAdaptorDIMACSOutput<> cls_adaptor_type_copy;
          typedef StandardDIMACSInput<cls_adaptor_type_copy> dimacs_input_type_copy;

          { // error tests
            typedef std::vector<std::string> test_error_vector_type;
            typedef test_error_vector_type::const_iterator iterator;
            {
              test_error_vector_type comment_errors;
              using namespace boost::assign;
              comment_errors +=
                "",
                "c ",
                "c p",
                "c \nc",
                "c\nc\ncp";
              const iterator& end = comment_errors.end();
              for (iterator i = comment_errors.begin(); i != end; ++i) {
                bool thrown = false;
                std::istringstream in(*i);
                cls_adaptor_type_stat cls_adaptor;
                try {
                  dimacs_input_type_stat dimacs_input(in, cls_adaptor);
                }
                catch (const CommentInputError&) { thrown = true; }
                if (not thrown)
                  OKLIB_THROW("CommentError not thrown for input\n" + *i);
              }
            }
            {
              test_error_vector_type parameter_errors;
              using namespace boost::assign;
              parameter_errors +=
                "x",
                "c \np",
                "p",
                "c \nc\npcnf",
                "c\nc\np cnf",
                "p cnf 3",
                "p cnf -4 8\n",
                "p cnf 4 -8\n",
                "p cnf 6 77 xx";
              const iterator& end = parameter_errors.end();
              for (iterator i = parameter_errors.begin(); i != end; ++i) {
                bool thrown = false;
                std::istringstream in(*i);
                cls_adaptor_type_stat cls_adaptor;
                try {
                  dimacs_input_type_stat dimacs_input(in, cls_adaptor);
                }
                catch (const ParameterInputError&) { thrown = true; }
                if (not thrown)
                  OKLIB_THROW("ParameterError not thrown for input\n" + *i);
              }
            }
            {
              test_error_vector_type clause_errors;
              using namespace boost::assign;
              clause_errors +=
                "p cnf 1 2\n 1",
                "c gg\np cnf 88 77 \n 1",
                "p cnf 0 0\n u",
                "p cnf 8 7\n 8 - 9 0 8",
                "p cnf 7 8\n 0 0 0 -8",
                "p cnf 1 1\n 2 0",
                "p cnf 4 1\n 2 -3 0 1 2 0",
                "p cnf 1 2\n+1 1 0 -1 -1 -1 0\n -1 +1 -1 +1 0",
                "p cnf 1 1\n - 1 0";
              const iterator& end = clause_errors.end();
              for (iterator i = clause_errors.begin(); i != end; ++i) {
                bool thrown = false;
                std::istringstream in(*i);
                cls_adaptor_type_stat cls_adaptor;
                try {
                  dimacs_input_type_stat dimacs_input(in, cls_adaptor);
                }
                catch (const ClauseInputError&) { thrown = true; }
                if (not thrown)
                  OKLIB_THROW("ClauseError not thrown for input\n" + *i);
              }
            }
          }

          { // tests for correct input
            typedef cls_adaptor_type_stat::statistics_type st_t;
            typedef boost::tuple<std::string, st_t, std::string> el_t;
            typedef std::vector<el_t> test_vector_type;
            typedef test_vector_type::const_iterator iterator;

            test_vector_type test_vector;
            using namespace boost::assign;
            test_vector +=
              el_t("p cnf 0 0\n", st_t(0,0,0,0,0,0,0), "p cnf 0 0\n"),
              el_t("p cnf 0 0\n\n\n", st_t(0,0,0,0,0,0,0), "p cnf 0 0\n"),
              el_t("p cnf 0 2\n\n\n0 0", st_t(0,0,2,0,2,0,0), "p cnf 0 2\n0\n0\n"),
              el_t("p cnf 3 4\n", st_t(0,3,4,0,0,0,0), "p cnf 3 4\n"),
              el_t("c\nc\np cnf 3 4\n", st_t(2,3,4,0,0,0,0), "c\nc\np cnf 3 4\n"),
              el_t("p cnf 4 5\n 1 -2 0 -3 -4 0", st_t(0,4,5,0,2,4,4), "p cnf 4 5\n-2 1 0\n-4 -3 0\n"),
              el_t("cx\nc y\np cnf 11 +6\n -1 1 -2 0 -3 -4 -4 0 7 -8 -9 3 4 3 0", st_t(2,11,6,1,2,12,7), "c x\nc y\np cnf 11 6\n-4 -3 0\n-9 -8 3 4 7 0\n"),
              el_t("p cnf 1 3\n+1 1 0 -1 -1 -1 0\n -1 +1 -1 +1 0", st_t(0,1,3,1,2,9,2), "p cnf 1 3\n1 0\n-1 0\n");
            const iterator& end(test_vector.end());
            for (iterator i = test_vector.begin(); i != end; ++i) {
              {
                std::istringstream in(i -> get<0>());
                cls_adaptor_type_stat cls_adaptor_stat;
                dimacs_input_type_stat dimacs_input(in, cls_adaptor_stat);
                OKLIB_TEST_EQUAL(cls_adaptor_stat.stat, i -> get<1>());
              }
              {
                std::istringstream in(i -> get<0>());
                std::ostringstream out;
                cls_adaptor_type_copy cls_adaptor_copy(out);
                dimacs_input_type_copy dimacs_input(in, cls_adaptor_copy);
                std::string out_copy(out.str());
                OKLIB_TEST_EQUAL(out_copy, i -> get<2>());
              }
            }
          }
        }
        {
          typedef signed char small_int_type;
          typedef CLSAdaptorStatistics<small_int_type> cls_adaptor_type_stat;
          typedef StandardDIMACSInput<cls_adaptor_type_stat> dimacs_input_type_stat;

          { // error tests regarding conversions
            typedef std::vector<std::string> test_error_vector_type;
            typedef test_error_vector_type::const_iterator iterator;
            {
              test_error_vector_type conversion_errors;
              const int too_large(std::numeric_limits<small_int_type>::max()+1);
              assert(too_large > std::numeric_limits<small_int_type>::max());
              const std::string too_large_str(boost::lexical_cast<std::string>(too_large));
              using namespace boost::assign;
              conversion_errors +=
                "p cnf " + too_large_str + " 0\n",
                "p cnf 0 " + too_large_str + "\n";
              const iterator& end = conversion_errors.end();
              for (iterator i = conversion_errors.begin(); i != end; ++i) {
                bool thrown = false;
                std::istringstream in(*i);
                cls_adaptor_type_stat cls_adaptor;
                try {
                  dimacs_input_type_stat dimacs_input(in, cls_adaptor);
                }
                catch (const ParameterInputError&) { thrown = true; }
                if (not thrown)
                  OKLIB_THROW("ParameterError not thrown for input\n" + *i);
              }
            }
          }
        }
      }
    };


  }

}

#endif
