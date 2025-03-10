#include "eqRoot.h"

#define MAX_ITER 10

typedef struct forIntegral {
    double x;
    double (*f)(double);
    double (*g)(double);
} integralNode;

double
f(double x) {
    return x * x - 6 * x + 10;
}

double
g(double x) {
    return 2 * x - 2;
}

double
h(double x) {
    return (x - 3) / 2 + 4;
}

double
area(double (*f)(double), double (*g)(double), double a, double b) {
    int i = 0;
    unsigned long long n = 1;
    double dX = (b - a) / n;
    double x_j = a;
    double mid = (a + b) / 2;
    double h = f(mid) - g(mid);
    double I = (b - a) * h;
    double Iprev = 0;

    while (fabs(I - Iprev) >= EPS) {
        ++i;
        n *= 2;
        Iprev = I;
        I = 0;
        dX = (b - a) / n;
        x_j = a;
        
        for (unsigned long long j = 0; j < n; ++j, x_j += dX) {
            I += (f(x_j + dX / 2) - g(x_j + dX / 2)) * dX;
        }

        if (i == MAX_ITER) break;
    }

    return fabs(I);
    
}

double
areaTriple(double (*f)(double), double (*g)(double), double (*h)(double), double a, double b) {
    integralNode x[3];
    x[0].x = root(f, g, a, b, 1);
    x[1].x = root(g, h, a, b, 1);
    x[2].x = root(h, f, a, b, 1);
    x[0].f = x[2].g = f;
    x[1].f = x[0].g = g;
    x[2].f = x[1].g = h;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2 - i; ++j) {
            if (x[j].x > x[j + 1].x) {
                integralNode tmp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = tmp;
            }
        }
    }
    printf("%g %g %g\n", x[0].x, x[1].x, x[2].x);
    return area(x[0].f, x[0].g, x[0].x, x[1].x) + area(x[2].f, x[2].g, x[1].x, x[2].x);
}

int
main() {
    double I = areaTriple(f, g, h, 2, 5);
    printf("%g\n", I);
}