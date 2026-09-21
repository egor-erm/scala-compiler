.\win_flex.exe -o lexer.cc lexer.l
g++ -std=c++17 -o lexer.exe lexer.cc
.\lexer.exe test.scala