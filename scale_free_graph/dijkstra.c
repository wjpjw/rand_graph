#define _GNU_SOURCE
#include "global.h"
graph*                 read_graph(char*filename){
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen(filename, "r");
  if (fp == NULL) exit(1);
  int line_number = 0; 
  int number_vertices = 0;
  graph * g = NULL;
  while ((read = getline(&line, &len, fp)) != -1){
    switch (line_number++){
    case 0:
      number_vertices = atoi(locate(line,':'));
      break;
    case 1:
      break;
    default:
      if(g == NULL){
	g = (graph *) malloc(sizeof(graph));
	init_graph(g, number_vertices);
      }
      int vertex_index = atoi(&(line[1]));
      parse_adl(locate(line,':'), vertex_index, g);
      break;
    }
  }
  fclose(fp);
  if (line) free(line);
  return g;
}
char*                  locate(char*line, char t){
  for(char* pos=line;pos!=0;pos++){
    if(*pos==t)
      return ++pos;
  }
  return 0;
}  
void                   parse_adl(char*adl, int v, graph*g){
  char *token = strtok(adl, " ");
  while (token != NULL && token[0]!='\n'&& token[0]!=' '&& token[0]!='\t'&& token[0]!='\b' ) {
    parse_edge(token,v,g);
    token = strtok(NULL, " ");
  }
}  
void                   parse_edge(char*edge,int v, graph*g){
  int v2     = atoi(edge);
  char* w=locate(edge,',');
  if(w==0)return;
  double weight = atof(w);
  add_edge(g,v,v2,weight);
}
double                 diameter(char*filename){
  double longest_longest_shortest=0;
  graph*G=read_graph(filename);
  printf("graph nr_vertices:%d, nr_edges:%d\n", G->nr_vertices, G->nr_edges);
  for(int i=0;i<G->nr_vertices;i++){
    dijkstra(G,i); //G is modified 
    double longest_shortest=0;
    for(int i=0;i<G->nr_vertices;i++){
      if(longest_shortest < G->vertices[i].priority){
	longest_shortest= G->vertices[i].priority;
      }
    }
    if(longest_longest_shortest<longest_shortest){
      longest_longest_shortest=longest_shortest;
    }  
    G=read_graph(filename); 
  }
  return longest_longest_shortest;
}
//update v's distance from vs after u is selected as the current nearest node, adl is the edge from u to v
void                    relax(graph*G, vertex*u,adjacency_list*adl){
  vertex*  v = &G->vertices[adl->v];
  double   tmp = u->priority + adl->weight;
  if(v->priority>tmp){
    v->priority=tmp;
  }  
}  
void                    dijkstra(graph*G, int vs){
  heap*Q=create_heap();
  for(int i=0;i<G->nr_vertices;i++){
    G->vertices[i].priority=DBL_MAX;
    hh_insert(Q, PO(G->vertices[i]));          
  }
  G->vertices[vs].priority=0;
  while(!hh_empty(Q)){
    double*    p = hh_root(Q);
    vertex*    u = CO(p,vertex);
    list_node* h = &u->list_head.node;
    for(list_node*pos=begin(h);not_ended(h,pos);pos=pos->next){
      adjacency_list* adl= WJP(pos,adjacency_list,node);
      relax(G, u, adl);
    }  
  }  
}  

