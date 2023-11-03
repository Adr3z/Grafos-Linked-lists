#include "linked_list.h"
#include "graph.h"

Edge *create_Edge(Vertex *rel)
{
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->vertex = rel;
    new_edge->next = NULL;
    return new_edge;
}

Vertex *create_Vertex(char id)
{
    Vertex* new_vertex = (Vertex*)malloc(sizeof(Vertex));
    new_vertex->id = id;
    new_vertex->edge_list = NULL;
    new_vertex->next = NULL;
    return new_vertex;
}

void addEdgeToVertex(Vertex* vertex, Vertex* neighbor) 
{
    Edge* new_edge = create_Edge(neighbor);

    if (vertex->edge_list == NULL) {
        vertex->edge_list = new_edge;
    } else {
        Edge* current_edge = vertex->edge_list;
        while (current_edge->next != NULL) {
            current_edge = current_edge->next;
        }
        current_edge->next = new_edge;
    }
}

void addVertex(Graph* graph, char id) 
{
    Vertex* new_vertex = create_Vertex(id);

    if (graph->vertex_list == NULL) {
        graph->vertex_list = new_vertex;
    } else {
        Vertex* current_vertex = graph->vertex_list;
        while (current_vertex->next != NULL) {
            current_vertex = current_vertex->next;
        }
        current_vertex->next = new_vertex;
    }

    graph->num_vertices++;
}

Vertex* findVertexById(Graph* graph, char id) 
{
    Vertex* current_vertex = graph->vertex_list;
    while (current_vertex != NULL) {
        if (current_vertex->id == id) {
            return current_vertex;
        }
        current_vertex = current_vertex->next;
    }
    return NULL;  
}

void removeEdgeFromVertex(Vertex *vertex, Vertex *neighbor) 
{
    if (vertex == NULL || neighbor == NULL) {
        return; // Verifica si los vértices son válidos
    }

    Edge *current_edge = vertex->edge_list;
    Edge *prev_edge = NULL;

    while (current_edge != NULL) {
        if (current_edge->vertex == neighbor) {
            // Encuentra la arista que conduce a la relacion y la elimina
            if (prev_edge == NULL) {
                // Si es la primera arista en la lista
                vertex->edge_list = current_edge->next;
            } else {
                prev_edge->next = current_edge->next;
            }
            free(current_edge); 
            return;
        }

        prev_edge = current_edge;
        current_edge = current_edge->next;
    }
}

void removeIncomingEdges(Graph* graph, Vertex* target_vertex) 
{
    Vertex* current_vertex = graph->vertex_list;

    while (current_vertex != NULL) {
        if (current_vertex != target_vertex) {
            removeEdgeFromVertex(current_vertex, target_vertex);
        }
        current_vertex = current_vertex->next;
    }
}

void free_edges(Edge *edge)
{
    while (edge != NULL) {
        Edge* next_edge = edge->next;
        free(edge);
        edge = next_edge;
    }
}


void free_vertex(Vertex *vertex)
{
     while (vertex != NULL) {
        Vertex* next_vertex = vertex->next;
        Edge* current_edge = vertex->edge_list;
        free_edges(current_edge);
        free(vertex);
        vertex = next_vertex;
    }
}
