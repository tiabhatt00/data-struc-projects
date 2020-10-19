/*
 * Tia Bhattacharya
 * rubhatta
 * Graph ADT that represents a graph as an array of Lists
 * Graph.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

// define
#define WHITE 0
#define BLACK 1
#define GRAY  2
// INF, NIL
#define INF -1
//#define NIL 0

// PRIVATE TYPES -------------------------------------
// GraphObj
typedef struct GraphObj {
    // initilaze variables
    List* adj;
    int* color; // 0-white, 1-grey, 2-black
    int* parent;    // parent of vertex
    int* discover;   // discover time
    int* finish;    // finish time
    int order;  // vertices
    int size;   // edges
    // int time;// for Visit()
} GraphObj;

// Constructors-Destructors -------------------------------------
// newGraph()
// creates new graph
Graph newGraph(int n) {
    Graph G = (Graph) malloc(sizeof(struct GraphObj));
    G->adj = (List*) malloc((n + 1) * sizeof(List));
    G->color = (int*) malloc((n + 1) * sizeof(int));
    G->parent = (int*) malloc((n + 1) * sizeof(int));
    G->discover = (int*) malloc((n + 1) * sizeof(int));
    G->finish = (int*) malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; ++i) {
        G->adj[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
    return G;
}
// freeGraph()
// Frees memory associated with *pG
// sets *pG to NULL
void freeGraph(Graph* pG) {
    Graph G = *pG;
    for (int i = 0; i <= G->order; ++i) {
        freeList(&G->adj[i]);
    }
    free(G->adj);
    free(G->color);
    free(G->parent);
    free(G->discover);
    free(G->finish);
    // free(G);
    free(*pG);
    *pG = NULL;
}

// Access Functions -------------------------------------
// getOrder()
// return num of vertices in G
// pre: G != NULL
int getOrder(Graph G) {
    // Error
    if (G == NULL) {
        printf("Graph error: calling getOrder() on NULL Graph\n");
        exit(1);
    }
    return G->order;
}
// getSize()
// return num of edges
int getSize(Graph G) {
    // Error
    if (G == NULL) {
        printf("Graph error: calling getSize() on NULL Graph\n");
        exit(1);
    }
    return G->size;
}
// getParent()
// returns parent of vertex
// Pre: 1 <= u <= n = getOrder(G)
int getParent(Graph G, int u) {
    // Error
    if (G == NULL) {
        printf("Graph error: calling getParent() on NULL Graph\n");
        exit(1);
    }
    // Pre
    int n = getOrder(G);
    if ( u < 1 || u > n ) {
        printf("Graph error: calling getParent() with out of bounds vertex\n");
        exit(1);
    }
    // return
    return G->parent[u];
}
// getDiscover()
// returns discover time
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u) {
    // Error
    if (G == NULL) {
        printf("Graph error: calling getDiscover() on NULL Graph\n");
        exit(1);
    }
    // Pre
    int n = getOrder(G);
    if ( u < 1 || u > n ) {
        printf("Graph error: calling geDiscover() with out of bounds vertex\n");
        exit(1);
    }
    // return
    return G->discover[u];
}
int getFinish(Graph G, int u) {
    // Error
    if (G == NULL) {
        printf("Graph error: calling getFinish() on NULL Graph\n");
        exit(1);
    }
    // Pre
    int n = getOrder(G);
    if ( u < 1 || u > n ) {
        printf("Graph error: calling getFinish() with out of bounds vertex\n");
        exit(1);
    }
    // return
    return G->finish[u];
}

// Manipulation Procedures -------------------------------------
// addArc()
// new directed edge from u to v
// Pre: 1 <= u <= n, 1 <= v <= n
void addArc(Graph G, int u, int v) {
    // Pre
    int n = getOrder(G);
    if(u < 1 || u > n || v < 1 || v > n) {
        printf("Graph Error: calling addArc() with out of bound vertices\n");
        exit(1);
    }
    // after pre
    List adj_u = G->adj[u];
    // moveFront
    moveFront(adj_u);
    
    while(index(adj_u) > -1 && v > get(adj_u)) {
        moveNext(adj_u);
    }
    // if index = -1, append
    if(index(adj_u) == -1){
        append(adj_u, v);
    }
    
    else {
        insertBefore(adj_u, v);
    }
    G->size++;
}
// addEdge()
// inserts new edge
// Pre: 1 <= u <= n, 1 <= v <= n
void addEdge(Graph G, int u, int v) {
    // Pre
    int n = getOrder(G);
    if(u < 1 || u > n || v < 1 || v > n) {
        printf("Graph Error: calling addEdge() with out of bounds vertices\n");
        exit(1);
    }
    
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
// Visit()
// DFS-Visit helper function
// recursive alg on List
// checks all vertices
// impelents time variable
void Visit (Graph G, List S, int u, int *time) {
    // Pre
    if (G == NULL) {
        printf("Graph Error: calling Visit()on NULL graph\n");
        exit(1);
    }
    // set color for vertex
    // while vertex u has just been discovered
    G->color[u] = GRAY;
    // G->time++;  // time = time + 1
    // discover time
    
    G->discover[u] = ++*time;   // u.d = time
    // List adj_u =  G->adj[u];
    // traverse through List
    // List functions , moveTo, moveNext, moveFront, moveBack
    moveFront(G->adj[u]);

    while (index(G->adj[u]) >= 0) {
        // initialize
        int k = get(G->adj[u]);
        // if u.color = WHITE
        if (G->color[k] == WHITE) {
            G->parent[k] = u;
            // call Visit() recursively
            Visit(G, S, k, time);
        }
        // move to  next
        moveNext(G->adj[u]);
    }
    // blacken u since it is finished
    G->color[u] = BLACK;    // u.color = black
    //G->time++;  // time = time + 1
    G->finish[u] = ++*time; // u.f = time
    // G->finish[u] = time++;  // time = time + 1
    prepend(S,u);
}
// DFS()
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
    // Pre
    if (G == NULL) {
        printf("Graph Error: calling DFS()on NULL graph\n");
        exit(1);
    }
    int n = getOrder(G);
    if (length(S) != n) {
        printf("Graph Error: calling DFS()on unequal sizes\n");
        exit(1);
    }
    // for each u
    int i;
    for (i = 1; i <= n; i++) {
        // u.color = WHITE
        G->color[i] = WHITE;
        // u.pi = NIL
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    // time = 0
    int time = 0;
    // traverse list
    moveFront(S);
    // for each u
    while (index(S) >= 0) {
        int u = get(S);
        // if u.color == WHITE
        if (G->color[get(S)] == WHITE) {
            // VISIT()
            // int u = get(S);
            Visit(G, S, u, &time);
        }
        moveNext(S);
    }

    int l = length(S)/2;

    // delete last element
    while (l > 0) {
        deleteBack(S);
        l--;
    }
    // freeList(&time);
}

// Other Functions -------------------------------------
// transpose()
// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
    // Pre
    if (G == NULL) {
        printf("Graph Error: calling traspose()on NULL graph\n");
        exit(1);
    }
    int n = getOrder(G);
    // new Graph
    Graph T = newGraph(n);
    int i;
    for (i = 1; i <= n; i++) {
        List adj_i = G->adj[i];
        // cursor at first, traverse
        moveFront(adj_i);
        // for each u
        while (index(adj_i) >= 0) {
            int u = get(adj_i);
            addArc(T, u, i);
            // move to next
            moveNext(adj_i);
        }
    }
    return T;
}
// copyGraph()
// returns copy of graph
Graph copyGraph(Graph G) {
    // Pre
    if (G == NULL) {
        printf("Graph Error: calling traspose()on NULL graph\n");
        exit(1);
    }
    int n = getOrder(G);
    // new Graph
    Graph New = newGraph(n);
    int i;
    for (i = 1; i <= n; i++) {
        List adj_i = G->adj[i];
        // cursor at first, traverse
        moveFront(adj_i);
        // for each u
        while (index(adj_i) >= 0) {
            int u = get(adj_i);
            addArc(New, i, u);
            // move to next
            moveNext(adj_i);
        }
    }
    return New;
}
// printGraph()
// prints to FILE out
void printGraph(FILE* out , Graph G) {
        if (G == NULL) {
            printf("Graph error: calling printGraph() on NULL Graph\n");
            exit(1);
        }
        for (int i = 1; i <= G->order; ++i) {
            fprintf(out, "%d:", i);
    
            int traversed = 0;
            List l = G->adj[i];
            moveFront(l);
            while (traversed < length(l)) {
                fprintf(out, " %d", get(l));
                moveNext(l);
                traversed++;
            }
            if (i != G->order) {
                fprintf(out, "\n");
            }
        }
}

//// printPath()
//// helper for FindPath
//// prints to out
//void printPath(FILE* out, Graph G, int u) {
//    fprintf(out, "\n\n");
//    if (G->distance[u] == INF) {
//        fprintf(out, "The distance from %d to %d is infinity\n", G->source, u);
//        fprintf(out, "No %d-%d path exists\n", G->source, u);
//        return;
//    }
//
//    fprintf(out, "The distance from %d to %d is %d\n", G->source, u,
//            G->distance[u]);
//    fprintf(out, "A shortest %d-%d path is:", G->source, u);
//    List L = newList();
//    getPath(L, G, u);
//    moveFront(L);
//    for (int i = 0; i < length(L); ++i) {
//        fprintf(out, " %d", get(L));
//        moveNext(L);
//    }
//    freeList(&L);
//}
