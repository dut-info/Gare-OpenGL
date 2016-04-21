#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point();
	Point(const double, const double, const double);
	bool operator==(const Point &op) const; 
  Point& operator=(const Point &op);
  Point operator+(const Point &op) const;
  Point operator-(const Point &op) const;
  Point& operator*=(const double op);
  Point operator*(const double op) const;
  Point& operator/=(const double op);
  Point operator/(const double op) const;
	double x;
	double y;
	double z;
};

#endif
