
#ifndef _STACK_H_
#define _STACK_H_
#include "Apartment.h"
#include <vector>

/**
 * this class represents a stack
 */
class Stack {
  std::vector<Apartment> vector;

 public:
  /**
   * Default constructor, constructs an empty stack
   */
  Stack ();

  /**
   * Constructor that gets vector of pairs, and pushes them as apartments to
   * the stack, when the first pair is pushed first.
   * @param coordinates vector of pairs
   */
  Stack (std::vector<std::pair<double, double>> coordinates);

  /**
   * Pushes an apartment to the top of the stack
   * @param apartment Apartment obj to push the stack
   */
  void push (const Apartment &apartment);

  /**
   * A method that deletes the item from the top of the stack.
   * Calling this method with an empty stack will throw an out of range
   * exception with an informative message of your choice.
   */
  void pop ();

  /**
   *A method that returns true if the stack is empty and otherwise false.
   */
  bool empty () const;

  /**
   * A method that returns how many items are inside the stack.
   */
  size_t size () const;

  /**
  * Method that return the item from the top of the stack, but do not remove
   * it from it. Calling this method with an empty stack will throw an out of
   * range exception with an informative message of your choice.
   * @return reference to the top most item
   */
  Apartment &top ();

  /**
   * Method that return the item from the top of the stack, but do not remove
   * it from it. Calling this method with an empty stack will throw an out of
   * range exception with an informative message of your choice.
   * @return copy to the top most item
   */
  Apartment top () const;

  /**
   * The stack should support the iterator (at least a forward iterator) so
   * that the item at the top of the stack is the first item.
   */
  typedef std::vector<Apartment>::reverse_iterator iterator;
  typedef std::vector<Apartment>::const_reverse_iterator const_iterator;

  /**
   * @return iterator object that corresponds to the beginning of the stack
   */
  iterator begin ();

  /**
   * @return const iterator object that corresponds to the beginning of the
   * stack
   */
  const_iterator begin () const;

  /**
   * @return const iterator object that corresponds to the beginning of the
   * stack
   */
  const_iterator cbegin () const;

  /**
   * @return iterator object that corresponds to the end of the stack
   */
  iterator end ();

  /**
   * @return const iterator object that corresponds to the end of the stack
   */
  const_iterator end () const;

  /**
   * @return const iterator object that corresponds to the end of the stack
   */
  const_iterator cend () const;
};

#endif //_STACK_H_
