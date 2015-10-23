# Graph Generation
* cd graph_gen
* make
* ./graph_gen1 10000 0.0001 ../data/10000_0p0001.txt
  
# Graph Analysis
* cd graph_analyze
* make
* ./bin/graph_analyze ../data/10000_0p0001.txt

#### OR

* valgrind --dsymutil=yes --leak-check=full ./bin/graph_analyze ../data/10000_0p0001.txt