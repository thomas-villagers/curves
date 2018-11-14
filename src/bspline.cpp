#include "point.h" 
#include <cassert> 

typedef std::vector<double> Knots; 

template<int n> class BSpline {
public: 
  Points di; 
  Knots T; 

  static BSpline endPointInterpolation(const Points& di) {
    Knots T; 
    T.insert(T.begin(), n, 0);
    for (double i = 0; i < di.size()-n+1; i++) { 
      T.push_back(i); 
    }
    T.insert(T.end(), n, T.back()); 
    return BSpline<n>(di, T);
  }

  static BSpline simpleKnotVector(const Points& di) {
    Knots T; 
    for (double i = 0; i < di.size()+n+1; i++) { 
      T.push_back(i); 
    }
    return BSpline<n>(di, T);
  }

  Point evaluate(double t) const { return deBoor(t); }

  void insertKnot(double t) {
    int i = findKnotInterval(t);
    Points dj(di.begin()+i-n, di.begin()+i+1);
    dj = deBoorStep(dj, t, i, 1);
    di.erase(di.begin()+i-n+1, di.begin()+i);
    di.insert(di.begin()+i-n+1, dj.begin(), dj.end());
    T.insert(T.begin()+i+1, t); 
  }

private: 
  BSpline(const Points& di, const Knots& T) : di(di), T(T) {} 

  Point deBoor(double t) const {
    int i = findKnotInterval(t);
    Points dj(di.begin()+i-n, di.begin()+i+1);
    for (int r = 1; r <= n; r++) {
      dj = deBoorStep(dj, t, i, r);
    }
    return dj[0]; 
  }

  Points deBoorStep(const Points& di, double t, int i, int r) const {
    Points dj(di.size()-1);
    for (int j = 0; j < di.size()-1; j++) {
      double alpha = (t - T[i-n+j+r]) / (T[i+j+1] - T[i-n+j+r]); 
      dj[j] = di[j]*(1-alpha) + di[j+1]*alpha; 
    }
    return dj; 
  }

  int findKnotInterval(double t) const {
    if (t >=  T.back()) return T.size()-n-2; 
    assert(t >= T[n]); 
    return findKnotInterval(n, T.size(), t);
  }

  int findKnotInterval(int a, int b, double t) const {
    int mid = (a+b)/2;
    if (t < T[mid]) return findKnotInterval(a, mid, t); 
    if (t < T[mid+1]) return mid;
    return findKnotInterval(mid+1, b, t);
  }
};

int main() {
  Points points({{0,0}, {-0.5,-0.5}, {-1,1}, {-0.5,1.75}, {2,1.75}, {2.2,0.5}, {2.6,0.5}, {2.6,1.6}, {4,1.25}, {4.5,0.5}}); 
  auto quadratic = BSpline<2>::endPointInterpolation(points); 
  auto quadratic2 = BSpline<2>::simpleKnotVector(points); 
  auto cubic = BSpline<3>::endPointInterpolation(points);
  auto cubic2 = BSpline<3>::simpleKnotVector(points);
  auto quartic = BSpline<4>::endPointInterpolation(points); 
  auto quartic2 = BSpline<4>::simpleKnotVector(points); 
  return 0;
}
