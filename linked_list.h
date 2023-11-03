#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>
#include "graph.h"

//crear una arista
Edge *create_Edge(Vertex *rel);

//crear un vertice
Vertex *create_Vertex(char id);

// Función para agregar una arista a un vértice
void addEdgeToVertex(Vertex *vertex, Vertex *neighbor);

//agregar un vértice al grafo
void addVertex(Graph *graph, char id);

//encontrar un vértice en el grafo por su identificador
Vertex* findVertexById(Graph *graph, char id);

//eliminar una arista
void removeEdgeFromVertex(Vertex *vertex, Vertex *neighbor);

//eliminar las aristas entrantes de otros vértices
void removeIncomingEdges(Graph* graph, Vertex* target_vertex);

//liberar aristas
void free_edges(Edge *edge);

//liberar vertices
void free_vertex(Vertex *vertex);

#endif
