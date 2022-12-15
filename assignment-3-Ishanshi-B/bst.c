/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Ishanshi Bhardwaj
 * Email: bhardwai@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node
{
  int key;
  void *value;
  struct bst_node *left;
  struct bst_node *right;
};

/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst
{
  struct bst_node *root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst *bst_create()
{
  struct bst *bst = malloc(sizeof(struct bst));
  bst->root = NULL;
  return bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst *bst)
{
  bst_free_recursive(bst->root);
  free(bst);
}
/*
 * This functions free the memory recursively by getting the root node from the bst_free function 
 *
 * Params:
 *   node - the single node that we want to get rid of 
 */
void bst_free_recursive(struct bst_node *node)
{
  if (node->left)
  {
    bst_free_recursive(node->left);
  }
  if (node->right)
  {
    bst_free_recursive(node->right);
  }
  free(node);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst *bst)
{
  struct bst_node *node = bst->root;
  return bst_s(node);
}
/*
 * This function returns the number of elements stored in the 
 * BST.
 *
 * Params:
 *   node - the bst single node whose elements needs to be counted.  May not be NULL.
 */
int bst_s(struct bst_node *node)
{
  if (node == NULL)
  {
    return 0;
  }
  //recursive step 
  return 1 + bst_s(node->left) + bst_s(node->right);
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst *bst, int key, void *value)
{
bst->root = newNodes(bst->root, key, value);
return;
}

/*
 * This function inserts the new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Resource used: https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 * 
 * Params:
 *   node - the bst root into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
struct bst_node *newNodes(struct bst_node *node, int key, void *value)
{
  //if that node is empty then create the new node 
  if (node == NULL)
  {
    struct bst_node *temp = (struct bst_node *)malloc(sizeof(struct bst_node));
    temp->key = key;
    temp->value = value;
    temp->left = temp->right = NULL;
    return temp;
  }
  //go down the tree 
  if (key < node->key)
  {
    node->left = newNodes(node->left, key, value);
  }
  else if (key > node->key)
  {
    node->right = newNodes(node->right, key, value);

  }
  return node;
}
/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 * 
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst *bst, int key)
{
 remove_node_bst(bst->root, key);

  return;
}
/*
 * This function removes a key/value pair with a specified key from a
 * given BST. 
 *
 * Params:
 *   node - the BST root from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
struct bst_node* remove_node_bst(struct bst_node* node, int key){

  //if the key we want to remove is a leaf and it is to the left 
  //find the value u want to delete 
  if(node == NULL){
    return NULL;
  }
  if(key < node->key){
    node->left = remove_node_bst(node->left, key);
  }
  //if the key is to the right 
  else if(key > node->key){
    node->right = remove_node_bst(node->right, key);
  }
  //if the key is not a leaf 
  else{
    if(node->right == NULL){
      struct bst_node *temp = node->left;
      free(node);
      return temp;
    }
    else if(node->left == NULL){
      struct bst_node *temp = node->right;
      free(node);
      return temp;
    }
    //two children case
    else{

      struct bst_node *temp = node->right;
      while(temp->left != NULL){
      
        temp = temp->left;
        
      }
      //replace with the inorder successor 
      node->key = temp->key;
      node->value = temp->value;
      node->right = remove_node_bst(node->right, temp->key);
    }

   }
  return node;
}


/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void *bst_get(struct bst *bst, int key)
{
  //call a function that does what we want 
  return search(bst->root, key);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   node - the BST root from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
struct bst_node* search(struct bst_node *node, int key){
  //check the root node 
  if(node == NULL || node->key == key){
    return node; 
  }
  if(node->key < key){
    return search(node->right, key);
  }
  if(node->key > key){
    return search(node->left, key);
  }


}
/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
int bst_height(struct bst *bst)
{
 return height(bst->root);
  
}
/*
 * This function returns the height of a given BST, which is the maximum
 * depth of any node in the tree.
 *
 * Resource Used: https://www.baeldung.com/cs/binary-tree-height
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   returns the height of bst.
 */
int height(struct bst_node* node){
  if(node == NULL){
    return -1;

  }
  //calculate the right and left child height recursively 
    int left = height(node->left);
    int right = height(node->right);

    if(left > right){
      return left + 1;
    }
    else{
      return right + 1;
    }
}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst *bst, int sum)
{
  
  return bst_node_path_sum(bst->root,sum);
}

/*
 * This function determines whether a specified value is a valid path
 * sum within a given BST. 
 *
 * Resource Used: https://afteracademy.com/blog/path-sum-in-binary-tree
 * 
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_node_path_sum(struct bst_node *node, int sum){
  
  if(node == NULL){return 0;}
 
  //if left and right key are null then just return the sum of the root key 
  if(node->left == NULL && node->right == NULL){
    return node->key == sum;
  }
  //else recursively go through the binary tree and go subtract sum by the value of the current node and if the remaining value is 0 then the sum exists.   
  return (bst_node_path_sum(node->left, (sum - node->key))|| bst_node_path_sum(node->right, (sum-node->key)));
  
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst *bst, int lower, int upper)
{
  return bst_ranges(bst->root, lower, upper);
}
/*
 * This function computes a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound. 
 * 
 * Resource Used: https://www.geeksforgeeks.org/sum-of-nodes-in-a-binary-search-tree-with-values-from-a-given-range/
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Returns the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_ranges(struct bst_node *node, int lower, int upper){
  int sum = 0;
  if(node == NULL){
    return sum;
  }
  //add to the sum integer and recursively go to both left and right side if the node key is between the lower and upper limits 
  if(node->key >= lower && node->key <= upper){
    sum += node->key;
    sum += bst_ranges(node->left,lower,upper);
    sum += bst_ranges(node->right,lower,upper);
  }
  //if the lower bound is greater than the root node then go towards the right of the tree
  else if(node->key < lower){
    sum += bst_ranges(node->right, lower, upper);
  }
  //if the lower bound is less than the root node then go towards the left of the tree
  else{
    sum+= bst_ranges(node->left,lower,upper);
  }
  return sum;
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator
{
  struct stack *stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator *bst_iterator_create(struct bst *bst)
{
  struct bst_iterator* iter = malloc(sizeof(struct bst_iterator*));
  iter->stack= stack_create();
  //create the root 
  struct bst_node* node = bst->root;
  //traverse left and the leftest most node and that is the start of the iterator
  while(node != NULL){
    stack_push(iter->stack, node);
    node = node->left;
  }

  return iter;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator *iter)
{
  stack_free(iter->stack);
  free(iter);
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator *iter)
{
  return (!stack_isempty(iter->stack));
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator *iter, void **value)
{
struct bst_node* current = stack_pop(iter->stack);
int new_key = current->key;
void * value = current->value;

if(iter== NULL){
  return NULL;
}

 //if the current node is null and the stack is empty
 while(current!=NULL || !stack_isempty(iter)){
  //push the current node to the stack an
  if(current != NULL){
    stack_push(current,value);
    current= current->left;
  }
    // otherwise, if the current node is null, pop an element from the stack
  else{
    current = stack_top(iter);
    stack_pop(iter);
    current= current->right;

  }

 }

  return 0;
}
