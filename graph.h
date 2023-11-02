#ifndef GRAPH_H
#define GRAPH_H

typedef char vertex_id_t;

typedef enum gt_enum {
    UNDIRECTED_GRAPH,
    DIRECTED_GRAPH
} graph_type_t;

typedef struct vertex node_vertex;
typedef struct arista node_awn;

struct vertex{
    char id;
    struct vertex *next;
    struct arista *awns;
};

struct arista{
    int w;
    struct arista *next;
    struct vertex *rel;
};

typedef struct{
    int type;
    int num_vertices;
    node_vertex *list;
    int **adj_mat;
}Graph;

//initialize the graph
Graph *init_graph( graph_type_t type);

//initialize the matrix
int **adjacency_matrix( int num_vertices);

//free matrix
void free_mat(int **mat, int num_vertices);

//fre graph
void free_graph(Graph *g);

//free edges list
void free_awns( node_awn *a);

//free vertex
void free_vertex( node_vertex *v);


//main functions
void read_adj_matrix();
void print_adj_list();
void print_dfs();
void print_bfs();
void add_vertex();
void add_edge();
void remove_vertex();
void remove_edge();
void vertex_degree();

#endif
