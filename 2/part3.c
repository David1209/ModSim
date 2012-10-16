#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"
#include "part2.h"
#include "part3.h"

void execute_part_three()
{
    double result;
    double (*func)(double);
    double (*derivfunc)(double);
    printf("\n *** Part Three ***\n");
    func = &function;
    derivfunc = &functiona;
    result = newton_raphson(-2.2, func, derivfunc, 0);
    printf("Uiteindelijk resultaat: %f\n", result);
}

double function(double x)
{
    return pow(x, 3.0) - (3*x) - 2;
}

double functiona(double x)
{
    return pow(3*x, 2.0) - 3;
}