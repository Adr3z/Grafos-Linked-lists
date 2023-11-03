#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

//Estructuras para el bfs
typedef struct QueueNode {
    Vertex *vertex;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;


//crear una cola
Queue* createQueue();

//revisar si la cola está vacía
int isEmpty(Queue *queue);

//agregar un elemento a la cola
void enqueue(Queue *queue, Vertex *vertex);

//eliminar un elemento de la cola
Vertex* dequeue(Queue *queue);

//recorrido dfs
void dfs(Graph *graph, Vertex *start_vertex);

//recorrido bfs
void bfs(Graph *graph, char start_vertex_id);

#endif
