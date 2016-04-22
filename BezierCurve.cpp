#include "BezierCurve.h"
#include "Point.h"
#include <vector>
#include <stdexcept>

BezierCurve::BezierCurve(std::vector<Point> points)
{
  this->points = std::vector<Point>(points);
}

Point BezierCurve::getTan(double t)
{
  Point p = points[0] * (1 - t)*(1 - t) * (-3) + points[1]*(3*(1 - t)*(1 - t) - 6*(1 - t)*t) + points[2]*(6*(1 - t)*t - 3*t*t) + points[3]*3*t*t;
  return p;
}

Point BezierCurve::getPoint(double t)
{
  std::vector<Point> tmp = std::vector<Point>(this->points);

  for (int i = tmp.size() - 1; i > 0; i--) {
    for (int k = 0; k < i; k++)
        tmp[k] = tmp[k] + ( tmp[k+1] - tmp[k] ) * t;
  }

  Point result = tmp[0];
  //delete tmp;
  return result;
}

Point BezierCurve::getNextPoint()
{
  Point p = this->getPoint(this->currentPoint);
  this->currentPoint += this->precision;

  return p;
}
