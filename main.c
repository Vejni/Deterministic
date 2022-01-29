#include "src/Deterministic.c"
#include "src/Rosenbrock.c"

int main(int argc, char *argv[]){
  int mode = argc>1? atoi(argv[1]) : 0;
  double x = argc>2? atof(argv[2]) : -1.5;
  double y = argc>3? atof(argv[3]) : -1;
  double gamma = argc>4? atof(argv[4]) : 0.00125;
  double epsilon = argc>5? atof(argv[5]) : 0.00001;
  int max_iter = argc>6? atoi(argv[6]) : 1000;
  char * path = argc>7? argv[7] : "logs/rosenbrock.csv";

  FILE *fp = fopen(path, "w");
  if(fp == NULL) exit(1);

  double * res = gradient_descent(rosenbrock_grad, x, y, gamma, epsilon, max_iter, fp);

  fclose(fp);
  return 0;
}
