#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EPS 1e-9

double
root(double (*f)(double), double (*g)(double), double a, double b, int der2) {
    double x = -(f(b) - g(b)) * (a - b) / (f(a) - f(b) - g(a) + g(b)) + b;
    if (fabs(f(x) - g(x)) < EPS) return x;
    if (x > b || x < a) {
        der2 *= -1;
    }
    return (der2 > 0) ? root(f, g, x, b, der2) : root(f, g, a, x, der2);
}