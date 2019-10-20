//
//  RankSplayTree.h
//  DataStructure-wet2
//
#ifndef RANKSPLAYTREE_H_
#define RANKSPLAYTREE_H_

#include <stdio.h>
#include <assert.h>
#include <ostream>
#include <stdlib.h>
#include <exception>

#define NANRANK 0;           // Ranking-Tree

class RankSplayTreeException : public std::exception{};

class RankSplayNotFound : public RankSplayTreeException{};
class RankSplayBadAlloc : public RankSplayTreeException{};
class RankSplayIllegalInput : public RankSplayTreeException{};
class RankSplayRankInvalid : public RankSplayTreeException{};

template<class T>
class RNode{
public:
    RNode* parent;
    RNode* left;
    RNode* right;
    int rank;           // Ranking-Tree Field...
    T* data;
    int size;
    int base_rank;

    RNode(){
        parent = NULL;
        left = NULL;
        right = NULL;
        data = NULL;
        rank = NANRANK;           // Ranking-Tree
        size = 1;
        base_rank = NANRANK;
    }
    
    RNode(const T& data, int _rank, RNode* parent, RNode* left, RNode* right){
        try{
            this->data = new T(data);
        } catch (std::bad_alloc){
            throw RankSplayBadAlloc();
        }
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->size = 1;
        this->rank = _rank;           // Ranking-Tree
        this->base_rank = _rank;
        if (left != NULL){
            this->size += left->size;
        }
        if (right != NULL){
            this->size += right->size;
        }
    }
    
    RNode(const RNode& node);
    RNode& operator=(const RNode& node);
    
    ~RNode(){
        delete this->data;
    }
    
    T* getData() const{
        return this->data;
    }
    
    int getRank() const{           // Ranking-Tree
        return this->rank;
    }
    
    void setRank(){              // Ranking-Tree
        this->rank = this->base_rank;
        if (this->getLeft() != NULL){
            this->rank += this->getLeft()->getRank();
        }
        if (this->getRight() != NULL){
            this->rank += this->getRight()->getRank();
        }
    }
    
    void resetRank(){              // Ranking-Tree
//        if (this->getLeft() != NULL){
//            this->rank -= this->getLeft()->getRank();
//        }
//        if (this->getRight() != NULL){
//            this->rank -= this->getRight()->getRank();
//        }
        this->rank = this->base_rank;
    }
    
    RNode* getParent(){
        return this->parent;
    }
    
    RNode* getLeft(){
        return this->left;
    }
    
    RNode* getRight(){
        return this->right;
    }
    
    int getSize() const{
        return this->size;
    }
    
    void setRight(RNode* new_right){
        this->right = new_right;
        this->setSize();
    }
    
    void setLeft(RNode* new_left){
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
    
    void setParent(RNode* parent){
        this->parent = parent;
    }
};




template<class T>
class RankSplayTree{
private:
    RNode<T>* root;
    
public:
    RankSplayTree(){
        root = NULL;
    }
    
    RankSplayTree(const RankSplayTree& tree);
    
    ~RankSplayTree(){
        if (this->root != NULL){
            RankSplayTree T1,T2;
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
        RNode<T>* tmp_node = this->root;
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
                this->RankSplay(tmp_node);
                this->root = tmp_node;
                return tmp_node->getData();
            }
        }
        this->RankSplay(tmp_node);
        return NULL;
    }
    
    T* FindMin(){
        if (this->root == NULL){
            return NULL;
        }
        RNode<T>* tmp_node = this->root;
        while(tmp_node->getLeft() != NULL){
            tmp_node = tmp_node->getLeft();
        }
        this->RankSplay(tmp_node);
        return tmp_node->getData();
    }
    
    T* FindMax(){
        if (this->root == NULL){
            return NULL;
        }
        RNode<T>* tmp_node = this->root;
        while(tmp_node->getLeft() != NULL){
            tmp_node = tmp_node->getLeft();
        }
        this->RankSplay(tmp_node);
        return tmp_node->getData();
    }
    
    void Join(RankSplayTree& T1, RankSplayTree& T2){
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
    
    void Split(T& data, RankSplayTree& T1, RankSplayTree& T2){
        Find(data);
        if (data < *this->root->getData()){
            T1.root = this->root->getLeft();
            root->setLeft(NULL);
            if (T1.root != NULL){
                T1.root->setParent(NULL);
            }
            T2.root = this->root;
            if (T1.root != NULL){
                T1.root->resetRank();
                T1.root->setRank();
            }
            if (T2.root != NULL){
                T2.root->resetRank();
                T2.root->setRank();
            }
        } else if (data > *this->root->getData() || data == *this->root->getData()){
            T2.root = this->root->getRight();
            root->setRight(NULL);
            if (T2.root != NULL){
                T2.root->setParent(NULL);
            }
            T1.root = this->root;
            if (T1.root != NULL){
                T1.root->resetRank();
                T1.root->setRank();
            }
            if (T2.root != NULL){
                T2.root->resetRank();
                T2.root->setRank();
            }
        }
    }
    
    void Insert(const T& data, int _rank){
        //        assert(data != NULL);
        RNode<T>* new_node = NULL;
        try{
            new_node = new RNode<T>(data, _rank, NULL, NULL, NULL);
        } catch(std::bad_alloc){
            throw RankSplayBadAlloc();
        }
        
        if(this->root != NULL){
            RankSplayTree T1 = RankSplayTree();
            RankSplayTree T2 = RankSplayTree();
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
//        this->root->resetRank();
        this->root->setRank();
    }
    
    void RankSplay(RNode<T>* node) {
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
    
    
    void Zig(RNode<T>* node){
        assert(node != NULL);
        RNode<T>* tmp_parent = NULL;
        if (node->getParent()->getLeft() == node){  // Left-Zig
            node->getParent()->resetRank();           // Ranking-Tree
            node->resetRank();           // Ranking-Tree
            tmp_parent = node->getParent();
            tmp_parent->setLeft(node->getRight());
            if (tmp_parent->getLeft() !=  NULL){
                tmp_parent->getLeft()->setParent(tmp_parent);
            }
            node->setRight(tmp_parent);
            node->setParent(tmp_parent->getParent());
            tmp_parent->setParent(node);
            tmp_parent->setRank();           // Ranking-Tree
            node->setRank();           // Ranking-Tree
        }else if (node->getParent()->getRight() == node){   // Right-Zig
            node->getParent()->resetRank();           // Ranking-Tree
            node->resetRank();           // Ranking-Tree
            tmp_parent = node->getParent();
            tmp_parent->setRight(node->getLeft());
            if (tmp_parent->getRight() != NULL){
                tmp_parent->getRight()->setParent(tmp_parent);
            }
            node->setLeft(tmp_parent);
            node->setParent(tmp_parent->getParent());
            tmp_parent->setParent(node);
            tmp_parent->setRank();           // Ranking-Tree
            node->setRank();           // Ranking-Tree
        }
        if (node->getParent() != NULL){     // ????
            node->getParent()->resetRank();           // Ranking-Tree
            if (node->getParent()->getLeft() == tmp_parent){
                node->getParent()->setLeft(node);
            } else if (node->getParent()->getRight() == tmp_parent){
                node->getParent()->setRight(node);
            }
            node->getParent()->setRank();           // Ranking-Tree
        }
        if (node->getLeft() != NULL){
            node->getLeft()->setSize();
        }
        if (node->getRight() != NULL){
            node->getRight()->setSize();
        }
        node->setSize();
    }
    
    void ZigZig(RNode<T>* node){
        assert(node != NULL);
        
        Zig(node->getParent());
        Zig(node);
    }
    
    void ZigZag(RNode<T>* node){
        assert(node != NULL);
        
        Zig(node);
        Zig(node);
    }
    
    
    void Delete(const T& data) {
        T* tmp_data = Find(data);
        if (tmp_data == NULL){
            throw RankSplayNotFound();
        }
        RankSplayTree T1 = RankSplayTree();
        T1.root = root->getLeft();
        if (T1.root != NULL){
            T1.root->setParent(NULL);
        }
        RankSplayTree T2 = RankSplayTree();
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
    
    int rPreOrderRec(RNode<T>* node, T** T_arrey,int n){
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
    
    int rPreOrderRecPtr(RNode<T>* node, T*** T_arrey,int n){
        if (node == NULL){
            return 0;
        }
        int right_n = rPreOrderRecPtr(node->getRight(),T_arrey,n);
        (*T_arrey)[n+right_n] = node->getData();
        int left_n = rPreOrderRecPtr(node->getLeft(),T_arrey,n+right_n+1);
        return right_n+left_n+1;
    }
    
    void Swap(RankSplayTree<T>& T1){
        RNode<T>* tmp = this->root;
        this->root = T1.root;
        T1.root = tmp;
    }
    
    int SelectRankBySize(int size){           // Ranking-Tree
        if (this->getSize() < size){
            return -1;
//            throw RankSplayRankInvalid();
        }
        this->FindMax();
        int rank=NANRANK;
        int rank_nodes=0;
        RNode<T>* tmp = this->root;
        if (this->getSize() == size) {
            return tmp->getRank();
        }
        while (tmp != NULL){
            if (rank_nodes == size){
                return rank;
            }else if (rank_nodes < size){
                if (tmp->getRight() != NULL &&
                    rank_nodes + 1 + tmp->getRight()->getSize() == size){
                    rank_nodes += 1;
                    tmp->resetRank();
                    rank += tmp->getRank() + tmp->getRight()->getRank();
                    tmp->setRank();
                    return rank;
                } else if (tmp->getRight() != NULL &&
                           rank_nodes + 1 + tmp->getRight()->getSize() < size){
                    rank_nodes += 1 + tmp->getRight()->getSize();
                    tmp->resetRank();
                    rank += tmp->getRank() + tmp->getRight()->getRank();
                    tmp->setRank();
                    assert(tmp->getLeft() != NULL);
                    tmp = tmp->getLeft();
                } else if (rank_nodes + 1 == size){
                    tmp->resetRank();
                    rank += tmp->getRank();
                    tmp->setRank();
                    return rank;
                } else if (tmp->getLeft() != NULL && rank_nodes + tmp->getLeft()->getSize() == size){
                    return rank + tmp->getLeft()->getRank();
                } else if (tmp->getLeft() != NULL && rank_nodes + tmp->getLeft()->getSize() > size){
                        tmp = tmp->getLeft();
//                } else if (tmp->getLeft() != NULL &&
//                           rank_nodes + tmp->getLeft()->getSize() < size){
//                    rank_nodes += 1;
//                    tmp->resetRank();
//                    rank += tmp->getRank() + tmp->getRight()->getRank();
//                    tmp->setRank();
//                    tmp = tmp->getLeft();
                } else if (tmp->getLeft() != NULL && rank_nodes + 1 + tmp->getLeft()->getSize() == size){
                    tmp->resetRank();
                    rank += tmp->getRank() + tmp->getLeft()->getRank();
                    tmp->setRank();
                    return rank;
//                    assert(2 == 1);
//                }
                } else if (tmp->getRight() != NULL &&
                           rank_nodes + 1 + tmp->getRight()->getSize() > size){
                    assert(tmp->getRight() != NULL);
                    rank += tmp->getRank() - tmp->getRight()->getRank();
                    rank_nodes += tmp->getSize() - tmp->getRight()->getSize();
                    tmp = tmp->getRight();
                }
            } else {
                assert(2 == 1);
            }
        }
        assert(2 == 1);
        return 1;
    }
    
    
};

#endif //RANKSPLAYTREE_H_

