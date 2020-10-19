/*
 Tia Bhattacharya
 rubhatta
 CSE 101
 Nov 25, 2019
 Header file for List ADT
 List.h
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// List
// reference type
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
// newList()
// constructor for List type
List newList(void);

// freeList()
// destructor for List type
// frees all heap memory associated with *pL
void freeList(List *pL);

// Access functions -----------------------------------------------------------
// length()
int length(List L);

// index()
int index(List L);

// front()
int front(List L);

// back()
int back(List L);

// get()
int get(List L);

// equals()
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------
// clear()
void clear(List L);

// moveFront()
void moveFront(List L);

// moveBack()
void moveBack(List L);

// movePrev()
void movePrev(List L);

// moveNext()
void moveNext(List L);

// prepend()
void prepend(List L, int data);

// append()
void append(List L, int data);

// insertBefore()
void insertBefore(List L, int data);


// insertAfter()
void insertAfter(List L, int data);

// deleteFront()
void deleteFront(List L);

// deleteBack()
void deleteBack(List L);

// delete()
void delete(List L);

// printList()
void printList(FILE* out, List L);

// copyList()
List copyList(List L);
#endif
