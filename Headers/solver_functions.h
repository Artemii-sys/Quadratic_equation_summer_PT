#pragma once
#include <stdio.h>
#include <math.h>


/** @brief What result the equation has. */
typedef enum NUMBER_OF_ROOTS {
    ZERO_ROOTS, 
    ONE_ROOT, 
    TWO_ROOTS, 
    INFINITY_ROOTS, 
    ENTER_ERROR,
    NO_NUMBER,
} NUMBER_OF_ROOTS;

/**
 * @brief Solves a quadratic equation.
 * @param a First coefficient.
 * @param b Second coefficient.
 * @param c Third coefficient.
 * @param x1 Place where the first root is written.
 * @param x2 Place where the second root is written.
 * @return Number of roots.
 */
NUMBER_OF_ROOTS solve_quadratic(double a, double b, double c, double *x1, double *x2);

/**
 * @brief Writes information about a failed test to the log file.
 * @param logfile File where the information will be written.
 * @param a First coefficient from the test.
 * @param b Second coefficient from the test.
 * @param c Third coefficient from the test.
 * @param x1 First root received from the program.
 * @param x2 Second root received from the program.
 * @param number_of_roots Expected number of roots.
 * @param result_for_x1 Expected first root.
 * @param result_for_x2 Expected second root.
 */
void write_into_logfile(FILE *logfile, double a,double b, double c,double x1, double x2, int number_of_roots, double result_for_x1, double result_for_x2);

/**
 * @brief Solves one test and compares the answer with the expected one.
 * @param logfile File for failed test information.
 * @param a First coefficient from the test.
 * @param b Second coefficient from the test.
 * @param c Third coefficient from the test.
 * @param x1 First expected/program root value.
 * @param x2 Second expected/program root value.
 * @param number_of_roots Expected number of roots.
 * @param result_for_x1 Expected first root.
 * @param result_for_x2 Expected second root.
 * @return 1 if the test passed, 0 otherwise.
 */
int check_for_number_of_roots_and_solve(FILE *logfile, double a,double b, double c,double x1, double x2, int number_of_roots, double result_for_x1, double result_for_x2);
