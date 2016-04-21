#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Point::operator==(const Point &op) const {
  return( x == op.x && y == op.y && z == op.z);
}

Point& Point::operator=(const Point &op) {
  x = op.x; y = op.y; z = op.z;
  return *this;
}

Point Point::operator+(const Point &op) const {
  return( Point( x + op.x, y + op.y, z + op.z) );
}

Point Point::operator-(const Point &op) const {
  return( Point( x - op.x, y - op.y, z - op.z) );
}

Point& Point::operator*=(const double op) {
  x *= op; y *= op; z *= op;
  return *this;
}

Point Point::operator*(const double op) const {
  return ( Point( x * op, y * op, z * op) );
}

Point& Point::operator/=(const double op) {
  x /= op; y /= op; z /= op;
  return *this;
}

Point Point::operator/(const double op) const {
  return ( Point( x / op, y / op, z / op) );
}
