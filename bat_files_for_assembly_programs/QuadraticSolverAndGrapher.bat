@echo off
cd /d "%~dp0"

g++ -I "Headers" ^
    "main_codes\IN-OUTput_and_solve.c" ^
    "Codes_for_quardatic\Solver.c" ^
    "Codes_for_quardatic\checker_functions.c" ^
    "Codes_for_quardatic\input_functions.c" ^
    -o "Quadratic_solver.exe"

if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

start "" "%~dp0Quadratic_solver.exe"
