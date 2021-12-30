
#include "Stack.h"
#define EMPTY_STACK_MSG_ERROR "Error: the stack is empty. illegal operation"

/**
 * Default constructor, constructs an empty stack
 */
Stack::Stack () : vector ({})
{}

/**
 * Constructor that gets vector of pairs, and pushes them as apartments to
 * the stack, when the first pair is pushed first.
 * @param coordinates vector of pairs
 */
Stack::Stack (std::vector<std::pair<double, double>> coordinates)
{
  for (auto x:coordinates)
    {
      Apartment a (x);
      push (a);
    }

}

/**
 * Pushes an apartment to the top of the stack
 * @param apartment Apartment obj to push the stack
 */
void Stack::push (const Apartment &apartment)
{
  vector.push_back (apartment);
}

/**
 * A method that deletes the item from the top of the stack.
 * Calling this method with an empty stack will throw an out of range
 * exception with an informative message of your choice.
 */
void Stack::pop ()
{
  if (empty ())
    {
      throw std::out_of_range (EMPTY_STACK_MSG_ERROR);
    }
  vector.pop_back ();
}

/**
 * A method that returns true if the stack is empty and otherwise false.
 */
bool Stack::empty () const
{
  return (vector.empty ());

}

/**
 * A method that returns how many items are inside the stack.
 */
size_t Stack::size () const
{
  return vector.size ();
}

/**
 * Method that return the item from the top of the stack, but do not remove
 * it from it. Calling this method with an empty stack will throw an out of
 * range exception with an informative message of your choice.
 * @return reference to the top most item
 */
Apartment &Stack::top ()
{
  if (empty ())
    {
      throw std::out_of_range (EMPTY_STACK_MSG_ERROR);
    }
  return vector.back ();
}

/**
 * Method that return the item from the top of the stack, but do not remove
 * it from it. Calling this method with an empty stack will throw an out of
 * range exception with an informative message of your choice.
 * @return copy to the top most item
 */
Apartment Stack::top () const
{
  if (empty ())
    {
      throw std::out_of_range (EMPTY_STACK_MSG_ERROR);
    }
  return vector.back ();
}

/**
 * @return iterator object that corresponds to the beginning of the stack
 */
Stack::iterator Stack::begin ()
{
  return vector.rbegin ();
}

/**
 * @return const iterator object that corresponds to the beginning of the
 * stack
 */
Stack::const_iterator Stack::begin () const
{
  return vector.rbegin ();
}

/**
 * @return const iterator object that corresponds to the beginning of the
 * stack
 */
Stack::const_iterator Stack::cbegin () const
{
  return vector.rbegin ();
}

/**
 * @return iterator object that corresponds to the end of the stack
 */
Stack::iterator Stack::end ()
{
  return vector.rend ();
}

/**
 * @return const iterator object that corresponds to the end of the stack
 */
Stack::const_iterator Stack::end () const
{
  return vector.rend ();
}

/**
 * @return const iterator object that corresponds to the end of the stack
 */
Stack::const_iterator Stack::cend () const
{
  return vector.rend ();
}

