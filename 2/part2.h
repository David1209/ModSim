#ifndef PART2
#define	PART2

void execute_part_two();
double f(double x);
double fa(double x);
int is_positive(double x);
int opposite_signs(double x, double y);
double bisection_method(double (*f)(double), double intmin, 
        double intmax, int rep);
double false_position_method(double (*f)(double), double intmin, 
        double intmax, int rep);
double newton_raphson(double startx, double(*f)(double), 
        double(*fa)(double), int rep);
#endif