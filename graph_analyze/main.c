#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graph.h"

int                    main(int argc, char* argv[])
{
    if (argc == 2)
    {
        char output_filename[100];
        strcpy(output_filename, argv[1]);
        
        graph * g = load_graph(output_filename);
        find_clusters(g);
        free_graph(g);

        return 0;
    }
    else
    {
        printf("Incorrect number of args!\nThis should be called with one argument:\nthe file name to be analyzed!\n\n\n");
    }
}
