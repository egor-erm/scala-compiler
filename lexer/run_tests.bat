@echo off
setlocal enabledelayedexpansion

set LEXER=lexer.exe
set INPUT_DIR=tests\input
set EXPECTED_DIR=tests\expected
set OUTPUT_DIR=tests\output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

set PASS=0
set FAIL=0

for %%F in ("%INPUT_DIR%\*.scala") do (
    set "FILENAME=%%~nF"
    echo Running test: !FILENAME!
    "%LEXER%" "%%F" > "%OUTPUT_DIR%\!FILENAME!.out"
    fc "%OUTPUT_DIR%\!FILENAME!.out" "%EXPECTED_DIR%\!FILENAME!.txt" >nul
    if !errorlevel! equ 0 (
        echo   PASS
        set /a PASS+=1
    ) else (
        echo   FAIL
        set /a FAIL+=1
        echo   Diff:
        fc "%OUTPUT_DIR%\!FILENAME!.out" "%EXPECTED_DIR%\!FILENAME!.txt"
    )
)

echo.
echo Tests passed: !PASS!
echo Tests failed: !FAIL!
endlocal