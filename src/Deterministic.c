#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

double * gradient_descent(void (*grad_func)(double, double, double *), double x, double y, double gamma, double epsilon, size_t max_iter, FILE * fp){
  double error = DBL_MAX;
  double x_prev, y_prev;
  size_t i = 0;

  double * grad;
  if((grad = (double *) malloc(2 * sizeof(double))) == NULL)
    exit(1);

  while (error > epsilon && i < max_iter){
    x_prev = x;
    y_prev = y;
    grad_func(x, y, grad);
    x -= gamma * grad[0];
    y -= gamma * grad[1];
    error = pow(pow((x - x_prev), 2) + pow((y - y_prev), 2), 0.5);
    fprintf(fp, "%f %f %f\n", x, y, error);
    i++;
  }

  // use grad to return values
  grad[0] = x;
  grad[1] = y;
  return grad;
}
