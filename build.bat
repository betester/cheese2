@echo off
gcc -o main.exe main.c chess.c -I./raylib/include -L./raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

if %ERRORLEVEL% NEQ 0 (
  echo compilation failed
  pause
) else (
  echo compilation succeeded
  pause
)
