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

        struct AscendingIterator{
        public:
            using valueType=int;
            using pointer = valueType*;
            using reference = valueType&;

            AscendingIterator();
            AscendingIterator(MagicalContainer& container);
            AscendingIterator(size_t idx,MagicalContainer &container);
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
            SideCrossIterator(size_t idx,MagicalContainer &container);
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
            PrimeIterator(size_t idx,MagicalContainer &container);
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
            MagicalContainer *magicalContainer;
            pointer ptr;
            size_t idx;
        };
        bool isPrime(int number);
    };

} // ariel

#endif //MAGICAL_ITERATORS_B_MAGICALCONTAINER_HPP
