#include "global.h"

int                    main(int argc, char* argv[]){
  //[0] init 
  srand((unsigned)time(NULL)); 
  char input_filename[100];
  strcpy(input_filename, argv[1]);
  //[1] read graph from file [2] find the scale-free graph's maximum shortest path among all vertices pairs
  printf("diameter:%f\n",diameter(input_filename));
  return 0;
}  
