#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

//valgrind --dsymutil=yes --leak-check=full
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

graph* load_graph(char* file_name)
{
    printf("LOADING\n");
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(file_name, "r");
    if (fp == NULL) exit(1);
    
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        switch (i++)
        {
            case 0:
                printf("%s", line);
                break;
            case 1:
                printf("%s", line);
                break;
            default:
                break;
                
        }
    }
    
    fclose(fp);
    if (line)
        free(line);
    
    
    return NULL;
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
        for(list_node* pos=begin(head);not_ended(head, pos);pos=pos->next)
        {
            fprintf(pFile, "%d ", WJP(pos,adjacency_list,node)->v);
        }
        fprintf(pFile, "\n");
    }  
    fclose (pFile);
}
