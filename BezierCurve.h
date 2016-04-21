#ifndef BEZIER_H
#define BEZIER_H

#include "Point.h"
#include <vector>

class BezierCurve
{
public:
  BezierCurve(std::vector<Point> points);
  Point getPoint(double t);
  Point getTan(double t);
  Point getNextPoint();
protected:
	std::vector<Point> points;
  double precision = 0.01;
  double currentPoint = 0.0;
};

#endif
