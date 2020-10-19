/*
 * Tia Bhattacharya
 * rubhatta
 * CSE 101
 * Nov 29, 2019
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
#define NIL 0

// PRIVATE TYPES -------------------------------------
// GraphObj
typedef struct GraphObj {
    // initilaze variables
    List* adj;
    int* color; // 0-white, 1-grey, 2-black
    int* parent;
    int* distance;
    int order;
    int size;
    int source;
} GraphObj;

// Constructors-Destructors -------------------------------------
// newGraph()
// creates new graph
Graph newGraph(int n) {
    Graph G = (Graph) malloc(sizeof(struct GraphObj));
    G->adj = (List*) malloc((n + 1) * sizeof(List));
    G->color = (int*) malloc((n + 1) * sizeof(int));
    G->parent = (int*) malloc((n + 1) * sizeof(int));
    G->distance = (int*) malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; ++i) {
        G->adj[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
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
    free(G->distance);
    // free(G);
    free(*pG);
    *pG = NULL;
}
// getOrder()
// returns field values
int getOrder(Graph G) {
    // pre G != NULL
    if (G == NULL) {
        printf("Graph error: calling getOrder() on NULL Graph\n");
        exit(1);
    }
    return G->order;
}
// getSize()
// returns field values
int getSize(Graph G) {
    // pre G != NULL
//    if (G == NULL) {
//        printf("Graph error: calling getSize() on NULL Graph\n");
//        exit(1);
//    }
    return G->size;
}
// getSource()
// returns source vertex mosty recently used in BFS()
// NIL if BFS() not called
int getSource(Graph G) {
    // pre G != NULL
    if (G == NULL) {
        printf("Graph error: calling getSource() on NULL Graph\n");
        exit(1);
    }
    return G->source;
}
// getParent()
// return parent vertex u in BF tree
// Pre:1 < u < getOrder(G)
int getParent(Graph G, int u) {
    // pre G != NULL
    if (G == NULL) {
        printf("Graph error: calling getParent() on NULL Graph\n");
        exit(1);
    }
    // Pre:1 <= u <= getOrder(G)
    if ( u < 1 || u > getOrder(G)) {
        printf("Graph error: calling getParent() with out of bounds vertex\n");
        exit(1);
    }
    
     return G->parent[u];
}
// getDist()
// return distance from most recent BFS source to u
// return INF if BFS() not called
// Pre:1 < u < getOrder(G)
int getDist(Graph G, int u) {
    // pre G != NULL
    if (G == NULL) {
        printf("Graph error: calling getDist() on NULL Graph\n");
        exit(1);
    }
    // Pre:1 <= u <= getOrder(G)
    if ( u < 1 || u > getOrder(G)) {
        printf("Graph error: calling getDist() with out of bounds vertex\n");
        exit(1);
    }
    
    // INF if BFS() not called
    if (getSource(G) == NIL) {
        return INF;
    }
    return G->distance[u];  // return
}
// getPath()
// appends to List L vertices of a shortest path in G from source to u
// appends to L the value NIL if no such path exists
// pre: getSource(G)!=NIL
// Pre:1 < u < getOrder(G)
void getPath(List L, Graph G, int u) {
    // getSource(G)!=NIL
    if (getSource(G) == NIL) {
        printf("Graph Error: BFS must be called before getPath() is called");
        return;
    }
    // pre G != NULL
    if (G == NULL) {
        printf("Graph error: calling getPath() on NULL Graph\n");
        exit(1);
    }
    // Pre:1 <= u <= getOrder(G)
    if ( u < 1 || u > getOrder(G)) {
        printf("Graph error: calling getPath() with out of bounds vertex\n");
        exit(1);
    }
    // after pre
    if (getSource(G) == u) {
        append(L, u);
        return;
    }
    if (G->parent[u] == NIL) {
        append(L, NIL);
        return;
    }
    
    while (u != NIL) {
        prepend(L, u);
        u = G->parent[u];
    }
}
// makeNULL()
// deletes all edge of G
void makeNull(Graph G) {
    for (int i = 0; i <= G->order; ++i) {
        while (length(G->adj[i]) > 0) {
            deleteBack(G->adj[i]);
        }
    }
}
// addEdge()
// inserts a new edge joining u to v
void addEdge(Graph G, int u, int v) {
    // List adj_u = G->adj[u];
    // Pre: u & v are >= 1, <= getOrder(G)
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addEdge() with out of bounds vertex vertices\n");
        exit(1);
    }
    
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
// addArc()
// inserts a new directed edge from u to v
void addArc(Graph G, int u, int v) {
    // Pre: u & v are >= 1, <= getOrder(G)
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addArc() with with out of bounds vertex verticiess\n");
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
// BFS()
// runs BFS on graph
void BFS(Graph G, int s) {
    // preprocess
    G->source = s;
    for (int i = 1; i <= G->order; ++i) {
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    
    List queue = newList();
    append(queue, s);
    G->color[s] = 1;
    G->distance[s] = 0;
    
    while (length(queue) != 0) {
        int v = front(queue);
        deleteFront(queue);
        G->color[v] = 2;
        G->distance[v] = G->distance[G->parent[v]] + 1;
        
        int traversed = 0;
        List neighbors = G->adj[v];
        moveFront(neighbors);
        while (traversed < length(neighbors)) {
            int u = get(neighbors);
            if (G->color[u] == 0) {
                append(queue, u);
                G->color[u] = 1;
                G->parent[u] = v;
            }
            moveNext(neighbors);
            ++traversed;
        }
    }
    
    freeList(&queue);
}
// printPath()
// helper for FindPath
// prints to out
void printPath(FILE* out, Graph G, int u) {
    fprintf(out, "\n\n");
    if (G->distance[u] == INF) {
        fprintf(out, "The distance from %d to %d is infinity\n", G->source, u);
        fprintf(out, "No %d-%d path exists\n", G->source, u);
        return;
    }
    
    fprintf(out, "The distance from %d to %d is %d\n", G->source, u,
            G->distance[u]);
    fprintf(out, "A shortest %d-%d path is:", G->source, u);
    List L = newList();
    getPath(L, G, u);
    moveFront(L);
    for (int i = 0; i < length(L); ++i) {
        fprintf(out, " %d", get(L));
        moveNext(L);
    }
    freeList(&L);
}
// printGraph()
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; ++i) {
        fprintf(out, "%d:", i);
        
        int traversed = 0;
        List l = G->adj[i];
        moveFront(l);
        while (traversed < length(l)) {
            fprintf(out, " %d", get(l));
            moveNext(l);
            ++traversed;
        }
        if (i != G->order) {
            fprintf(out, "\n");
        }
    }
}
