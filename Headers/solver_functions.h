#pragma once
#include <stdio.h>
#include <math.h>


typedef enum NUMBER_OF_ROOTS {
    ZERO_ROOTS, 
    ONE_ROOT, 
    TWO_ROOTS, 
    INFINITY_ROOTS, 
    ENTER_ERROR,
    NO_NUMBER,
} NUMBER_OF_ROOTS;

NUMBER_OF_ROOTS solve_quadratic(double a, double b, double c, double *x1, double *x2);

void write_into_logfile(FILE *logfile, double a,double b, double c,double x1, double x2, int number_of_roots, double result_for_x1, double result_for_x2);

int check_for_number_of_roots_and_solve(FILE *logfile, double a,double b, double c,double x1, double x2, int number_of_roots, double result_for_x1, double result_for_x2);
