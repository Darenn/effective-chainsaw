/*!
 * \file
 * \brief Test file: tries the Heap for sorting \c int and then \c string.
 *
 * \author PASD
 * \date 2016
 */


# include <vector>
# include <stdlib.h>

# include "heap.hpp"

using namespace std ;


namespace { 

  /*! Capacity for the heap. */
  unsigned int const size = 100 ; 

  /*! Template function to test Heap.
   * \param V Type of the values.
   * \param a Array holding the values.
   * \param nbr Number of elements in the array \c a.
   * \param e1 Value to insert.
   * \param e2 Value to insert after.
   */
  template < class V >
  void test_trier ( V a [] ,
		    const unsigned int size ,
		    V e1 ,
		    V e2 ) {
    Heap < V > h ( size );
  
    for ( unsigned int i = 0 ; i < size ; i ++ ) {
      h.push ( a [ i ] ) ;
    }
    cout << h << endl ;

    cout << "removing " << h.pop () << endl ;
    cout << "adding " << e1 << endl ; 
    h.push ( e1 ) ;
    cout << h << endl ;
    
    cout << "removing " << h.pop () << endl ;
    cout << "adding " << e2 << endl ; 
    h.push ( e2 ) ;
    cout << h << endl ;

    cout << "Sorted output" << endl ; 
    while ( ! h.is_empty () ) {
      cout << h.pop () << " " ;
    }
    cout << endl ;
  }


}



int main () {

  //  Heap < int > h ( size );
    
  int ti []  = { 115 , 182 , 129 , 223 , -235 , 286 , 240 , 249 , 8 , 7 , 72 , 23 , 50 , 43 , -136 ,  192 , 293 , 136 , 177 , 267 , 283 , 235 , 290 ,  272 , 69 , 237 , 170 , 235 , 242 , 230 , 11 , 62 , 62 , 126 , -68 , 127 , 67 , 226 , -172 , 121 ,  286 , 259 , 263 , 3 , 8 , 199 } ;
  test_trier ( ti , sizeof ( ti ) / sizeof ( int ) , -5 , 43 ) ;

  string ts []  = { "valgrind" , "./test_heap" , "Memcheck," , "a" , "memory" , "error" , "detector" , "Copyright" , "(C)" , "2002-2013," , "and" , "GNU" , "GPL'd," , "by" , "Julian" , "Seward" , "et" , "al." , "Using" , "Valgrind-3.10.1" , "and" , "LibVEX;" , "rerun" , "with" , "-h" , "for" , "copyright" , "info" , "Command:" , "./test_heap" } ;
  test_trier ( ts , sizeof ( ts ) / sizeof ( string ) , ( string ) "Afd",  ( string ) "Asf" ) ;

  return 0 ;
}
