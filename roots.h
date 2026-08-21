#pragma once
#include <math.h>   


int is_equal(double first_number,double second_number );

int test(void);

enum VariantsOfSolutions {
    ZERO_ROOTS, 
    ONE_ROOT, 
    TWO_ROOTS, 
    INFINITY_ROOTS, 
    ENTER_ERROR
};

//тест логи, is eqaul


int solve_quadratic(double a, double b, double c, double *x1, double *x2);


