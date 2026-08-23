#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "..\Headers\solver_functions.h"
#include "..\Headers\additional_functions.h"


int main(int argc, char *argv[]){
    char buffer[200] = {0};
    char * path = NULL;
    if (argc < 2) {
        printf("Enter the path to the file with test inputs (can be with quotes): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input.\n");
            program_crash();
        }
        remove_newline(buffer);
        remove_quotes(buffer);
        path = buffer;
    } 
    else {
        remove_quotes(argv[1]);
        path = argv[1];
    }

    NUMBER_OF_ROOTS number_of_roots = NO_NUMBER;
    double x1 = 0;
    double x2 = 0;
    double a = 0;
    double b = 0;
    double c = 0;
    double result_for_x1 = 0;
    double result_for_x2 = 0;
    printf("Running test from: " RED "%s" RESET "\n", path);
    FILE *testfile = fopen(path, "r");

    if (testfile == NULL) {
        printf("Problem to open file with tests\n");
        program_crash();
    }

    FILE *logfile = fopen("log.txt", "w");
    if (logfile == NULL) {
        perror("Problem");
        printf("Problem to create log file\n");
        fclose(testfile);
        program_crash();
    }
    int counter_of_passed_tests = 0;
    int number_all_tests = 0;
    while (fscanf(testfile, "%lf,%lf,%lf, %d, %lf,%lf", &a, &b, &c, &number_of_roots, &result_for_x1, &result_for_x2) == 6) {
        number_all_tests++;
        if (check_for_number_of_roots_and_solve(logfile, a, b, c, x1, x2, number_of_roots, result_for_x1, result_for_x2)){
            counter_of_passed_tests += 1;
        }
    }
    printf("\n//////////////////////\n");
    printf("Was made " GREEN "%d" RESET " tests\n" "Succesfully passed " YELLOW "%d" RESET "\n", number_all_tests, counter_of_passed_tests);
    printf("Unpassed tests saved into " YELLOW "log.txt" RESET);
    fclose(logfile);
    fclose(testfile);
    return EXIT_SUCCESS;
}
