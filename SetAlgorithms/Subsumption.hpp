// Oliver Kullmann, 2.7.2005 (Swansea)

#ifndef SUBSUMPTION_yhgBBv567

#define SUBSUMPTION_yhgBBv567

#include <algorithm>
#include <iterator>
#include <cassert>
#include <set>

#include <boost/utility.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/mpl/if.hpp>

#include "TypeTraitsContainer.hpp"
#include "TaggingPolymorphism.hpp"

namespace OKlib {

  namespace SetAlgorithms {

    namespace SubsumptionsTags {

      struct size_tag : OKlib::MetaProgramming::property_tag {};
      struct use_size_of_hyperedges : size_tag {};
      struct do_not_use_size_of_hyperedges : size_tag {};

      struct uniqueness_tag : OKlib::MetaProgramming::property_tag {};
      struct hyperedges_are_unique : uniqueness_tag {};
      struct hyperedges_may_not_be_unique : uniqueness_tag {};

      struct order_tag : OKlib::MetaProgramming::property_tag {};
      struct hyperedges_sorted_by_size : order_tag {};
      struct hyperedges_may_not_be_sorted_by_size : order_tag {};

    }

    // Helper constructions

    template <typename Iterator>
    struct Get_underlying_iterator {
      typedef Iterator iterator;
      const Iterator& operator() (const Iterator& i) {
        return i;
      }
    };
    template <typename Iterator>
    struct Get_underlying_iterator<boost::reverse_iterator<Iterator> > {
      typedef Iterator iterator;
      typedef boost::reverse_iterator<Iterator> reverse_iterator;
      Iterator operator() (const reverse_iterator& i) const {
        return boost::prior(i.base());
      }
    };
    template <typename Iterator>
    struct Get_underlying_iterator<std::reverse_iterator<Iterator> > {
      typedef Iterator iterator;
      typedef std::reverse_iterator<Iterator> reverse_iterator;
      Iterator operator() (const reverse_iterator& i) const {
        return boost::prior(i.base());
      }
    };

    // ---------------------------


    template <class Container>
    struct Erase {
      typedef typename Container::iterator iterator;
      iterator operator() (Container& C, const iterator& i) const {
        return C.erase(i);
      }
    };
    template <typename T>
    struct Erase<std::set<T> > {
      typedef std::set<T> Container;
      typedef typename Container::iterator iterator;
      iterator operator() (Container& C, const iterator& i) const {
        iterator j(i); ++j;
        C.erase(i);
        return j;
      }
    };
    template <typename T>
    struct Erase<std::multiset<T> > {
      typedef std::multiset<T> Container;
      typedef typename Container::iterator iterator;
      iterator operator() (Container& C, const iterator& i) const {
        iterator j(i); ++j;
        C.erase(i);
        return j;
      }
    };


    // ToDo: These functors should move to the iterator tools ?! (On the other hand they
    // should be adaptable to the *special* situation at hand.)


    // -------------------------------------------------------------------------------------------------------------------
      
    /*!
      \class Subsumption_elimination
      \brief Functor: Eliminates all inclusions from a container.
    */

    /*!
      \class Subsumption_elimination
      \todo ContainerSets is conceptually a hypergraph; if ContainerSets actually is equipped
      with a (the) vertex-hyperedge graph, then for every hyperedge H we can run (efficiently) through
      all hyperedges H' with non-empty intersection with H and compute the size of H - H': if the size
      is 0, then H' <= H, if the size is |H'| - |H|, then H <= H'.
      \todo Create the concept; the requirement must include that ContainerSets supports erase without invalidating iterators.
    */

    template <class ContainerSets,
              class UniquenessTag = SubsumptionsTags::hyperedges_may_not_be_unique,
              class OrderTag = SubsumptionsTags::hyperedges_may_not_be_sorted_by_size,
              class SizeTag = typename boost::mpl::if_<typename OKlib::MetaProgramming::has_size_function<ContainerSets>::type, SubsumptionsTags::use_size_of_hyperedges, SubsumptionsTags::do_not_use_size_of_hyperedges>::type
    >
    struct Subsumption_elimination {

      typedef SizeTag size_tag;
      typedef UniquenessTag uniqueness_tag;
      typedef OrderTag order_tag;

      template <typename Iterator>
      void upward(ContainerSets& C, Iterator begin, const Iterator end) const {
        upward(C, begin, end, size_tag());
      }

      template <typename Iterator>
      void upward(ContainerSets& C, Iterator begin, const Iterator end, SubsumptionsTags::do_not_use_size_of_hyperedges) const {
        for (; begin != end; ++begin)
          for (Iterator j(boost::next(begin)); j != end;)
            if (std::includes(j -> begin(), j -> end(), begin -> begin(), begin -> end()))
              j = Iterator(Erase<ContainerSets>()(C, Get_underlying_iterator<Iterator>()(j)));
            else
              ++j;
      }
      template <typename Iterator>
      void upward(ContainerSets& C, Iterator begin, const Iterator end, SubsumptionsTags::use_size_of_hyperedges) const {
        for (; begin != end; ++begin) {
          typedef typename std::iterator_traits<Iterator>::value_type::size_type size_type;
          const size_type& size(begin -> size());
          for (Iterator j(boost::next(begin)); j != end;)
            if (cheque_unnecessary(j, size, order_tag(), uniqueness_tag()))
              ++j;
            else if (std::includes(j -> begin(), j -> end(), begin -> begin(), begin -> end()))
              j = Iterator(Erase<ContainerSets>()(C, Get_underlying_iterator<Iterator>()(j)));
            else
              ++j;
        }
      }

      template <typename Iterator, typename Size>
      bool cheque_unnecessary(const Iterator j, const Size size, SubsumptionsTags::hyperedges_sorted_by_size, SubsumptionsTags::hyperedges_are_unique) const {
        assert(size <= j -> size());
        return size == j -> size();
      }
      template <typename Iterator, typename Size>
      bool cheque_unnecessary(const Iterator j, const Size size, SubsumptionsTags::hyperedges_sorted_by_size, SubsumptionsTags::hyperedges_may_not_be_unique) const {
        assert(size <= j -> size());
        return false;
      }
      template <typename Iterator, typename Size>
      bool cheque_unnecessary(const Iterator j, const Size size, SubsumptionsTags::hyperedges_may_not_be_sorted_by_size, SubsumptionsTags::hyperedges_are_unique) const {
        return size >= j -> size();
      }
      template <typename Iterator, typename Size>
      bool cheque_unnecessary(const Iterator j, const Size size, SubsumptionsTags::hyperedges_may_not_be_sorted_by_size, SubsumptionsTags::hyperedges_may_not_be_unique) const {
        return size > j -> size();
      }

      void operator() (ContainerSets& C) const {
        eliminate(C, order_tag());
      }

      void eliminate(ContainerSets& C, SubsumptionsTags::hyperedges_sorted_by_size) const {
        upward(C, C.begin(), C.end());
      }
      void eliminate(ContainerSets& C, SubsumptionsTags::hyperedges_may_not_be_sorted_by_size) const {
        typedef typename ContainerSets::iterator iterator;
        const iterator& end(C.end());
        upward(C, C.begin(), end);
        upward(C, boost::make_reverse_iterator(end), boost::make_reverse_iterator(C.begin()));
      }

    };
    
    template <class ContainerSets>
    inline void subsumption_elimination_upward(ContainerSets& C) {
      Subsumption_elimination<ContainerSets>().upward(C, C.begin(), C.end());
    }

    template <class ContainerSets>
    inline void subsumption_elimination(ContainerSets& C) {
      Subsumption_elimination<ContainerSets>()(C);
    }

  }

}

#endif
