# scala-compiler

Синтаксис SCALA: 
https://scala-lang.org/files/archive/spec/3.4/01-lexical-syntax.html

Использование flex:
.\win_flex.exe --o lexer.cc lexer.l

Нужно скачать https://www.msys2.org/

Открой MSYS2 MinGW 64-bit (не просто MSYS2 Shell) и выполни:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb mingw-w64-x86_64-make

Компиляция лексера:
g++ -std=c++17 -o lexer.exe lexer.cc

Обязательно (FlexLexer.h из files/win_flex_bison):
C:\msys64\mingw64\include\FlexLexer.h

Запуск лексера:
.\lexer.exe test.scala