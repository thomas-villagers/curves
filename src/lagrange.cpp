#include <point.h>
#include "canvas.h"

using namespace std; 

class Lagrange {

public: 
  PointList CVs; 
  vector<double> ti; 

  Lagrange(std::initializer_list<Point> p) {
    std::copy(p.begin(), p.end(), back_inserter(CVs)); 
    for (int i = 0; i < CVs.size(); i++) {  // aequidistant 
      ti.push_back(i); 
    }
  } 

  Point evaluate(double t) const {
    Point result;
    for(int i = 0; i < CVs.size(); i++) {
      result += CVs[i]*lagrange(i,t); 
    }
    return result;
  }

private:
  double lagrange(int i, double t) const {
    float nominator = 1;
    float denominator =1;
    for (int j = 0; j < CVs.size(); j++) {
      if (j != i) {
        nominator *= t - ti[j];
	denominator *= ti[i] - ti[j]; 
      }
    }
    return nominator/denominator;
  }
};

template<typename T> 
PointList sampling(const T& curve, double t0, double t1, int steps) {
  double dt = (t1-t0)/steps; 
  double t = t0;
  PointList result;
  for (int i = 0; i < steps+1; i++,t+=dt) {
    result.push_back(curve.evaluate(t));
  }
  return result; 
}

int main() {
  auto curve = Lagrange({{10,10},{70,100},{130,10},{190,100},{250,10}});
  PointList points = sampling(curve, curve.ti[0], curve.ti.back(), 40);  
  return 0; 
}
