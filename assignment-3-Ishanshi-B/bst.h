/*
 * This file contains the definition of the interface for the binary search
 * tree you'll implement.  You should not modify anything in this file.  You
 * can find descriptions of the binary search tree functions, including their
 * parameters and their return values, in bst.c.
 */

#ifndef __BST_H
#define __BST_H

/*
 * Structure used to represent a binary search tree.
 */
struct bst;
struct bst_node;



/*
 * Basic binary search tree interface function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
struct bst* bst_create();
void bst_free(struct bst* bst);
int bst_size(struct bst* bst);
void bst_insert(struct bst* bst, int key, void* value);
void bst_remove(struct bst* bst, int key);
void* bst_get(struct bst* bst, int key);
void bst_free_recursive (struct bst_node*);
struct bst_node *newNodes(struct bst_node *node, int key, void *value);
struct bst_node *search(struct bst_node *node, int key);
struct bst_node* remove_node_bst(struct bst_node* node, int key);
int height(struct bst_node* node);
int bst_node_path_sum(struct bst_node *node, int sum);
int bst_ranges(struct bst_node *node, int lower, int upper);
/*
 * Binary search tree "puzzle" function p\rototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
int bst_height(struct bst* bst);
int bst_s(struct bst_node* node);
int bst_path_sum(struct bst* bst, int sum);
int bst_range_sum(struct bst* bst, int lower, int upper);


/*
 * Structure used to represent a binary search tree iterator.
 */
struct bst_iterator;

/*
 * Binary search tree iterator interface prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst);
void bst_iterator_free(struct bst_iterator* iter);
int bst_iterator_has_next(struct bst_iterator* iter);
int bst_iterator_next(struct bst_iterator* iter, void** value);

#endif
