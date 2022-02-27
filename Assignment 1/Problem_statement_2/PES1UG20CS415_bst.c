// Name:SHRUJAN
// SRN: PES1UG20CS415
#include "bst.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
*/

// Initializes the root of the bst
void init_bst(bst_t *bst){
    bst->root = NULL;
    

}

// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
void insert(bst_t *tree, int key, int *count_ptr){
    tree->root = insertNode(tree->root,key,count_ptr);

}

// Delete key from the BST
// Replaces node with in-order successor
void delete_element(bst_t *tree, int key, int *count_ptr)
{

}

// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{

}

// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{

}

// Deletes all the elements of the bst
void free_bst(bst_t *bst) 
{

}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{

}


node_t* createNode(int key){
    node_t *element = (node_t*)malloc(sizeof(node_t));
    element->key = key;
    element->left = element->right = NULL;
    return element;
}

node_t* insertNode(node_t *root,int key,int *count_ptr){
    (*count_ptr)++;
    if(root == NULL){
        return(createNode(key));

    }
    else if(key > root->key){
        root->right = insertNode(root->right,key,count_ptr);
    }    
    else{
        root->left = insertNode(root->left,key,count_ptr);
    }
    return root;
}