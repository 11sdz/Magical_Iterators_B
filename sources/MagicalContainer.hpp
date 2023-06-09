//
// Created by mintsdz on 6/8/23.
//

#ifndef MAGICAL_ITERATORS_B_MAGICALCONTAINER_HPP
#define MAGICAL_ITERATORS_B_MAGICALCONTAINER_HPP
#include <vector>
#include <cstddef>
#include <iterator>
#include <cmath>
#include <algorithm>
using namespace std;
namespace ariel {

    class MagicalContainer {
    private:
        vector<int> elements;
        vector<int*> crossElements;
        vector<int*> primeElements;

    public:
        MagicalContainer();
        void addElement(int ele);
        void removeElement(int ele);
        size_t size();

        virtual ~MagicalContainer();

        struct AscendingIterator{
        public:
            using valueType=int;
            using pointer = valueType*;
            using reference = valueType&;

            AscendingIterator();
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(const AscendingIterator& ascendingIterator);
            AscendingIterator& operator=(const AscendingIterator& ascendingIterator);
            AscendingIterator begin();
            AscendingIterator end();

            reference operator*() const;
            pointer operator->();
            AscendingIterator& operator++();

            bool operator<(AscendingIterator other);
            bool operator>(AscendingIterator other);
            bool operator==(AscendingIterator other);
            bool operator!=(AscendingIterator other);

        private:
            AscendingIterator(size_t idx,MagicalContainer &container);
            MagicalContainer *magicalContainer;
            pointer ptr;
            size_t idx;
        };
        struct SideCrossIterator{
        public:
            using valueType=int;
            using pointer = valueType*;
            using reference = valueType&;

            SideCrossIterator();
            SideCrossIterator(MagicalContainer& container);
            SideCrossIterator(const SideCrossIterator& crossIterator);
            SideCrossIterator& operator=(const SideCrossIterator& crossIterator);
            SideCrossIterator begin();
            SideCrossIterator end();

            reference operator*() const;
            pointer operator->();
            SideCrossIterator& operator++();

            bool operator<(SideCrossIterator other);
            bool operator>(SideCrossIterator other);
            bool operator==(SideCrossIterator other);
            bool operator!=(SideCrossIterator other);

        private:
            SideCrossIterator(size_t idx,MagicalContainer &container);
            MagicalContainer *magicalContainer;
            pointer ptr;
            size_t idx;
        };
        struct PrimeIterator{
        public:
            using valueType=int;
            using pointer = valueType*;
            using reference = valueType&;

            PrimeIterator();
            PrimeIterator(MagicalContainer& container);
            PrimeIterator(const PrimeIterator& primeIterator);
            PrimeIterator& operator=(const PrimeIterator& primeIterator);
            PrimeIterator begin();
            PrimeIterator end();

            reference operator*() const;
            pointer operator->();
            PrimeIterator& operator++();

            bool operator<(PrimeIterator other);
            bool operator>(PrimeIterator other);
            bool operator==(PrimeIterator other);
            bool operator!=(PrimeIterator other);

        private:
            PrimeIterator(size_t idx,MagicalContainer &container);
            MagicalContainer *magicalContainer;
            pointer ptr;
            size_t idx;
        };
        bool isPrime(int number);
    };

} // ariel

#endif //MAGICAL_ITERATORS_B_MAGICALCONTAINER_HPP
