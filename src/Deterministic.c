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

double backtrack_search(double (*func)(double *), void (*grad_func)(double *, double *), double * x, double * grad, int n, double alpha, double beta, size_t max_iter){
  double epsilon = 1.0;
  double left, right;
  size_t j, i = 0;

  double * temp;
  if((temp = (double *) malloc(n * sizeof(double))) == NULL) exit(1);

  do {
    left = func(x);

    grad_func(x, grad);
    right = 0;
    for (j = 0; j < n; j++) right += grad[j]*grad[j];
    right *= alpha * epsilon;
    for (j = 0; j < n; j++) temp[j] = x[j] - epsilon * grad[j];
    right += func(temp);
    printf("%f\n", func(temp));

    epsilon *= beta;
    i++;
  } while(left < right && i < max_iter);
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
  double alpha, error, beta, norm = DBL_MAX;
  size_t j, i = 0;

  double * p;
  if((p = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * x_prev;
  if((x_prev = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * grad;
  if((grad = (double *) malloc(n * sizeof(double))) == NULL) exit(1);
  double * grad_prev;
  if((grad_prev = (double *) malloc(n * sizeof(double))) == NULL) exit(1);

  grad_func(x, grad);
  for (j = 0; j < n; j++) p[j] = -grad[j];

  while (norm > epsilon && i < max_iter){
    for (j = 0; j < n; j++) x_prev[j] = x[j];
    for (j = 0; j < n; j++) grad_prev[j] = grad[j];

    // Get alpha
    alpha = backtrack_search(func, grad_func, x, grad, n, 0.3, 0.8, max_iter);
    for (j = 0; j < n; j++) x[j] += alpha * p[j];

    grad_func(x, grad);

    // Get beta
    beta = 0;
    for (j = 0; j < n; j++) beta += grad[j] * grad[j];
    for (j = 1; j < n; j++) grad_prev[0] += grad_prev[j];
    beta /= grad_prev[0];

    // Get p
    for (j = 0; j < n; j++) p[j] = -grad[j] + beta * p[j];

    // Log
    error = calc_error(x, x_prev, n);
    for (size_t j = 0; j < n; j++) fprintf(fp, "%f, ", x[j]);
    fprintf(fp, "%f \n", error);
    //printf("%f\n", error);

    // Conditions
    norm = calc_norm(grad, n);
    i++;
  }

  return x;
}
