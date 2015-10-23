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
    al1->v=v1;
    init(&al1->node);
    push_back(&g->lists[v2].node, &al1->node);

    adjacency_list* al2=(adjacency_list*)malloc(sizeof(adjacency_list));
    al2->v=v2;
    init(&al2->node);
    push_back(&g->lists[v1].node, &al2->node);
    
    g->nr_edges++;
}

void         free_graph(graph * g)
{
    for (int i=0; i<g->nr_vertices; i++)
    {
        list_node * head = &g->lists[i].node;
        while(!empty(head))
        {
            list_node * beginning = begin(head);
            adjacency_list * al = WJP(beginning,adjacency_list,node);
            erase(beginning); // REMOVE FROM THE LIST OF NODE
            free(al);
        }
    }
    free(g->lists);
    free(g);
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
    
    if (number_edges != 0) printf("Number of edges appears to be incorrect!\n"); // Sanity Check
    
    fclose(fp);
    if (line) free(line);
    
    return g;
}

#define SAM_FALSE 0
#define SAM_TRUE 1
#define bool char

int find_clusters_recursive_depth_first(graph * g, // Our graph data structure
                                        bool * not_explored_yet, // array of booleans storing if node has been expanded yet
                                        int index // Index of current node to expand
                                        )
{
    int connections = 1;
    not_explored_yet[index] = SAM_FALSE;
    
    list_node * head=&g->lists[index].node;
    for(list_node* pos=begin(head); not_ended(head, pos); pos=pos->next)
    {
        int sister_dex = WJP(pos,adjacency_list,node)->v;
        if (not_explored_yet[sister_dex] == SAM_TRUE)
        {
            connections += find_clusters_recursive_depth_first(g, not_explored_yet, sister_dex);
        }
    }
    return connections;
}

void find_clusters_breadth_first(graph * g, // Our graph data structure
                                 bool * not_explored_yet, // array of booleans storing if node has been expanded yet
                                 int index, // Index of current node to expand
                                 list_node * frontier
                                 )
{
    list_node * head=&g->lists[index].node;
    for(list_node* pos=begin(head); not_ended(head, pos); pos=pos->next)
    {
        int sister_dex = WJP(pos,adjacency_list,node)->v;
        if (not_explored_yet[sister_dex] == SAM_TRUE)
        {
            not_explored_yet[sister_dex] = SAM_FALSE;
            adjacency_list * al=(adjacency_list*) malloc(sizeof(adjacency_list));
            al->v=sister_dex;
            init(&al->node);
            push_back(frontier, &al->node);
        }
    }
}

int find_clusters_recursive_breadth_first(graph * g, // Our graph data structure
                                          bool * not_explored_yet, // array of booleans storing if node has been expanded yet
                                          int index // Index of current node to expand
                                          )
{
    int connections = 0;
    not_explored_yet[index] = SAM_FALSE;
    
    // Created a frontier FIFO queue (linked list)
    list_node * frontier = (list_node *) malloc(sizeof(list_node));
    init(frontier);
    
    // Seed the frontier with the given node.
    adjacency_list * al=(adjacency_list*) malloc(sizeof(adjacency_list));
    al->v=index;
    init(&al->node);
    push_back(frontier, &al->node);
    
    while(!empty(frontier))
    {
        list_node * beginning = begin(frontier);
        adjacency_list * al = WJP(beginning,adjacency_list,node);
        erase(beginning); // REMOVE FROM THE LIST OF NODE
        find_clusters_breadth_first(g, not_explored_yet, al->v, frontier);
        free(al);
        connections++;
    }
    
    free(frontier);
    return connections;
}


void find_clusters(graph * g)
{
    bool * not_explored_yet = malloc(sizeof(bool) * (g->nr_vertices));
    int * number_of_clusters_with_count = malloc(sizeof(int) * (1 + g->nr_vertices));
    number_of_clusters_with_count[g->nr_vertices] = 0;
    
    // Initialze Arrays
    for (int start_dex = 0; start_dex < g->nr_vertices; start_dex++)
    {
        not_explored_yet[start_dex] = SAM_TRUE;
        number_of_clusters_with_count[start_dex] = 0;
    }
    
    // Search for clusters, only search nodes that havent been explored yet!
    for (int start_dex = 0; start_dex < g->nr_vertices; start_dex++)
    {
        if (not_explored_yet[start_dex] == SAM_TRUE)
        {
            if (0) // Depth First
            {
                int cluster_count = find_clusters_recursive_depth_first(g, not_explored_yet, start_dex);
                number_of_clusters_with_count[cluster_count]++;
            }
            else // Breadth First
            {
                int cluster_count = find_clusters_recursive_breadth_first(g, not_explored_yet, start_dex);
                number_of_clusters_with_count[cluster_count]++;
            }
        }
    }

    // Total number of nodes that werent clustered
    int total_count = g->nr_vertices;
    int largest_cluster_size = 0;
    
    for (int start_dex = 0; start_dex <= g->nr_vertices; start_dex++)
    {
        int number = number_of_clusters_with_count[start_dex];
        if (number != 0)
        {
            total_count -= number * start_dex;
            largest_cluster_size = start_dex;
            printf("Clusters with %i nodes: %i\n", start_dex, number);
        }
    }
    
    printf("\nLargest Cluster Size: %i\n\n", largest_cluster_size);
    
    if (total_count != 0) printf("Every node was not clustered once: %i!\n", total_count); // Sanity Check

    free(not_explored_yet);
    free(number_of_clusters_with_count);
    
}
