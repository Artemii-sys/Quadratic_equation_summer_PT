@echo off
cd /d "%~dp0"

g++ -I "Headers" ^
    "main_codes\Test_checker.c" ^
    "Codes_for_quardatic\Solver.c" ^
    "Codes_for_quardatic\checker_functions.c" ^
    "Codes_for_quardatic\input_functions.c" ^
    -o "Tests_maker.exe"

if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

start "" "%~dp0Tests_maker.exe"
