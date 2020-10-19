/*
 * Tia Bhattacharya
 * rubhatta
 * Client file for pa5
 * FindComponents
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"

#define MAX_LEN 255

int main(int argc, char * argv[]){
    FILE *in, *out;
    char line[MAX_LEN];
    // int s = 0;
    // conditon
    // command line must have 3 arguements
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing -----------------------------------------------
    // FILE in, input file
    in = fopen(argv[1], "r");   // first arg = input file
    // FILE out, output file
    out = fopen(argv[2], "w");  // second arg = output file
    // check contents of output file
    // check contents of input file
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // call max
    fgets(line, MAX_LEN, in);
    int k = 0;
    sscanf(line, "%d", &k);

    // create new List
    List N = newList();
    // for each u
    for (int i = 1; i <= k; i++) {
        append(N,i);
    }

    // create new Graph
    Graph new_G = newGraph(k);
    // while the in file contains something
    while (fgets(line, MAX_LEN, in) != NULL) {
        int a,b = 0;
        // scan line
        sscanf (line, "%d %d", &a, &b);
        // if both a and b equal 0
        // break
        if ( a == 0 && b == 0) {
            // break
            break;
        }
        // new directed edge for new G
        addArc(new_G, a, b);
    }
    // print text to out file
    // fprintf(out, "Adjacency list representation of G:\n");
    // printGraph(out, new_G);
    // fprintf(out, "\n");

    // implement DFS()
    DFS(new_G, N);
    // transpose
    Graph trans = transpose(new_G); // make new graph
    int s = 0;
    // DFS on transposed Graph
    DFS(trans, N);
    // moveFront
    moveFront(N);

    // while list has something
    while (index(N) >= 0) {
        if(getParent(trans, get(N)) == NIL) {
            s++;
            // on to next
            // moveNext(N);
        }
        moveNext(N);
    }

    // for each u
    // int get_O = getOrder(transposed);
    // for (int i = 0; i <= get_O; i++) {
    //
    // if (
    // }

    // new List
    List new_L[s];
    // for each u
    for (int i = 0; i < s; i++) {
        new_L[i] = newList();   // add new List
    }

    // moveFront
    moveFront(N);

    int j = s;
    // while list contains something
    while (index(N) >= 0) {
        if(getParent(trans, get(N)) == NIL) {
            --j;
        }
        // if vertex l = s, then break
        if ( j == s) {
            break;
        }
        append(new_L[j], get(N));
        // on to next
        moveNext(N);
    }

    // PRINT TEXT to out file
    // Adj list rep
    fprintf(out, "Adjacency list representation of G:\n");
    // to out
    printGraph(out, new_G);
    // "contains..."
    fprintf(out, "\nG contains %d strongly connected components:", s);

    int c;
    // for each u
    for(c = 0; c < s; c++) {
        // COMPONENT..
        fprintf(out, "\nComponent %d: ", (c + 1));
        // to out
        printList(out, new_L[c]);
        // free memory
        freeList(&(new_L[c]));
    }
    // add line
    fprintf(out, "\n");

    // free all memory
    freeGraph(&new_G);
    freeGraph(&trans);
    freeList(&N);

    // close both in and out files
    fclose(in);
    fclose(out);
    return(0);
}
