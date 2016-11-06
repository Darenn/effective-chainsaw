# ifndef __HEAP_ID_HPP_
# define __HEAP_ID_HPP_

/*!
 * \file
 * \brief This module provide a generic (template) heap together with id in order to access the elements in the heap.
 *
 * Id are managed in order to have constant time to get the id as well as to go from id to element.
 *
 * \author PASD
 * \date 2016
 */

# include <iostream>
# include <utility> // pair


# undef NDEBUG 
# include <assert.h>


// Pre-declaration to declare operator <<
template < class Element >
class Heap_Id ;


// Pre-declaration to declare friend after
template < class Element >
std :: ostream & operator << ( std :: ostream & ,
			       Heap_Id < Element > const & ) ;




/*!
 * \brief This class implements a generic heap with id for the elements.
 *
 * It uses a binary tree such that the value held in any node is greater (or equal) to the value in its sons.
 * 
 * Auxiliary arrays are used to go from id to positions and to record available id.
 *
 * \pre \c Element must be comparable: operators < and <= must be defined.
 *
 * Implementation: 
 * \li the tree is folded into an array.
 * \li reference / pointers are used to store elements (i.e. no copy is made)
 */
template < class Element >
class Heap_Id {

public :

  /*! Maximal capacity of the Heap_Id */ 
  const unsigned int capacity ;

private :
 
  /*!
   * Nature of the nodes: pointers to elements together with an id (\c unsigned \c int).
   * The number of elements is \c capacity. 
   */ 
  typedef std :: pair < Element * , unsigned int > Node ;

  /*! Pointer to array of size capacity. 
    The array holds the values. */
  Node * const elements ;

  /*! Number of values in the Heap_Id.
   * It is always at most the capacity. */
  unsigned int nb_elem ;

  /*! Record the map id to pos location */
  unsigned int * const id_to_pos ;

  /*! Record the ids, used then free.
   * Free are in position \c nb_elem to \c capacity -1.
   */
  unsigned int * const id_free ;

  /*! To compare two elements (less than).
   * \param pos_1 position of the left node.
   * \param pos_2 position of the right node.
   * \pre \c  pos_1 and \c pos_2 are legal positions.
   * \return true iff the node at \c pos_1 has a value LESSER THAN the one at node \c pos_2 ). 
   */
  bool lt ( unsigned int const pos_1 ,
	    unsigned int const pos_2 ) const {
    return true ;
  }
  

  /*! To compare two elements (less or equal).
   * \param pos_1 position of the left node.
   * \param pos_2 position of the right node.
   * \pre \c  pos_1 and \c pos_2 are legal positions.
   * \return true iff the node at \c pos_1 has a value LESSER than or EQUAL to the one at node \c pos_2 ) */
  bool le ( unsigned int const pos_1 ,
	    unsigned int const pos_2 ) const {
    return true ;
  }


  /*!
   * To compute the index of the left son.
   * \param i position of the node.
   * \pre \c i is a legal position
   * \post returns a legal position.
   * \return the index (in the array) of the left son of the node (indicated by index i). 
   */
  unsigned int get_pos_left_son ( unsigned int i ) const { 
    return -1 ;
  } ;
  
  /*!
   * To compute the index of the left son.
   * \param i position of the node.
   * \pre \c i is a legal position
   * \post returns a legal position.
   * \return the index (in the array) of the right son of the node (indicated by index i). 
   */
  unsigned int get_pos_right_son ( unsigned int i ) const { 
    return -1 ;
  } ;
  
  /*!
   * To compute the index of the father.
   * \param i position of the node.
   * \pre \c i is a legal position.
   * \post returns a legal position.
   * \return the index (in the array) of the right son of the node (indicated by index i), except for the root (it returns 0). 
   */
  unsigned int get_pos_father ( unsigned int i ) const { 
    return -1 ;
  } ;


  /*!
   * Exchange two elements in the array. 
   * \param pos_a position of one node.
   * \param pos_b position of other node.
   * \param i position of the node.
   * \pre \c pos_a and \c pos_b are legal positions.
   */
  void swap ( const unsigned int pos_a ,
	      const unsigned int pos_b ) {
  }

  /*! 
   * To check the validity of the head_ip.
   * \return true iff the Heap_Id is correct (each father less than or equal to sons) and indexing array are ok and free index array is ok.
   * This should to be used in asserts.
   */
  bool is_valid () const ;


  /*! 
   * Swap the node pos down throughout the Heap_Id till consistency is restored.
   * \param pos position of the node to lower
   * \pre pos is a valid location.
   * \post The Heap_Id is valid.
   */
  void lower ( unsigned pos ) ;

  /*! 
   * Swap the node pos up throughout the Heap_Id till consistency is restored.
   * \pre pos is a valid location.
   * \post The Heap_Id is valid.
   */
  void raise ( unsigned pos ) ;


public :

  
  //
  //  CONSTRUCTOR
  //

  /*! Build an empty Heap_Id  with given capacity. */
  
  Heap_Id ( unsigned int _capacity )
    : capacity ( _capacity )
    , elements ( new Node [ _capacity ] )
    , nb_elem ( 0 )
    , id_to_pos ( new unsigned int [ _capacity ] )
    , id_free ( new unsigned int [ _capacity ] )
  { 
  } ;

  
  //
  //  DESTRUCTOR
  //
  
  /*! Release the arrays. */
  ~Heap_Id () { 
  }

  
  //
  //  PUBLIC METHODS
  //

  /*!
   * To test the emptyness of the heap. 
   * \return true iff the Heap_Id  is empty 
   */
  bool is_empty () const { 
    return true ;
  }
  
  /*! 
   * Remove and return the root of the heap.
   * The Heap_Id  is re equilibrated by putting the last element at the root and lowering it.
   * \pre The Heap_Id  is valid.
   * \post The Heap_Id  is valid.
   * \return the minimum of the heap.
   */
  Element & pop () ;

  // TODO
  void reposition ( const unsigned int id ) ;
  

  /*!
   * Add a value at the bottom of the tree (first empty cell) and swap it up (raise).
   * \param v value to add.
   * \pre The Heap_Id  is valid.
   * \post The Heap_Id  is valid.
   * \return The id of inserted value.
   */
  unsigned int push ( Element & v ) ;

  
  //
  //  FRIENDS
  //
  
  friend std :: ostream & operator << < Element > ( std :: ostream & ,
						    Heap_Id < Element > const & ) ;  
} ;



//
// TEMPLATE 
// => METHODS MUST BE HERE 
//


template < class Element >
bool Heap_Id < Element > :: is_valid () const { 
  return false ;
}


template < class Element >
void Heap_Id < Element > :: lower ( unsigned int pos ) { 
}


template < class Element >
unsigned int Heap_Id < Element > :: push ( Element & v ) { 
  return -1 ;
}


template < class Element >
void Heap_Id < Element > :: raise ( unsigned int pos ) { 
}


template < class Element >
Element & Heap_Id < Element > :: pop () { 
  return * ( Element * ) NULL ;
}


template < class Element >
void Heap_Id < Element > :: reposition ( const unsigned int id ) { 
}


/*! Print the heap on the \c ostream as an array with the format:
 * \verbatim [ e0 , e1 , ... , en ] \endverbatim 
 * \param out \c ostream to output to.
 * \param h Heap_Id to output
 * \return the ostream
 */
template < class Element >
std :: ostream & operator << ( std :: ostream & out ,
			       Heap_Id < Element > const & h ) {
  return out ;
}



# endif
