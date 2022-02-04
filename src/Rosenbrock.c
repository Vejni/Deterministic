#include <math.h>

double rosenbrock(double * x){
  return pow((1 - x[0]), 2) + 100*pow((x[1] - x[0]*x[0]), 2);
}

void rosenbrock_grad(double * x, double * grad){
  grad[0] = -400*x[0]*x[1] + 400*x[0]*x[0]*x[0] + 2*x[0] - 2;
  grad[1] = 200*x[1] - 200*x[0]*x[0];
}
