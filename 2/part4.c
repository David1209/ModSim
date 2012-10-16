#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"
#include "part4.h"

void execute_part_four()
{
    double (*func)(double) = &function_part4;
    printf("\n *** Part Four ***\n");
    printf("Integral using rectangle rule: %f\n", 
            rect_rule(func, 0.0, 5.0, 50));
    printf("Integral using trapezoidal rule: %f\n", 
            trap_rule(func, 0.0, 5.0, 50));
    printf("Integral using Simpson rule: %f\n", 
            simpson_rule(func, 0.0, 5.0, 50));
    printf("Integral using Two Point Gauss: %f\n", 
            two_point_gauss(func, 0.0, 5.0, 50));
}

double function_part4(double x)
{
    return x*x;
}

double rect_rule(double (*f)(double), double intmin, double intmax, 
        int subints)
{
    int i;
    double total = 0.0;
    double intsize = (intmax - intmin) / subints;
    for(i = 0; i < subints; i++)
        total += f(intmin + (i * intsize) + (0.5 * intsize));
    return total * ((intmax-intmin)/subints);
}

double trap_rule(double (*f)(double), double intmin, double intmax, 
        int subints)
{
    int i;
    double total = 0.0;
    double intsize = (intmax - intmin) / subints;
    for(i = 0; i < subints; i++)
        total += (f(intmin + (i * intsize)) + f(intmin + ((i+1) * intsize)))/2;
    return total * ((intmax-intmin)/subints);
}

double simpson_rule(double (*f)(double), double intmin, double intmax, 
        int subints)
{
    return (2*rect_rule(f, intmin, intmax, subints) + 
            trap_rule(f, intmin, intmax, subints)) / 3;
}

double two_point_gauss(double (*f)(double), double intmin, 
        double intmax, int subints)
{
    int i;
    double total = 0.0;
    double intsize = (intmax - intmin) / subints;
    for(i = 0; i < subints; i++)
    {
        double p1, p2, x;
        x = intmin + (i * intsize);
        p1 = x + (0.5*intsize)*(1+(1/sqrt(3)));
        p2 = x + (0.5*intsize)*(1-(1/sqrt(3)));
        total += (f(p1) + f(p2)) / 2;
    }
    return total * ((intmax-intmin)/subints);
}