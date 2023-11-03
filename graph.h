#ifndef GRAPH_H
#define GRAPH_H

typedef char vertex_id_t;

typedef enum gt_enum {
    UNDIRECTED_GRAPH,
    DIRECTED_GRAPH
} graph_type_t;

// Estructura para representar una arista
typedef struct Edge {
    struct Vertex *vertex;    // Apuntador al vértice relacionado por la arista
    struct Edge *next;        // Apuntador a la siguiente arista en la lista
} Edge;

// Estructura para representar un vértice
typedef struct Vertex {
    char id;                   // Identificador del vértice
    struct Edge *edge_list;    // Cabecera de la lista de aristas
    struct Vertex *next;       // Apuntador al siguiente vértice
    int visited;               // Auxiliar para los recorridos
} Vertex;

// Estructura para representar el grafo
typedef struct Graph {
    int num_vertices;         // Número de vértices en el grafo
    graph_type_t graph_type;  // Tipo de grafo (no dirigido o dirigido)
    Vertex *vertex_list;      // Lista de vértices
    int **adjacency_matrix;   // Matriz de adyacencia
} Graph;


// Función para crear un grafo
Graph* createGraph(graph_type_t type);

//Crear matriz de adyacencia
int **adj_mat( int num_vertices);

//Imprimir matriz de adyacencia
void printMatrix(int **matrix, int num_vertices);

//generar lista de adyacencias
void create_list(Graph *g, int number_of_vertices);

//liberar la memoria de un grafo y sus elementos
void destroyGraph(Graph *graph);


//main functions
void read_adj_matrix(Graph *g);
void print_adj_list(Graph *g);
void print_dfs(Graph *g);
void print_bfs(Graph *g);
void add_vertex(Graph *g);
void add_edge(Graph *g);
void remove_vertex(Graph *g);
void remove_edge(Graph *g);
void vertex_degree(Graph *g);

#endif
