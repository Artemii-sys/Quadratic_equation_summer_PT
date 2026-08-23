#include <stdio.h>
#include <stdlib.h>
#include "..\Headers\solver_functions.h"
#include "..\Headers\additional_functions.h"

void write_into_logfile(FILE *logfile, double a,double b, double c,double x1, double x2, int number_of_roots, double result_for_x1, double result_for_x2){
    fprintf(logfile, "False\n");
    fprintf(logfile, "x1 is %.4lf\n", x1);
    fprintf(logfile, "x2 is %.4lf\n", x2);
    fprintf(logfile, "drop with parameter a = %lf /// b = %lf /// c = %lf\n", a,b,c);
    fprintf(logfile, "Was expecting number of roots %d \nx1 = %lf\nx2 = %lf\n", number_of_roots, result_for_x1, result_for_x2);
    fprintf(logfile, "\n/////////////////////////////\n\n");
}

int check_for_number_of_roots_and_solve(FILE *logfile, double a, double b, double c,double x1, double x2, int number_of_roots, double result_for_x1, double result_for_x2){
    NUMBER_OF_ROOTS actual_number_of_roots = solve_quadratic(a, b, c, &x1, &x2);
    int test_passed = 0;

    switch (number_of_roots) {
        case TWO_ROOTS:
            test_passed = actual_number_of_roots == TWO_ROOTS &&
                ((is_equal(x1, result_for_x1) && is_equal(x2, result_for_x2)) ||
                 (is_equal(x1, result_for_x2) && is_equal(x2, result_for_x1)));
            break;

        case ONE_ROOT:
            test_passed = actual_number_of_roots == ONE_ROOT &&
                (is_equal(x1, result_for_x1) || is_equal(x1, result_for_x2));
            break;

        case ZERO_ROOTS:
            test_passed = actual_number_of_roots == ZERO_ROOTS;
            break;

        case INFINITY_ROOTS:
            test_passed = actual_number_of_roots == INFINITY_ROOTS;
            break;

        default:
            printf("There is unusable number in \"number of roots\"\n");
            break;
    }
    if (!test_passed){
        switch (number_of_roots){
            case ZERO_ROOTS:
            case ONE_ROOT:
            case TWO_ROOTS:
            case INFINITY_ROOTS:
                write_into_logfile(logfile, a, b, c, x1, x2, number_of_roots, result_for_x1, result_for_x2);
                break;
            default:
                break;
        }
        return test_passed;
    }
    return test_passed;
}   
