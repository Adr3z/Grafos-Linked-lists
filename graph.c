#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph *init_graph( graph_type_t type)
{
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->type = type;
    g->list = NULL;
    g->adj_mat = NULL;
    return g;
}

int **adjacency_matrix(int num_vertices) {
    int **matrix = (int **)malloc(num_vertices * sizeof(int *));
    if (matrix) {
        for (int i = 0; i < num_vertices; i++) {
            matrix[i] = (int *)malloc(num_vertices * sizeof(int));
            if (matrix[i]) {
                for (int j = 0; j < num_vertices; j++) {
                    matrix[i][j] = 0;
                }
            } else {
                // Manejar error de asignación de memoria para matriz[i]
                // Puede ser necesario liberar la memoria previamente asignada.
                for (int k = 0; k < i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return NULL; // Devolver NULL en caso de error
            }
        }
        return matrix;
    }
    return NULL; // Devolver NULL en caso de error
}



void free_mat(int **mat, int num_vertices)
{
    for(int i = 0; i < num_vertices; i++){
        free( *(mat + i));
    }
    free(mat);
}

void free_awns(node_awn *a)
{
    while( a != NULL){
        node_awn *tmp = a;
        a = a->next;
        free(tmp);
    }
}

void free_vertex(node_vertex *v)
{
    free_awns(v->awns);
    free(v);
}

void free_graph(Graph *g)
{
    node_vertex *current = g->list;
    while (current != NULL) {
        node_vertex *tmp = current;
        current = current->next; 
        free_vertex(tmp); 
    }
    
    free_mat(g->adj_mat, g->num_vertices);
    free(g);
}

node_awn* create_awn(int weight) 
{
    node_awn *new_awn = (node_awn *)malloc(sizeof(node_awn));
    if (new_awn) {
        new_awn->w = weight;
        new_awn->next = NULL;
        new_awn->rel = NULL;
    }
    return new_awn;
}

node_vertex* create_vertex(char id) 
{
    node_vertex *new_vertex = (node_vertex *)malloc(sizeof(node_vertex));
    if (new_vertex) {
        new_vertex->id = id;
        new_vertex->next = NULL;
        new_vertex->awns = NULL;
    }
    return new_vertex;
}

void add_vertex_to_graph(Graph *g, node_vertex *new_vertex)
 {
    new_vertex->next = g->list;
    g->list = new_vertex;
    g->num_vertices++;
}

void add_awn_to_vertex(node_vertex *vertex, node_awn *new_awn) 
{
    new_awn->next = vertex->awns;
    vertex->awns = new_awn;
}

node_vertex* find_vertex(Graph *g, char id) {
    node_vertex* current = g->list;
    
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL; 
}

void adjacency_list_from_matrix(Graph *g) {
    int num_vertices = g->num_vertices;
    g->list = NULL; 

    node_vertex **current_vertex = &(g->list);

    for (int i = 0; i < num_vertices; i++) {
        node_vertex *vertex = find_vertex(g, i + 'A'); 

        if (vertex == NULL) {
            continue;
        }

        node_awn **current_awn = &(vertex->awns);

        for (int j = 0; j < num_vertices; j++) {
            if (*(*((g->adj_mat) + i) + j) != 0) {
                node_awn *new_awn = create_awn(*(*((g->adj_mat) + i) + j));

                new_awn->rel = find_vertex(g, j + 'A');

                if (new_awn->rel == NULL) {
                    free(new_awn); 
                    continue;
                }
                // Agrega la arista al vértice
                *current_awn = new_awn;
                current_awn = &((*current_awn)->next);
            }
        }

        // Agrega el vértice a la lista de adyacencias
        *current_vertex = vertex;
        current_vertex = &((*current_vertex)->next);
    }
}

//main functions
void read_adj_matrix(Graph *g)
{
    int number_of_vertices, adjacency;
    scanf("%d", &number_of_vertices);
    g->num_vertices = number_of_vertices;
    g->adj_mat = adjacency_matrix(number_of_vertices);

    for (int i = 0; i < number_of_vertices; i++)    {
        for (int j = 0; j < number_of_vertices; j++)    {
            scanf("%d", &adjacency);
            *(*((g->adj_mat) + i) + j) = adjacency;
            // TODO: add edge between 'A'+i and 'A'+j
#ifdef DEBUG
            if (adjacency)  {
                printf("Adding adjacency between %c and %c\n", 'A'+i, 'A'+j);
            }
#endif
        }
    }
    adjacency_list_from_matrix(g);
}

void print_adj_list()
{
    printf("\nThe graph's adjacency list is:\n");
    printf("------------------------------\n");
    // TODO: print adjacency list
}

void print_dfs()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nThe DFS from vertex with id = %c is: {", vertex_id);
    // TODO: print DFS from vertex id
    printf("}\n");
}

void print_bfs()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nThe BFS from vertex with id = %c is: {", vertex_id);
    // TODO: print BFS from vertex id
    printf("}\n");
}

void add_vertex()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nAdding vertex with id = %c\n", vertex_id);
    // TODO: Add the vertex only if doesn't exist
}

void add_edge()
{
    vertex_id_t vertex_u, vertex_v;
    scanf("\n%c %c", &vertex_u, &vertex_v);
    printf("\nAdding edge between the vertices %c and %c\n", vertex_u, vertex_v);
    // TODO: Find the vertices and add them if don't exist yet
    // TODO: Add edge between vertices
}

void remove_vertex()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    printf("\nRemoving vertex with id = %c\n", vertex_id);
    // TODO: Remove vertex only if exists
}

void remove_edge()
{
    vertex_id_t vertex_u, vertex_v;
    scanf("\n%c %c", &vertex_u, &vertex_v);
    printf("\nRemoving edge between the vertices %c and %c\n", vertex_u, vertex_v);
    // TODO: Find the vertices and remove the edge between them
}

void vertex_degree()
{
    vertex_id_t vertex_id;
    scanf("\n%c", &vertex_id);
    // TODO: calculate the vertex degree
    int degree = 0;
    printf("\nThe vertex %c has degree = %d\n", vertex_id, degree);
}
