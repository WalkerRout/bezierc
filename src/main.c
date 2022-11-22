#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __V2d_t {
  double x, y;
} V2d;

// returns a vector of size num_elements+1, as the vector includes the lower and upper bounds a and b
double *lin_space(double a, double b, unsigned int num_elements){
  double *spaced = malloc(sizeof(double) * num_elements + 1); // +1 for the initial bound at the beginning

  spaced[0] = a;
  double step_value = b / (double) num_elements;
  
  int i;
  for(i = 1; i < num_elements + 1; ++i){
    spaced[i] = spaced[i-1] + step_value;
  }

  return spaced;
}

int __factorial(int n, int acc){
  if(n <= 1) return acc;
  return __factorial(n-1, n * acc);
}
#define factorial(n) (__factorial((n), 1))

int binomial_coefficient(int n, int i){
  int res = factorial(n) / (factorial(i) * factorial(n - i));
  //printf("binomial_coefficient: %lf\n", res);
  return res;
}

double bernstein_polynomial(int n, int i, double t){
  double res = binomial_coefficient(n, i) * pow(t, i) * pow(1 - t, n - i);
  return res;
}

V2d bezier_curve(double x, V2d *points, int num_points){
  V2d res = {0};

  int i;
  for(i = 0; i < num_points; ++i){
    double bern_poly = bernstein_polynomial(num_points-1, i, x);
    res.x += bern_poly * points[i].x;
    res.y += bern_poly * points[i].y;
  }

  return res;
}

void generate_curve(V2d *points, unsigned int num_points) {
  double *x_vals = lin_space(0.0, 1.0, 50);

  printf("\t----------------------------\n");
  printf("\t Generating Bezier Curve... \n");
  printf("\t----------------------------\n\n");

  printf("[");
  for(int i = 0; i <= 50; ++i){
    V2d t = bezier_curve(x_vals[i], points, num_points);
    printf("Vec2(%lf, %lf), ", t.x, t.y);
  }
  printf("\b\b]\n");
  
  free(x_vals);
}

int main(void) {
  V2d points[] = {
    (V2d) {1, 1},
    (V2d) {6, 0},
    (V2d) {8, 20},
    (V2d) {12, 2}
  };
  const int num_points = sizeof(points)/sizeof(V2d);
  
  generate_curve(points, num_points);
  return 0;
}	
