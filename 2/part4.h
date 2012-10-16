#ifndef PART4
#define	PART4

void execute_part_four();
double function_part4(double x);

double rect_rule(double (*f)(double), double intmin, double intmax, 
        int subints);
double trap_rule(double (*f)(double), double intmin, double intmax, 
        int subints);
double simpson_rule(double (*f)(double), double intmin, double intmax, 
        int subints);
double two_point_gauss(double (*f)(double), double intmin, double intmax, 
        int subints);

#endif

