#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graph.h"

int                    main(int argc, char* argv[]){
  //[0] init 
  srand((unsigned) time(NULL)); 
  int N=atoi(argv[1]);
  double P=atof(argv[2]);
  if(N==0)exit(-1);
  char output_filename[100];
  strcpy(output_filename, argv[3]);
  //[1] rand graph generation & output
  graph g;
  init_graph(&g, N);
  generate_rand_graph(&g, P);
  print_graph(&g, output_filename);
  return 0;
}  
