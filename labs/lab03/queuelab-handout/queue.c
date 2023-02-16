/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if(q == NULL) {
	    return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    int buffer;
    char* sp;
    bool done = true;
    char let = 'x';

    
    if(q == NULL) {
	    return;
    }

    if(q->head == NULL) {
	    free(q);
	    return;
    }
    
     sp = &let;
    buffer = strlen(q->head->value) + 1;

    while(done == true) {
	    done = q_remove_head(q,sp,buffer);
    }

    free(q);
    
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if(q == NULL) {
	    return false;
    }
    list_ele_t *newh;
    char *inner;
    inner = malloc(strlen(s)+1);
    if(inner == NULL) {
	    return false;
    }
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(newh == NULL) {
	    free(inner);
	    return false;
    }
    strcpy(inner, s);
    newh->value = inner;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size++;
    if(q->size == 1) {
    	q->tail = newh;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    
    
    if(q == NULL) {
	    return false;
    }
    list_ele_t *newt;
    char *inner;
    inner = malloc(strlen(s)+1);
    if(inner == NULL) {
	    return false;
    }
    /* What should you do if the q is NULL? */
    newt = malloc(sizeof(list_ele_t));
    if(newt == NULL) {
	    free(inner);
	    return false;
    }
    strcpy(inner, s);
    newt->value = inner;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    q->tail->next = newt;
    q->tail = newt;
    q->size++;
    return true;

}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    
    //char oldval[bufsize];
    list_ele_t* oldq;
    if(q == NULL || q->head == NULL) {
	    return false;
    }

    
    if(sp != NULL) {
	*sp = '\0'; strncat(sp, q->head->value,bufsize -1);
    }
    
    oldq = q->head;
    //oldval = q->head->value;
    free(q->head->value);
    q->head = q->head->next;

    free(oldq);
    q->size--;
    if(q->size == 0) {
    	q->head = NULL;
    	q->tail = NULL;
    }
    //free(oldval);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q != NULL) {
    	return(q->size);
    }
   //printf("%d",size);
  return 0; 
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{ 
    if(q == NULL || q->head == NULL) {
	    return;
    }
    list_ele_t* curr;
    list_ele_t* prev;
    list_ele_t* back;

    int size;
    int count;

    curr = q->head;
    prev = q->head;

    size = q_size(q) - 1;
    count = size;

    while(count > 0) {
	    curr = curr->next;
	    count--;
    }
    back = curr;
    count = size - 1;
    while(count > 0) {
	    prev = prev->next;
	    count--;
    }
	
    curr->next = prev;
    size--;

    while(size > 0) {
	    count = size;
	    curr = q->head;
	    prev = q->head;
	    while(count > 0) {
		    curr = curr->next;
		    count--;
	    }
	    count = size - 1;
	    while(count > 0) {
		    prev = prev->next;
		    count--;
	    }
	    curr->next = prev;
	    size--;
    }
    prev->next = NULL;
    q->head = back;




}
