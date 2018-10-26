#include "point.h"

class BezierCurve {

public:
  PointList CVs; 

  BezierCurve(std::initializer_list<Point> pi) {
    std::copy(pi.begin(), pi.end(), back_inserter(CVs)); 
  } 

  int degree() { return CVs.size()-1; }

  Point deCasteljau(double t) {
    PointList bi; 
    std::copy(CVs.begin(), CVs.end(), back_inserter(bi));
    for (int i = 0; i < degree(); i++) { 
      bi = deCasteljauStep(bi, t);
    }
    return bi[0];
  }

  PointList subdivide(int iterations) {
    return subdivide(CVs, iterations);
  }

private:
  PointList deCasteljauStep(const PointList& CVs, double t) {
    PointList bi(CVs.size()-1); 
    for (int i = 0; i < CVs.size()-1; i++) {
      bi[i] = (CVs[i]*(1-t) + CVs[i+1]*t); 
    }
    return bi; 
  }

  PointList subdivide(const PointList& CVs, int iterations) {
    if (iterations == 0) return CVs;
    PointList left, right;
    subdivideStep(CVs, left, right);
    left = subdivide(left, iterations-1);
    right = subdivide(right, iterations-1); 
    left.insert(left.end(), right.begin()+1, right.end());
    return left;     
  }

  void subdivideStep(const PointList& CVs, PointList &left, PointList &right) {
    PointList bi;
    copy(CVs.begin(), CVs.end(), back_inserter(bi)); 
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
