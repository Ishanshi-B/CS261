/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Ishanshi Bhardwaj
 * Email: bhardwai@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq
{
  struct dynarray *heap;
};

struct pq_element
{
  int priority;
  void *item;
};
/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq *pq_create()
{
  struct pq *pq = malloc(sizeof(struct pq));
  pq->heap = dynarray_create();
  return pq;
}

//Testing 
// void print_arr(struct pq *pq)
// {
//   printf("testing %i\n", dynarray_size(pq->heap));
// }

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq *pq)
{
  dynarray_free(pq->heap);
  free(pq);
  return;
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq *pq)
{
  if (dynarray_size(pq->heap) == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq *pq, void *value, int priority)
{
  struct pq_element *p_element = malloc(sizeof(struct pq_element));

  //store the value and the priority 
  p_element->item = value;
  p_element->priority = priority;
  
  //insert the element in the heap
  dynarray_insert(pq->heap, p_element);
  int current = dynarray_size(pq->heap) - 1;
  int parent = (current - 1) / 2;
  //create new elements 
  struct pq_element *one;
  struct pq_element *two;
  //till the time the current is not 0 meaning the size of the heap is not Null 
  while (current != 0)
  {
    //set the element one as the value of the parent 
    one = dynarray_get(pq->heap, parent);
    //set the element two as the value of the current node 
    two = dynarray_get(pq->heap, current);
    //check to see if the priority of the parent is greater than the child or not 
    if (two->priority < one->priority)
    {
      //if that is the case then swap the parent and children 
      swap_elements(pq, parent, current);
    }
    //reset the current value 
    current = parent;
    //reset the parent value 
    parent = (current - 1) / 2;
  }
}

/*
 * This function swaps the parent and the child elements when called. So basically when the parent values is 
 * greater than the child we would need to switch the spots they are in and that is why the swap function exists. 
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   parent - the value of the parent node 
 *   current - the value of the child node 
 */
void swap_elements(struct pq *pq, int parent, int current)
{
  // store the current and the parent
  struct pq_element *one = dynarray_get(pq->heap, current);
  struct pq_element *two = dynarray_get(pq->heap, parent);

  //swap the values but setting them 
  dynarray_set(pq->heap, parent, one);
  dynarray_set(pq->heap, current, two);
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void *pq_first(struct pq *pq)
{
  struct pq_element *first_item = dynarray_get(pq->heap, 0);
  return first_item->item;
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq *pq)
{
  struct pq_element *first_item = dynarray_get(pq->heap, 0);
  return first_item->priority;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void *pq_remove_first(struct pq *pq)
{
  //get the last element index 
  int last = dynarray_size(pq->heap) - 1;
  //store the first value 
  struct pq_element *first = dynarray_get(pq->heap, 0);
  void *firstValue = first->item;

  //swap the elements 
  swap_elements(pq, 0, last);
  //free the last value to remove it 
  free(dynarray_get(pq->heap, last));
  //remove it from the heap 
  dynarray_remove(pq->heap, last);
  if (dynarray_size(pq->heap) > 0)
  {
    array_fix(pq, 0);
  }
  return firstValue;
}

/*
 * This function helps with fixing the array but putting them in the right spots.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *  j - the current index value 
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void array_fix(struct pq *pq, int j)
{
  // initially the left child is 1 and the right child is 2 and min is 0
  // they are the index of the left and the right children of the current
  int leftChild = 2 * j + 1;
  int rightChild = 2 * j + 2;
  // index of the lowest priority child
  int min = j;

  struct pq_element *leftEl;
  struct pq_element *rightEl;
  struct pq_element *minEl;

  // this while loops goes till the left child is less than the size of the priority queue
  while (leftChild < dynarray_size(pq->heap))
  {
    // set the left element as the value we get for the left child
    leftEl = dynarray_get(pq->heap, leftChild);
    // set the min element as the value we get for the min
    minEl = dynarray_get(pq->heap, min);
    // if right index is out of the bounds
    if (rightChild >= dynarray_size(pq->heap))
    {
      // if the left index has a lower priority than the min
      if (leftEl->priority < minEl->priority)
      {
        // set min as the value of the left child
        min = leftChild;
      }
    }
    else
    {

      rightEl = dynarray_get(pq->heap, rightChild);
      // determining which child would have a lower priority
      if (leftEl->priority < minEl->priority && leftEl->priority <= rightEl->priority)
      {
        min = leftChild;
      }
      if (rightEl->priority < minEl->priority && leftEl->priority > rightEl->priority)
      {
        min = rightChild;
      }
    }
    if (min == j)
    {
      break;
    }

    else
    {
      swap_elements(pq, j, min);
      j = min;
      leftChild = (j * 2) + 1;
      rightChild = (j * 2) + 2;
    }
  }
}