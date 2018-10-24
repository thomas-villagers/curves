#include <point.h>

class Lagrange {

public: 
  PointList CVs; 
  std::vector<double> ti; 

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
    float denominator = 1;
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
PointList sampling(const T& curve, double a, double b, int segments) {
  double dt = (b-a)/segments; 
  double t = a;
  PointList result;
  for (int i = 0; i < segments+1; i++,t+=dt) {
    result.push_back(curve.evaluate(t));
  }
  return result; 
}

int main() {
  auto curve = Lagrange({{1,0},{2,2},{3,1},{4,4},{5,2}});
  PointList points = sampling(curve, curve.ti[0], curve.ti.back(), 50);  
  return 0; 
}
