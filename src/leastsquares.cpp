#include <eigen/Eigen/Dense> 
#include "point.h" 
#include "canvas.h"

using namespace std; 
using namespace Eigen;

template<int T> class LeastSquares {

public: 
  PointList CVs;
  vector<int> ti; // uniform ? 
  VectorXd cx, cy; 

  LeastSquares(std::initializer_list<Point> pi) {
    copy(pi.begin(), pi.end(), back_inserter(CVs)); 
    for (int i = 0; i < CVs.size(); i++) {  // aequidistant 
      ti.push_back(i); 
    }

    MatrixXd M(CVs.size(),T+1); 
    for (int i = 0; i < CVs.size(); i++) {
      for (int j = 0; j < T+1; j++) {
        M(i,j) = monomialBasis(ti[i], j); 
      }
    }
    VectorXd bx(CVs.size());
    VectorXd by(CVs.size());
    for (int i = 0; i < CVs.size(); i++) {
      bx(i) = CVs[i].x; 
      by(i) = CVs[i].y;
    }

    cx = M.colPivHouseholderQr().solve(bx);
    cy = M.colPivHouseholderQr().solve(by);
  } 

  Point evaluate(double t) const {
    Point result; 
    for (int i = 0; i < T+1; i++) {
      result.x += monomialBasis(t, i)*cx(i);
      result.y += monomialBasis(t, i)*cy(i);
    }
    return result; 
  }

  double monomialBasis(double t, int i) const {
    double result=1;
    for (int j = 0; j < i; j++) {
      result*=t;
    }
    return result;
  }
};

template<typename T> PointList sampling(const T& curve, int steps) {
  double t0 = curve.ti[0];
  double t1 = curve.ti.back();
  double dt = (t1-t0)/steps; 
  double t = t0;
  PointList result;
  for (int i = 0; i < steps+1; i++,t+=dt) {
    result.push_back(curve.evaluate(t));
  }
  return result; 
}

int main() {
  auto curve = LeastSquares<4>({{10,10},{70,100},{130,10},{190,100},{250,10}});
  PointList points = sampling(curve,30);
  return 0;
}
