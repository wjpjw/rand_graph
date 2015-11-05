#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graph.h"

int                    main(int argc, char* argv[]){
    //[0] init
    srand((unsigned) time(NULL));
    int N=atoi(argv[1]);
    if(N <= 5)
    {
        printf("N must be greater than 5!");
        exit(-1);
    }
    
    char output_filename[100];
    strcpy(output_filename, argv[2]);
    //[1] rand graph generation & output
    graph g;
    init_graph(&g, N);
    generate_rand_graph(&g, 5);
    print_graph(&g, output_filename);
    return 0;
}  
