//
// Created by mintsdz on 6/8/23.
//

#include "MagicalContainer.hpp"

namespace ariel {
    /*
     * =====================================================================
     * =====================MagicalContainer================================
     * =====================================================================
     */
    MagicalContainer::MagicalContainer(){}
    MagicalContainer::~MagicalContainer() {

    }

    MagicalContainer::MagicalContainer(const MagicalContainer &magicalContainer) {
        this->elements=magicalContainer.elements;
        this->primeElements=magicalContainer.primeElements;
        this->crossElements=magicalContainer.crossElements;
    }

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &magicalContainer) {
        this->elements=magicalContainer.elements;
        this->primeElements=magicalContainer.primeElements;
        this->crossElements=magicalContainer.crossElements;
        return *this;
    }
    /**
     * adding the element to elements list
     * adding a pointer to crossElements list
     * adding a pointer to primeElements
     * @param ele
     */
    void MagicalContainer::addElement(int ele) {
        if(!elements.contains(ele)) {
            this->elements.addSorted(ele);
            int *pEle = elements.get(ele);
            if (isPrime(ele)) {
                //adding if ele is prime the pEle at sorted order
                primeElements.addSorted(pEle);
            }
            if(crossElements.len()>=2) {
                //if len>=3 we need to pushback and sort in crossOrder
                this->crossElements.pushback(pEle);
                crossElements.crossOrder();
            }else{
                //if len<=2 we add in a ascending order since its 2 elements at most Smallest,Biggest
                crossElements.addSorted(pEle);
            }
        }
    }
    /**
     * removing ele and removing pointer from each list
     * and maintaining ascending and crossordered
     * @param ele
     */
    void MagicalContainer::removeElement(int ele) {
        if(this->size()) {
            if (!elements.contains(ele)) {
                throw runtime_error("no such element");
            }
            int *pEle = this->elements.get(ele);
            this->elements.remove(ele);
            this->crossElements.remove(pEle);
            if (crossElements.len() > 1) {
                this->crossElements.crossOrder();
            }
            if (isPrime(ele)) {
                primeElements.remove(pEle);
            }
        }
    }

    /**
     * return size
     * @return
     */
    size_t MagicalContainer::size() {
        return elements.len();
    }

    /*
       * =====================================================================
       * =====================AscendingIterator===============================
       * =====================================================================
       */
    MagicalContainer::AscendingIterator::AscendingIterator() {
        this->magicalContainer=nullptr;
        this->ptr= nullptr;
        this->pNode= nullptr;
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) {
        this->magicalContainer=&container;
        this->pNode=container.elements.getHead();
        this->ptr=&(this->pNode->data);
    }

    MagicalContainer::AscendingIterator::AscendingIterator(
            const MagicalContainer::AscendingIterator &ascendingIterator) {
        this->magicalContainer=ascendingIterator.magicalContainer;
        this->ptr=ascendingIterator.ptr;
        this->pNode=ascendingIterator.pNode;
    }

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &ascendingIterator) {
        if (this->magicalContainer!=ascendingIterator.magicalContainer){
            throw runtime_error("iterators are pointing at different containers\n"
                                "  AscendingIterator");
        }
        this->magicalContainer=ascendingIterator.magicalContainer;
        this->ptr=ascendingIterator.ptr;
        this->pNode=ascendingIterator.pNode;
        return *this;
    }
/**
 * creating end() or begin()
 * @param pNode
 */
    MagicalContainer::AscendingIterator::AscendingIterator(Node<int>* pNode){
        //end => all parameters are nullptr
        //begin=> pNode = head of the list , ptr = &(head->data)
        this->pNode=pNode;
        this->ptr= nullptr;
        if(pNode!= nullptr){
            this->ptr=&(pNode->data);
        }
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(magicalContainer->elements.getHead());
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return AscendingIterator(nullptr);
    }
    /**
     * retunring reference to the current element that the iterators points to
     * @return int&
     */
    MagicalContainer::AscendingIterator::reference MagicalContainer::AscendingIterator::operator*() const {
        return *this->ptr;
    }
    /**
     * retunring pointer to the current element that the iterators points to
     * @return int*
     */
    MagicalContainer::AscendingIterator::pointer MagicalContainer::AscendingIterator::operator->() {
        return ptr;
    }

    /**
     * iterating to the next Node
     * @return AscendingIterator
     */
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if(this->pNode== nullptr){
            throw runtime_error("beyond end Asc++");
        }
        pNode=pNode->next;
        this->ptr = &(pNode->data);
        return *this;
    }
/**
 * binary operators
 * @param other
 * @return true/false
 */
    bool MagicalContainer::AscendingIterator::operator<(MagicalContainer::AscendingIterator other) {
        if(this->magicalContainer!=other.magicalContainer){
            throw runtime_error("cannot compare between different containers");
        }
        if(this->ptr== nullptr){
            if(other.ptr== nullptr){
                return false;
            }else{
                return true;
            }
        }else if(other.ptr== nullptr){
            return false;
        }
        return *(this->ptr)< *(other.ptr);
    }
/**
 * binary operators
 * @param other
 * @return true/false
 */
    bool MagicalContainer::AscendingIterator::operator>(MagicalContainer::AscendingIterator other) {
        return !(*this<other) && !(*this==other);
    }
/**
 * binary operators
 * @param other
 * @return true/false
 */
    bool MagicalContainer::AscendingIterator::operator==(MagicalContainer::AscendingIterator other) {
        return this->ptr==other.ptr;
    }
/**
 * binary operators
 * @param other
 * @return true/false
 */
    bool MagicalContainer::AscendingIterator::operator!=(MagicalContainer::AscendingIterator other) {
        return !(*this==other);
    }
    /*
        * =====================================================================
        * =====================SideCrossIterator===============================
        * =====================================================================
        */
    MagicalContainer::SideCrossIterator::SideCrossIterator() {

    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) {
        this->magicalContainer=&container;
        this->pNode=container.crossElements.getHead();
        this->ptr= nullptr;
        if(pNode!= nullptr) {
            this->ptr = (this->pNode->data);
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &crossIterator) {
        this->magicalContainer=crossIterator.magicalContainer;
        this->ptr=crossIterator.ptr;
        this->pNode=crossIterator.pNode;
    }

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &crossIterator) {
        if (this->magicalContainer!=crossIterator.magicalContainer){
            throw runtime_error("iterators are pointing at different containers\n"
                                "  AscendingIterator");
        }
        this->magicalContainer=crossIterator.magicalContainer;
        this->ptr=crossIterator.ptr;
        this->pNode=crossIterator.pNode;
        return *this;
    }
/**
 * creating end() or begin()
 * @param pNode
 */
    MagicalContainer::SideCrossIterator::SideCrossIterator(Node<int*>* pNode){
        this->pNode=pNode;
        this->ptr= nullptr;
        if(pNode!= nullptr){
            this->ptr=(pNode->data);
        }
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return MagicalContainer::SideCrossIterator(magicalContainer->crossElements.getHead());
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return MagicalContainer::SideCrossIterator(nullptr);
    }
/**
     * retunring reference to the current element that the iterators points to
     * @return int&
     */
    MagicalContainer::SideCrossIterator::reference MagicalContainer::SideCrossIterator::operator*() const {
        return *this->ptr;
    }
/**
     * retunring pointer to the current element that the iterators points to
     * @return int*
     */
    MagicalContainer::SideCrossIterator::pointer MagicalContainer::SideCrossIterator::operator->() {
        return ptr;
    }
    /**
     * iterating to the next Node
     * @return SideCrossIterator
     */
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if(this->pNode== nullptr){
            throw runtime_error("beyond end Cross++");
        }
        this->pNode=pNode->next;
        this->ptr= nullptr;
        if(pNode!= nullptr) {
            this->ptr = pNode->data;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator<(MagicalContainer::SideCrossIterator other) {
        if(this->magicalContainer!=other.magicalContainer){
            throw runtime_error("cannot compare between different containers");
        }
        if(this->ptr== nullptr){
            if(other.ptr== nullptr){
                return false;
            }else{
                return true;
            }
        }else if(other.ptr== nullptr){
            return false;
        }
        return *(this->ptr)<*(other.ptr);
    }

    bool MagicalContainer::SideCrossIterator::operator>(MagicalContainer::SideCrossIterator other) {
        return !(*this<other) && !(*this==other);
    }

    bool MagicalContainer::SideCrossIterator::operator==(MagicalContainer::SideCrossIterator other) {
        return this->ptr==other.ptr;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(MagicalContainer::SideCrossIterator other) {
        return !(this->ptr==other.ptr);
    }
    /*
    * =====================================================================
    * =====================Prime Iterators================================
    * =====================================================================
    */
    MagicalContainer::PrimeIterator::PrimeIterator() {

    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) {
        this->magicalContainer=&container;
        this->pNode=container.primeElements.getHead();
        this->ptr= nullptr;
        if(pNode!= nullptr) {
            this->ptr = (this->pNode->data);
        }
    }
    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &primeIterator) {
        this->magicalContainer=primeIterator.magicalContainer;
        this->ptr=primeIterator.ptr;
        this->pNode=primeIterator.pNode;
    }

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator &primeIterator) {
        if (this->magicalContainer!=primeIterator.magicalContainer){
            throw runtime_error("iterators are pointing at different containers\n"
                                "  AscendingIterator");
        }
        this->magicalContainer=primeIterator.magicalContainer;
        this->ptr=primeIterator.ptr;
        this->pNode= primeIterator.pNode;
        return *this;
    }
/**
 * creating end() or begin()
 * @param pNode
 */
    MagicalContainer::PrimeIterator::PrimeIterator(Node<int*>* pNode) {
        this->pNode=pNode;
        this->ptr= nullptr;
        if(pNode!= nullptr){
            this->ptr=(pNode->data);
        }
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return MagicalContainer::PrimeIterator(this->magicalContainer->primeElements.getHead());
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return MagicalContainer::PrimeIterator(nullptr);
    }
/**
     * retunring reference to the current element that the iterators points to
     * @return int&
     */
    MagicalContainer::PrimeIterator::reference MagicalContainer::PrimeIterator::operator*() const {
        return *this->ptr;
    }
/**
     * retunring pointer to the current element that the iterators points to
     * @return int*
     */
    MagicalContainer::PrimeIterator::pointer MagicalContainer::PrimeIterator::operator->() {
        return ptr;
    }
    /**
     * iterating to the next Node
     * @return PrimeIterator
     */
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if(this->pNode== nullptr){
            throw runtime_error("beyond end Asc++");
        }
        this->pNode=pNode->next;
        this->ptr= nullptr;
        if(pNode!= nullptr) {
            this->ptr = pNode->data;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator<(MagicalContainer::PrimeIterator other) {
        if(this->ptr== nullptr){
            if(other.ptr== nullptr){
                return false;
            }else{
                return false;
            }
        }else if(other.ptr== nullptr){
            return false;
        }
        return *this->ptr<*other.ptr;
    }

    bool MagicalContainer::PrimeIterator::operator>(MagicalContainer::PrimeIterator other) {
        return !(*this<other) && !(*this==other);
    }

    bool MagicalContainer::PrimeIterator::operator==(MagicalContainer::PrimeIterator other) {
        return this->ptr==other.ptr;
    }

    bool MagicalContainer::PrimeIterator::operator!=(MagicalContainer::PrimeIterator other) {
        return !(this->ptr == other.ptr);
    }
} // ariel