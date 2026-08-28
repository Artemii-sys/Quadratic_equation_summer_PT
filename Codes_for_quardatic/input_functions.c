#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "..\Headers\additional_functions.h"



void clear_input(void) {
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}



void remove_newline(char string[]) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }
}

void remove_quotes(char * line){
    int write_index = 0;
    for (int current_index = 0; line[current_index] != '\0'; current_index++){
        if (line[current_index] != '"'){
            line[write_index] = line[current_index];
            write_index++;
        }

    }
    line[write_index] = '\0';
}

void program_crash(void) {
    printf(RED "\nInput error. " RESET "Press any key to exit...\n");
    _getch();
    exit(EXIT_FAILURE);
}
