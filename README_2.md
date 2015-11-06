# Graph Generation
* cd graph_gen_2
* make
* ./graph_gen1 1000 ../data/1000.txt
  
# Graph Analysis
* cd scale_free_graph
* make
* ./graph_analysis ../data/1000.txt

#### OR

* valgrind --dsymutil=yes --leak-check=full ./graph_analysis ../data/1000.txt