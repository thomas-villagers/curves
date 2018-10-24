#include <eigen/Eigen/Dense> 
#include "point.h" 

using namespace Eigen;

template<int n> class LeastSquares {

public: 
  PointList CVs;
  std::vector<int> ti; 
  VectorXd cx, cy; 

  LeastSquares(std::initializer_list<Point> pi) {
    copy(pi.begin(), pi.end(), back_inserter(CVs)); 
    for (int i = 0; i < CVs.size(); i++) {  // aequidistant 
      ti.push_back(i); 
    }
    MatrixXd M(CVs.size(),n+1); 
    for (int i = 0; i < CVs.size(); i++) {
      for (int j = 0; j < n+1; j++) {
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
    for (int i = 0; i < n+1; i++) {
      result.x += monomialBasis(t, i)*cx(i);
      result.y += monomialBasis(t, i)*cy(i);
    }
    return result; 
  }

private: 
  double monomialBasis(double t, int i) const {
    double result=1;
    for (int j = 0; j < i; j++) {
      result *= t;
    }
    return result;
  }
};

int main() {
  auto curve = LeastSquares<3>({{1,0},{2,2},{3,1},{4,4},{5,2}});  
  PointList points = sampling(curve,curve.ti[0], curve.ti.back(), 30);
  return 0;
}
