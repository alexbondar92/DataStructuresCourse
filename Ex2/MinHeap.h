#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <stdio.h>
#include <assert.h>
//#include <exception>


class HeapException {};
class EmptyHeap : public HeapException {};


template<class T>
class MinHeap{
    T* array;
    int n;
    int max_size;
    
    void SiftDown(int index){
        if (this->n < 2*index){
            return;
        } else if (this->n < (2*index + 1) && this->array[index] > this->array[2*index]){
            int temp = this->array[index];
            this->array[index] = this->array[2*index];
            this->array[2*index] = temp;
            this->SiftDown(2*index);
        } else if (2*index+1 < this->n && this->array[index] > this->array[2*index] && this->array[2*index+1] > this->array[2*index]){
            int temp = this->array[index];
            this->array[index] = this->array[2*index];
            this->array[2*index] = temp;
            this->SiftDown(2*index);
        } else if (2*index+1 < this->n && this->array[index] > this->array[2*index+1] && this->array[2*index] > this->array[2*index+1]){
            T temp = this->array[index];
            this->array[index] = this->array[2*index+1];
            this->array[2*index+1] = temp;
            this->SiftDown(2*index+1);
        }
    }
    
    void SiftUp(int index){
        if (index/2 != 0 && this->array[index] < this->array[index/2]){
            T temp = this->array[index];
            this->array[index] = this->array[index/2];
            this->array[index/2] = temp;
            this->SiftUp(index/2);
        }
    }
    
    void DoubleArraySize(){
        T* temp_arr = new T[this->max_size*2+1];
        for (int i = 1; i <= this->n; i++){
            temp_arr[i] = this->array[i];
        }
        delete[] this->array;
        this->array = temp_arr;
        this->max_size = this->max_size*2+1;
    }
    
public:
    MinHeap();
    MinHeap(T* const data, int size){
        this->array = new T[2*(size+1)];
        this->n = size;
        this->max_size = 2*(size+1);
        for (int i=1; i <= this->n; i++){
            this->array[i] = data[i-1];
        }
        
        for (int i=n/2; 1<=i; i--){
            this->SiftDown(i);
        }
    }
    
    ~MinHeap(){
        delete[] this->array;
    }
    
    MinHeap(const MinHeap& heap);
    
    MinHeap& operator=(const MinHeap& heap);
    
    void Insert(T& x){
        this->n ++;
        this->array[this->n] = x;
        this->SiftUp(this->n);
        if (this->n == (this->max_size-1)){
            this->DoubleArraySize();
        }
    }
    
    void DecKey(T* p, T& x);        // ====================== Not Needed =============================
    
    T& FindMin(){
        return this->array[1];
    }
    
    void DelMin(){
        if (this->n == 0){
            throw EmptyHeap();
        }
        this->array[1] = this->array[this->n];
        this->n --;
        this->SiftDown(1);
    }
};
#endif /* MINHEAP_H_ */
