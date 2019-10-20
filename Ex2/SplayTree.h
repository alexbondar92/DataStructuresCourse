//
//  SplayTree.h
//  DataStructure-wet1
//
#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include <stdio.h>
#include <assert.h>
#include <ostream>
#include <stdlib.h>

class SplayTreeException{};

class SplayNotFound : public SplayTreeException{};
class SplayBadAlloc : public SplayTreeException{};
class SplayIllegalInput : public SplayTreeException{};

template<class T>
class Node{
    Node* parent;
    Node* left;
    Node* right;
    T* data;
    int size;
public:
    Node(){
        parent = NULL;
        left = NULL;
        right = NULL;
        data = NULL;
        size = 1;
    }
    
    Node(const T& data, Node* parent, Node* left, Node* right){
        try{
            this->data = new T(data);
        } catch (std::bad_alloc){
            throw SplayBadAlloc();
        }
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->size = 1;
        if (left != NULL){
            this->size += left->size;
        }
        if (right != NULL){
            this->size += right->size;
        }
    }
    
    Node(const Node& node);
    Node& operator=(const Node& node);
    
    ~Node(){
        delete this->data;
    }
    
    T* getData() const{
        return this->data;
    }
    
    Node* getParent(){
        return this->parent;
    }
    
    Node* getLeft(){
        return this->left;
    }
    Node* getRight(){
        return this->right;
    }
    
    int getSize() const{
        return this->size;
    }
    
    void setRight(Node* new_right){
        this->right = new_right;
        this->setSize();
    }
    
    void setLeft(Node* new_left){
        this->left = new_left;
        this->setSize();
    }
    
    void setSize(){
        this->size = 1;
        if (this->left != NULL){
            this->size += this->left->size;
        }
        if (this->right != NULL){
            this->size += this->right->size;
        }
    }
    
    void setParent(Node* parent){
        this->parent = parent;
    }
};




template<class T>
class SplayTree{
private:
    Node<T>* root;
    
public:
    SplayTree(){
        root = NULL;
    }
    SplayTree(const SplayTree& tree);
    
    
    ~SplayTree(){
        if (this->root != NULL){
            SplayTree T1,T2;
            T1.root = this->root->getLeft();
            T2.root = this->root->getRight();
            delete this->root;
        }
    }
    
    int getSize() const{
        if (this->root != NULL){
            return this->root->getSize();
        } else{
            return 0;
        }
    }
    
    T* Find(const T& data){
        Node<T>* tmp_node = this->root;
        if (this->root == NULL){
            return NULL;
        }
        while (tmp_node->getLeft() != NULL || tmp_node->getRight() != NULL ||
               *tmp_node->getData() == data){
            
            if (*tmp_node->getData() > data){
                if(tmp_node->getLeft() == NULL)
                    break;
                tmp_node = tmp_node->getLeft();
            } else if (*tmp_node->getData() < data){
                if(tmp_node->getRight() == NULL)
                    break;
                tmp_node = tmp_node->getRight();
            } else {
                this->Splay(tmp_node);
                this->root = tmp_node;
                return tmp_node->getData();
            }
        }
        this->Splay(tmp_node);
        return NULL;
    }
    
    T* FindMin(){
        if (this->root == NULL){
            return NULL;
        }
        Node<T>* tmp_node = this->root;
        while(tmp_node->getLeft() != NULL){
            tmp_node = tmp_node->getLeft();
        }
        this->Splay(tmp_node);
        return tmp_node->getData();
    }
    
    T* FindMax(){
        if (this->root == NULL){
            return NULL;
        }
        Node<T>* tmp_node = this->root;
        while(tmp_node->getRight() != NULL){
            tmp_node = tmp_node->getRight();
        }
        this->Splay(tmp_node);
        return tmp_node->getData();
    }
    
    void Join(SplayTree& T1, SplayTree& T2){
        if(*(T1.FindMax()) < *(T2.FindMin())){
            T1.FindMax();
            T2.root->setLeft(T1.root);
            T1.root->setParent(T2.root);
            T2.root->setParent(this->root);
            this->root = T2.root;
        } else if(*(T1.FindMin()) > *(T2.FindMax())){
            T2.FindMax();
            T1.root->setLeft(T2.root);
            T2.root->setParent(T1.root);
            T1.root->setParent(this->root);
            this->root = T1.root;
        }
    }
    
    void Split(T& data, SplayTree& T1, SplayTree& T2){
        Find(data);
        if (data < *this->root->getData()){
            T1.root = this->root->getLeft();
            root->setLeft(NULL);
            if (T1.root != NULL){
                T1.root->setParent(NULL);
            }
            T2.root = this->root;
        } else if (data > *this->root->getData() || data == *this->root->getData()){
            T2.root = this->root->getRight();
            root->setRight(NULL);
            if (T2.root != NULL){
                T2.root->setParent(NULL);
            }
            T1.root = this->root;
        }
    }
    
    void Insert(const T& data){
        //        assert(data != NULL);
        Node<T>* new_node = NULL;
        try{
            new_node = new Node<T>(data, NULL, NULL, NULL);
        } catch(std::bad_alloc){
            throw SplayBadAlloc();
        }
        
        if(this->root != NULL){
            SplayTree T1 = SplayTree();
            SplayTree T2 = SplayTree();
            Split(*new_node->getData(), T1, T2);
            this->root = new_node;
            this->root->setLeft(T1.root);
            this->root->setRight(T2.root);
            if (this->root->getLeft() != NULL){
                this->root->getLeft()->setParent(this->root);
            }
            if (this->root->getRight() != NULL){
                this->root->getRight()->setParent(this->root);
            }
            T1.root = NULL;
            T2.root = NULL;
        }
        this->root = new_node;
    }
    
    void Splay(Node<T>* node) {
        assert(node != NULL);
        
        while (node->getParent() != NULL) {
            if (node->getParent()->getParent() != NULL) {
                if (node->getParent()->getParent()->getLeft() != NULL &&
                    node->getParent()->getParent()->getLeft()->getLeft() != NULL &&
                    node->getParent()->getParent()->getLeft()->getLeft() == node) {
                    ZigZig(node);
                } else if (node->getParent()->getParent()->getRight() != NULL &&
                           node->getParent()->getParent()->getRight()->getRight() != NULL &&
                           node->getParent()->getParent()->getRight()->getRight() == node) {
                    ZigZig(node);
                } else if (node->getParent()->getRight() == node) {
                    ZigZag(node);
                } else if (node->getParent()->getLeft() == node) {
                    ZigZag(node);
                }
            } else if (node->getParent()->getParent() == NULL) {
                Zig(node);
            }
        }
        this->root = node;
    }
    
    
    void Zig(Node<T>* node){
        assert(node != NULL);
        Node<T>* tmp_parent = NULL;
        if (node->getParent()->getLeft() == node){
            tmp_parent = node->getParent();
            tmp_parent->setLeft(node->getRight());
            if (tmp_parent->getLeft() !=  NULL){
                tmp_parent->getLeft()->setParent(tmp_parent);
            }
            node->setRight(tmp_parent);
            node->setParent(tmp_parent->getParent());
            tmp_parent->setParent(node);
        }else if (node->getParent()->getRight() == node){
            tmp_parent = node->getParent();
            tmp_parent->setRight(node->getLeft());
            if (tmp_parent->getRight() != NULL){
                tmp_parent->getRight()->setParent(tmp_parent);
            }
            node->setLeft(tmp_parent);
            node->setParent(tmp_parent->getParent());
            tmp_parent->setParent(node);
        }
        if (node->getParent() != NULL){
            if (node->getParent()->getLeft() == tmp_parent){
                node->getParent()->setLeft(node);
            } else if (node->getParent()->getRight() == tmp_parent){
                node->getParent()->setRight(node);
            }
        }
        if (node->getLeft() != NULL){
            node->getLeft()->setSize();
        }
        if (node->getRight() != NULL){
            node->getRight()->setSize();
        }
        node->setSize();
    }
    
    void ZigZig(Node<T>* node){
        assert(node != NULL);
        
        Zig(node->getParent());
        Zig(node);
    }
    
    void ZigZag(Node<T>* node){
        assert(node != NULL);
        
        Zig(node);
        Zig(node);
    }
    
    
    void Delete(const T& data) {
        T* tmp_data = Find(data);
        if (tmp_data == NULL){
            throw SplayNotFound();
        }
        SplayTree T1 = SplayTree();
        T1.root = root->getLeft();
        if (T1.root != NULL){
            T1.root->setParent(NULL);
        }
        SplayTree T2 = SplayTree();
        T2.root = root->getRight();
        if (T2.root != NULL){
            T2.root->setParent(NULL);
        }
        delete this->root;
        if (T1.getSize() == 0){
            this->root = T2.root;
        } else if (T2.getSize() == 0){
            this->root = T1.root;
        } else{
            this->Join(T1, T2);
        }
        if (this->root != NULL){
            this->root->setParent(NULL);
        }
        T1.root = NULL;
        T2.root = NULL;
    }
    
    T* rPreOrder(){
        T* T_arrey = (T*)malloc(sizeof(T)*this->getSize());
        if (T_arrey == NULL){
            throw std::bad_alloc();
        }
        rPreOrderRec(this->root, &T_arrey, 0);
        return T_arrey;
    }
    
    int rPreOrderRec(Node<T>* node, T** T_arrey,int n){
        if (node == NULL){
            return 0;
        }
        int right_n = rPreOrderRec(node->getRight(),T_arrey,n);
        (*T_arrey)[n+right_n] = *node->getData();
        int left_n = rPreOrderRec(node->getLeft(),T_arrey,n+right_n+1);
        return right_n+left_n+1;
    }
    
    T** rPreOrderPtr(){
        T** T_arrey = (T**)malloc(sizeof(T*)*this->getSize());
        if (T_arrey == NULL){
            throw std::bad_alloc();
        }
        rPreOrderRecPtr(this->root, &T_arrey, 0);
        return T_arrey;
    }
    
    int rPreOrderRecPtr(Node<T>* node, T*** T_arrey,int n){
        if (node == NULL){
            return 0;
        }
        int right_n = rPreOrderRecPtr(node->getRight(),T_arrey,n);
        (*T_arrey)[n+right_n] = node->getData();
        int left_n = rPreOrderRecPtr(node->getLeft(),T_arrey,n+right_n+1);
        return right_n+left_n+1;
    }
    
    void Swap(SplayTree<T>& T1){
        Node<T>* tmp = this->root;
        this->root = T1.root;
        T1.root = tmp;
    }
};

#endif //SPLAYTREE_H_

