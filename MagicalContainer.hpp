//
// Created by mintsdz on 6/8/23.
//

#ifndef CMAKEITER_MAGICALCONTAINER_HPP
#define CMAKEITER_MAGICALCONTAINER_HPP
#include <vector>
#include <cstddef>
#include <iterator>
#include <algorithm>
#include "MagicalLinkList.hpp"
using namespace std;
namespace ariel {

    class MagicalContainer {
    private:
        MagicalLinkList<int> elements;
        MagicalLinkList<int*> crossElements;
        MagicalLinkList<int*> primeElements;

    public:
        MagicalContainer();
        MagicalContainer(const MagicalContainer&);
        MagicalContainer& operator=(const MagicalContainer&);
        MagicalContainer(MagicalContainer&&) = delete;
        MagicalContainer& operator=(MagicalContainer&&) = delete;
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
            AscendingIterator(AscendingIterator&&) = delete;
            AscendingIterator& operator=(AscendingIterator&&) = delete;
            AscendingIterator(Node<int>*pNode);
            ~AscendingIterator()=default;
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
            Node<int>* pNode;
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
            SideCrossIterator(SideCrossIterator&&) = delete;
            SideCrossIterator& operator=(SideCrossIterator&&) = delete;
            SideCrossIterator(Node<int*>*pNode);
            ~SideCrossIterator()=default;
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
            bool flag;
            MagicalContainer *magicalContainer;
            pointer ptr;
            Node<int*>* pNode;
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
            PrimeIterator(PrimeIterator&&) = delete;
            PrimeIterator& operator=(PrimeIterator&&) = delete;
            PrimeIterator(Node<int*>* pNode);
            ~PrimeIterator()=default;
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
            Node<int*>* pNode;

        };
    };

} // ariel

#endif //MAGICAL_ITERATORS_B_MAGICALCONTAINER_HPP