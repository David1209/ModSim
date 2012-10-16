#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"
#include "part2.h"

void execute_part_two()
{
    double result;
    double (*function)(double);
    double (*derivfunction)(double);
    printf("\n *** Part Two ***\n");
    function = &f;
    printf("Bisection Method: \n");
    result = bisection_method(function, 0.0, 10.0, 0);
    printf("Uiteindelijk resultaat: %f\n", result);
    printf("\nFalse Postition Method: \n");
    result = false_position_method(function, 0.0, 2.0, 0);
    printf("Uiteindelijk resultaat: %f\n", result);
    derivfunction = &fa;
    printf("\nNewton-Raphnson Method:\n");
    result = newton_raphson(3.0, function, derivfunction, 0);
    printf("Uiteindelijk resultaat: %f\n", result);
}

double f(double x)
{
    return (x*x)-2;
}

double fa(double x)
{
    return 2 * x;
}

int is_positive(double x)
{
    if(x < 0) return 0;
    return 1;
}

int opposite_signs(double x, double y)
{
    if(is_positive(x) ^ is_positive(y)) return 1;
    return 0;
}

double bisection_method(double (*f)(double), double intmin, 
        double intmax, int rep)
{
    double center;
    if(!opposite_signs(f(intmin), f(intmax))) return 0.0;
    center = (intmin + intmax) / 2;
    if(rep >= REPS) return center;
    rep++;
    printf("Herhaling %d: Interval %f - %f, waardes %f en %f. Center: %f.\n", 
            rep, intmin, intmax, f(intmin), f(intmax), center);
    if(f(center) == 0.0) return center;
    if(opposite_signs(f(intmin), f(center))) 
        return bisection_method(f, intmin, center, rep);
    return bisection_method(f, center, intmax, rep);
}

double false_position_method(double (*f)(double), double intmin, 
        double intmax, int rep)
{
    double c;
    if(!opposite_signs(f(intmin), f(intmax))) return 0.0;
    c = intmax - f(intmax) * ((intmax-intmin)/(f(intmax)-f(intmin)));
    if(rep >= REPS) return c;
    rep++;
    printf("Herhaling %d: Interval %f - %f, waardes %f en %f. C: %f\n", 
            rep, intmin, intmax, f(intmin), f(intmax), c);
    if(f(c) == 0.0) return ;
    if(opposite_signs(f(intmin), f(c))) 
        return false_position_method(f, intmin, c, rep);
    return false_position_method(f, c, intmax, rep);
}

double newton_raphson(double startx, double(*f)(double), 
        double(*fa)(double), int rep)
{
    double newx;
    if(rep >= REPS) return startx;
    rep++;
    newx = startx - (f(startx) / fa(startx));
    printf("Herhaling %d. Oude x: %f. Nieuwe x: %f\n", rep, startx, newx);
    return newton_raphson(newx, f, fa, rep);
}