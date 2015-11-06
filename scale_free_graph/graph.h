#ifndef GRAPH_H_
#define GRAPH_H_
//directed wieghed graph
typedef struct{
  list_node       node;
  int             v;         // vertices are indexed from 0 to N-1
  double          weight;    // edge weight
}adjacency_list;
typedef struct{
  double         priority;    // distance from a source
  adjacency_list list_head;
}vertex;
typedef struct{
  int             nr_vertices;              
  int             nr_edges;
  vertex*         vertices;
}graph;
static inline void            init_graph(graph* g, int N){
  g->vertices=(vertex*) malloc(sizeof(vertex)*N);
  for(int i=0;i<N;i++){
    init(&g->vertices[i].list_head.node);
    g->vertices[i].priority=DBL_MAX;
  }
  g->nr_edges=0;
  g->nr_vertices=N;
}
static inline void            add_edge(graph* g, int v1, int v2, double weight){
  adjacency_list* al=(adjacency_list*)malloc(sizeof(adjacency_list));
  al->v=v2;
  al->weight=weight;
  init(&al->node);
  push_back(&g->vertices[v1].list_head.node, &al->node);
  g->nr_edges++;

  adjacency_list* al2=(adjacency_list*)malloc(sizeof(adjacency_list));
  al2->v=v1;
  al2->weight=weight;
  init(&al2->node);
  push_back(&g->vertices[v2].list_head.node, &al2->node);
  g->nr_edges++;
}

static inline void            print_graph(graph*g){
  for(int i=0;i<g->nr_vertices;i++){
    vertex*v=&g->vertices[i];
    printf("v%d:", i);
    list_node* head=&v->list_head.node;
    int j = 0;
    for(list_node* pos=begin(head);not_ended(head, pos);pos=pos->next){
      if (j != 0) printf(",");
      adjacency_list*l=WJP(pos,adjacency_list,node);
      printf(" %d,%f", l->v, l->weight);
      j++;
    }
    printf("\n");
  }  
}
static inline void            print_priority(graph*g){
  for(int i=0;i<g->nr_vertices;i++){
    vertex*v=&g->vertices[i];
    printf("v%d:%f", i, v->priority);
    printf("\n");
  }  
}


#endif
