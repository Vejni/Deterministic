#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>



double calc_error(double * x, double * x_prev, int n){
  double total = 0;
  for (size_t i = 0; i < n; i++) {
    total += pow((x[i] - x_prev[i]), 2);
  }
  return pow(total, 0.5);
}

double calc_norm(double * x, int n){
  double total = 0;
  for (size_t i = 0; i < n; i++) {
    total += pow(x[i]*x[i], 2);
  }
  return pow(total, 0.5);
}

double backtrack_search(double (*func)(double *), double * grad, double * x0, double * dx, int n, double beta, size_t max_iter){
  double epsilon = 1.0;
  double alpha = 0.5;
  double prod = 0;
  size_t j, i = 0;
  double * x;
  if((x = (double *) malloc(n * sizeof(double))) == NULL) exit(1);

  double fx0 = func(x0);
  for (j = 0; j < n; j++){
    x[j] = x0[j];
    prod += grad[j] * dx[j];
  }


  while((func(x) > fx0 + alpha * epsilon * prod) && i < max_iter){
    epsilon *= beta;
    for (j = 0; j < n; j++) x[j] = x0[j] + epsilon * dx[j];
    i++;
  }

  return epsilon;
}

double * gradient_descent(void (*grad_func)(double *, double *), double * x, int n, double gamma, double epsilon, size_t max_iter, FILE * fp){
  double error = DBL_MAX;
  size_t j, i = 0;

  double * grad;
  if((grad = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * x_prev;
  if((x_prev = (double *) malloc(n * sizeof(double))) == NULL) exit(1);

  while (error > epsilon && i < max_iter){
    for (j = 0; j < n; j++) x_prev[j] = x[j];

    // Update
    grad_func(x, grad);
    for (j = 0; j < n; j++) x[j] -= gamma * grad[j];

    // Get error
    error = calc_error(x, x_prev, n);

    // Log
    for (j = 0; j < n; j++) fprintf(fp, "%f, ", x[j]);
    fprintf(fp, "%f \n", error);
    i++;
  }

  return x;
}

double * conjugate_gradient(double (*func)(double *), void (*grad_func)(double *, double *), double * x, int n, double epsilon, size_t max_iter, FILE * fp){
  double alpha, error, beta, temp, norm = DBL_MAX;
  size_t j, i = 0;

  double * dx;
  if((dx = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * s;
  if((s = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * x_prev;
  if((x_prev = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * grad;
  if((grad = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * grad_prev;
  if((grad_prev = (double *) malloc(n * sizeof(double))) == NULL) exit(1);

  // Iteration 0
  grad_func(x, grad);
  for (j = 0; j < n; j++) dx[j] = -grad[j];
  alpha = backtrack_search(func, grad, x, dx, n, 0.5, max_iter);
  for (j = 0; j < n; j++) {
    x[j] += alpha * dx[j];
    s[j] = dx[j];
  }

  while (norm > epsilon && i < max_iter){
    for (j = 0; j < n; j++) {
      x_prev[j] = x[j];
      grad_prev[j] = grad[j];
    }

    // Calculate Steepest Direction
    grad_func(x, grad);
    for (j = 0; j < n; j++) dx[j] = -grad[j];

    // Get beta - RF
    beta = 0;
    for (j = 0; j < n; j++){
       beta += grad[j] * grad[j];
       temp += grad_prev[j] * grad_prev[j];
     }
    beta /= temp;

    // Update Conjugate Direction
    for (j = 0; j < n; j++) s[j] = dx[j] + beta * s[j];

    // Get alpha
    alpha = backtrack_search(func, grad, x, s, n, 0.5, max_iter);

    // Update Position
    for (j = 0; j < n; j++) x[j] += alpha * s[j];

    // Log
    error = calc_error(x, x_prev, n);
    for (size_t j = 0; j < n; j++) fprintf(fp, "%f, ", x[j]);
    fprintf(fp, "%f, ", error);

    // Conditions
    norm = calc_norm(grad, n);
    fprintf(fp, "%f \n", error);
    i++;
  }

  return x;
}
