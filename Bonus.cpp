
#define Y 35.18577781093502
#define X 31.81428051893798
#include "MesureTimeHelper.h"
#include <vector>
#include <cstddef>
#include <unordered_set>
#include <string>
#include <chrono>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Apartment.h"
#include "AVL.h"
#include "Stack.h"
#include <sstream>
#include "Find.h"
#include <iostream>
#include <unordered_set>

void insertion_stack (Stack stack,
                      std::vector<std::pair<double, double>> vector)
{
  for (auto apt: vector)
    {
      stack.push (apt);
    }
}

void searching_stack (Stack stack, Apartment apt_to_find)
{
  find (stack.begin (), stack.end (), apt_to_find);
}

void insertion_avl (AVL avl,
                    std::vector<std::pair<double, double>> vector)
{
  for (auto apt: vector)
    {
      avl.insert (apt);
    }
}

void searching_avl (AVL avl, Apartment apt_to_find)
{
  avl.find (apt_to_find);
}

void searching_avl_general (AVL avl, Apartment apt_to_find)
{
  find (avl.begin (), avl.end (), apt_to_find);
}

void insertion_set (std::unordered_set<Apartment, MyHashFunction> set,
                    std::vector<std::pair<double, double>> vector)
{
  for (auto apt: vector)
    {
      set.insert (apt);
    }
}

auto searching_set (std::unordered_set<Apartment, MyHashFunction> set,
                    Apartment apt_to_find)
{
  auto x = set.find (apt_to_find);
  return x;
}

void searching_set_general (std::unordered_set<Apartment, MyHashFunction> set,
                            Apartment apt_to_find)
{
  find (set.begin (), set.end (), apt_to_find);
}

void run (std::string file_name)
{
  std::pair<double, double> pair (X, Y);
  Apartment apt_to_find (pair);

  auto vector1 = xy_from_file (file_name);
  Stack stack1;

  auto t1 = std::chrono::high_resolution_clock::now ();
  insertion_stack (stack1, vector1);
  auto t2 = std::chrono::high_resolution_clock::now ();
  auto result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;
  t1 = std::chrono::high_resolution_clock::now ();
  searching_stack (stack1, apt_to_find);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;

  AVL avl1;
  t1 = std::chrono::high_resolution_clock::now ();
  insertion_avl (avl1, vector1);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  searching_avl (avl1, apt_to_find);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  searching_avl_general (avl1, apt_to_find);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;

  std::unordered_set<Apartment, MyHashFunction> set1;
  t1 = std::chrono::high_resolution_clock::now ();
  insertion_set (set1, vector1);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  searching_set (set1, apt_to_find);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  searching_set_general (set1, apt_to_find);
  t2 = std::chrono::high_resolution_clock::now ();
  result = std::chrono::duration_cast<std::chrono::nanoseconds> (
      t2 - t1).count ();
  std::cout << result << std::endl << std::endl << std::endl << std::endl;

}

