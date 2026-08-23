#pragma once
#include <stdio.h>
#include <math.h>

int is_equal(double first_number,double second_number );
int is_zero(double number);

void remove_quotes(char * line);
void remove_newline(char string[]);
void clear_input(void);
void program_crash(void);

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"