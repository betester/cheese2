@echo off
gcc -o main.exe .\main.c

if %ERRORLEVEL% NEQ 0 (
  echo compilation failed
  pause
) else (
  echo compilation succeeded
  pause
)
