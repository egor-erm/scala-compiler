%option c++
%option noyywrap 
%option never-interactive

%x STRING

%{
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cstdlib>
    using namespace std;

    static string stringBuffer;

    void printLiteral(string type, string literal);
    void printType(string type);
    void printKeyword(string keyword);
    void printOperator(string op);

    string normalizeNumber(string str);
%}

LETTER [a-zA-Z_]
DIGIT [0-9]
NON_ZERO_DIGIT [1-9]
BIN_DIGIT [01]
HEX_DIGIT [0-9a-fA-F]

NUMBER {DIGIT}("_"*{DIGIT})*
EXP [eE][+-]?{NUMBER}

WHITESPACE [ \t\r\n]
COMMENT "//"[^\n]*|"/*"([^*]|\*+[^*/])*\*+"/"

OPCHAR [!#%&*+\-/:<=>?@\\^|~]
OP {OPCHAR}+ 

IDREST ({LETTER}|{DIGIT})*("_" {OP})? /* хвост имени */
VARID [a-z_]{IDREST} /* variable (переменная, функция, метод) */
CONID [A-Z]{IDREST} /*constructor identifier (класс, объект, тип) */

%%

{WHITESPACE}+        { /* пропуск пробелов */ }

{COMMENT}            { /* пропуск комментариев */ }

{NUMBER}    { printLiteral("int", normalizeNumber(YYText())); }


Int     { printType(YYText()); }
Double  { printType(YYText()); }
String  { printType(YYText()); }
Char    { printType(YYText()); }
Array   { printType(YYText()); }
Unit    { printType(YYText()); } /* аналог void */

abstract    { printKeyword(YYText()); }
case        { printKeyword(YYText()); }
catch       { printKeyword(YYText()); }
class       { printKeyword(YYText()); }
def         { printKeyword(YYText()); }
do          { printKeyword(YYText()); }
else        { printKeyword(YYText()); }
enum        { printKeyword(YYText()); }
export      { printKeyword(YYText()); }
extends     { printKeyword(YYText()); }
false       { printKeyword(YYText()); }
final       { printKeyword(YYText()); }
finally     { printKeyword(YYText()); }
for         { printKeyword(YYText()); }
given       { printKeyword(YYText()); }
if          { printKeyword(YYText()); }
implicit    { printKeyword(YYText()); }
import      { printKeyword(YYText()); }
lazy        { printKeyword(YYText()); }
match       { printKeyword(YYText()); }
new         { printKeyword(YYText()); }
null        { printKeyword(YYText()); }
object      { printKeyword(YYText()); }
override    { printKeyword(YYText()); }
package     { printKeyword(YYText()); }
private     { printKeyword(YYText()); }
protected   { printKeyword(YYText()); }
return      { printKeyword(YYText()); }
sealed      { printKeyword(YYText()); }
super       { printKeyword(YYText()); }
then        { printKeyword(YYText()); }
throw       { printKeyword(YYText()); }
trait       { printKeyword(YYText()); }
true        { printKeyword(YYText()); }
try         { printKeyword(YYText()); }
type        { printKeyword(YYText()); }
val         { printKeyword(YYText()); }
var         { printKeyword(YYText()); }
while       { printKeyword(YYText()); }
with        { printKeyword(YYText()); }
yield       { printKeyword(YYText()); }

"?=>"       { printKeyword(YYText()); }
"=>>"       { printKeyword(YYText()); }
"=>"        { printKeyword(YYText()); }
"<-"        { printKeyword(YYText()); }
"<:"        { printKeyword(YYText()); }
">:"        { printKeyword(YYText()); }
"="         { printKeyword(YYText()); }
":"         { printKeyword(YYText()); }
"#"         { printKeyword(YYText()); }
"@"         { printKeyword(YYText()); }

"+"     { printOperator(YYText()); }
"-"     { printOperator(YYText()); }
"*"     { printOperator(YYText()); }
"/"     { printOperator(YYText()); }
"%"     { printOperator(YYText()); }

"=="    { printOperator(YYText()); }
"!="    { printOperator(YYText()); }
">"     { printOperator(YYText()); }
"<"     { printOperator(YYText()); }
">="    { printOperator(YYText()); }
"<="    { printOperator(YYText()); }

\"                   { stringBuffer = ""; BEGIN(STRING); }
<STRING>[^\\"\n]+    { stringBuffer += YYText(); }
<STRING>\\n          { stringBuffer += '\n'; }
<STRING>\\\\         { stringBuffer += '\\'; }
<STRING>\\\"         { stringBuffer += '"'; }

<STRING>\\t          { stringBuffer += '\t'; }
<STRING>\\r          { stringBuffer += '\r'; }
<STRING>\\b          { stringBuffer += '\b'; }
<STRING>\\f          { stringBuffer += '\f'; }

<STRING>\"           { printLiteral("string", stringBuffer);
                       BEGIN(INITIAL); }

<STRING>\n           { cerr << "ERROR: EOL in string" << endl;
                       BEGIN(INITIAL); }

%%

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <file.scala>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    yyFlexLexer lexer(&in, &cout);
    lexer.yylex();

    return 0;
}

void printLiteral(string type, string literal) {
    cout << type << " literal: " << literal << endl;
}

void printType(string type) {
    cout << "type: " << type << endl;
}

void printKeyword(string keyword) {
    cout << "keyword: " << keyword << endl;
}

void printOperator(string op) {
    cout << "operator: " << op << endl;
}

string normalizeNumber(const string s) {
    string result;

    result.reserve(s.size());
    for (char c : s) {
        if (c != '_') result += c;
    }

    int i = 0;
    while (i + 1 < result.size() && result[i] == '0') i++;

    return result.substr(i);
}