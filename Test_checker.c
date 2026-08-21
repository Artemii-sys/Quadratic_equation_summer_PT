#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "roots.h"

int main(int argc, char *argv[]){
    char way[100] = {};
    if (argc < 2){
        printf("Enter the way to the file with test inputs");
        if (scanf("%99s", way) != 1) {
            printf("Error reading input.\n");
            return 1;
        }
    double x1 = 0;
    double x2 = 0;

    double a = 0;
    double b = 0;
    double c = 0;
    double result_for_x1 = 0;
    double result_for_x2 = 0;
    //argc argv
    printf("Введите путь до файла с тестовыми задачами:   ");

    FILE *testfile = fopen(way, "r");

    FILE *logfile = fopen("C:\\Users\\ArtemiiNikPT\\Desktop\\log.txt", "w");
        if (logfile == NULL) {
            return 1;
        }

    while (fscanf(testfile, "%lf,%lf,%lf,%lf,%lf", &a, &b, &c, &result_for_x1, &result_for_x2) == 5) {
        if (solve_quadratic(a,b,c,&x1,&x2) == TWO_ROOTS){
            if ( (is_equal(x1, result_for_x1) && is_equal(x2, result_for_x2)) || (is_equal(x1, result_for_x2) && is_equal(x2, result_for_x1)) ){
                printf("True\n");
            }
        }
        else{
            fprintf(logfile, "False\n");
            fprintf(logfile, "x1 is %.4lf\n", x1);
            fprintf(logfile, "x2 is %.4lf\n", x2);
            fprintf(logfile, "drop with parameter a = %lf /// b = %lf /// c = %lf\n", a,b,c);
            fprintf(logfile, "Was expecting x1 = %lf\nx2 = %lf\n", result_for_x1, result_for_x2);
            fprintf(logfile, "\n/////////////////////////////\n\n");
            
        } 
    }
    fclose(logfile);
    fclose(testfile);
}