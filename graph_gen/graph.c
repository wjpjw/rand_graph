#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

double                 urand(void)
{
  return rand()/(double) RAND_MAX;
}
void                   init_graph(graph* g, int N){
  g->lists=(adjacency_list*) malloc(sizeof(adjacency_list)*N);
  for(int i=0;i<N;i++){
    init(&g->lists[i].node);
  }
  g->nr_edges=0;
  g->nr_vertices=N;
}
void                   add_edge(graph* g, int v1, int v2){
  adjacency_list* al=(adjacency_list*)malloc(sizeof(adjacency_list));
  al->v=v2;
  init(&al->node);
  push_back(&g->lists[v1].node, &al->node);
  g->nr_edges++;
}  
void                   generate_rand_graph(graph* g, double P){
  for(int i=0;i<g->nr_vertices;i++){
    for(int j=i+1;j<g->nr_vertices;j++){
      if(urand()<P){
	add_edge(g, i, j);
      }
    }  
  }  
}  
void                   print_graph(graph*g, char* file_name){
  FILE * pFile;
  pFile = fopen (file_name,"w");
  fprintf (pFile, "Number of vertices:%d\n", g->nr_vertices);
  fprintf (pFile, "Number of edges:%d\n", g->nr_edges);
  for(int i=0;i<g->nr_vertices;i++){
    list_node*head=&g->lists[i].node; 
    fprintf(pFile, "v%d:", i);
    for(list_node* pos=begin(head);not_ended(head, pos);pos=pos->next){
      fprintf(pFile, "%d ", WJP(pos,adjacency_list,node)->v);
    }
    fprintf(pFile, "\n");
  }  
  fclose (pFile);
}  
