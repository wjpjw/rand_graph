#include "graph.h"
#include <math.h>
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
    int * current_edges = (int*) malloc(sizeof(int) * starting_count);
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
        int number_edges_connected_to = 0;
        
        int max_number_viable_edges = total_number_edges * 2;
        
        while (number_edges_connected_to != starting_count)
        {
            int ne = (int)round(urand() * max_number_viable_edges);
            
            for (int j = 0; j < i; j++)
            {
                int not_already_connected_to_this_edge = 1;
                
                for (int dex = 0; dex < number_edges_connected_to; dex++)
                {
                    if (j == current_edges[dex])
                    {
                        not_already_connected_to_this_edge = 0;
                        break;
                    }
                }

                if (not_already_connected_to_this_edge == 1)
                {
                    ne -= number_edges[j];
                    if (ne <= 0)
                    {
                        max_number_viable_edges -= number_edges[j]; // Can't select this edge no more!
                        current_edges[number_edges_connected_to] = j; // Remember We've Already connected node i to j
                        number_edges_connected_to ++; // Count number of nodes we've connected i too                        

                        add_edge(g, i, j);
                        number_edges[i]++;
                        number_edges[j]++;
                        total_number_edges++;

                        break;
                    }
                }

                
                if (j == i - 1) printf("GOT TO END\n");
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
            fprintf(pFile, " %d,%f", WJP(pos,adjacency_list,node)->v, urand());
            j++;
        }
        fprintf(pFile, "\n");
    }  
    fclose (pFile);
}
