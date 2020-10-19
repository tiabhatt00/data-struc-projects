/*
 * Tia Bhattacharya
 * rubhatta
 * CSE 101
 * Nov 29, 2019
 * Test client for Graph.c
 * GraphTest.c
 */
#include <stdio.h>

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {
    int n = 5;
    // new Graph
    Graph G = newGraph(n);
    // add edge
    addEdge(G, 3, 5);
    addEdge(G, 1, 2);
    addEdge(G, 9, 30);

    // print new Graph
    printf("Graph G:\n");
    printGraph(stdout, G);
    // BFS()
    BFS(G, 2);
    List L = newList();
    getPath(L, G, 2);
    // new BFS
    BFS(G, 3);
    List newL = newList();
    getPath(newL, G, 3);
    
    
    // makeNULL
    makeNull(G);
    // result makeNull()
    printf("after makeNull():\n");
    printGraph(stdout, G);
    // test addArc()
    addArc(G, 3, 5);
    addArc(G, 1, 2);
    addArc(G, 9, 30);
    // result addArc
    printf("after addArc\n");
    // print
    printGraph(stdout, G);
    // prints order of graph
    printf("G ORDER %d, size %d\n", getOrder(G), getSize(G));
    
    // free memory
    freeList(&L);
    freeList(&newL);
    freeGraph(&G);
    return (0);
}
