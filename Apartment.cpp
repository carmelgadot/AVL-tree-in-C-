
#include "Apartment.h"

/**
 * Constructor that get pair of points, and creates new apartment.
 * @param Coordinates std::pair, which the first is the x coordinate and the
 * second is the y.
 */
Apartment::Apartment (const std::pair<double, double> &Coordinates)
{
  _x = Coordinates.first;
  _y = Coordinates.second;
}

/**
 * @return the x coordinate of the apartment
 */
double Apartment::get_x () const
{
  return _x;
}

/**
 * @return the y coordinate of the apartment
 */
double Apartment::get_y () const
{
  return _y;
}

/**
 * Operator <, apartment is smaller than other if it closer to
 * [35.213506, 31.772425]
 * @param other Apartment obj
 * @return true, if this apartment is smaller than the other one,
 * false otherwise
 */
bool Apartment::operator< (const Apartment &other) const
{
  return (get_distance_from_feelbox (_x, _y)
          < get_distance_from_feelbox (other._x, other._y));

}

/**
 * Operator >, apartment is greater than other if it farther from
 * [35.213506, 31.772425]
 * @param other Apartment obj
 * @return true, if this apartment is greater than the other one,
 * false otherwise
 */
bool Apartment::operator> (const Apartment &other) const
{
  return (get_distance_from_feelbox (_x, _y)
          > get_distance_from_feelbox (other._x, other._y));
}

/**
 * calculate the distance of apartment from feelbox
 * @param point_x x coordinate of apartment
 * @param point_y y coordinate of apartment
 * @return distance of apartment from feelbox
 */
double Apartment::get_distance_from_feelbox (double point_x, double point_y)
{
  double x = point_x - X_FEEL_BOX;
  double y = point_y - Y_FEEL_BOX;
  double distance = sqrt (x * x + y * y);
  return distance;
}

/**
 * Operator ==, Two apartments are identical if their x and y values are the
 * same, to the point of an epsilon = 0.0001
 * @param other
 * @return true if the two apartments are equal, false otherwise
 */
bool Apartment::operator== (const Apartment &other) const
{
  return (abs (_x - other._x) <= EPSILON &&
          abs (_y - other._y) <= EPSILON);

}

/**
 * Insertion operator, prints the apartment in the format: (x,y)\n
 * @param os reference to std::ostream
 * @param apartment
 * @return os reference to std::ostream
 */
std::ostream &operator<< (std::ostream &os, const Apartment &apartment)
{
  os << LEFT_PARENTHESIS << apartment._x << COMMA << apartment._y
     << RIGHT_PARENTHESIS << std::endl;
  return os;
}

