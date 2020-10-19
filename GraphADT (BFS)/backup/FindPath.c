/*
 * Tia Bhattacharya
 * rubhatta
 * CSE 101
 * Nov 29, 2019
 * Client module for List ADT Graph.c
 * FindPath.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

Graph readGraph(FILE *in) {
    int size;
    fscanf(in, "%d", &size);
    Graph G = newGraph(size);
    
    int u, v;
    fscanf(in, "%d %d", &u, &v);
    while (u != 0 && v != 0) {
        addEdge(G, u, v);
        fscanf(in, "%d %d", &u, &v);
    }
    
    return G;
}
void solve(FILE* in, FILE* out) {
    Graph G = readGraph(in);
    printGraph(out, G);
    
    int s, d;
    fscanf(in, "%d %d", &s, &d);
    while (s != 0 && d != 0) {
        BFS(G, s);
        printPath(out, G, d);
        fscanf(in, "%d %d", &s, &d);
    }
}

int main(int argc, char *argv[]) {
    FILE *in, *out;
    
    // conditon
    // command line must have 3 arguements
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing -----------------------------------------------
    // FILE in, input file
    in = fopen(argv[1], "r");   // first arg = input file
    // check contents of input file
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    
    // FILE out, output file
    out = fopen(argv[2], "w");  // second arg = output file
    // check contents of output file
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    solve(in, out);
    fclose(out);
    fclose(in);
}
