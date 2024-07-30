@echo off
gcc -o main.exe main.c chess.c -I./raylib-windows/include -L./raylib-windows/lib -lraylib -lopengl32 -lgdi32 -lwinmm

if %ERRORLEVEL% NEQ 0 (
  echo compilation failed
  pause
) else (
  echo compilation succeeded
  pause
)
