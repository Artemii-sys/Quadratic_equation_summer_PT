#include "..\Headers\TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include "..\Headers\solver_functions.h"
#include "..\Headers\additional_functions.h"
#include <string.h>
#include <conio.h>

typedef struct CoefficientsS {
    double a;
    double b;
    double c;
} COEFFICIENTS;

typedef struct WindowS {
    double window_width;
    double window_length;
    double graph_scale;
} WINDOW;

typedef struct RootsS {
    double x1;
    double x2;
} ROOTS;

typedef enum DECISIONS{
    NO_DECISION,
    DECISION_SINGLE = 's', 
    DECISION_MULTIPLE = 'm',
} DECISION;

typedef enum DECISIONS_FOR_GRAPH{
    NO_DECISION_FOR_GRAPH,
    YES_FOR_GRAPH = 'y',
    NO_FOR_GRAPH = 'n',
} DECISION_FOR_GRAPH;

void better_print(FILE* resultfile, double a, double b, double c);
void draw_graph(const COEFFICIENTS *coefficients, const WINDOW *window);
int graph_and_solve_if_multiple(void);
int solve_if_single(void);
void draw_cute_small_useless_graph(void);
void what_to_do_for_decision_of_graph(DECISION_FOR_GRAPH decision_for_graph,
                                      const COEFFICIENTS *coefficients);
void solve_if_single_input(double *a, double *b, double *c,
                           int *a_scanf_status,
                           int *b_scanf_status,
                           int *c_scanf_status);

static void show_result(NUMBER_OF_ROOTS n_of_roots, double x1, double x2){
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
            printf("Enter problem. Got not number. And please go away. And learn math.");
            break;
        case NO_NUMBER:
            printf("something went wrong while counting number of roots in function \"solve_quadratic\"");
            break;

        default:
            printf("Unknown solution type\n");
            break;
    }
}

static void write_result(FILE *resultfile,
                         NUMBER_OF_ROOTS n_of_roots,
                         const COEFFICIENTS *coefficients,
                         const ROOTS *roots){
    double a = coefficients->a;
    double b = coefficients->b;
    double c = coefficients->c;
    double x1 = roots->x1;
    double x2 = roots->x2;

    switch(n_of_roots){
        case ZERO_ROOTS:
            better_print(resultfile, a, b, c);
            fprintf(resultfile, "no roots for this equation\n");
            break;

        case ONE_ROOT:
            better_print(resultfile, a, b, c);
            fprintf(resultfile, "there is only 1 root x1 = %.4lf\n", x1);
            break;

        case TWO_ROOTS:
            better_print(resultfile, a, b, c);
            fprintf(resultfile, "there are 2 roots: x1 = %.4lf\nx2 = %.4lf\n", x1, x2);
            break;

        case INFINITY_ROOTS:
            better_print(resultfile, a, b, c);
            fprintf(resultfile, "Any x is a root for this equation\n");
            break;

        case ENTER_ERROR:
            fprintf(resultfile, "Input error\n");
            break;
    
        case NO_NUMBER:
            fprintf(resultfile, "something went wrong while counting number of roots in function \"solve_quadratic\"");
            break;

        default:
            fprintf(resultfile, "Unknown solution type\n");
            break;
    }
}

//===============================================================================

/////////////////////////////////////////////////////////////////////////////////

int main(void) {
    char decision = NO_DECISION;
    printf("Do you want to solve one equation or read equations from a file?\n");
    printf("Enter 's' for single or 'm' for multiple: ");
    if (scanf(" %c", &decision) != 1) {
        printf("Input error. Program got not symbol, it got smth else...\n");
        program_crash();
    }

    clear_input();

    //--------------------------------

    if (decision == DECISION_SINGLE) {
        solve_if_single();
    }
        
    //--------------------------------

    else if (decision == DECISION_MULTIPLE) {
        graph_and_solve_if_multiple();
    }

    else {
        printf("Wrong mode. Use 's' or 'm'. Or die.\n");
        program_crash();
    }
}


void better_print(FILE* resultfile, double a, double b, double c){
    fprintf(resultfile, "Equation: %.4lf*x^2 + %.4lf*x + %.4lf = 0\n", a, b, c);
}



void draw_graph(const COEFFICIENTS *coefficients, const WINDOW *window){
    double a = coefficients->a;
    double b = coefficients->b;
    double c = coefficients->c;
    double window_height = window->window_length;
    double window_width = window->window_width;
    double graph_scale = window->graph_scale;
    double centerX = window_width/2;
    double centerY = window_height/2;

    txCreateWindow(window_width, window_height);                           //ВОТ ЗДЕСЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬ
    txSetFillColor(TX_WHITE);
    txClear();
    
    txSetColor(TX_BLACK, 1);
    txLine(0, centerY, window_width, centerY);
    txLine(centerX, 0, centerX, window_height);

    for (int screenX = 0; screenX < window_width; screenX++){
        double x = (screenX - centerX) / graph_scale;
        double y = a * x * x + b * x + c;
        double screenY = centerY - (y * graph_scale);
        if (screenY >= 0 && screenY < window_height){
            txSetPixel(screenX, screenY, TX_RED);
        }
    }
    
    //txDisableAutoPause();
    //txSleep(60000);
}

int graph_and_solve_if_multiple(void){
    char buffer[200] = {0};
    printf("Enter the path to the file with equations (can be with brakes): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error reading input.\n");
        program_crash();
    }
    remove_newline(buffer);
    remove_quotes(buffer);
    printf("Running test from: %s\n", buffer);
    FILE *taskfile = fopen(buffer, "r");
    if (taskfile == NULL) {
        printf("Problem to open file with tests\n");
        program_crash();
    }
    FILE *resultfile = fopen("result.txt", "w");
    if (resultfile == NULL) {
        printf("Problem to create result file\n");
        fclose(taskfile);
        program_crash();
    }
    double a = 0;
    double b = 0;
    double c = 0;
    int task_number = 0;
    while (fscanf(taskfile, "%lf,%lf,%lf", &a, &b, &c) == 3) {
        if (isfinite(a) && isfinite(b) && isfinite(c)){
            double x1 = 0;
            double x2 = 0;
            NUMBER_OF_ROOTS n_of_roots = solve_quadratic(a, b, c, &x1, &x2);
            task_number++;
            fprintf(resultfile, "Task %d:\n", task_number);
            COEFFICIENTS coefficients = {a, b, c};
            ROOTS roots = {x1, x2};
            write_result(resultfile, n_of_roots, &coefficients, &roots);
            fprintf(resultfile, "\n");
        }
        else {
            fprintf(resultfile, "Invalid coefficients: a=%lf, b=%lf, c=%lf\n\n",a, b, c);
        }
    }
    fclose(resultfile);
    fclose(taskfile);
    printf("Processed " YELLOW "%d" RESET " equation(s). Results saved to " GREEN "result.txt\n" RESET, task_number);
    return EXIT_SUCCESS;
}

int solve_if_single(void){
    double a = 0;
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;
    NUMBER_OF_ROOTS n_of_roots = NO_NUMBER;
    printf("enter please a, b, c of Quadratic Equation\nwith type of ax^2 + bx + c = 0\n");
    int a_scanf_status = -1;
    int b_scanf_status = -1;
    int c_scanf_status = -1;
    //
    solve_if_single_input(&a, &b, &c, &a_scanf_status, &b_scanf_status, &c_scanf_status);
    if (a_scanf_status + b_scanf_status + c_scanf_status == 3 && isfinite(a) && isfinite(b) && isfinite(c)){
        n_of_roots = solve_quadratic(a, b, c, &x1, &x2);
        show_result(n_of_roots, x1, x2);
        char decision_for_graph_input = '\0';
        printf(GREEN "Would u like to draw graph in new window?: (y/n) " RESET);
        if (scanf(" %c", &decision_for_graph_input) != 1){
            printf("Input error");
            program_crash();
        }
        DECISION_FOR_GRAPH decision_for_graph = (DECISION_FOR_GRAPH) decision_for_graph_input;
        COEFFICIENTS coefficients = {a, b, c};
        what_to_do_for_decision_of_graph(decision_for_graph, &coefficients);
         
    }
    //
    else {
        printf("\nInput error.\n");
        printf("Status of taking your inputs\n");
        printf("a b c\n");
        printf("%d %d %d\n", a_scanf_status, b_scanf_status, c_scanf_status);
        printf("1 means correct, 0 means problem, -1 parameter didn`t even changed its based (by program) value\n");
        program_crash();
    }
    return 1;
    
}


void draw_cute_small_useless_graph(void){
    printf("+--------------> width\n");
    printf("|\n");
    printf("|\n");
    printf("|\n");
    printf("v\n");
    printf("height\n\n");
}


void what_to_do_for_decision_of_graph(DECISION_FOR_GRAPH decision_for_graph,
                                      const COEFFICIENTS *coefficients){
    switch (decision_for_graph){
        case YES_FOR_GRAPH:{ //выкинуть в функц
            int window_height = 0; // проверки
            int window_width = 0;
            draw_cute_small_useless_graph();
            printf("Enter size of the window height , width (example: 800 600): ");
            if (scanf("%d %d", &window_height, &window_width) == 2){
                double graph_scale = 0;
                printf("Enter " YELLOW "graph" RESET " scale: ");
                scanf(" %lf", &graph_scale);
                if (!isfinite(graph_scale)){
                    printf("Input Error. Your typed number is INF or NAN");
                    program_crash();
                }
                printf("\n");
                WINDOW window = {
                    (double) window_width,
                    (double) window_height,
                    graph_scale
                };
                draw_graph(coefficients, &window);
                break;
            }
            else{
                printf("Problem in scanning your inputing scales of window");
                printf("Program have: height: %d, width: %d", window_height, window_width);
                program_crash();
                break;
            }
        
        }
        case NO_FOR_GRAPH:{
            printf("U don`t want to draw graph");
            break;
        }
        default:
            break;
    }
}


void solve_if_single_input(double *a, double * b, double * c, int* a_scanf_status, int* b_scanf_status, int* c_scanf_status){
    printf("a = ");
    *a_scanf_status = scanf(" %lf", a);
    clear_input();
    printf("b = ");
    *b_scanf_status = scanf(" %lf", b);
    clear_input();
    printf("c = ");
    *c_scanf_status = scanf(" %lf", c);
    clear_input();
}
