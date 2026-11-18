#ifndef SCALA_LEXER_DRIVER_H
#define SCALA_LEXER_DRIVER_H

class yyFlexLexer;

void setScalaLexer(yyFlexLexer* lexer);
void setScalaLexerParserMode(bool enabled);
int yylex();

#endif
