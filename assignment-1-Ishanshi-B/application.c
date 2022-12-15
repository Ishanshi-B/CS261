/*
 * In this file, you should implement an application that compares the
 * performance of a dynamic array and a linked list, as described in the
 * README. Don't forget to include your name and @oregonstate.edu email
 * address below.
 *
 * Name: Ishanshi Bhardwaj
 * Email: bhardwai@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "dynarray.h"
#include "list.h"

#define TEST_DATA_SIZE 1000000

/*
 * This function generates and an array of random integers of size n.
 */
int *generate_random_array(int n)
{
  int *arr = malloc(n * sizeof(int));
  int i;

  for (i = 0; i < n; i++)
  {
    arr[i] = rand();
  }

  return arr;
}

int main(int argc, char const *argv[])
{

  int *test_data = generate_random_array(TEST_DATA_SIZE);
  /*
   * You should write code here to insert the data in test_data into a
   * dynamic array using the dynamic array interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      dynamic array.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the dynamic array.
   * To help with this, you can use the C functions time() and difftime()
   * from time.h.  Don't forget to include time.h above!
   */
  // call test_dynarray
  struct dynarray *da;
  struct list* list; 

  // create the dynarray
  da = dynarray_create();
  list = list_create();

  clock_t start_t, end_t;
  clock_t dynarray_start_time, dynarray_end_time;

  clock_t start_i, end_i;
  clock_t linked_start_time, linked_end_time;
  double total_t, total_element_time, total_i, total_element_time_i;

  start_t = clock();

  double maxAddTime = 0;
  //go through the elements and check the time 
  for (int i = 0; i < TEST_DATA_SIZE; i++)
  {
    dynarray_start_time = clock();

    dynarray_insert(da, &test_data[i]);
    dynarray_end_time = clock();
    total_element_time = (double)(dynarray_end_time - dynarray_start_time) / CLOCKS_PER_SEC;

    //Max time is added 
    if (total_element_time > maxAddTime){
      maxAddTime = total_element_time;
    }
  }
  end_t = clock();
 
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Total time Dynammic Array: %f\n", total_t);
  printf("Max time for one element Dynammic Array: %f\n", maxAddTime);

  /*
   * You should write code here to insert the data in test_data into a
   * linked list using the linked list interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      linked list.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the linked list.
   * Again, you can use the C functions time() and difftime() from time.h to
   * help with this.
   *
   * How do the times associated with the dynamic array compare to the times
   * associated with the linked list?  How does this change if you modify the
   * value of TEST_DATA_SIZE above?
   */

start_i = clock();

  double maxLinkedTime = 0;
  //check the total linked list time and then check the element time 
  for (int i = 0; i < TEST_DATA_SIZE; i++)
  {
    linked_start_time = clock();

    list_insert(list, &test_data[i]);
    linked_end_time = clock();
    total_element_time_i = (double)(linked_end_time - linked_start_time) / CLOCKS_PER_SEC;
    //Max time is added 
    if (total_element_time_i > maxLinkedTime){
      maxLinkedTime = total_element_time_i;
    }
  }
  end_i = clock();
 
  total_i = (double)(end_i - start_i) / CLOCKS_PER_SEC;
  printf("Total time linked list: %f\n", total_i);
  printf("Max time linked list: %f\n", maxLinkedTime);



  dynarray_free(da);
  list_free(list);
  free(test_data);

  return 0;
}