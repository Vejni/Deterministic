#include <math.h>

double rosenbrock(double x, double y){
  return pow((1 - x), 2) + 100*pow((y - x*x), 2);
}

void rosenbrock_grad(double x, double y, double * grad){
  grad[0] = -400*x*y + 400*x*x*x + 2*x - 2;
  grad[1] = 200*y - 200*x*x;
}
