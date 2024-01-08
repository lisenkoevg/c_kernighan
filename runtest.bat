@echo off
setlocal enabledelayedexpansion

if "%1"=="*" (
  goto :runAll
  goto :eof
)
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
  %pf% %2 < %%i > !tn!_actual.out
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
popd
call :setESC
echo.
if %c%==%cp% (
  nircmd beep 5000 100
  call :echoGreen Total: %c%, passed: %cp%, FAILED: %cf%
) else (
  nircmd beep 1000 100
  call :echoRed Total: %c%, passed: %cp%, FAILED: %cf%
)
endlocal

goto :eof
:runAll
  for /f %%i in ('ls -1d *[1]_[0-9]*') do (
    pushd %%i
    echo !cd!
    make && make test && make clean
    popd
  )
goto :eof
:echoRed
  echo !ESC![31m%*!ESC![0m
goto :eof

:echoGreen
  echo !ESC![32m%*!ESC![0m
goto :eof

:setESC
  for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
    set ESC=%%b
    goto :eof
  )
goto :eof
