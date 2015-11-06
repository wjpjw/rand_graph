#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

graph*                 read_graph(char*filename);
double                 diameter(char*filename);
void                   parse_edge(char*edge,int v, graph*g);
void                   parse_adl(char*adl, int v, graph*g);
char*                  locate(char*line, char t);
void                   dijkstra(graph*G, int vs);
void                   relax(graph*G, vertex*u,adjacency_list*adl);
#endif
