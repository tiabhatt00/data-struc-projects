/*
 * Tia Bhattacharya
 * rubhatta
 * CSE 101
 * Dec 5, 2019
 * Test Client for Graph
 * GraphTest.c
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
    
    int n = 8;
    
    // new List, Graph
    List new_L = newList();
    Graph new_G = newGraph(n);
    
    for (int i = 1; i <= n; i++) {
        append(new_L, i);
    }
    
    addArc(new_G, 1, 3);
    addArc(new_G, 1, 6);
    addArc(new_G, 2, 4);
    addArc(new_G, 2, 7);
    addArc(new_G, 3, 3);
    addArc(new_G, 3, 8);
    addArc(new_G, 4, 2);
    
    fprintf(stdout, "Vertices in G): %d \n\n", getOrder(G));
    fprintf(stdout, "Adjancency Matrix\n\n\n");
    printGraph(stdout, new_G);
    
    fprintf(stdout, "DFS(): %d \n\n");
    DFS(new_G, new_L);
    
    for(int i = 1; i <= n; i++){
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(new_G, i),
        getFinish(new_G, i), getParent(new_G, i));
    }
    // test transpose and copy
    Graph A = transpose(new_G);
    Graph B = copyGraph(new_G);
    
    // Print
    // Copy
    fprintf(stdout, "\n");
    fprintf(stdout,"Copy: \n\n\n");
    // to out
    printGraph(stdout, B);
    fprintf(stdout, "\n");
    // Transpose
    fprintf(stdout,"Transpose: \n\n\n");
    // to out
    printGraph(stdout, A);
    fprintf(stdout, "\n");
    
    DFS (A, new_L);
    
    // check Stack
    for (int i = 1; i <= n, i++) {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(new_G, i),
        getFinish(new_G, i), getParent(new_G, i));
    }
    // free all memory 
    freeList(&new_L);
    freeGraph(&new_G);
    freeGraph(&A);
    freeGraph(&B);
    return(0);
}
