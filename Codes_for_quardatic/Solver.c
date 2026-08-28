#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "..\Headers\solver_functions.h"
#include "..\Headers\additional_functions.h"

#define NDEBUG
#ifdef NDEBUG
    #define my_assert(equation) 
#else
    #define my_assert(equation) if(equation){printf("smth"); abort();}
#endif

const double EPS = 1e-9;

int is_equal(double first_number,double second_number ){
    if (fabs(first_number - second_number) <= EPS){
        return 1;
    }
    return 0;
}

int is_zero(double number){
    return is_equal(number, 0);
}

static NUMBER_OF_ROOTS solve_for_constant (double c)
    {
    return (is_zero (c))? INFINITY_ROOTS : ZERO_ROOTS;
    }

static NUMBER_OF_ROOTS solve_linear_equation(double a, double b, double *x1){
    if (is_zero(a)){
        return solve_for_constant(b);
    }
    else{
        *x1 = -b / a;
        return ONE_ROOT;
    }
}

static double calculate_discriminant(double a, double b, double c){
    return (b * b - 4 * a * c);
}

static NUMBER_OF_ROOTS solve_discriminant(double a, double b, double c,  double *x1, double *x2){
    double Discriminant = calculate_discriminant(a,b,c);
    if (Discriminant > 0){
        *(x1) = (-b + sqrt(Discriminant)) /  (2 * a);
        *x2 = ((-b) - sqrt(Discriminant)) /  (2 * a);
        return TWO_ROOTS;
    }
    else if (is_zero(Discriminant)){
        *x1 = -b / (2 * a);
        return ONE_ROOT;
    }
    return ZERO_ROOTS;
}

NUMBER_OF_ROOTS solve_quadratic(double a, double b, double c, double *x1, double *x2){
    my_assert(x1 == NULL);
    my_assert(x2 == NULL);


    if (is_zero(a)){
        return solve_linear_equation(b,c, x1);
    }

    else{
        return solve_discriminant(a,b,c,x1,x2);

    }
}
