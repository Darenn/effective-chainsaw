#ifndef __HEAP_ID_HPP_
#define __HEAP_ID_HPP_

/*!
 * \file
 * \brief This module provide a generic (template) heap together with id in
 * order to access the elements in the heap.
 *
 * Id are managed in order to have constant time to get the id as well as to go
 * from id to element.
 *
 * \author PASD
 * \date 2016
 */

#include <iostream>
#include <utility> // pair

#undef NDEBUG
#include <assert.h>

// Macros for assertions
#define ASSERT_IN_RANGE(value, min, max)                                       \
  {                                                                            \
    assert(value >= min);                                                      \
    assert(value <= max);                                                      \
  }

// Pre-declaration to declare operator <<
template <class Element> class Heap_Id;

// Pre-declaration to declare friend after
template <class Element>
std::ostream &operator<<(std::ostream &, Heap_Id<Element> const &);

/*!
 * \brief This class implements a generic heap with id for the elements.
 *
 * It uses a binary tree such that the value held in any node is greater (or
 * equal) to the value in its sons.
 *
 * Auxiliary arrays are used to go from id to positions and to record available
 * id.
 *
 * \pre \c Element must be comparable: operators < and <= must be defined.
 *
 * Implementation:
 * \li the tree is folded into an array.
 * \li reference / pointers are used to store elements (i.e. no copy is made)
 */
template <class Element> class Heap_Id {

public:
  /*! Maximal capacity of the Heap_Id */
  const unsigned int capacity;

private:
  /*!
   * Nature of the nodes: pointers to elements together with an id (\c unsigned
   * \c int).
   * The number of elements is \c capacity.
   */
  typedef std::pair<Element *, unsigned int> Node;

  /*! Pointer to array of size capacity.
    The array holds the values. */
  Node *const elements;

  /*! Number of values in the Heap_Id.
   * It is always at most the capacity. */
  unsigned int nb_elem;

  /*! Record the map id to pos location */
  unsigned int *const id_to_pos;

  /*! Record the ids, used then free.
   * Free are in position \c nb_elem to \c capacity -1.
   */
  unsigned int *const id_free;

  /*! To compare two elements (less than).
   * \param pos_1 position of the left node.
   * \param pos_2 position of the right node.
   * \pre \c  pos_1 and \c pos_2 are legal positions.
   * \return true iff the node at \c pos_1 has a value LESSER THAN the one at
   * node \c pos_2 ).
   */
  bool lt(unsigned int const pos_1, unsigned int const pos_2) const {
    ASSERT_IN_RANGE(pos_1, 0, capacity - 1);
    ASSERT_IN_RANGE(pos_2, 0, capacity - 1);
    return (*(elements[pos_1]).first) < (*(elements[pos_2]).first);
  }

  /*! To compare two elements (less or equal).
   * \param pos_1 position of the left node.
   * \param pos_2 position of the right node.
   * \pre \c  pos_1 and \c pos_2 are legal positions.
   * \return true iff the node at \c pos_1 has a value LESSER than or EQUAL to
   * the one at node \c pos_2 ) */
  bool le(unsigned int const pos_1, unsigned int const pos_2) const {
    ASSERT_IN_RANGE(pos_1, 0, capacity - 1);
    ASSERT_IN_RANGE(pos_2, 0, capacity - 1);
    return (*(elements[pos_1]).first) <= (*(elements[pos_2]).first);
  }

  /*!
   * To compute the index of the left son.
   * \param i position of the node.
   * \pre \c i is a legal position
   * \post returns a legal position.
   * \return the index (in the array) of the left son of the node (indicated by
   * index i).
   */
  unsigned int get_pos_left_son(unsigned int i) const {
    ASSERT_IN_RANGE(i, 0, capacity - 1);
    unsigned int pos_right_son = 2 * i + 1;
    return pos_right_son;
  };

  /*!
   * To compute the index of the left son.
   * \param i position of the node.
   * \pre \c i is a legal position
   * \post returns a legal position.
   * \return the index (in the array) of the right son of the node (indicated by
   * index i).
   */
  unsigned int get_pos_right_son(unsigned int i) const {
    ASSERT_IN_RANGE(i, 0, capacity - 1);
    unsigned int pos_right_son = 2 * i + 2;
    return pos_right_son;
  };

  /*!
   * To compute the index of the father.
   * \param i position of the node.
   * \pre \c i is a legal position.
   * \post returns a legal position.
   * \return the index (in the array) of the right son of the node (indicated by
   * index i), except for the root (it returns 0).
   */
  unsigned int get_pos_father(unsigned int i) const {
    ASSERT_IN_RANGE(i, 0, capacity - 1);
    unsigned int pos_father;
    if (i == 0) {
      pos_father = 0;
    } else {
      pos_father = (i - 1) * 0.5;
    }
    ASSERT_IN_RANGE(pos_father, 0, capacity - 1);
    return pos_father;
  };

  /*!
   * Exchange two elements in the array.
   * \param pos_a position of one node.
   * \param pos_b position of other node.
   * \param i position of the node.
   * \pre \c pos_a and \c pos_b are legal positions.
   */
  void swap(const unsigned int pos_a, const unsigned int pos_b) {
    ASSERT_IN_RANGE(pos_a, 0, capacity - 1);
    ASSERT_IN_RANGE(pos_b, 0, capacity - 1);
    const unsigned int temp_pos_a = pos_a;
    id_to_pos[(elements[pos_a]).second] = pos_b;
    id_to_pos[(elements[pos_b]).second] = temp_pos_a;
    Node buffer = elements[pos_a];
    elements[pos_a] = elements[pos_b];
    elements[pos_b] = buffer;
  }

  /*!
   * To check the validity of the head_ip.
   * \return true iff the Heap_Id is correct (each father less than or equal to
   * sons) and indexing array are ok and free index array is ok.
   * This should to be used in asserts.
   */
  bool is_valid() const;

  /*!
   * Swap the node pos down throughout the Heap_Id till consistency is restored.
   * \param pos position of the node to lower
   * \pre pos is a valid location.
   * \post The Heap_Id is valid.
   */
  void lower(unsigned pos);

  /*!
   * Swap the node pos up throughout the Heap_Id till consistency is restored.
   * \pre pos is a valid location.
   * \post The Heap_Id is valid.
   */
  void raise(unsigned pos);

public:
  //
  //  CONSTRUCTOR
  //

  /*! Build an empty Heap_Id  with given capacity. */

  Heap_Id(unsigned int _capacity)
      : capacity(_capacity), elements(new Node[_capacity]), nb_elem(0),
        id_to_pos(new unsigned int[_capacity]),
        id_free(new unsigned int[_capacity]) {
    // Fill the id free with ids
    for (size_t i = 0; i < capacity; i++) {
      id_free[i] = i;
    }
  };

  //
  //  DESTRUCTOR
  //

  /*! Release the arrays. */
  ~Heap_Id() {
    delete[] elements;
    delete[] id_to_pos;
    delete[] id_free;
  }

  //
  //  PUBLIC METHODS
  //

  /*!
   * To test the emptyness of the heap.
   * \return true iff the Heap_Id  is empty
   */
  bool is_empty() const { return nb_elem == 0; }

  /*!
   * Remove and return the root of the heap.
   * The Heap_Id  is re equilibrated by putting the last element at the root and
   * lowering it.
   * \pre The Heap_Id  is valid.
   * \post The Heap_Id  is valid.
   * \return the minimum of the heap.
   */
  Element &pop();

  // TODO
  void reposition(const unsigned int id);

  /*!
   * Add a value at the bottom of the tree (first empty cell) and swap it up
   * (raise).
   * \param v value to add.
   * \pre The Heap_Id  is valid.
   * \post The Heap_Id  is valid.
   * \return The id of inserted value.
   */
  unsigned int push(Element &v);

  //
  //  FRIENDS
  //

  friend std::ostream &operator<<<Element>(std::ostream &,
                                           Heap_Id<Element> const &);
};

//
// TEMPLATE
// => METHODS MUST BE HERE
//

template <class Element> bool Heap_Id<Element>::is_valid() const {
  return true;
  for (size_t i = 0; i < nb_elem; i++) {
    if (get_pos_right_son(i) < nb_elem) {
      if (!le(i, get_pos_right_son(i))) {
        return false;
      }
    }
    if (get_pos_left_son(i) < nb_elem) {
      if (!le(i, get_pos_left_son(i))) {
        return false;
      }
    }
  }
  return true;
}

template <class Element> void Heap_Id<Element>::lower(unsigned int pos) {
  ASSERT_IN_RANGE(pos, 0, capacity - 1);
  unsigned int pos_left_son = get_pos_left_son(pos);
  unsigned int pos_right_son = get_pos_right_son(pos);
  // While the node has children, and the node is lesser than one of its
  // children, swap with the lesser child
  while ((pos_left_son < nb_elem && lt(pos_left_son, pos)) ||
         (pos_right_son < nb_elem && lt(pos_right_son, pos))) {
    unsigned pos_to_swap_with;
    if (pos_right_son < nb_elem && lt(pos_right_son, pos_left_son)) {
      pos_to_swap_with = pos_right_son;
    } else {
      pos_to_swap_with = pos_left_son;
    }
    swap(pos, pos_to_swap_with);
    // Reset positions for next iteration
    pos = pos_to_swap_with;
    pos_left_son = get_pos_left_son(pos);
    pos_right_son = get_pos_right_son(pos);
  }
  assert(is_valid());
}

template <class Element> unsigned int Heap_Id<Element>::push(Element &v) {
  assert(is_valid());
  assert(nb_elem < capacity);
  std::pair<Element *, unsigned int> *pair =
      new std::pair<Element *, unsigned int>(&v, id_free[nb_elem]);
  Node n = *pair;
  elements[nb_elem] = n;
  id_to_pos[n.second] = nb_elem;
  nb_elem++;
  raise(nb_elem - 1);
  assert(is_valid());
  return n.second;
}

template <class Element> void Heap_Id<Element>::raise(unsigned int pos) {
  ASSERT_IN_RANGE(pos, 0, capacity - 1);
  unsigned int pos_father = get_pos_father(pos);
  // While the node has a father and is lesser than it, swap the node
  // with its father.
  while (pos_father >= 0 && lt(pos, pos_father)) {
    swap(pos, pos_father);
    pos = pos_father;
    pos_father = get_pos_father(pos);
  }
  assert(is_valid());
}

template <class Element> Element &Heap_Id<Element>::pop() {
  assert(is_valid());
  swap(0, nb_elem - 1);
  Node *popped_node = &elements[nb_elem - 1];
  Element *popped_element = popped_node->first;
  // elements[nb_elem - 1] = NULL;
  nb_elem--;
  lower(0);
  assert(is_valid());
  // delete (popped_node);
  return *popped_element;
}

template <class Element>
void Heap_Id<Element>::reposition(const unsigned int id) {
  raise(id_to_pos[id]);
  lower(id_to_pos[id]);
}

/*! Print the heap on the \c ostream as an array with the format:
 * \verbatim [ e0 , e1 , ... , en ] \endverbatim
 * \param out \c ostream to output to.
 * \param h Heap_Id to output
 * \return the ostream
 */
template <class Element>
std::ostream &operator<<(std::ostream &out, Heap_Id<Element> const &h) {
  out << '[';
  for (size_t i = 0; i < h.nb_elem; i++) {
    if (i == h.nb_elem - 1) {
      out << ' ' << *((h.elements[i]).first) << ' ';
    } else {
      out << ' ' << *((h.elements[i]).first) << " ,";
    }
  }
  out << ']';
  return out;
}

#endif
