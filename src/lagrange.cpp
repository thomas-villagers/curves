#include "point.h"

class Lagrange {
public: 
  Points pi; 
  std::vector<double> ti; 

  Lagrange(const Points& pi) : pi(pi) {
    for (int i = 0; i < pi.size(); i++) { 
      ti.push_back(i);  // aequidistant 
    }
  } 

  Point evaluate(double t) const {
    Point result;
    for(int i = 0; i < pi.size(); i++) {
      result += pi[i]*lagrange(i,t); 
    }
    return result;
  }

private:
  double lagrange(int i, double t) const {
    double nominator = 1;
    double denominator = 1;
    for (int j = 0; j < pi.size(); j++) {
      if (j != i) {
        nominator *= t - ti[j];
	denominator *= ti[i] - ti[j]; 
      }
    }
    return nominator/denominator;
  }
};

template<typename T> 
Points sampling(const T& curve, double a, double b, int segments) {
  double dt = (b-a)/segments; 
  double t = a;
  Points result;
  for (int i = 0; i < segments+1; i++,t+=dt) {
    result.push_back(curve.evaluate(t));
  }
  return result; 
}

int main() {
  auto curve = Lagrange({{1,0},{2,2},{3,1},{4,4},{5,2}});
  Points points = sampling(curve, curve.ti[0], curve.ti.back(), 50);  
  return 0; 
}
