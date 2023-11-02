#include <stdio.h>
#include "graph.h"

#define DEBUG

typedef enum op_enum {
    READ_ADJ_MATRIX = 1,
    PRINT_ADJ_LIST,
    ADD_VERTEX, 
    ADD_EDGE, 
    REMOVE_VERTEX, 
    REMOVE_EDGE,
    VERTEX_DEGREE,
    PRINT_DFS,
    PRINT_BFS
} operation_t;

int main(void)  {
    freopen("input.txt", "rt", stdin);
    //freopen("output.txt", "rt", stdout);

    graph_type_t graph_type;
    int number_of_operations;
    scanf("%u%d", &graph_type, &number_of_operations);
    Graph *g = createGraph(graph_type);
#ifdef DEBUG
    printf("The graph type is %s\n", 
        graph_type == DIRECTED_GRAPH ? "Directed" : "Undirected");
#endif
    while (number_of_operations--) {
        operation_t op;
        scanf("%u", &op);
        switch (op) {
            case READ_ADJ_MATRIX:
                read_adj_matrix(g);
            break;
            case PRINT_ADJ_LIST:   
                print_adj_list(g);
            break;
            case ADD_VERTEX:    
                add_vertex(g);
            break;
            case ADD_EDGE:      
                add_edge(g);
            break;
            case REMOVE_VERTEX: 
                remove_vertex(g);
            break;
            case REMOVE_EDGE:   
                remove_edge(g);
            break;
            case VERTEX_DEGREE:   
                vertex_degree(g);
            break;
            case PRINT_DFS:
                print_dfs(g);
            break;
            case PRINT_BFS:
                print_bfs(g);
            break;
        }
    }
    destroyGraph(g);
    return 0;
}
