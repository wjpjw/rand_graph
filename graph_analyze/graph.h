#ifndef GRAPH_H_
#define GRAPH_H_
#include "list.h"
typedef struct{
  list_node       node;
  int             v;         // vertices are indexed from 0 to N-1, N is the number of vertices.
}adjacency_list;

typedef struct{
  int             nr_vertices;              
  int             nr_edges;
  adjacency_list *lists;     // each vertice has a adjacency list. list[i] is the list head of the i-th vertice.   
}graph;


void                   free_graph(graph * g);
void                   init_graph(graph* g, int N);
void                   add_edge(graph* g, int v1, int v2);
void                   find_clusters(graph * g);
graph*                 load_graph(char* file_name);
  
  

#endif
