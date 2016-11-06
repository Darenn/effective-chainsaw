/*!
 * \file
 * \brief Test file: tries the Heap_Id for sorting \c int and then \c string.
 *
 * \author PASD
 * \date 2016
 */

# include <vector>

# include <stdlib.h>

# include "heap_id.hpp"


using namespace std ;


namespace {

  /*! Capacity for the heap. */
  unsigned int const size = 33 ; 

  /*! Template function to test Heap.
   * \param V Type of the values.
   * \param a Array holding the values.
   * \param nbr Number of elements in the array \c a.
   * \param e1 Value to insert after.
   * \param e2 Value new value for e1.
   */
  template < class V >
  void test_trier ( V a [] ,
		    const unsigned int nbr ,
		    V e1 ,
		    V e2 ) {
    Heap_Id < V > h ( nbr + 1 );
    // Insert the value in the heap.
    for ( unsigned int i = 0 ; i < nbr ; i ++ ) {
      h.push ( a [ i ] ) ;
    }
    cout << h << endl ;

    // add a value.
    int id1 = h.push ( e1 ) ; // id for e1
    cout << e1 << " inserted" << endl ;
    cout << h << endl ;

    // Change the value of e1
    cout << "value " << e1 << " changed to " << e2 << endl ;
    e1 = e2 ;
    h.reposition ( id1 ) ;
    cout << h << endl ;

    // sorted output
    while ( ! h.is_empty () ) {
      cout << h.pop () << " " ;
    }
    cout << endl ;
  }



}


int main () {

  // Test with int
  int ti []  = { 115 , 182 , 129 , 223 , 235 , -286 , 240 , 249 , 8 , 7 , 72 , 23 , 50 , 43 , 136 ,  192 , 293 , 136 , 177 , 267 , 283 ,- 235 , 290 ,  272 , 69 , 237 , 170 , 235 , 242 , 230 , -11 , 62 , 62 , 126 , 68 , -127 , 67 , 226 , 172 , 121 ,  286 , 259 , -263 , 3 , 8 , 199 } ;
  test_trier ( ti , sizeof ( ti ) / sizeof ( int ) , 2 , 180 ) ;

  
  // Test with string
  string ts []  = { "valgrind" , "./test_heap" , "Memcheck," , "a" , "memory" , "error" , "detector" , "Copyright" , "(C)" , "2002-2013," , "and" , "GNU" , "GPL'd," , "by" , "Julian" , "Seward" , "et" , "al." , "Using" , "Valgrind-3.10.1" , "and" , "LibVEX;" , "rerun" , "with" , "-h" , "for" , "copyright" , "info" , "Command:" , "./test_heap" } ;
  test_trier < std :: basic_string < char > > ( ts , sizeof ( ts ) / sizeof ( string ) , "Abacus" , "index" ) ;

  return 0 ;
}
