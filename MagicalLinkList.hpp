//
// Created by mintsdz on 6/12/23.
//

#ifndef CMAKEITER_MAGICALLINKLIST_HPP
#define CMAKEITER_MAGICALLINKLIST_HPP
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "MyAlgos.hpp"
using namespace std;
namespace ariel {

    template<typename T>
    struct Node{
        T data;
        Node<T>* prev;
        Node<T>* next;
        Node(Node<T>*prev,T data,Node<T>*next):data(data),prev(prev),next(next){};
    };

    template <typename T>
    class MagicalLinkList {
    private:
        size_t _size;
        Node<T> *_head;
        Node<T> *_tail;
    public:
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

        virtual ~MagicalLinkList() {
            Node<T> *temp=_head;
            while(temp!= nullptr){
                Node<T>*next=temp->next;
                delete(temp);
                temp=next;
            }
        }

        void crossOrder(){
            vector<Node<T>*> vector1;
            Node<T>* minmax= nullptr;
            bool flag= true;
            while (vector1.size()<len()) {
                if(flag) {
                    minmax = getMin(_head, _tail);
                    flag=false;
                }else{
                    minmax = getMax(_head,_tail);
                    flag= true;
                }
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
                vector1.push_back(minmax);
            }
            _tail=vector1.back();
            std::reverse(vector1.begin(), vector1.end());
            _head=vector1.back();
            Node<T>* start=_head;
            Node<T>* prev= nullptr;
            while(!vector1.empty()){
                start=vector1.back();
                vector1.pop_back();
                start->next= nullptr;
                if(!vector1.empty()){
                    start->next=vector1.back();
                }
                prev=start;
                start=start->next;
                if(start!= nullptr) {
                    start->prev = prev;
                }
            }
        }
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
        void remove(T data){
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
        int* get(T data){
            Node <T>*temp=_head;
            while (temp->data!=data){
                temp=temp->next;
            }
            return &temp->data;
        }

        Node<T>* getHead(){
            return _head;
        }
        Node<T>* getTail(){
            return _tail;
        }
        size_t len(){
            return _size;
        }
    };

} // ariel
#endif //CMAKEITER_MAGICALLINKLIST_HPP
