#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "defines.h"
#include "part5.h"
#include <gsl/gsl_integration.h>
     
double function_part5(double x, void * params)
{
    return x*x;
}
     
void execute_part_five()
{
    printf("\n *** Part Five *** \n");
    gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
    double result, error;
    gsl_function F;
    F.function = &function_part5;
    gsl_integration_qags (&F, 0, 5, 0, 1e-7, 1000,
                        w, &result, &error); 
    printf ("result          = %f\n", result);
    printf ("intervals       = %d\n", w->size);
    gsl_integration_workspace_free (w);
}