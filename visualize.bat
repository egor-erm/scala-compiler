@echo off
setlocal
cd /d %~dp0

if "%~1"=="" (
    echo Usage: visualize.bat ^<file.scala^>
    exit /b 2
)

call build.bat
if errorlevel 1 exit /b 1

scala-compiler.exe "%~1" > out\ast.dot 2> out\example_parsing.txt
set PARSE_STATUS=%errorlevel%
if not "%PARSE_STATUS%"=="0" exit /b %PARSE_STATUS%

python files\BiVi-bison-visualizer\bivi.py out\example_parsing.txt > out\parse_tree.dot
if errorlevel 1 exit /b 1

echo AST:         out\ast.dot
echo BiVi tree:   out\parse_tree.dot
echo BiVi trace:  out\example_parsing.txt

where dot >nul 2>nul
if errorlevel 1 (
    echo Graphviz dot was not found; SVG generation skipped.
    exit /b 0
)

dot -Tsvg out\ast.dot -o out\ast.svg
if errorlevel 1 exit /b 1
dot -Tsvg out\parse_tree.dot -o out\parse_tree.svg
if errorlevel 1 exit /b 1

echo AST SVG:     out\ast.svg
echo BiVi SVG:    out\parse_tree.svg
