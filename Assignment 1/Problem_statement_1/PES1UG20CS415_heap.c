// Name:Shrujan
// SRN: PES1UG20CS415
#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
static void heapify(heap_t *heap,int parentNode,int heapifyLoop,int *count_ptr);


void init_heap(heap_t *heap, int max_size) {
    heap->arr = (int*)malloc(max_size*sizeof(int));
    heap->max_size = max_size;
    heap->size = 0;

}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr) {
    if(heap->size < heap->max_size){
        (*count_ptr)++;
        heap->arr[heap->size] = key;
        heap->size++;
        int heapifyLoop = 1;
        for(int parentNode=(heap->size)/2-1;parentNode>=0;parentNode--){
            heapify(heap,parentNode,heapifyLoop,count_ptr);
        }
        
    }
    
}

// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int extract_max(heap_t *heap, int *count_ptr) {
    int maxValue = 0;
    if(heap->size >= 0){
        (*count_ptr)++;
        maxValue = heap->arr[0];
        heap->arr[0]=heap->arr[heap->size-1];
        (heap->size)--; 
        for(int parentNode=(heap->size)/2-1;parentNode>=0;parentNode--){
            heapify(heap,parentNode,1,count_ptr);
        }
    }
    return maxValue;
    
}
// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr) {
    int searchElement = -1;
    int notFound = 1;
    for(int i =0 ;i<heap->size && notFound ;i++){
        (*count_ptr)++;
        if(heap->arr[i]==key){
            searchElement = key;
            notFound = 0;
            (*count_ptr)++;
        }
    }
    return searchElement;
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr) {
    int maxValue = -1;
    if(heap->size >=0){
        (*count_ptr)++;
        maxValue = heap->arr[0];
    }
    return maxValue;
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr) {
    int minValue = heap->arr[0];
    for(int i = heap->arr[(heap->size)/2 -1];i<heap->size;i++){
        
        if(minValue > heap->arr[i]){
            (*count_ptr)++;
            minValue = heap->arr[i];
        }
    }
    return minValue;
}

// Clears the heap for reuse
void clear_heap(heap_t *heap) {
    for(int i=0;i<heap->max_size;i++){
        heap->arr[i]=0;
    }
    heap->size = 0;
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap) {
    free(heap->arr);

}
    

//Heapify Function 
void heapify(heap_t *heap,int parentNode,int heapifyLoop,int *count_ptr){
    while(heapifyLoop == 1){
        if(heap->size !=1){
            int largest = parentNode;
            int leftNode = 2*parentNode+1;
            int rightNode = 2*parentNode+2;
            if(leftNode < heap->size && heap->arr[leftNode] > heap->arr[largest]){
                largest = leftNode;
                (*count_ptr)++;
            }
            if(rightNode < heap->size && heap->arr[rightNode] > heap->arr[largest]){
                largest = rightNode;
                (*count_ptr)++;
            }
            if(largest != parentNode){
                (*count_ptr)++;
                int temp = heap->arr[largest];
                heap->arr[largest] = heap->arr[parentNode];
                heap->arr[parentNode] = temp;
                parentNode = largest ; 
            }
            else{
                heapifyLoop = 0;
            }
                    
        }
    }
}