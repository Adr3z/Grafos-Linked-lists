#ifndef GRAPH_H
#define GRAPH_H

typedef char vertex_id_t;

typedef enum gt_enum {
    UNDIRECTED_GRAPH,
    DIRECTED_GRAPH
} graph_type_t;

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
