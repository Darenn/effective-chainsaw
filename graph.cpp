/*!
 * \file
 * \biref This module provides the Dijsktra algorithm on graph, the rest (graph definition) is in the header file.
 *
 * \author PASD
 * \date 2016
 */

# include "graph.hpp"
# include "heap_id.hpp"


using namespace std ;


namespace {

  /*!
   * Class used to put a Head_Id to store, for a vertex (identifyed by \c i ):
   */
  class Vertex_Distance {

    /*! Reachable vertex number. */
    unsigned int i ;

    /*! Lower distance found to get to i, yet. */
    float distance ;

    /*! From where to come from to get this distance. */
    unsigned int from ;

    
  public :


    //
    //  CONSTRUCTORS
    //
    
    Vertex_Distance () {} 
    Vertex_Distance ( unsigned int _i ,
		      float _distance ,
		      unsigned int _from )
      : i ( _i )
      , distance ( _distance )
      , from ( _from )
    {}
      
    //
    //  PUBLIC METHODS
    //

    /*! Comparison according to distance.
     * \param cd2 Vertex_Distance to compare to.
     * \return true if vd2 is at a longer distance.
     */
    bool operator < ( Vertex_Distance const & vd2 ) const {
      return distance < vd2 . distance ;
    }

    /*! Comparison according to distance.
     * \param cd2 Vertex_Distance to compare to.
     * \return true if vd2 is at a longer or equal distance.
     */
    bool operator <= ( Vertex_Distance const & vd2 ) const {
      return distance <= vd2 . distance ;
    }

    /*! 
     * To change the value held.
     * \param _distance new value for distance.
     * \param _from new value for from.
     * \pre distance should be decreasing.
     */
    void update ( float const _distance ,
		  unsigned int const _from ) {
    }


    //
    //  FRIENDS
    //
    
    friend class :: Graph ;
    
  } ;

  /*! Constant to indicate that the node is not reachable yet. */
  int const id_undefined = -1 ;
  
  /*! Constant to indicate that the node was treated. */
  int const id_treated = -2 ;

}


void Graph :: print_dijkstra ( unsigned int from ,
			       unsigned int to ) const {
}

