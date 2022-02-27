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
static void freeNode(node_t *root);
static node_t* findMaxNode(node_t *root,int *count_ptr);
static node_t* searchNode(node_t *root,int key,int *count_ptr);
static node_t* findMinNode(node_t *root);
static node_t* deleteNode(node_t *root,int key,int *count_ptr);
static node_t* insertNode(node_t *root,int key,int *count_ptr);
static node_t* createNode(int key);

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
void delete_element(bst_t *tree, int key, int *count_ptr){
        tree->root = deleteNode(tree->root,key,count_ptr);

}

// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr){
    node_t *searchElement;
    int searchValue = -1;
    searchElement = searchNode(tree->root,key,count_ptr);
    if(searchElement != NULL){
        searchValue = searchElement->key;
    }

    return searchValue;
}

// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr){
    node_t *temp;
    temp = findMaxNode(tree->root,count_ptr);
    int maxValue = -1;
    if(temp != NULL){
        maxValue = temp->key;
    }
    return maxValue;
}

// Deletes all the elements of the bst
void free_bst(bst_t *bst) {
    freeNode(bst->root);
    free(bst);

}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    freeNode(bst->root);
    bst->root = NULL;

}


//Function returns a  address of a node created
node_t* createNode(int key){
    node_t *element = (node_t*)malloc(sizeof(node_t));
    element->key = key;
    element->left = element->right = NULL;
    return element;
}


//Insert the element into the tree recursively
node_t* insertNode(node_t *root,int key,int *count_ptr){
    (*count_ptr)++;
    if(root == NULL){
        (*count_ptr)++;
        return(createNode(key));

    }
    else if(key > root->key){
        (*count_ptr)++;
        root->right = insertNode(root->right,key,count_ptr);
    }    
    else{
        (*count_ptr)++;
        root->left = insertNode(root->left,key,count_ptr);
    }
    return root;
}


//Deletes the Nodes specified by the key recursively
node_t* deleteNode(node_t *root,int key,int *count_ptr){
    if(root == NULL){
        (*count_ptr)++;
        return NULL;
    }
    if(key > root->key){
        (*count_ptr)++;
        root->right = deleteNode(root->right,key,count_ptr);
    }
    else if(key < root->key){
        (*count_ptr)++;
        root->left = deleteNode(root->left,key,count_ptr);
    }
    else{
        //no children
        if(root->left == NULL && root->right == NULL){
            (*count_ptr)++;
            free(root);
            return NULL;
        }
        else if(root->left == NULL || root->right == NULL){
            (*count_ptr)++;
            node_t *temp;
            if(root->left == NULL){
                (*count_ptr)++;
                temp = root->right;
            }
            else{
                (*count_ptr)++;
                temp = root->left;
            }
            free(root);
            return temp;

        }
        else{
            (*count_ptr)++;
            node_t *temp = findMinNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,temp->key,count_ptr);
        }
        
    }
    return root;
}


//Finds the node in the BST with minimum value
node_t* findMinNode(node_t *root){
    if(root == NULL){
        return NULL;
    }
    else if(root->left != NULL){
        return findMinNode(root->left);
    }
    return root;
}


//Finds the element present in the tree recursive code
node_t* searchNode(node_t *root,int key,int *count_ptr){
    if(root == NULL || root->key == key){
        (*count_ptr)++;
        return root;
    }
    else if(key > root->key){
        (*count_ptr)++;
        return searchNode(root->right,key,count_ptr);
    }
    else{
        return searchNode(root->left,key,count_ptr);
    }
}


//Finds the Node with maximum value in the tree
node_t* findMaxNode(node_t *root,int *count_ptr){
    if(root == NULL){
        (*count_ptr)++;
        return NULL;
    }
    else if(root->right !=NULL){
        (*count_ptr)++;
        return findMaxNode(root->right,count_ptr);
    }
    return root;
}


//Deallocates the memory allocated to the nodes of the BST using recursion
void freeNode(node_t *root){
    if(root == NULL){
        return;
    }
    freeNode(root->right);
    freeNode(root->left);
    free(root);

}