@echo off
echo Building the calculator...
x86_64-w64-mingw32-g++ -std=c++17 src/main.cpp -o calculator.exe -lgdi32 -luser32
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)
echo Build successful!
echo Running the calculator...
start calculator.exe
