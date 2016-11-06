# ifndef __GRAPH_HPP_
# define __GRAPH_HPP_

/*! 
 * \file
 * \brief This module provide a simple implantation of undirected graph.
 *
 * \author PASD
 * \date 2016
 */


# include <sstream>

# include <utility> // pair
# include <vector>


# undef NDEBUG
# include <assert.h>



/*! 
 * \brief To encode an undirected graph.
 *
 * A graph is created with a given number of vertices and no edge.
 * Edges are then added.
 *
 * Vertices are numbered from 0.
 */
class Graph {

public :

  /*!
   * Type to store edges:
   * \li other extremity, and
   * \li length.
   */
  typedef std :: pair < unsigned int ,
			float > Edge ;

  /*! 
   * Type to store vertices:
   * \li String to name it,
   * \li Vector to store the edges going out of it.
   */
  typedef std :: pair < std :: string ,
			std :: vector < Edge > >  Vertex ;

  /* Number of vertices. */
  unsigned int const nbr_vertices ;

  
private :

  /*! Array to store the vertices. */
  Vertex * const vertices ;

  
public :

  
  //
  //  CONSTRUCTOR
  //

  /*!
   * Create a graph with given number of vertices.
   * Names are provided for vertices: n0, n1…
   * \param _nbr_vertices number of vertices.
   * The graph has no edges.
   */
  Graph ( unsigned int _nbr_vertices )
    : nbr_vertices ( _nbr_vertices )
    , vertices ( new Vertex [ _nbr_vertices ] )
  {
    std :: string prefix ( "n" ) ;
    for ( unsigned int i = 0 ;
	  i < nbr_vertices ;
	  i ++ ) {
      // "magic formula" for to_string ()
      vertices [ i ] . first = prefix + static_cast < std :: ostringstream * > ( & ( std :: ostringstream () << i ) ) -> str() ;
      // still looking for better (and yet not C++11)
    }
  }

  
  //
  //  DESTRUCTOR
  //

  /*! Release the resources. */
  ~Graph () { 
    delete[] vertices ;
  }

  
  //
  //  PUBLIC METHODS
  //

  /*! Add edge both way.
   * i.e. (i,j) and (j,i)
   * \param i,j endpoints of the edge.
   * \param len length of the array.
   * \pre \c i and \c j are legal vertex number.
   * \pre \c len is strictly positive.
   */
  void add_edge ( unsigned int i ,
		  unsigned int j ,
		  float len ) {
    assert ( i < nbr_vertices ) ;
    assert ( j < nbr_vertices ) ;
    assert ( 0 < len ) ;
    vertices  [ i ] . second . push_back ( Edge ( j , len ) ) ;
    vertices  [ j ] . second . push_back ( Edge ( i , len ) ) ;
  }

  /*!
   * Print the result of Dijkstra's algorithm in the form:
   * \verbatim
   <last node>       <total distance>
   <penultimate note>    <distance to node from initial node>
   … …
   <second node>   <distance to node from initial node>
   <initial node>
   * \endverbatim
   * \param i,j endpoints of the path to search.
   * \pre \c i and \c j are legal vertex number.
   */
  void print_dijkstra ( unsigned int i ,
			unsigned int j ) const ;

} ;

# endif
