#ifndef GRAPH_H
#define GRAPH_H


//Inicié el trabajo desde 0 para ver si podía arreglar la fuga de memoria y otros problemas 
//Spoiler: no funcionó
//Prácticamente todas las funciones son iguales pero con cambios en los nombres de variables

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
    char id;                   // Identificador del vértice (puede ser una letra)
    struct Edge *edge_list;    // Cabecera de la lista de aristas
    struct Vertex *next; 
    int visited;     // Apuntador al siguiente vértice
} Vertex;

// Estructura para representar el grafo
typedef struct Graph {
    int num_vertices;         // Número de vértices en el grafo
    graph_type_t graph_type;  // Tipo de grafo (no dirigido o dirigido)
    Vertex *vertex_list;      // Lista de vértices
    int **adjacency_matrix;   // Matriz de adyacencia (solo para referencia)
} Graph;

// Función para crear un grafo
Graph* createGraph(graph_type_t type);

// Función para liberar la memoria de un grafo y sus elementos
void destroyGraph(Graph *graph);

// Función para agregar un vértice al grafo
void addVertex(Graph *graph, char id);

// Función para agregar una arista a un vértice
void addEdgeToVertex(Vertex *vertex, Vertex *neighbor);

// Función para encontrar un vértice en el grafo por su identificador
Vertex* findVertexByChar(Graph *graph, char id);

//Crear matriz de adyacencia
int **adj_mat( int num_vertices);

//liberar vertices
void free_vertex(Vertex *vertex);

//liberar aristas
void free_edges(Edge *edge);

//crear un vertice
Vertex *create_Vertex(char id);

//crear una arista
Edge *create_Edge(Vertex *rel);

//generar lista de adyacencias
void create_list(Graph *g, int number_of_vertices);

void dfs(Graph *graph, Vertex *start_vertex);

//main functions
void read_adj_matrix(Graph *g);
void print_adj_list(Graph *g);
void print_dfs(Graph *g);
void print_bfs();
void add_vertex();
void add_edge();
void remove_vertex();
void remove_edge();
void vertex_degree(Graph *g);

#endif
