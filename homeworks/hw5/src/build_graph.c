#include <stdio.h>
#include <stdlib.h>

#include <object_list.h> 
#include "simple_graph.h"

int main( void ) {
    ObjectList *graph = ol_create();
    grh_load_file(graph, stdin);
    grh_print_graph(graph);
    grh_delete_graph(graph);

    return EXIT_SUCCESS;
}