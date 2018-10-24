#include <iostream>
#include <vector> 

class Point {
public:
  double x,y;
  Point(double x, double y) : x(x), y(y) {}
  Point() : Point(0,0) {} 

  Point operator+=(const Point& rhs) {
    this->x += rhs.x; this->y += rhs.y;
    return *this; 
  }

  Point operator-=(const Point& rhs) {
    this->x -= rhs.x; this->y -= rhs.y;
    return *this; 
  }

  Point operator*=(double s) {
    this->x *= s; this->y *= s;
    return *this; 
  }


};

const Point operator+(const Point& lhs, const Point& rhs) {
  Point p(lhs);
  p+= rhs; 
  return p;
}

const Point operator-(const Point& lhs, const Point& rhs) {
  Point p(lhs);
  p-= rhs; 
  return p;
}

const Point operator*(const Point& p, double s) {
  Point result(p.x, p.y);
  result *= s;
  return result; 
}

double operator*(const Point& lhs, const Point& rhs) {
  return lhs.x*rhs.x + lhs.y*rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << "(" << point.x << "," << point.y << ")"; 
}

typedef std::vector<Point> PointList;
