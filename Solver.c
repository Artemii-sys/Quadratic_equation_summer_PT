#include <stdio.h>
#include <stdlib.h>
#include "roots.h"

#define my_assert(expression) do\
 { if (!expression) abort();} \
 while(0)

const double EPS = 1e-9;

//условная комплияция, assert не должен работать если включён флаг компиляции -DNDEBUG
int is_equal(double first_number,double second_number ){
    if (fabs(first_number - second_number) <= EPS){
        return 1;
    }
    return 0;
}

int is_zero(double number){
    return is_equal(number, 0);
}

int solve_for_constant(double c){
    if (is_zero(c)){
        return INFINITY_ROOTS;
    }
    else{
        return ZERO_ROOTS;
    }
}


// static const int INFINITY_ROOTS = 3;



int solve_linear_equation(double a, double b, double *x1){
    if (is_zero(a)){
        return solve_for_constant(b);
    }
    else{
        *x1 = -b / a;
        return ONE_ROOT;
    }
}

double calculate_discriminant(double a, double b, double c){
    double Discriminant = b * b - 4 * a * c;
    return Discriminant;
}

int solve_discriminant(double a, double b, double c,  double *x1, double *x2){
    double Discriminant = calculate_discriminant(a,b,c);
    if (Discriminant > 0){
        *x1 = (-b + sqrt(Discriminant)) /  (2 * a);
        *x2 = (-b - sqrt(Discriminant)) /  (2 * a);
        return TWO_ROOTS;
    }
    else if (is_zero(Discriminant)){
        *x1 = -b / (2 * a);
        return ONE_ROOT;
    }
    return ZERO_ROOTS;
}


int solve_quadratic(double a, double b, double c, double *x1, double *x2){
    my_assert(x1 != 0);
    my_assert(x2 != 0);


    if (is_zero(a)){
        return solve_linear_equation(b,c, x1);
    }

    else{
        return solve_discriminant(a,b,c,x1,x2);

    }
}
