@echo off
setlocal
cd /d %~dp0

..\files\win_flex_bison-2.5.25\win_bison.exe -d -o ..\parser\parser.tab.c ..\parser\parser.y
if errorlevel 1 exit /b 1

.\win_flex.exe -o lexer.cc lexer.l
if errorlevel 1 exit /b 1

g++ -std=c++17 -DSCALA_LEXER_STANDALONE -I.. -I..\parser -I. -o lexer.exe lexer.cc
if errorlevel 1 exit /b 1

.\lexer.exe test.scala
