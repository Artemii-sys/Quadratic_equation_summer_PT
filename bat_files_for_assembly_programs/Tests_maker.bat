@echo off
cd /d "%~dp0"

g++ -I "Headers" ^
    "main_codes\Test_checker.c" ^
    "Codes_for_quardatic\Solver.c" ^
    "Codes_for_quardatic\checker_functions.c" ^
    "Codes_for_quardatic\input_functions.c" ^
    -o "big_test.exe"

if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

start "" "%~dp0big_test.exe"
