#include <stdio.h>
#include "graph.h"

void read_adj_matrix()
{
    int number_of_vertices, adjacency;
    scanf("%d", &number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)    {
        for (int j = 0; j < number_of_vertices; j++)    {
            scanf("%d", &adjacency);
            // TODO: add edge between 'A'+i and 'A'+j
#ifdef DEBUG
            if (adjacency)  {
                printf("Adding adjacency between %c and %c\n", 'A'+i, 'A'+j);
            }
#endif
        }
    }
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
