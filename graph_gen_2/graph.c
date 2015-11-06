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
void                   generate_rand_graph(graph* g, int starting_count){
    
    int * number_edges = (int*) malloc(sizeof(int) * g->nr_vertices);
    int total_number_edges = 0;
    
    for (int i=0; i<g->nr_vertices; i++)
    {
        number_edges[i] = 0;
    }

    for (int i=0; i<starting_count; i++)
    {
        for(int j=i+1; j<starting_count; j++)
        {
            add_edge(g, i, j);
            number_edges[i]++;
            number_edges[j]++;
            total_number_edges++;
        }
    }

    for (int i=starting_count;i<g->nr_vertices;i++)
    {
        for(int j=0; j < i;j++)
        {
            if(urand() * total_number_edges < number_edges[j])
            {
                add_edge(g, i, j);
                number_edges[i]++;
                number_edges[j]++;
                total_number_edges++;
            }
        }  
    }
    
    free(number_edges);
}
void                   print_graph(graph*g, char* file_name){
    FILE * pFile;
    pFile = fopen (file_name,"w");
    fprintf (pFile, "Number of vertices:%d\n", g->nr_vertices);
    fprintf (pFile, "Number of edges:%d\n", g->nr_edges);
    for(int i=0;i<g->nr_vertices;i++)
    {
        list_node*head=&g->lists[i].node;
        fprintf(pFile, "v%d:", i);
        int j = 0;
        for(list_node* pos=begin(head);not_ended(head, pos);pos=pos->next)
        {
            if (j != 0) fprintf(pFile, ",");
            fprintf(pFile, " %d, %f", WJP(pos,adjacency_list,node)->v, urand());
            j++;
        }
        fprintf(pFile, "\n");
    }  
    fclose (pFile);
}
