#include "point.h"

Points cornerCuttingStep(const Points& pi) {
  Points result; 
  for (int i = 0; i < pi.size()-1; i++) {
    result.push_back(pi[i]*0.75 + pi[i+1]*0.25); 
    result.push_back(pi[i]*0.25 + pi[i+1]*0.75); 
  }
  return result; 
}

Points cornerCutting(const Points& pi, int iterations) {
  if (iterations == 0) return pi;
  return cornerCutting(cornerCuttingStep(pi), iterations-1);
}

int main() {
  Points points = cornerCutting({{10,10},{70,100},{130,10},{190,100},{250,10}},3); 
  return 0;
}
