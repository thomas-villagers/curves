#include <eigen/Eigen/Dense> 
#include "point.h" 

template<int n> class LeastSquares {
public: 
  std::vector<double> ti; 
  Eigen::VectorXd cx, cy; 

  LeastSquares(const Points& pi) {
    for (int i = 0; i < pi.size(); i++) { 
      ti.push_back(i); // aequidistant 
    }
    Eigen::MatrixXd M(pi.size(),n+1); 
    for (int i = 0; i < pi.size(); i++) {
      for (int j = 0; j < n+1; j++) {
        M(i,j) = monomialBasis(ti[i], j); 
      }
    }
    Eigen::VectorXd bx(pi.size());
    Eigen::VectorXd by(pi.size());
    for (int i = 0; i < pi.size(); i++) {
      bx(i) = pi[i].x; 
      by(i) = pi[i].y;
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
  Points points = sampling(curve,curve.ti[0], curve.ti.back(), 30);
  return 0;
}
