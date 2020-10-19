/*
 Tia Bhattacharya
 rubhatta
 Integer List ADT in C to alphabetize lines in a file
 List.c
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"


// PRIVATE TYPES -------------------------------------

// NodeObj
typedef struct NodeObj {
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
}
NodeObj;

// Node
typedef NodeObj* Node;

// ListObj
typedef struct ListObj {
    // initialize variable
    Node head;  // front element
    Node last;  // back element
    Node cursor;    // cursor to distinguish element
    int length;     // length of List, # of elements
    int c_index;    // index range 0 to length-1
} ListObj;


// Constructors-Destructors -------------------------------------

// new Node ()
// constructor
Node newNode (int data) {
    Node N = malloc(sizeof(NodeObj));
    // assert(N! = NULL);
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);
}
// freeNode ()
// destructor
void freeNode (Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}
// newList()
// Creates and returns a new empty List
List newList(void) {
    List L = malloc(sizeof(ListObj));
    // assert(L != NULL);
    // create empty List
    L->head = NULL;
    L->last = NULL;
    L-> cursor = NULL;
    // for integers
    L-> c_index = -1;  // index ranging from 0 (front) to 𝑛 − 1 (back)
    L->length = 0; // number of elements in List L
    // return new empty List
    return(L);
}
// freeList()
// Frees all heap memory associated with *pL
// sets *pL to NULL
void freeList(List* pL) {
    if (pL!=NULL && *pL!=NULL) {
        while(length(*pL) > 0) {
            deleteFront(*pL);
        }
        // free node
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -------------------------------------
// length()
// returns the number of elements in L
int length(List L) {
    // if L is empty
    if (L == NULL) {
        printf("List error: calling length() on NULL List reference\n");
        exit(1);
    }
    // num elements = L->length
    return L->length;
}
// index()
// Returns number of index cursor element if defined
// -1 otherwise (undefined)
// pre: length() > 0
int index(List L) {
    // if L is empty
    if (L == NULL) {
        printf("List error: calling index() on NULL List reference\n");
        exit(1);
    }
    // if undefined
    if (length(L) <= 0){
        // -1
        return -1;
    }
    // if defined
    // number of index cursor element
    return L->c_index;
}
// front()
// returns front element of L
// pre: length() > 0
int front(List L) {
    // if L is empty
    if (L == NULL) {
        printf("List error: calling front() on NULL List reference\n");
        exit(1);
    }
    // else error
    if (length(L) <= 0) {
        printf(" List error: front() called on empty List\n");
        // exit(1);
    }
    // while List contains data, return front element
    return L->head->data;
}
// back()
// returns back element of L
// pre: length() > 0
int back(List L) {
    // if L is empty
    if (L == NULL) {
        printf("List error: calling back() on NULL List reference\n");
        exit(1);
    }
    //  error
    if (length(L) <= 0) {
        printf(" List error: back() called on empty List\n");
        // exit(1);
    }
    // while List contains data, return last element
    return L->last->data;
}
// get()
// returns cursor element of L
// pre: length()>0 and index()>=0
int get(List L) {
    // if L is empty
    if (L == NULL) {
        printf("List error: calling get() on NULL List reference\n");
        exit(1);
    }
    // else error if length <= 0
    if (length(L) <= 0) {
        printf(" List error: get() called on empty List\n");
        // exit(1);
    }
    // else error if index <= 0
    if (L->cursor == NULL) {
        printf(" List error: get() called on NULL cursor\n");
        // exit(1);
    }
    // while List contains data, return cursor element
    return L->cursor->data;
}
// equals()
// returns true (1) iff Lists A and B are in same state
// false (0) otherwise
int equals (List A, List B) {
    // Queue as reference
    // initializations
    int eq = 0;
    Node N = NULL;
    Node M = NULL;
    
    // error is List A/B is empty
    if (A==NULL || B==NULL) {
        printf("List error: calling equals() on NULL List reference");
        exit(1);
    }
    eq = (A->length == B->length);
    N = A->head;
    M = B->head;
    while(eq && N!=NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Manipulation procedures ----------------------------------------------
// clear()
// Resets L ro original empty state
void clear(List L) {
    // if L is empty
    if (L == NULL) {
        printf("List error: calling clear() on NULL List reference\n");
        exit(1);
    }
    // reset to empty state
    // Dictionary.c as reference
    while (length(L) > 0) {
        deleteFront(L);
    }
    // reset everything to original state
    // head, last, cursor NULL
    // length 0
    // c_index -1
    L->head = NULL;
    L->last = NULL;
    L->cursor = NULL;
    // for integers
    L->length = 0; // length of List L
    L-> c_index = -1;
}
// moveFront()
// if L is non-empty, sets cursor under the front element
// otherwise does nothing
// pre: length() > 0
void moveFront(List L) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if (length(L) > 0) {
        // under front
        L->cursor = L->head;
        // index of front = 0
        L->c_index = 0;
    }
}
// moveBack()
// if L is non-empty, sets cursor under back element
// otherwise nothing
// pre: length()>0
void moveBack(List L) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if (length(L) > 0) {
        // under back
        L->cursor = L->last;
        // index of back = 𝑛 − 1
        // where n is length of the list
        // c_index = length -1
        L->c_index = L->length - 1;
    }
}
// movePrev()
// if cursor is defined and NOT AT front
// move cursor one step toward front of L
// if cursor is defined and AT front
// cursor becomes undefined
// if cursor is undefined, do nothing
void movePrev(List L) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    // if cursor is NOT at front
    if (L->cursor != L->head) {
        // move cursor one step forward
        L->cursor = L->cursor->prev;
        // decrement cursor index
        L->c_index--;
    }
    // if cursor is AT front
    else {
        // cursor becomes undefined = NULL
        L->cursor = NULL;
        // cursor index set back to original state
        L->c_index = -1;
    }
}
// moveNext()
// if cursor is defined and NOT AT back
// move cursor one step toward back
// if cursor is defined and AT back
// cursor becomes undefined
// if undefined, do nothing
void moveNext(List L) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    // if cursor is NOT at back
    if (L->cursor != L->last) {
        // move cursor one step back
        L->cursor = L->cursor->next;
        // increment cursor index
        L->c_index++;
    }
    // if cursor is AT back
    else {
        // cursor becomes undefined = NULL
        L->cursor = NULL;
        // cursor index set back to original state
        L->c_index = -1;
    }
}
// prepend()
// insert new element into L
// if L is non-empty, insertion before front element
void prepend(List L, int data) {
    // Queue.c & Stack.c as reference
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);
    // insert new element if front is empty
    if (L->head == NULL) {
        L->head = N;
        L->last = N;
        // set cursor to front
        L->cursor = L->head;
    }
    // if L is non-empty, insert before front element
    else {
        // set before front
        L->head->prev = N;
        N->next = L->head;
        L->head = N;
        L->c_index++; // increment cursor index every time insertions before front element
    }
    L->length++;
}
// append()
// insert new element into L
// if L is non-empty, insert after back element
void append(List L, int data) {
    // Queue.c & Stack.c as reference
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);
    // insert new element if back is empty
    if (L->last == NULL) {
        L->head = N;
        L->last = N;
        // set cursor to front
        L->cursor = L->last;
    }
    // if L is non-empty, insert before front element
    else {
        // set after back
        L->last->next = N;
        N->prev = L->last;
        L->last = N;
        N->next = NULL;
    }
    L->length++;
}
// insertBefore()
// insert new element before cursor
// pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    // if cursor is undefined
    if (L->cursor == NULL) {
        printf("List error: calling insertBefore() on undefined cursor\n");
        //  exit(1);
    }
    // if cursor = head, call prepend
    if (L->cursor == L->head) {
        prepend(L, data);
    }
    // else insert element before cursor
    else {
        Node N = newNode(data);
        N->prev = L->cursor->prev; // new prev = cursor prev
        N->next = L->cursor; // new next = cursor
        L->cursor->prev->next = N; // new cursor = N
        L->cursor->prev = N; // prev new cursor = N, new element before cursor
        // increment cursor index and length
        L->c_index++;
        L->length++;
    }
}
// insertAfter()
// insert new element after cursor
// pre: length()>0, index()>=0
void insertAfter (List L, int data) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    // if cursor is undefined
    if (L->cursor == NULL) {
        printf("List error: calling insertAfter() on undefined cursor\n");
        // exit(1);
    }
    // if cursor = last, call append
    if (L->cursor == L->last) {
        append(L, data);
    }
    // else insert element before cursor
    else {
        Node N = newNode(data);
        L->cursor->next->prev = N; // set cursor as new cursor
        N->next = L->cursor->next; // set new next as cursor next
        N->prev = L->cursor; // set new prec as cursor
        L->cursor->next = N; // element after cursor becomes new cursor
        // = new element after cursor
        // increment length
        L->length++;
    }
}
// deleteFront()
// delete the front element
// pre: length()>0
void deleteFront(List L) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    // else error if length <= 0
    if (length(L) <= 0) {
        printf(" List error: deleteFront() called on empty List\n");
    }
    // if only one element in List, delete
    else {
        if (L->length == 1) {
            Node temp = L->head; // new node is front element
            freeNode(&temp); // free memeory
            L->cursor = NULL; // set cursor undefined
            L->head = NULL;
            L->last = NULL;
            // set cursor index to original state
            L->c_index = -1;
        }
        // otherwise
        else {
            // new Node = front element
            Node temp = L->head;
            L->head = L->head->next; // new front is next element
            // delete front
            L->head->prev = NULL; // element before new head aka front element
            // L->length--;
            // if cursor still defined, decrement index
            if (L->cursor != NULL) {
                L->c_index--;
            }
            freeNode(&temp);
        }
        L->length--;
    }
}
// deleteBack()
// delete the back element
// pre: length()>0
void deleteBack(List L) {
    // precondition if L is empty
    if (L == NULL) {
        printf("List error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    // else error if length <= 0
    if (length(L) <= 0) {
        printf(" List error: deleteBack() called on empty List\n");
    }
    // if only one element in List, delete
    else {
        if (L->length == 1) {
            Node temp = L->head; // new node is front element
            freeNode(&temp); // free memeory
            L->cursor = NULL; // set cursor undefined
            L->head = NULL;
            L->last = NULL;
            // set cursor index to original state
            L->c_index = -1;
        }
        // otherwise
        else {
            // new Node = front element
            Node temp = L->last;
            L->last = L->last->prev; // new front is next element
            // delete front
            L->last->next = NULL; // element before new head aka front element
            // L->length--;
            // cursor index range = length -1
            if (L->c_index == L->length-1) {
                L->c_index = -1;
            }
            freeNode(&temp);
        }
        L->length--;
    }
}
// delete()
// delete cursor element, making cursor undefined
// pre: length()>0, index()>=0
void delete(List L) {
    // precondition
    if (L == NULL) {
        printf("List error: calling delete() on NULL List reference\n");
        exit(1);
    }
    // else error if length <= 0
    if (length(L) <= 0 || L->cursor == NULL) {
        printf(" List error: deleteBack() called on empty List\n");
    }
    // if cursor is at front element, call on deleteFront
    if (L->cursor == L->head) {
        deleteFront(L);
    }
    // if cursor is at back element, call on deleteBack
    else if (L->cursor == L->last) {
        deleteBack(L);
    }
    else {
        Node temp = L->cursor; // create placeholder
        L->cursor->prev->next = L->cursor->next; // new cursor = next cursor
        L->cursor->next->prev = L->cursor->prev; // new prev cursor = prev of next cursor
        freeNode(&temp);
        // make cursor undefined
        L->cursor = NULL;
        // index at original state
        // L->c_index = -1;
        // decrement length
        L->length--;
    }
    // index at original state
    L->c_index = -1;
}


// Other operation -----------------------------------------------------------
// printList()
// prints to file pointed to by out
// string rep of L consisting of space seperated sequence of ints
// front on left
void printList(FILE* out, List L) {
    // Stack.c as reference
    Node N = NULL;
    // precondition
    if (L == NULL) {
        printf("List error: calling printList() on NULL List reference\n");
        exit(1);
    }
    for (N = L->head; N!=NULL; N=N->next) {
        fprintf(out," %d", N->data);
        fprintf(out, " ");
    }
}
// copyList()
// returns new List seperating same integer sequence as L
// cursor in new List is undefined
// state of L unchanged
List copyList(List L) {
    // precondition
    if (L == NULL) {
        printf("List error: calling copyList() on NULL List reference\n");
        exit(1);
    }
    // list copy, create new list
    Node N = L->head;
    List Copy = newList();
    
    if (length(L) > 0) {
        // while list contains something
        
        while ( N != NULL) {
            append(Copy, N->data);
            N = N->next; // traverse through list
        }
    }
    // cursor new List is undefined
//    Copy->cursor = NULL;
    // state unchanged
//    Copy->c_index = -1;
    // return new List
    return Copy;
}
