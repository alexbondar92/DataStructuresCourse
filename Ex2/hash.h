//
// Created by Anastasia Neiman on 1/1/2018.
//

#ifndef HW2_HASH_H
#define HW2_HASH_H

#include <stdio.h>
#include <assert.h>
#include <ostream>
#include <list>

const int FACTOR = 2;
class HashExeptions{};

class HashNotFound : public HashExeptions{};
class HashBadAlloc : public HashExeptions{};
class HashIllegalInput : public HashExeptions{};

class ListExeptions{};

class ListNotFound : public HashExeptions{};
class ListBadAlloc : public HashExeptions{};
class ListIllegalInput : public HashExeptions{};
class ListElementAlredyExist : public HashExeptions{};


template<class T>
class HNode{
public:
    int key;
    HNode* prev;
    T* data;
    HNode* next;
    bool last;
    
    HNode(){
        this->key = -1;
        this->data = NULL;
        this->prev = this;
        this->next = NULL;
        this->last = true;
    }
    
    HNode(T* data, int ID, HNode* prev, HNode* next){
        this->data = data;
        this->key = ID;
        this->prev = prev;
        this->next = next;
        this->last = false;
    }

    HNode(const HNode& n);
    
    HNode& operator=(const HNode& n);
    
//    ~HNode();
    ~HNode(){
//        delete this->data;
    }
    
    T* getData() const{
        return this->data;
    }
    
    int getKey() const{
        return this->key;
    }
    
    HNode* nextNode() const{
        return this->next;
    }
    
    HNode* prevNode() const{
        return this->prev;
    }
    
    void setNext(HNode* next){
        this->next = next;
    }
    
    void setPrev(HNode* prev){
        this->prev = prev;
    }
    bool isLast(){
        return this->last;
    }
};

template<class T>
class List{
public:
    friend class HNode<T>;
    HNode<T>* head;
    HNode<T>* tail;
    int size;
    
    List(const List& l);
    
    List& operator=(const List& l);
    
    List(){
        this->size = 0;
        HNode<T>* dummy = new HNode<T>();
        dummy->prev = NULL;
        this->head = dummy;
        this->tail = dummy;
    }
    
    ~List(){
        if (this->size != 0){
            while(this->head->next != NULL){
                HNode<T>* tmp = this->head;
                this->head = this->head->next;
                this->head->prev = NULL;
                tmp->next = NULL;
                delete tmp;
//                this->head->next = this->head->next->next;
//                if (this->head->next->prev->data != NULL){
//                    delete this->head->next->prev->data;
//                }
//                delete this->head->next->prev;
//                this->head->next->prev = this->head;
            }
        }
        if (this->head->data != NULL){
            delete this->head->data;
        }
        delete this->head;
    }
    
    T* findElement(int _key){
        if(this->size == 0)
            return NULL;
        HNode<T>* iterator = this->head->next;
//        node->next = this->head;
        for(int i = 0; i < this->size ; i++ ){
            if (iterator->key == _key) {
                return iterator->data;
            }
//            iterator->next = iterator->next->next;
            iterator = iterator->next;
        }
        return NULL;
    }
    
    void insert(T* data, int _key){
//        HNode<T>* node = new HNode<T>();
        if(this->findElement(_key) != NULL) {
//            delete node;
            throw ListElementAlredyExist();
        }
//        delete node;
        HNode<T>* new_node = new HNode<T>(data, _key, this->head, this->head->next);
        if(this->head->next == NULL){
            this->head->next = new_node;
            new_node->last = true;
            this->head->last = false;
        } else {
            this->head->next->prev = new_node;
            this->head->next = new_node;
        }
        this->size++;

    }
};


template <class T>
class Hash{

public:
    List<T>* hashTable;
    int size;
    int numOfElements;

    friend class List<T>;
    friend class HNode<T>;
    
    Hash(const Hash& h);
    
    Hash& operator=(const Hash& h);

    Hash(int n){
        this->hashTable = new List<T>[n*FACTOR];
        this->size = n*FACTOR;
        this->numOfElements = 0;
    }
    
    ~Hash(){
        delete[] this->hashTable;
    }

     void HashInsertElement(T* data, int _key){
        if(this->numOfElements == this->size) {
            this->HashIncreaseSize();
        }
//        HNode<T>* node = new HNode<T>();
        try{
            this->hashTable[_key % this->size].findElement(_key);          // =========== it doesn't throwing anything ======!!!!!!!!
        } catch(ListElementAlredyExist) {
//            delete node;
            throw HashIllegalInput();
        }
//        delete node;
        this->hashTable[_key % this->size].insert(data, _key);
        this->numOfElements++;
    }

    void HashIncreaseSize(){
//        Hash* new_hash = new Hash(this->size);
        List<T>* new_hash_table = new List<T>[this->size*FACTOR];
//        if (&new_hash == NULL)
//            throw HashBadAlloc();             // Who catching ???!?!?
//        int new_index = 0;
        HNode<T>* tmp_node/*= new HNode<T>()*/;

        for (int i = 0; i < this->size ; ++i) {
            if (this->hashTable[i].size > 0){
                tmp_node = this->hashTable[i].head->nextNode();
                for (int j = 0; j < this->hashTable[i].size; j++){
//                while (tmp_node->next != NULL) {
                    new_hash_table[tmp_node->key%(this->size*FACTOR)].insert(tmp_node->getData(),tmp_node->getKey());
                    tmp_node->data = NULL;
//                    new_hash->HashInsertElement(tmp_node->getData(), tmp_node->getKey());
                    tmp_node = tmp_node->nextNode();
//                    this->hashTable[i].size--;
                }
            }
        }
        delete[] this->hashTable;
        this->hashTable = new_hash_table;
        this->size = this->size*FACTOR;
//        return new_hash;
    }

    T* HashFindElement(int ID){
        T* data = this->hashTable[ID % this->size].findElement(ID);
        return data;
    }

};


#endif //HW2_HASH_H
