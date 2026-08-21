CC = gcc
CFLAGS = -Wall -Wextra -g

LIBS = -lm

SOLVER = solve_program
CHECKER = test_program

all: $(SOLVER) $(CHECKER)

$(SOLVER): IN-OUTput_and_solve.c Solver.c roots.h
  $(CC) $(CFLAGS) IN-OUTput_and_solve.c Solver.c -o $(SOLVER) $(LIBS)

$(CHECKER): Test_checker.c Solver.c roots.h
  $(CC) $(CFLAGS) Test_checker.c Solver.c -o $(CHECKER) $(LIBS)

clean:
  rm -f $(SOLVER) $(CHECKER)
