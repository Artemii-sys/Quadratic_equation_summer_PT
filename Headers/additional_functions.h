#pragma once
#include <stdio.h>
#include <math.h>

/**
 * @brief Compares two double numbers with a small allowed error.
 * @param first_number First number.
 * @param second_number Second number.
 * @return 1 if the numbers are close enough, 0 otherwise.
 */
int is_equal(double first_number,double second_number );
/**
 * @brief Checks if a number is close to zero.
 * @param number Number to check.
 * @return 1 if the number is zero, 0 otherwise.
 */
int is_zero(double number);

/**
 * @brief Removes quotes from a file path.
 * @param line String with the path.
 */
void remove_quotes(char * line);
/**
 * @brief Removes the newline at the end of a string.
 * @param string String to change.
 */
void remove_newline(char string[]);
/** @brief Clears the rest of the current input line. */
void clear_input(void);
/** @brief Shows an error and closes the program. */
void program_crash(void);

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"
