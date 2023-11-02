#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

Graph* createGraph(graph_type_t type) 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = 0; 
    graph->graph_type = type;
    graph->vertex_list = NULL;
    graph->adjacency_matrix = NULL;
    return graph;
}

int **adj_mat(int num_vertices)
{
    int **mat = (int**)malloc(num_vertices * sizeof(int*));
    for(int i = 0; i < num_vertices; i++){
        *(mat + i) = (int*)malloc(num_vertices * sizeof(int));
        for(int j = 0; j < num_vertices; j++){
            *(*(mat +i) + j) = 0;
        }
    }
    return mat;
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

void free_edges(Edge *edge)
{
    while (edge != NULL) {
        Edge* next_edge = edge->next;
        free(edge);
        edge = next_edge;
    }
}

void destroyGraph(Graph* graph) 
{
    if (graph == NULL) {
        return;
    }
    if (graph->adjacency_matrix != NULL) {
        for (int i = 0; i < graph->num_vertices; i++) {
            free(*(graph->adjacency_matrix + i));
        }
    }

    // Liberar los vértices y las aristas
    Vertex* current_vertex = graph->vertex_list;
    free_vertex(current_vertex);

    // Liberar la estructura del grafo
    free(graph);
}

Vertex* findVertexByChar(Graph* graph, char id) 
{
    Vertex* current_vertex = graph->vertex_list;
    while (current_vertex != NULL) {
        if (current_vertex->id == id) {
            return current_vertex;
        }
        current_vertex = current_vertex->next;
    }
    return NULL;  // El vértice no se encontró en el grafo
}

Vertex *create_Vertex(char id)
{
    Vertex* new_vertex = (Vertex*)malloc(sizeof(Vertex));
    new_vertex->id = id;
    new_vertex->edge_list = NULL;
    new_vertex->next = NULL;
    return new_vertex;
}

Edge *create_Edge(Vertex *rel)
{
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->vertex = rel;
    new_edge->next = NULL;
    return new_edge;
}

void addEdgeToVertex(Vertex* vertex, Vertex* neighbor) 
{

     Edge* new_edge = create_Edge(neighbor);

    // Agregar la arista al final de la lista de aristas del vértice
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

    // Agregar el vértice al final de la lista de vértices
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

void printMatrix(int** matrix, int num_vertices) 
{
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void create_list(Graph *g, int number_of_vertices)
{
    for (int i = 0; i < number_of_vertices; i++) {
        char vertex_id = 'A' + i;
        addVertex(g, vertex_id);
    }

    // Actualizar las listas de adyacencia
     for (int i = 0; i < number_of_vertices; i++) {
        for (int j = i; j < number_of_vertices; j++) {
            int adjacency = *((*(g->adjacency_matrix + i)) + j);
            if (adjacency) {
                char from = 'A' + i;
                char to = 'A' + j;

                Vertex *from_vertex = findVertexByChar(g, from);
                Vertex *to_vertex = findVertexByChar(g, to);

                if (from_vertex != NULL && to_vertex != NULL) {
                    addEdgeToVertex(from_vertex, to_vertex);

                    if (g->graph_type == UNDIRECTED_GRAPH && i != j) {
                        //grafos no dirigidos
                        addEdgeToVertex(to_vertex, from_vertex);
                    }
                }
            }
        }
    }
}

void dfs(Graph *graph, Vertex *start_vertex) 
{
    if (start_vertex == NULL || start_vertex->visited) {
        return;
    }

    start_vertex->visited = 1; // Marcar el vértice como visitado
    printf("%c ", start_vertex->id);

    Edge *current_edge = start_vertex->edge_list;
    while (current_edge != NULL) {
        Vertex *neighbor = current_edge->vertex;
        dfs(graph, neighbor); // Recursivamente visitar los vértices adyacentes no visitados
        current_edge = current_edge->next;
    }
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
            free(current_edge); // Libera la memoria de la arista eliminada
            return;
        }

        prev_edge = current_edge;
        current_edge = current_edge->next;
    }
}

//main functions
void read_adj_matrix(Graph *g)
{
    int number_of_vertices;
    scanf("%d", &number_of_vertices);
    g->adjacency_matrix = adj_mat(number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = 0; j < number_of_vertices; j++)   {
            scanf("%d", (*(g->adjacency_matrix + i) + j));

#ifdef DEBUG
#endif
        }
    }
    create_list(g, number_of_vertices);
}

void print_adj_list(Graph *g)
{
    printf("\nThe graph's adjacency list is:\n");
    printf("------------------------------\n");
    Vertex* current_vertex = g->vertex_list;
    while (current_vertex != NULL) {
        printf("%c", current_vertex->id);
        Edge* current_edge = current_vertex->edge_list;
        while (current_edge != NULL) {
            printf(" %c", current_edge->vertex->id);
            current_edge = current_edge->next;
        }
        printf("\n");
        current_vertex = current_vertex->next;
    }
}

void print_dfs(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nThe DFS from vertex with id = %c is: {", vertex_id);
    Vertex *start_vertex = findVertexByChar(g, vertex_id);
    if (start_vertex != NULL) {
        Vertex *current_vertex = g->vertex_list;
        while (current_vertex != NULL) {
            current_vertex->visited = 0;
            current_vertex = current_vertex->next;
        }
        dfs(g, start_vertex);
        printf("}\n");
    } else {
        printf("Vértice %c no encontrado en el grafo.\n", vertex_id);
    }
}

void print_bfs()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nThe BFS from vertex with id = %c is: {", vertex_id);
    // TODO: print BFS from vertex id
    printf("}\n");
}

void add_vertex(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nAdding vertex with id = %c\n", vertex_id);
     if (findVertexByChar(g, vertex_id) != NULL) {
        printf("El vértice %c ya existe en el grafo.\n", vertex_id);
        return;
    }

    addVertex(g, vertex_id);
}

void add_edge(Graph *g)
{
    vertex_id_t vertex_u, vertex_v;
    scanf("\n%c %c", &vertex_u, &vertex_v);
    printf("\nAdding edge between the vertices %c and %c\n", vertex_u, vertex_v);
    Vertex *u_vertex = findVertexByChar(g, vertex_u);
    Vertex *v_vertex = findVertexByChar(g, vertex_v);

    if (u_vertex != NULL && v_vertex != NULL) {
        // Actualiza la matriz de adyacencia si es un grafo no dirigido
        if (g->graph_type == UNDIRECTED_GRAPH) {
            int u_index = vertex_u - 'A';
            int v_index = vertex_v - 'A';
            *((*(g->adjacency_matrix + u_index)) + v_index) = 1;
            *((*(g->adjacency_matrix + v_index)) + u_index) = 1;
        }

        // Agrega la arista a los vértices
        addEdgeToVertex(u_vertex, v_vertex);

        // Si es un grafo no dirigido, agrega la arista en la otra dirección
        if (g->graph_type == UNDIRECTED_GRAPH) {
            addEdgeToVertex(v_vertex, u_vertex);
        }
    } 
}

void remove_vertex()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nRemoving vertex with id = %c\n", vertex_id);
    // TODO: Remove vertex only if exists
}

void remove_edge(Graph *g)
{
    vertex_id_t vertex_u, vertex_v;
    scanf("\n%c %c", &vertex_u, &vertex_v);
    printf("\nRemoving edge between the vertices %c and %c\n", vertex_u, vertex_v);
    Vertex *u_vertex = findVertexByChar(g, vertex_u);
    Vertex *v_vertex = findVertexByChar(g, vertex_v);

    if (u_vertex != NULL && v_vertex != NULL) {
        // Actualiza la matriz de adyacencia si es un grafo no dirigido
        if (g->graph_type == UNDIRECTED_GRAPH) {
            int u_index = vertex_u - 'A';
            int v_index = vertex_v - 'A';
            *((*(g->adjacency_matrix + u_index)) + v_index) = 0;
            *((*(g->adjacency_matrix + v_index)) + u_index) = 0;
        }

        // Elimina la arista de los vértices
        removeEdgeFromVertex(u_vertex, v_vertex);

        // Si es un grafo no dirigido, elimina la arista en la otra dirección
        if (g->graph_type == UNDIRECTED_GRAPH) {
            removeEdgeFromVertex(v_vertex, u_vertex);
        }
    }
}

void vertex_degree(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    Vertex *vertex = findVertexByChar(g, vertex_id);
    if (vertex == NULL) {
        printf("Vértice %c no encontrado en el grafo.\n", vertex_id);
    }

    int degree = 0;
    Edge *current_edge = vertex->edge_list;
    while (current_edge != NULL) {
        degree++;
        current_edge = current_edge->next;
    }

    printf("\nThe vertex %c has degree = %d\n", vertex_id, degree);
}
