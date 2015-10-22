#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graph.h"

int                    main(int argc, char* argv[])
{
  //[0] init
    if (argc == 2)
    {
        char output_filename[100];
        strcpy(output_filename, argv[1]);
        
        graph * g = load_graph(output_filename);

        free(g);
//        init_graph(&g, N);
//        generate_rand_graph(&g, P);
//        print_graph(&g, output_filename);
        return 0;
    }
    else
    {
        printf("Incorrect number of args!\n");
    }
}
