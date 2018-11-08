#include "point.h"

class BezierCurve {
public:
  Points bi; 

  BezierCurve(const Points& bi) : bi(bi) {}
  int degree() const { return bi.size()-1; }
  Point evaluate(double t) const { return deCasteljau(t); }

  Points subdivide(int iterations) const {
    return subdivide(bi, iterations);
  }

private:
  Point deCasteljau(double t) const {
    Points bir(bi); 
    for (int r = 0; r <= degree(); r++) { 
      bir = deCasteljauStep(bir, t);
    }
    return bir[0];
  }

  Points deCasteljauStep(const Points& bi, double t) const {
    Points bir(bi.size()-1); 
    for (int i = 0; i < bi.size()-1; i++) {
      bir[i] = bi[i]*(1-t) + bi[i+1]*t; 
    }
    return bir; 
  }

  Points subdivide(const Points& points, int iterations) const {
    if (iterations == 0) return points;
    Points left, right;
    subdivideStep(points, left, right);
    left = subdivide(left, iterations-1);
    right = subdivide(right, iterations-1); 
    left.insert(left.end(), right.begin()+1, right.end());
    return left;     
  }

  void subdivideStep(const Points& pi, Points &left, Points &right) const {
    Points bi(pi);
    left.push_back(bi[0]);
    right.insert(right.begin(), bi.back()); 
    for (int i = 0; i < degree(); i++) {
      bi = deCasteljauStep(bi, 0.5);
      left.push_back(bi[0]);
      right.insert(right.begin(), bi.back()); 
    }
  }
};

int main() {
  auto quadratic = BezierCurve({{10,10},{100,100},{190,10}});
  auto cubic = BezierCurve({{10,10},{70,150},{130,10},{190,150}});
  auto quartic = BezierCurve({{10,10},{70,100},{130,10},{190,100},{250,10}});
  return 0;
}
