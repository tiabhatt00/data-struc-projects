/*
Tia Bhattacharya
Integer List ADT takes file input-output and execute List.c
Lex.c
*/

// FileIO & charType.c as reference
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 255

int main (int argc, char* argv[]) {
    int n = 0;
    int count = 0;
    FILE *in, *out;
    char line[MAX_LEN];
    
    // conditon
    // command line must have 3 arguements
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    // FILE in
    in = fopen(argv[1], "r");   // first arg = input file
    // check contents of input file
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    // FILE out
    out = fopen(argv[2], "w");  // second arg = output file
    // check contents of output file
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    // read each line of input file
    while (fgets(line, MAX_LEN, in) != NULL) {
        count++;
    }
    
    // move cursor/position indicator to beginning of input file
    // rewind() moves cursor back
    rewind(in);
    
    // char holds each line
    char allLine[count][MAX_LEN];
    // cursor index
    
    while(fgets(line, MAX_LEN, in) != NULL) {
        strcpy(allLine[n], line);
        n++;    // increment
    }
    
    // begin with initially empty list
    List Lex = newList();
    // insert indices one by one into appropriate place
    // insert new element = append
    append(Lex, 0);
    
    // Insertion Sort, for (i = 1; i < n; i++)
    for (int i=1; i<count; i++) {
        // arr[i]
        char *temp = allLine[i];
        int j = i - 1;
        // moveBack, set cursor under front element
        moveBack(Lex);
        // move elements to one position ahead of current
        // strcmp() determines lexicographic ordering of strings
        while (j>=0 && strcmp(temp, allLine[get(Lex)]) <=0) {
            // decrement line
            j--;
            // check at cursor one step forward
            // movePrev()
            movePrev(Lex);
        }
        // if cursor index of List Lex is >= 0,
        // insert new element before cursor
        if (index(Lex) >= 0) {
            insertAfter(Lex, i);
        }
        else {
            // insert before front element
            // prepend()
            prepend(Lex, i);
        }
    }
    
    // cursor moved back to front of Lex
    moveFront(Lex);
    
    // print
    // while index is defined
    while (index(Lex) >= 0) {
        fprintf(out,"%s", allLine[get(Lex)]);
        // move cursor towards back of Lex
        moveNext(Lex);
    }
    
    
    
    // close files
    fclose(in);
    fclose(out);
    // free memory
    freeList(&Lex);
    return(0);
}
