#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    adjacency_list* al1=(adjacency_list*)malloc(sizeof(adjacency_list));
    al1->v=v2;
    init(&al1->node);
    push_back(&g->lists[v2].node, &al1->node);

    adjacency_list* al2=(adjacency_list*)malloc(sizeof(adjacency_list));
    al2->v=v2;
    init(&al2->node);
    push_back(&g->lists[v1].node, &al2->node);
    
    g->nr_edges++;
}

graph* load_graph(char* file_name)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(file_name, "r");
    if (fp == NULL) exit(1);

    int line_number = 0; // Line Number
    
    int number_vertices = 0;
    int number_edges = 0;
    
    graph * g = NULL;
    
    // Iterate through the lines of the file!
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // Get the length (number of characters) in current line;
        int strlens = strlens = (int) strlen(line);
        
        switch (line_number++)
        {
            case 0:
                for (int index = 0; index < strlens; index++)
                {
                    if (line[index] == ':')
                    {
                        number_vertices = atoi(&(line[index + 1]));
                    }
                }
                break;
            case 1:
                for (int index = 0; index < strlens; index++)
                {
                    if (line[index] == ':')
                    {
                        number_edges = atoi(&(line[index + 1]));
                    }
                }
                break;
            default:
                if (g == NULL)
                {
                    g = (graph *) malloc(sizeof(graph));
                    init_graph(g, number_vertices);
                    printf("Loaded graph with %i vertices and %i edges!\n", number_vertices, number_edges);
                }
                
                int vertex_index = atoi(&(line[1]));
                int index = 1;
                
                while (1)
                {
                    char current = line[index];
                    
                    // Move out of the numbered part to next break
                    while (((current <= '9') && (current >= '0'))
                           && index < strlens) current = line[++index];
                    
                    // Move out of break to the next numbered part
                    while (((current > '9') || (current < '0'))
                           && index < strlens) current = line[++index];

                    // Make sure we still are within bounds of string!
                    if (index == strlens) break;

                    int sister_index = atoi(&(line[index]));
                    add_edge(g, vertex_index, sister_index);
                    number_edges--;
                }
                break;
                
        }
    }
    
    if (number_edges != 0) printf("Number of edges appears to be incorrect!\n");
    
    fclose(fp);
    if (line) free(line);
    
    return g;
}

#define SAM_FALSE 0
#define SAM_TRUE 1


int find_clusters_recursive(graph * g, char * validity, int index)
{
    int connections = 1;
    validity[index] = SAM_FALSE;

    
    list_node*head=&g->lists[index].node;
    for(list_node* pos=begin(head);not_ended(head, pos);pos=pos->next)
    {
        int sister_dex = WJP(pos,adjacency_list,node)->v;
        if (validity[sister_dex] == SAM_TRUE)
        {
            connections += find_clusters_recursive(g, validity, sister_dex);
        }
    }

    return  connections;
}

void find_clusters(graph * g)
{
    char * validity = malloc((g->nr_vertices));
    
    for (int start_dex = 0; start_dex < g->nr_vertices; start_dex++) validity[start_dex] = SAM_TRUE;
    
    for (int start_dex = 0; start_dex < g->nr_vertices; start_dex++)
    {
        if (validity[start_dex] == SAM_TRUE)
        {
            int cluster_count = find_clusters_recursive(g, validity, start_dex);
            printf("Cluster With %i nodes\n", cluster_count);
        }
    }

    free(validity);
    
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
