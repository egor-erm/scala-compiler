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
    void printIdentificator(string id);
    void printSeparator(string separator);

    string stripUnderscores(string s);
    string stripSuffix(string s, string chars);
    string normalizeInt(string s);
    string normalizeBinInt(string s);
    string normalizeHexInt(string s);
    string normalizeDouble(string s);

    string normalizeChar(string s);
    string decodeChar(string s);

%}

LETTER [a-zA-Z_$]
DIGIT [0-9]
NON_ZERO_DIGIT [1-9]
BIN_DIGIT [01]
HEX_DIGIT [0-9a-fA-F]

NUMBER {DIGIT}("_"*{DIGIT})*
EXP [eE][+-]?{NUMBER}
FLOAT_TYPE [fFdD]

HEX_LITERAL 0(x|X)(_*{HEX_DIGIT})*
BIN_LITERAL 0(b|B)(_*{BIN_DIGIT})*

FLOATING_POINT_LITERAL {NUMBER}?"\."{DIGIT}(_*{DIGIT})*{EXP}?{FLOAT_TYPE}?|{NUMBER}{EXP}{FLOAT_TYPE}?|{NUMBER}{FLOAT_TYPE}

WHITESPACE [ \t\r\n]
COMMENT "//"[^\n]*|"/*"([^*]|\*+[^*/])*\*+"/"

OPCHAR [!#%&*+\-/:<=>?@\\^|~]
OP {OPCHAR}+ 

/* хвост имени */
IDREST ({LETTER}|{DIGIT})*(_{OP})?

/* variable */
VARID [a-z_]{IDREST}

/*constructor identifier (класс, объект, тип) */
CONID [A-Z]{IDREST}

CHAR_ESCAPE \\[btnfr"'\\]
CHAR_UNICODE \\u{HEX_DIGIT}{4}
CHAR_OCT \\[0-7]{1,3}
CHAR_CONTENT ([^'\\\n]|{CHAR_ESCAPE}|{CHAR_UNICODE}|{CHAR_OCT})
CHAR_LITERAL '{CHAR_CONTENT}'

%%

{WHITESPACE}+        { /* пропуск пробелов */ }

{COMMENT}            { /* пропуск комментариев */ }

Int     { printType(YYText()); }
Double  { printType(YYText()); }
String  { printType(YYText()); }
Char    { printType(YYText()); }
Array   { printType(YYText()); }
Unit    { printType(YYText()); } /* аналог void */

abstract    { printKeyword(YYText()); } /* Regular keywords */
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
":"         { printKeyword(YYText()); }
"#"         { printKeyword(YYText()); }
"@"         { printKeyword(YYText()); }

as          { printKeyword(YYText()); } /* Soft keywords */
derives     { printKeyword(YYText()); }
end         { printKeyword(YYText()); }
extension   { printKeyword(YYText()); }
infix       { printKeyword(YYText()); }
inline      { printKeyword(YYText()); }
opaque      { printKeyword(YYText()); }
open        { printKeyword(YYText()); }
transparent { printKeyword(YYText()); }
using       { printKeyword(YYText()); }

{FLOATING_POINT_LITERAL}    { printLiteral("double", normalizeDouble(YYText())); }

{NUMBER}                    { printLiteral("int", normalizeInt(YYText())); }
{BIN_LITERAL}               { printLiteral("int", normalizeBinInt(YYText())); }
{HEX_LITERAL}               { printLiteral("int", normalizeHexInt(YYText())); }

{CHAR_LITERAL}              { printLiteral("char", normalizeChar(YYText())); }

{VARID}     { printIdentificator(YYText()); }
{CONID}     { printIdentificator(YYText()); }

"("         { printSeparator(YYText()); } /* Разделители */
")"         { printSeparator(YYText()); }
"["         { printSeparator(YYText()); }
"]"         { printSeparator(YYText()); }
"{"         { printSeparator(YYText()); }
"}"         { printSeparator(YYText()); }
","         { printSeparator(YYText()); }
";"         { printSeparator(YYText()); }
"."         { printSeparator(YYText()); }

"+"     { printOperator(YYText()); } /* Операторы */
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

"="     { printOperator(YYText()); }
"+="    { printOperator(YYText()); }
"-="    { printOperator(YYText()); }
"*="    { printOperator(YYText()); }
"/="    { printOperator(YYText()); }
"%="    { printOperator(YYText()); }
"<<="   { printOperator(YYText()); }
">>="   { printOperator(YYText()); }
"&="    { printOperator(YYText()); }
"^="    { printOperator(YYText()); }
"|="    { printOperator(YYText()); }

\"                      { stringBuffer = ""; BEGIN(STRING); }
<STRING>[^\\\"\n]+       { stringBuffer += YYText(); }
<STRING>\\n             { stringBuffer += '\n'; }
<STRING>\\\\            { stringBuffer += '\\'; }
<STRING>\\\"            { stringBuffer += '"'; }

<STRING>\\t             { stringBuffer += '\t'; }
<STRING>\\r             { stringBuffer += '\r'; }
<STRING>\\b             { stringBuffer += '\b'; }
<STRING>\\f             { stringBuffer += '\f'; }

<STRING>{CHAR_UNICODE} {stringBuffer += decodeChar(YYText());}
<STRING>{CHAR_OCT} {stringBuffer += decodeChar(YYText());}

<STRING>\\\n           {  }

<STRING>\"           { printLiteral("string", stringBuffer);
                       BEGIN(INITIAL); }

<STRING>\n           { cerr << "ERROR: EOL in string" << endl;
                       BEGIN(INITIAL); }

<*>.     { cerr << "Unexpected char \'" << YYText()[0] << "\'" << endl; BEGIN(INITIAL);}

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

void printIdentificator(string id) {
    cout << "id: " << id << endl;
}

void printSeparator(string separator) {
    cout << "separator: " << separator << endl;
}

string stripUnderscores(string s) {
    string result;
    result.reserve(s.size());
    for (char c : s) {
        if (c != '_') result += c;
    }
    return result;
}

string stripSuffix(string s, string chars) {
    if (s.empty()) return s;

    char last = s[s.size() - 1];
    for (char c : chars) {
        if (c == last) return s.substr(0, s.size() - 1);
    }
    return s;
}

string normalizeInt(string s) {
    string result = stripUnderscores(s);
    result = stripSuffix(result, "lL");

    int i = 0;
    while (i + 1 < (int)result.size() && result[i] == '0') i++;
    return result.substr(i);
}

string normalizeBinInt(string s) {
    string clean = stripUnderscores(s);

    bool isLong = false;
    if (!clean.empty()
        && (clean[clean.size() - 1] == 'l' || clean[clean.size() - 1] == 'L')) {
        clean = clean.substr(0, clean.size() - 1);
        isLong = true;
    }

    int start = 0;
    if (clean.size() >= 2
        && clean[0] == '0'
        && (clean[1] == 'b' || clean[1] == 'B')) {
        start = 2;
    }

    unsigned long long v = 0;
    for (int i = start; i < (int)clean.size(); i++) {
        char c = clean[i];
        if (c == '0' || c == '1') {
            v = (v << 1) | (unsigned long long)(c - '0');
        }
    }

    string result = to_string(v);
    if (isLong) result += "L";
    return result;
}

string normalizeHexInt(string s) {
    string clean = stripUnderscores(s);

    bool isLong = false;
    if (!clean.empty()
        && (clean[clean.size() - 1] == 'l' || clean[clean.size() - 1] == 'L')) {
        clean = clean.substr(0, clean.size() - 1);
        isLong = true;
    }

    int start = 0;
    if (clean.size() >= 2
        && clean[0] == '0'
        && (clean[1] == 'x' || clean[1] == 'X')) {
        start = 2;
    }

    unsigned long long v = 0;
    for (int i = start; i < (int)clean.size(); i++) {
        char c = clean[i];
        int d = -1;
        if (c >= '0' && c <= '9')      d = c - '0';
        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
        if (d >= 0) v = v * 16 + (unsigned long long)d;
    }

    string result = to_string(v);
    if (isLong) result += "L";

    return result;
}

string normalizeDouble(string s) {
    string result = stripUnderscores(s);
    result = stripSuffix(result, "fFdD");

    bool hasDotOrExp = false;
    for (char c : result) {
        if (c == '.' || c == 'e' || c == 'E') {
            hasDotOrExp = true;
            break;
        }
    }

    if (!hasDotOrExp) result += ".0";

    return result;
}

string normalizeChar(string s) {
    // отрезаем обрамляющие '
    string inner = s.substr(1, s.size() - 2);

    return decodeChar(inner);
}

string decodeChar(string inner) {
    // одиночный символ — как есть
    if (inner.size() == 1) return inner;

    // \uXXXX -> попытаемся раскрыть, если печатаемый
    if (inner.size() == 6 && inner[0] == '\\' && inner[1] == 'u') {
        unsigned int code = 0;
        for (int i = 2; i < 6; i++) {
            char c = inner[i];
            int d = -1;
            if (c >= '0' && c <= '9')      d = c - '0';
            else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
            else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
            if (d < 0) return inner;
            code = code * 16 + d;
        }
        if (code >= 32 && code < 127 && code != '\'' && code != '\\') {
            return string(1, (char)code);
        }
        return inner;
    }

    // \NNN — восьмеричный escape
    if (inner.size() >= 2 && inner[0] == '\\'
        && inner[1] >= '0' && inner[1] <= '7') {
        unsigned int code = 0;
        int digits = 0;
        for (int i = 1; i < (int)inner.size() && digits < 3; i++) {
            char c = inner[i];
            if (c < '0' || c > '7') break;
            code = code * 8 + (c - '0');
            digits++;
        }
        if (code >= 32 && code < 127 && code != '\'' && code != '\\') {
            return string(1, (char)code);
        }
        return inner;   // непечатаемый — оставляем \NNN
    }

    // остальные escape (\n, \t, \', \\ и т.п.) — как есть
    return inner;
}