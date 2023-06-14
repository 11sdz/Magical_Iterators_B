//
// Created by mintsdz on 6/12/23.
//

#ifndef CMAKEITER_MAGICALLINKLIST_HPP
#define CMAKEITER_MAGICALLINKLIST_HPP
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "MyAlgos.hpp"

/**
 * This file represents my MagicalLinkList
 * This LinkList can only be templaet T can only be int or int* for the purposes of the assigment
 * and contains Nodes linked by next and prev pointers
 */
using namespace std;
namespace ariel {
    /**
     * struct Node
     * contains T type of data (int or int*)
     * prev,next holds pointer to another Node<T> of the same type
     * @tparam T int or int* only
     */
    template<typename T>
    struct Node{
        static_assert(std::is_same_v<T, int> || std::is_same_v<T, int*>, "T must be int or int*");/*asserting T is int or int**/
        T data;
        Node<T>* prev;
        Node<T>* next;
        Node(Node<T>*prev,T data,Node<T>*next):data(data),prev(prev),next(next){}/*Node constructor prev,data,next*/
    };
/**
 * MagicalLinkList class
 * has head and tail
 * this MagicalLinkList has to insertion methods addSorted for ascending sorted lists ,and pushback inserting Nodes at tail
 * this MagicalLinkList also support a "sorting operation" to sort in SideCrossOrder (smallest,biggest,2nd smallest,2nd biggest....)
 * a getMax method getting the biggest Node by data
 * a getMin method getting the smallest Node by data
 * a method to remove specific element
 * a method to check if element is contained
 * len method for getting the amount of Nodes in the list
 * @tparam T
 */
    template <typename T>
    class MagicalLinkList {
    public:
        static_assert(std::is_same_v<T, int> || std::is_same_v<T, int*>, "T must be int or int*");
    private:
        size_t _size;
        Node<T> *_head;
        Node<T> *_tail;
    public:
        /*Constructors */
        MagicalLinkList():_size(0),_head(nullptr),_tail(nullptr){}
        MagicalLinkList(const MagicalLinkList& other): _size(other._size),_head(other._head),_tail(other._tail){}
        MagicalLinkList& operator=(const MagicalLinkList& other){
            if(this==&other){
                return *this;
            }
            this->_head=other._head;
            this->_tail=other._tail;
            this->_size=other._size;
            return *this;
        }
        MagicalLinkList(MagicalLinkList&& other) noexcept: _size(other._size),_head(other._head),_tail(other._tail){}
        MagicalLinkList& operator=(MagicalLinkList&& other) noexcept{
            this->_head=other._head;
            this->_tail=other._tail;
            this->_size=other._size;
            return *this;
        }
/*Destructor*/
        virtual ~MagicalLinkList() {
            Node<T> *temp=_head;
            while(temp!= nullptr){
                Node<T>*next=temp->next;
                delete(temp);
                temp=next;
            }
        }
/**
 * crossOrdering sorting
 */
        void crossOrder(){
            vector<Node<T>*> sideCrossVector;
            Node<T>* minmax= nullptr;
            bool flag= true; /*acting like switch true-> we getMin , false->we getMax*/
            while (sideCrossVector.size()<len()) {
                /* unlinking 1 Node in each iteration from the list
                 * odd iterations Minimum Node , even iterations Maximum node
                 * and pushing the node to the back of vector
                 */
                if(flag) {
                    minmax = getMin(_head, _tail);
                    flag=false;
                }else{
                    minmax = getMax(_head,_tail);
                    flag= true;
                }
                //unlinking node cases _head=_tail ,_tail,_head,middle
                if (minmax == _head && minmax!=_tail) {
                    _head = minmax->next;
                    _head->prev = nullptr;
                } else if (minmax == _tail && minmax!=_head) {
                    _tail = minmax->prev;
                    _tail->next = nullptr;
                }else if(minmax!=_head && minmax!=_tail){
                    minmax->prev->next=minmax->next;
                    minmax->next->prev=minmax->prev;
                }
                minmax->next= nullptr;
                minmax->prev= nullptr;
                sideCrossVector.push_back(minmax);
            }
            /*
             *  using vector.back() because vector only support pop_back() operations
             */
            _tail=sideCrossVector.back(); // the last node in vector represents tail
            std::reverse(sideCrossVector.begin(), sideCrossVector.end()); //reversing
            _head=sideCrossVector.back(); //the last node in vector is the _head
            Node<T>* start=_head;// like "iterator" over nodes
            Node<T>* prev= nullptr; //holds the prev assigned as nullptr because the first node is the head
            while(!sideCrossVector.empty()){
                start=sideCrossVector.back();
                sideCrossVector.pop_back();
                start->next= nullptr;
                if(!sideCrossVector.empty()){
                    //if is empty we got the tail
                    start->next=sideCrossVector.back();
                }
                /* holding the current Node
                 * iterating to the nextNode
                 * assigning the current Node as the prev of nextNode
                 */
                prev=start;
                start=start->next;
                if(start!= nullptr) {
                    start->prev = prev;
                }
            }
        }
        /**
         * finding the Maximum inbetween start and end
         * @param start
         * @param end
         * @return node represents the maximum data between start and end
         */
        Node<T>* getMax(Node<T>* start,Node<T>*end){
            int maxi=std::numeric_limits<int>::min();
            Node<T>* node=start;
            while(start!= nullptr){
                maxi=max(maxi,*start->data);
                if(maxi==*start->data){
                    node=start;
                }
                start=start->next;
            }
            return node;
        }
                /**
                * finding the Minimum inbetween start and end
                * @param start
                * @param end
                * @return node represents the minimum data between start and end
                */
        Node<T>* getMin(Node<T>* start,Node<T>*end){
            int mini=std::numeric_limits<int>::max();
            Node<T>* node=start;
            while(start!= nullptr){
                mini=min(mini,*start->data);
                if(mini==*start->data){
                    node=start;
                }
                start=start->next;
            }
            return node;
        }
/**
 * inserting a new Node at the tail
 * @param data
 */
        void pushback(T data){
            if(_head== nullptr){
                _head=new Node<T>(nullptr,data, nullptr);
                _tail=_head;
            }else if(_tail==_head){
                _tail=new Node<T>(nullptr,data,nullptr);
                _tail->prev=_head;
                _head->next=_tail;
            }else{
                Node<T>* temp=_tail;
                _tail=new Node<T>(temp, data, nullptr);
                temp->next=_tail;
            }
            _size++;
        }
/**
 * adding at sorted order for ascending ordered lists
 * @param data
 */
        void addSorted(T data){
            Node<T> *node = new Node<T>(nullptr, data,  nullptr);
            if(_head == nullptr) {
                _head = node;
                _tail = _head;
            }else if(compareValues(_tail->data,data)<0){
                _tail->next=node;
                node->prev=_tail;
                _tail=node;
            }else if(compareValues(_head->data,data)>0){
                _head->prev=node;
                node->next=_head;
                _head=node;
            }else{
                Node<T> *temp = _head;
                while(compareValues(temp->data,data)<0){
                    temp=temp->next;
                }
                temp->prev->next=node;
                node->prev=temp->prev;
                node->next=temp;
                temp->prev=node;
            }
            _size++;
        }
        /**
         * unlinking and removing Node from the list that represents data
         * @param data
         */
        void remove(T data){
            if(!contains(data)){
                return;
            }
            _size--;
            if(_head->data==data && _tail->data==data){
                delete _head;
                _head= nullptr;
                _tail= nullptr;
                return;
            }if(_head->data==data){
                Node<T>* temp=_head;
                _head=_head->next;
                _head->prev= nullptr;
                delete temp;
                return;
            }if(_tail->data==data){
                Node<T>* temp=_tail;
                _tail=_tail->prev;
                _tail->next= nullptr;
                delete temp;
                return;
            }
            Node <T>*curr=_head;
            while(curr->data!=data){
                curr=curr->next;
            }
            Node<T>* temp=curr->prev;
            temp->next=curr->next;
            temp->next->prev=temp;
            delete curr;
        }
        /**
         * check if lists contains the node that holds data
         * @param data
         * @return true / false - contains/not contained
         */
        bool contains(T data){
            if(len()==0){
                return false;
            }
            if(_head->data==data || _tail->data==data){
                return true;
            }
            Node <T>*temp=_head;
            while(temp->next!= nullptr){
                temp=temp->next;
                if(temp->data==data){
                    return true;
                }
            }
            return false;
        }
        /**
         * finding the Node containing data if any and returning a pointer to the data
         * @param data
         * @return &(Node->data)
         */
        T* get(T data){
            if(contains(data)) {
                Node<T> *temp = _head;
                while (temp->data != data) {
                    temp = temp->next;
                }
                return &temp->data;
            }
            return nullptr;
        }
        /**
         * getHead
         * @return head Node
         */
        Node<T>* getHead(){
            return _head;
        }
        /**
         * getTail
         * @return tail Node
         */
        Node<T>* getTail(){
            return _tail;
        }
        /**
         * returning length amount of nodes
         * @return size_t amount of nodes
         */
        size_t len(){
            return _size;
        }
    };

} // ariel
#endif //CMAKEITER_MAGICALLINKLIST_HPP
