//
// Created by mintsdz on 6/8/23.
//

#include "MagicalContainer.hpp"

namespace ariel {
    MagicalContainer::MagicalContainer(){

    }

    void MagicalContainer::addElement(int ele) {
        if (std::count(elements.begin(), elements.end(), ele) > 0) {
            return;
        }
        if (this->elements.capacity() == (elements.size())) {
            this->elements.reserve(this->elements.capacity() * 2);
            this->crossElements.reserve(this->crossElements.capacity() * 2);
        }
        int *num = new int(ele);
        this->elements.push_back(*num);
        std::sort(this->elements.begin(), this->elements.end());
        if (isPrime(ele)) {
            primeElements.clear();
            for (size_t i = 0; i < elements.size(); ++i) {
                if (isPrime(elements[i])) {
                    primeElements.push_back(&elements[i]);
                }
            }
        }
        crossElements.push_back(nullptr); //filler
        size_t high = elements.size() - 1, low = 0;
        size_t idx = 0;
        bool flag= true;
        while (low <= high && idx<size()) {
            if(flag) {
                crossElements[idx] = &elements[low];
                low++;
                flag= false;
            }else {
                crossElements[idx] = &elements[high];
                high--;
                flag= true;
            }
            idx++;
        }
    }

    void MagicalContainer::removeElement(int ele) {
        if(std::count(elements.begin(), elements.end(),ele)==0){
            throw runtime_error("no such element");
            return;
        }
        size_t idx=0;
        auto it= elements.begin();
        while(*it!=ele){
            it++;
        }
        int *num=it.operator->();
        elements.erase(it);
        std::remove(primeElements.begin(), primeElements.end(),num);
        std::remove(crossElements.begin(), crossElements.end(),num);
    }

    size_t MagicalContainer::size() {
        return elements.size();
    }

    /*
     * Iterators
     */
    MagicalContainer::AscendingIterator::AscendingIterator() {
        this->magicalContainer=NULL;
        this->ptr= nullptr;
        this->idx=0;
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) {
        this->magicalContainer=&container;
        this->ptr=&container.elements[0];
        this->idx=0;
    }
    MagicalContainer::AscendingIterator::AscendingIterator(size_t idx,MagicalContainer& container) {
        this->magicalContainer=&container;
        this->ptr=&magicalContainer->elements[idx];
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return MagicalContainer::AscendingIterator(0,*this->magicalContainer);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return MagicalContainer::AscendingIterator(this->magicalContainer->size(),*this->magicalContainer);
    }

    int &MagicalContainer::AscendingIterator::operator*() const {
        return *this->ptr;
    }

    MagicalContainer::AscendingIterator::pointer MagicalContainer::AscendingIterator::operator->() {
        return ptr;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        this->idx++;
        this->ptr=&(this->magicalContainer->elements[idx]);
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator<(MagicalContainer::AscendingIterator other) {
        return this->magicalContainer->elements[idx]< other.magicalContainer->elements[other.idx];
    }

    bool MagicalContainer::AscendingIterator::operator>(MagicalContainer::AscendingIterator other) {
        return !(*this<other);
    }

    bool MagicalContainer::AscendingIterator::operator==(MagicalContainer::AscendingIterator other) {
        return this->ptr==other.ptr;
    }

    bool MagicalContainer::AscendingIterator::operator!=(MagicalContainer::AscendingIterator other) {
        return !(*this==other);
    }
    /*
     * SideCross Iterators
     */
    MagicalContainer::SideCrossIterator::SideCrossIterator() {

    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) {
        this->magicalContainer=&container;
        this->ptr=container.crossElements[0];
        this->idx=0;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(size_t idx, MagicalContainer &container) {
        this->magicalContainer=&container;
        this->ptr=magicalContainer->crossElements[idx];
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return MagicalContainer::SideCrossIterator(0,*this->magicalContainer);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return MagicalContainer::SideCrossIterator(this->magicalContainer->size(),*this->magicalContainer);
    }

    int &MagicalContainer::SideCrossIterator::operator*() const {
        return *this->ptr;
    }

    MagicalContainer::SideCrossIterator::pointer MagicalContainer::SideCrossIterator::operator->() {
        return ptr;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        this->idx++;
        this->ptr=this->magicalContainer->crossElements[idx];
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator<(MagicalContainer::SideCrossIterator other) {
        return *this->magicalContainer->crossElements[idx]<*other.magicalContainer->crossElements[other.idx];
    }

    bool MagicalContainer::SideCrossIterator::operator>(MagicalContainer::SideCrossIterator other) {
        return !(*this<other);
    }

    bool MagicalContainer::SideCrossIterator::operator==(MagicalContainer::SideCrossIterator other) {
        return this->ptr==other.ptr;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(MagicalContainer::SideCrossIterator other) {
        return !(this->ptr==other.ptr);
    }
    /*
     * Prime Iterators
     */
    MagicalContainer::PrimeIterator::PrimeIterator() {

    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) {
        this->magicalContainer=&container;
        this->ptr=container.primeElements[0];
        this->idx=0;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(size_t idx, MagicalContainer &container) {
        this->ptr=container.primeElements[idx];
        this->magicalContainer=&container;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return MagicalContainer::PrimeIterator(0,*this->magicalContainer);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return MagicalContainer::PrimeIterator(this->magicalContainer->primeElements.size(),*this->magicalContainer);
    }

    int &MagicalContainer::PrimeIterator::operator*() const {
        return *this->ptr;
    }

    MagicalContainer::PrimeIterator::pointer MagicalContainer::PrimeIterator::operator->() {
        return ptr;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        this->idx++;
        this->ptr=this->magicalContainer->primeElements[idx];
        return *this;
    }

    bool MagicalContainer::isPrime(int number) {
        if(number<=0){
            return false;
        }
        if(number%2==0){
            return false;
        }
        int sqrtNumber= sqrt(number)+1;
        for (int i = 3; i <sqrtNumber ; i=i+2) {
            if(number%i==0){
                return false;
            }
        }
        return true;
    }

    bool MagicalContainer::PrimeIterator::operator<(MagicalContainer::PrimeIterator other) {
        return *this->magicalContainer->primeElements[idx]<*other.magicalContainer->primeElements[other.idx];
    }

    bool MagicalContainer::PrimeIterator::operator>(MagicalContainer::PrimeIterator other) {
        return !(*this<other);
    }

    bool MagicalContainer::PrimeIterator::operator==(MagicalContainer::PrimeIterator other) {
        return this->ptr==other.ptr;
    }

    bool MagicalContainer::PrimeIterator::operator!=(MagicalContainer::PrimeIterator other) {
        return !(this->ptr==other.ptr);
    }
} // ariel