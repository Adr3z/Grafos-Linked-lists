#include "search.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>

Queue* createQueue() 
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue) {
    if(queue->front == NULL){
        return 1;
    }
    return 0;
}

void enqueue(Queue *queue, Vertex *vertex) 
{
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->vertex = vertex;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Vertex* dequeue(Queue *queue) 
{
    if (isEmpty(queue)) {
        return NULL;
    }

    QueueNode *temp = queue->front;
    Vertex *vertex = temp->vertex;

    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }

    free(temp);
    return vertex;
}


void dfs(Graph *graph, Vertex *start_vertex) 
{
    //caso base
    if (start_vertex == NULL || start_vertex->visited) {
        return;
    }

    start_vertex->visited = 1; 
    printf("%c ", start_vertex->id);

    Edge *current_edge = start_vertex->edge_list;
    while (current_edge != NULL) {
        Vertex *neighbor = current_edge->vertex;
        //caso recursivo
        dfs(graph, neighbor); 
        current_edge = current_edge->next;
    }
}

void bfs(Graph *graph, char start_vertex_id) 
{
    // Encuentra el vértice de inicio
    Vertex *start_vertex = findVertexById(graph, start_vertex_id);
    if (start_vertex == NULL) {
        printf("El vértice de inicio no se encontró en el grafo.\n");
        return;
    }

    // Inicializa una cola para el recorrido BFS
    Queue *queue = createQueue();

    // Marca todos los vértices como no visitados
    Vertex *current_vertex = graph->vertex_list;
    while (current_vertex != NULL) {
        current_vertex->visited = 0;
        current_vertex = current_vertex->next;
    }

    // Marca el vértice de inicio como visitado y encola
    start_vertex->visited = 1;
    enqueue(queue, start_vertex);

    while (isEmpty(queue) == 0) {
        // Desencola un vértice
        Vertex *current_vertex = dequeue(queue);
        printf("%c ", current_vertex->id);

        // Procesa los vértices adyacentes no visitados
        Edge *edge = current_vertex->edge_list;
        while (edge != NULL) {
            Vertex *neighbor = edge->vertex;
            if (!neighbor->visited) {
                neighbor->visited = 1;
                enqueue(queue, neighbor);
            }
            edge = edge->next;
        }
    }

    printf("}\n");

    free(queue);
}
