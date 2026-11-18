@echo off
setlocal
cd /d %~dp0

set TOOLS=files\win_flex_bison-2.5.25

if not exist out mkdir out

%TOOLS%\win_bison.exe -d -v -Wcounterexamples -o parser\parser.tab.c parser\parser.y
if errorlevel 1 exit /b 1

lexer\win_flex.exe -o lexer\lexer.cc lexer\lexer.l
if errorlevel 1 exit /b 1

g++ -std=c++17 -I. -Iparser -Ilexer -I%TOOLS% ^
    main.cpp ^
    nodes\Node.cpp nodes\Types.cpp ^
    nodes\exprs\ExprNodes.cpp ^
    nodes\stmts\StmtNodes.cpp nodes\stmts\TopStmtNodes.cpp ^
    nodes\class\ClassNodes.cpp nodes\templates\TemplateNodes.cpp ^
    nodes\generator\GeneratorNodes.cpp nodes\try\TryNodes.cpp ^
    nodes\import\ImportNodes.cpp ^
    parser\parser.tab.c lexer\lexer.cc ^
    -o scala-compiler.exe
if errorlevel 1 exit /b 1

echo Built scala-compiler.exe
