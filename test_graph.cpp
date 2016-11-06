/*! 
 * \file
 * \brief Test file: constructs a graph and call print_dijkstra on it.
 */

# include "graph.hpp"


int main () {

  // 10 vertices
  Graph g ( 10 ) ;

  // all the edges
  g . add_edge ( 0 , 1 , 2.0 ) ;
  g . add_edge ( 0 , 2 , 4.0 ) ;
  g . add_edge ( 0 , 3 , 7.0 ) ;
  g . add_edge ( 1 , 2 , 3.0 ) ;
  g . add_edge ( 1 , 4 , 3.0 ) ;
  g . add_edge ( 2 , 3 , 2.0 ) ;
  g . add_edge ( 2 , 4 , 9.0 ) ;
  g . add_edge ( 2 , 5 , 7.0 ) ;
  g . add_edge ( 2 , 6 , 9.0 ) ;
  g . add_edge ( 3 , 6 , 4.0 ) ;
  g . add_edge ( 4 , 5 , 4.0 ) ;
  g . add_edge ( 4 , 7 , 9.0 ) ;
  g . add_edge ( 5 , 6 , 6.0 ) ;
  g . add_edge ( 5 , 7 , 5.0 ) ;
  g . add_edge ( 5 , 8 , 1.0 ) ;
  g . add_edge ( 5 , 9 , 6.0 ) ;
  g . add_edge ( 6 , 8 , 9.0 ) ;
  g . add_edge ( 7 , 9 , 3.0 ) ;
  g . add_edge ( 8 , 9 , 4.0 ) ;

  g . print_dijkstra ( 0 , 9 ) ;
  return 0 ;
}
