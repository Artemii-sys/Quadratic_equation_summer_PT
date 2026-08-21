#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "roots.h"

// int check_for_parameter_a(int a, int b, int c, char *x1, char *x2){
//     if (a == 0){
//         lineal_equation(b,c, x1);
//     }

//     else{
//         check_for_Discriminant(a,b,c,x1,x2);

//     }
//}



// argc argv 

// int check_for_test(void){
//     char status_agree[4] = "1";
//     printf("Do u want to make some tests to check Script? (y/n)");
//     scanf("%3s", status_agree);
//     if (strcmp(status_agree, "y") == 0){
//         test();
//         printf("///////////////////////////////\n");
//         printf("Test completed. Check log file\n");
//         printf("///////////////////////////////\n");
//     }
//     else{
//         printf("starting without test");
//     }
//     return 0;
// }
void show_result(int n_of_roots, double x1, double x2){
    switch(n_of_roots){
        case ZERO_ROOTS: 
            printf("no roots for this equation\n");
            break;
        
        case ONE_ROOT:
            printf("there is only 1 root x1 = %.4lf\n", x1);
            break;

        case TWO_ROOTS:
            printf("there are 2 roots: x1 = %.4lf\nx2 = %.4lf\n", x1, x2);
            break;
        case INFINITY_ROOTS:
            printf("Any x is a root for this equation\n");
            break;
        
        case ENTER_ERROR:
            printf("Enter problem. Got not number");
            break;
    }
}


int main(void) {
    double a = 0;
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;
    enum VariantsOfSolutions n_of_roots = ENTER_ERROR;

    // check_for_test();

    printf("enter please a, b, c of Quadratic Equation\nwith type of ax^2 + bx + c = 0\n");
    if (scanf("%lf %lf %lf", &a, &b, &c) == 3){
        n_of_roots = solve_quadratic(a,b,c, &x1, &x2);
        
    }
    show_result(n_of_roots, x1, x2);
    return 0;
}


