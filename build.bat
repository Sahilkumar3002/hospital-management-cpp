@echo off
echo Building Hospital Management System...

:: Compile SQLite C code with GCC
echo Compiling SQLite...
gcc -c sqlite3.c -o sqlite3.o

:: Compile C++ code and link with SQLite object file
echo Compiling C++ files...
g++ main.cpp Database.cpp HospitalSystem.cpp sqlite3.o -o hospital.exe

if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
)

echo Build successful! You can now run hospital.exe.
