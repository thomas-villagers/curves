#include "point.h"

PointList cornerCuttingStep(const PointList& points) {
  PointList result; 
  for (int i = 0; i < points.size()-1; i++) {
    result.push_back(points[i]*0.75 + points[i+1]*0.25); 
    result.push_back(points[i]*0.25 + points[i+1]*0.75); 
  }
  return result; 
}

PointList cornerCutting(const PointList& points, int iterations) {
  if (iterations == 0) return points;
  return cornerCutting(cornerCuttingStep(points), iterations-1);
}

int main() {
  PointList points({{10,10},{70,100},{130,10},{190,100},{250,10}});
  auto result = cornerCutting(points,3); 
  return 0;
}
