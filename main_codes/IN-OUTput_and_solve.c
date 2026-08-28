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

typedef struct GraphContextS {
    WINDOW window;
    double centerX;
    double centerY;
} GRAPH_CONTEXT;

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
/**
 * @brief Draws the whole graph using the helper functions below.
 * @param coefficients Values a, b and c.
 * @param window Window size and scale.
 */
void draw_graph(const COEFFICIENTS *coefficients, const WINDOW *window);
/**
 * @brief Draws the light grid in the background.
 * @param context Current window and coordinate center.
 */
static void draw_grid(const GRAPH_CONTEXT *context);
/**
 * @brief Draws the two main coordinate axes.
 * @param context Current window and coordinate center.
 */
static void draw_axes(const GRAPH_CONTEXT *context);
/**
 * @brief Adds marks and numbers to the coordinate axes.
 * @param context Current window and coordinate center.
 */
static void draw_axis_marks(const GRAPH_CONTEXT *context);
/**
 * @brief Draws the parabola pixel by pixel.
 * @param coefficients Values a, b and c.
 * @param context Current window and coordinate center.
 */
static void draw_parabola(const COEFFICIENTS *coefficients, const GRAPH_CONTEXT *context);
/**
 * @brief Marks the roots and the point where y equals c.
 * @param coefficients Values a, b and c.
 * @param context Current window and coordinate center.
 */
static void draw_intersections(const COEFFICIENTS *coefficients, const GRAPH_CONTEXT *context);
/**
 * @brief Marks the vertex of the parabola.
 * @param coefficients Values a, b and c.
 * @param context Current window and coordinate center.
 */
static void draw_vertex(const COEFFICIENTS *coefficients, const GRAPH_CONTEXT *context);
/** @brief Reads equations from a file and writes their answers to result.txt. */
int graph_and_solve_if_multiple(void);
/** @brief Reads and solves one equation from the console. */
int solve_if_single(void);
void draw_cute_small_useless_graph(void);
void what_to_do_for_decision_of_graph(DECISION_FOR_GRAPH decision_for_graph,
                                      const COEFFICIENTS *coefficients);
void solve_if_single_input(double *a, double *b, double *c,
                           int *a_scanf_status,
                           int *b_scanf_status,
                           int *c_scanf_status);
/** @brief Prints text with a small delay between characters. */
void ai_printf(const char *text, int delay_ms);

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
    printf("===================================================\n");
    printf("|            QUADRATIC EQUATION SOLVER            |\n");
    printf("|                   made by WA                    |\n");
    printf("===================================================\n");
    printf("\n");
    ai_printf("Do you want to solve one equation or read equations from a file?\n", 50);
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
    double window_height = window->window_length;
    double window_width = window->window_width;
    double centerX = window_width/2;
    double centerY = window_height/2;

    txCreateWindow(window_width, window_height);                           //ВОТ ЗДЕСЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬЬ
    txSetFillColor(TX_WHITE);
    txClear();
    
    GRAPH_CONTEXT context = {*window, centerX, centerY};
    draw_grid(&context);
    draw_axes(&context);
    draw_axis_marks(&context);
    draw_parabola(coefficients, &context);
    draw_intersections(coefficients, &context);
    draw_vertex(coefficients, &context);
    
    //txDisableAutoPause();
    //txSleep(60000);
}

static void draw_grid(const GRAPH_CONTEXT *context) {
    double centerX = context->centerX;
    double centerY = context->centerY;
    double window_width = context->window.window_width;
    double window_height = context->window.window_length;
    double graph_scale = context->window.graph_scale;
    txSetColor(RGB(220, 220, 220), 1);
    for (int x = (int) centerX; x < window_width; x += (int) graph_scale)
        txLine(x, 0, x, window_height);
    for (int x = (int) centerX; x > 0; x -= (int) graph_scale)
        txLine(x, 0, x, window_height);
    for (int y = (int) centerY; y < window_height; y += (int) graph_scale)
        txLine(0, y, window_width, y);
    for (int y = (int) centerY; y > 0; y -= (int) graph_scale)
        txLine(0, y, window_width, y);
}

static void draw_axes(const GRAPH_CONTEXT *context) {
    double centerX = context->centerX;
    double centerY = context->centerY;
    double window_width = context->window.window_width;
    double window_height = context->window.window_length;
    txSetColor(TX_BLACK, 2);
    txLine(0, centerY, window_width, centerY);
    txLine(centerX, 0, centerX, window_height);
}

static void draw_axis_marks(const GRAPH_CONTEXT *context) {
    double centerX = context->centerX;
    double centerY = context->centerY;
    double window_width = context->window.window_width;
    double window_height = context->window.window_length;
    double graph_scale = context->window.graph_scale;
    char axis_number[32] = {0};
    int max_x_mark = (int) (window_width / (2 * graph_scale));
    int max_y_mark = (int) (window_height / (2 * graph_scale));
    for (int i = 1; i <= max_x_mark; i++){
        int right_x = (int) centerX + (int) (i * graph_scale);
        int left_x = (int) centerX - (int) (i * graph_scale);
        txLine(right_x, centerY - 5, right_x, centerY + 5);
        txLine(left_x, centerY - 5, left_x, centerY + 5);
        sprintf(axis_number, "%d", i);
        txTextOut(right_x - 4, centerY + 8, axis_number);
        sprintf(axis_number, "-%d", i);
        txTextOut(left_x - 8, centerY + 8, axis_number);
    }
    for (int i = 1; i <= max_y_mark; i++){
        int upper_y = (int) centerY - (int) (i * graph_scale);
        int lower_y = (int) centerY + (int) (i * graph_scale);
        txLine(centerX - 5, upper_y, centerX + 5, upper_y);
        txLine(centerX - 5, lower_y, centerX + 5, lower_y);
        sprintf(axis_number, "%d", i);
        txTextOut(centerX + 8, upper_y - 6, axis_number);
        sprintf(axis_number, "-%d", i);
        txTextOut(centerX + 8, lower_y - 6, axis_number);
    }
    txTextOut((int) window_width - 25, (int) centerY + 10, "X");
    txTextOut((int) centerX + 10, 5, "Y");
}

static void draw_parabola(const COEFFICIENTS *coefficients, const GRAPH_CONTEXT *context) {
    for (int screenX = 0; screenX < context->window.window_width; screenX++) {
        double x = (screenX - context->centerX) / context->window.graph_scale;
        double y = coefficients->a * x * x + coefficients->b * x + coefficients->c;
        double screenY = context->centerY - y * context->window.graph_scale;
        if (screenY >= 0 && screenY < context->window.window_length)
            txSetColor(TX_RED, 3);
            //txSetFillColor(TX_RED); 
            //txSetPixel(screenX, screenY, TX_RED);
            //txRectangle(screenX - 1, screenY - 1, screenX + 1, screenY + 1);
            txCircle(screenX, screenY, 2);
    }
}

static void draw_intersections(const COEFFICIENTS *coefficients, const GRAPH_CONTEXT *context) {
    double centerX = context->centerX;
    double centerY = context->centerY;
    const WINDOW *window = &context->window;
    char point_label[64] = {0};
    double y_intersection = centerY - coefficients->c * window->graph_scale;
    if (y_intersection >= 0 && y_intersection < window->window_length) {
        txSetColor(TX_BLUE, 2);
        txCircle(centerX, y_intersection, 5);
        sprintf(point_label, "(0; %.2lf)", coefficients->c);
        txTextOut((int) centerX + 8, (int) y_intersection - 8, point_label);
    }
    double x1 = 0;
    double x2 = 0;
    NUMBER_OF_ROOTS roots_number = solve_quadratic(
        coefficients->a, coefficients->b, coefficients->c, &x1, &x2);
    if (roots_number == ONE_ROOT || roots_number == TWO_ROOTS) {
        txSetColor(TX_GREEN, 2);
        int root_x = (int) (centerX + x1 * window->graph_scale);
        if (root_x >= 0 && root_x < window->window_width) {
            txCircle(root_x, centerY, 5);
            sprintf(point_label, "(%.2lf; 0)", x1);
            txTextOut(root_x + 8, (int) centerY - 25, point_label);
        }
        if (roots_number == TWO_ROOTS) {
            root_x = (int) (centerX + x2 * window->graph_scale);
            if (root_x >= 0 && root_x < window->window_width) {
                txCircle(root_x, centerY, 5);
                sprintf(point_label, "(%.2lf; 0)", x2);
                txTextOut(root_x + 8, (int) centerY - 25, point_label);
            }
        }
    }
}

static void draw_vertex(const COEFFICIENTS *coefficients,
                        const GRAPH_CONTEXT *context) {
    double centerX = context->centerX;
    double centerY = context->centerY;
    const WINDOW *window = &context->window;
    if (!is_zero(coefficients->a)) {
        char vertex_label[64] = {0};
        double vertex_x = -coefficients->b / (2 * coefficients->a);
        double vertex_y = coefficients->a * vertex_x * vertex_x +
                          coefficients->b * vertex_x + coefficients->c;
        int screen_x = (int) (centerX + vertex_x * window->graph_scale);
        int screen_y = (int) (centerY - vertex_y * window->graph_scale);
        if (screen_x >= 0 && screen_x < window->window_width &&
            screen_y >= 0 && screen_y < window->window_length) {
            txSetColor(TX_MAGENTA, 2);
            txCircle(screen_x, screen_y, 5);
            sprintf(vertex_label, "V(%.2lf; %.2lf)",
                     vertex_x, vertex_y);
            txTextOut(screen_x + 8, screen_y - 25, vertex_label);
        }
    }
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



void ai_printf(const char *text, int delay_ms){
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        Sleep(delay_ms);
    }
    putchar('\n');
}                                                                                                                                                                                                   
