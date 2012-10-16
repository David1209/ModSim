#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"
#include "part1.h"

double right_hand_diff(double (*func)(double), double x, double h)
{
    return (func(x+h) - func(x)) / h;
}

double central_diff(double (*func)(double), double x, double h)
{
    return (func(x+h) - func(x-h)) / (2*h);
}

void execute_part_one()
{
    printf(" *** Part One ***\n");
    double (*function)(double) = &sin;
    double x = PI/3;
    double h = 0.0001;
    printf("x = %f\nh = %f\n", x, h);
    printf("Result using right hand differentation: %f\n", 
            right_hand_diff(function, x, h));
    printf("Result using central differentation: %f\n", 
            central_diff(function, x, h));
}