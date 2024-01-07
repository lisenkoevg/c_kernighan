@echo off
setlocal enabledelayedexpansion

if "%1"=="" (
  echo Usage: %0 program.exe
  goto :eof
)
set p=%~n1
set pexe=%p%.exe
set pf=%cd%\%pexe%
if not exist %pexe% echo Program "%pexe%" not found && goto :eof

set testdir=test_%p%
if not exist %testdir% echo Test dir %testdir% not found && goto :eof

pushd %testdir%
set c=0 & set cp=0 & set cf=0
for %%i in (*.in) do (
  set tn=%%~ni
  %pf% < %%i > !tn!_actual.out
  diff -N !tn!.out !tn!_actual.out > nul && (
    set /a cp=cp+1 > nul
    del !tn!_actual.out
    echo !tn!... ok
  ) || (
    set /a cf=cf+1 > nul
    echo !tn!... FAILED
  )
  set /a c=c+1 > nul
)
if %c%==%cp% nircmd beep 5000 100
if not %c%==%cp% nircmd beep 1000 100
echo.
echo Total: %c%, passed: %cp%, FAILED: %cf%
popd

endlocal
