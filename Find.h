

#ifndef _FIND_H_
#define _FIND_H_
#include "Apartment.h"

/**
 * The function returns an iterator to the item that corresponds to the item
 * we were looking for. If there is no such member, returns end ().
 * @param first InputIt obj to begin the search
 * @param last InputIt obj to end the search
 * @param value the item we are looking for
 * @return InputIt obj to the item that corresponds to the item
 * we were looking for. If there is no such member, returns end ().
 */
template<class InputIt>
InputIt find (InputIt first, InputIt last, const Apartment &value)
{
  while (first != last)
    {
      if (*first == value)
        {
          return first;
        }
      first++;
    }
  return last;
}
#endif //_FIND_H_
