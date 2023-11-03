#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "linked_list.h"
#include "search.h"

Graph* createGraph(graph_type_t type) 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph != NULL) {
        graph->num_vertices = 0; 
        graph->graph_type = type;
        graph->vertex_list = NULL;
        graph->adjacency_matrix = NULL;
    }
    return graph;
}

int **adj_mat(int num_vertices)
{
    int **mat = (int **)malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++) {
        *(mat + i) = (int *)malloc(num_vertices * sizeof(int));
        for (int j = 0; j < num_vertices; j++) {
            *(*(mat + i) + j) = 0;
        }
    }
    return mat;
}

void printMatrix(int **matrix, int num_vertices) 
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
    //Se añaden todos los vértices
    for (int i = 0; i < number_of_vertices; i++) {
        char vertex_id = 'A' + i;
        addVertex(g, vertex_id);
    }
    
    //Se añaden las aristas a las listas de los vértices
    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = i; j < number_of_vertices; j++) {
            int adjacency = *((*(g->adjacency_matrix + i)) + j);
            if (adjacency) {
                char from = 'A' + i;
                char to = 'A' + j;

                Vertex *from_vertex = findVertexById(g, from);
                Vertex *to_vertex = findVertexById(g, to);

                if (from_vertex != NULL && to_vertex != NULL) {
                    addEdgeToVertex(from_vertex, to_vertex);

                    if (g->graph_type == 1) {
                        // se añade la arista para grafos no dirigidos
                        addEdgeToVertex(to_vertex, from_vertex);
                    }
                }
            }
        }
    }
}

void destroyGraph(Graph* graph) 
{
    if (graph == NULL) {
        return;
    }

    //Liberar la matriz
    if (graph->adjacency_matrix != NULL) {
        for (int i = 0; i < graph->num_vertices; i++) {
            free(*(graph->adjacency_matrix + i));
        }
        free(graph->adjacency_matrix);
    }

    // Liberar los vértices y las aristas
    Vertex* current_vertex = graph->vertex_list;
    free_vertex(current_vertex);

    // Liberar la estructura del grafo
    free(graph);
}


//main functions
void read_adj_matrix(Graph *g)
{
    int number_of_vertices;
    scanf("%d", &number_of_vertices);

    //lectura de la matriz
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

    Vertex *start_vertex = findVertexById(g, vertex_id);
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

void print_bfs(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nThe BFS from vertex with id = %c is: {", vertex_id);
    bfs(g, vertex_id);
}

void add_vertex(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nAdding vertex with id = %c\n", vertex_id);
     if (findVertexById(g, vertex_id) != NULL) {
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

    Vertex *u_vertex = findVertexById(g, vertex_u);
    Vertex *v_vertex = findVertexById(g, vertex_v);

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
        if (g->graph_type == 1) {
            addEdgeToVertex(v_vertex, u_vertex);
        }
    } 
}

void remove_vertex(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nRemoving vertex with id = %c\n", vertex_id);
    Vertex *vertex_to_remove = findVertexById(g, vertex_id);
    if (vertex_to_remove == NULL) {
        printf("El vértice %c no se encontró en el grafo.\n", vertex_id);
        return;
    }

    Vertex* current_vertex = g->vertex_list;
    Vertex* prev_vertex = NULL;

    while (current_vertex != NULL && current_vertex->id != vertex_id) {
        prev_vertex = current_vertex;
        current_vertex = current_vertex->next;
    }

    if (current_vertex == NULL) {
        return;
    }

    free_edges(current_vertex->edge_list);

    removeIncomingEdges(g, current_vertex);

    if (prev_vertex == NULL) {
        g->vertex_list = current_vertex->next;
    } else {
        prev_vertex->next = current_vertex->next;
    }
    free(current_vertex);

    g->num_vertices--;
}

void remove_edge(Graph *g)
{
    vertex_id_t vertex_u, vertex_v;
    scanf("\n%c %c", &vertex_u, &vertex_v);
    printf("\nRemoving edge between the vertices %c and %c\n", vertex_u, vertex_v);
    Vertex *u_vertex = findVertexById(g, vertex_u);
    Vertex *v_vertex = findVertexById(g, vertex_v);

    if (u_vertex != NULL && v_vertex != NULL) {
        // Actualiza la matriz de adyacencia si es un grafo no dirigido
        if (g->graph_type == 1) {
            int u_index = vertex_u - 'A';
            int v_index = vertex_v - 'A';
            *((*(g->adjacency_matrix + u_index)) + v_index) = 0;
            *((*(g->adjacency_matrix + v_index)) + u_index) = 0;
        }

        // Elimina la arista de los vértices
        removeEdgeFromVertex(u_vertex, v_vertex);

        // Si es un grafo no dirigido, elimina la arista en la otra dirección
        if (g->graph_type == 1) {
            removeEdgeFromVertex(v_vertex, u_vertex);
        }
    }
}

void vertex_degree(Graph *g)
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    Vertex *vertex = findVertexById(g, vertex_id);
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
