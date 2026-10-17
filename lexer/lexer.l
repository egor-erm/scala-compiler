%option c++
%option noyywrap 
%option never-interactive

%x STRING
%x ML_COMMENT

%{
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <cstdlib>
    #include <vector>
    using namespace std;

    enum TokenClass { TC_LITERAL, TC_IDENT, TC_KEYWORD, TC_OPERATOR, TC_SEPARATOR };

    void onGap(const char* text);                     // пробелы и комментарии между токенами
    void onToken(TokenClass cls, const string& text); // учёт токена для вставки nl
    void printNewline(string kind);

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
BIN_DIGIT [01]
HEX_DIGIT [0-9a-fA-F]

NUMBER {DIGIT}("_"*{DIGIT})*
EXP [eE][+-]?{NUMBER}
FLOAT_TYPE [fFdD]

HEX_LITERAL 0(x|X)(_*{HEX_DIGIT})*
BIN_LITERAL 0(b|B)(_*{BIN_DIGIT})*

FLOATING_POINT_LITERAL {NUMBER}?"\."{DIGIT}(_*{DIGIT})*{EXP}?{FLOAT_TYPE}?|{NUMBER}{EXP}{FLOAT_TYPE}?|{NUMBER}{FLOAT_TYPE}

WHITESPACE [ \t\r\n]

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

%{
    string stringBuffer = "";
    int mlCommentDepth = 0;
%}

{WHITESPACE}+        { onGap(YYText()); /* пробелы: могут содержать переводы строк */ }

"//"[^\n]*           { onGap(YYText()); /* однострочный комментарий */ }

"/*"                 { mlCommentDepth = 1; BEGIN(ML_COMMENT); }
<ML_COMMENT>"/*"     { mlCommentDepth++; onGap(YYText()); }
<ML_COMMENT>"*/"     { onGap(YYText()); if (--mlCommentDepth == 0) BEGIN(INITIAL); }
<ML_COMMENT>\n|.     { onGap(YYText()); /* перевод строки внутри комментария учитывается*/ }
<ML_COMMENT><<EOF>>  { cerr << "ERROR: unterminated multi-line comment" << endl;
                       BEGIN(INITIAL); }

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
extends     { printKeyword(YYText()); }
false       { printKeyword(YYText()); }
final       { printKeyword(YYText()); }
finally     { printKeyword(YYText()); }
for         { printKeyword(YYText()); }
if          { printKeyword(YYText()); }
implicit    { printKeyword(YYText()); }
import      { printKeyword(YYText()); }
lazy        { printKeyword(YYText()); }
macro       { printKeyword(YYText()); }
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
this        { printKeyword(YYText()); }
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

"=>"        { printOperator(YYText()); }
"<-"        { printOperator(YYText()); }
"<:"        { printOperator(YYText()); }
">:"        { printOperator(YYText()); }
":"         { printOperator(YYText()); }
"#"         { printOperator(YYText()); }
"@"         { printOperator(YYText()); }

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

"("         { printSeparator(YYText()); } /* Разделители */
")"         { printSeparator(YYText()); }
"["         { printSeparator(YYText()); }
"]"         { printSeparator(YYText()); }
"{"         { printSeparator(YYText()); }
"}"         { printSeparator(YYText()); }
","         { printSeparator(YYText()); }
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

"&&"    { printOperator(YYText()); }
"||"    { printOperator(YYText()); }
"!"     { printOperator(YYText()); }

"&"     { printOperator(YYText()); }
"^"     { printOperator(YYText()); }
"|"     { printOperator(YYText()); }
"~"     { printOperator(YYText()); }
">>"    { printOperator(YYText()); }
"<<"    { printOperator(YYText()); }

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

{CHAR_LITERAL}              { printLiteral("char", normalizeChar(YYText())); }

\"                      { stringBuffer = ""; BEGIN(STRING); }
<STRING>[^\\\"\n]+      { stringBuffer += YYText(); }
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

{VARID}     { printIdentificator(YYText()); }
{CONID}     { printIdentificator(YYText()); }
{OP}        { printIdentificator(YYText()); }

";"         { printSeparator(YYText()); }

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

bool gapHasNewline = false;   // между предыдущим и текущим токеном был перевод строки
bool gapHasBlankLine = false; // между токенами несколько перводом строк
bool gapAfterLF = false;      // после последнего \n встречались только пробельные символы
bool lastCanEnd = false;      // предыдущий токен может завершать оператор

// Стек областей: ожидаемые закрывающие токены ")", "]", "}", "=>". */
vector<string> regions;

bool pendingCase = false;     // был case; ещё неизвестно, case class/object или ветка

bool isOneOf(const string& text, initializer_list<const char*> words) {
    for (const char* w : words) {
        if (text == w) return true;
    }
    return false;
}

// Токены, которые могут завершать оператор
bool canEndStatement(TokenClass cls, const string& text) {
    switch (cls) {
        case TC_LITERAL:
        case TC_IDENT:
            return true;
        case TC_KEYWORD:
            if (isOneOf(text, {"this", "null", "true", "false", "return", "type", "_"})) return true;
            // в Scala 2.13 это не зарезервированные слова, а обычные идентификаторы
            return isOneOf(text, {"enum", "export", "given", "then", "as", "derives", "end",
                                  "extension", "infix", "inline", "opaque", "open",
                                  "transparent", "using"});
        case TC_OPERATOR:
            // зарезервированные операторы не завершают оператор, остальные — идентификаторы
            return !isOneOf(text, {"=", "=>", "<-", "<:", ">:", "<%", ":", "#", "@"});
        case TC_SEPARATOR:
            return isOneOf(text, {")", "]", "}"});
    }
    return false;
}

// Токены, которые могут начинать оператор
bool canBeginStatement(TokenClass cls, const string& text) {
    switch (cls) {
        case TC_LITERAL:
        case TC_IDENT:
            return true;
        case TC_KEYWORD:
            return !isOneOf(text, {"catch", "else", "extends", "finally", "forSome",
                                   "match", "with", "yield"});
        case TC_OPERATOR:
            return !isOneOf(text, {"=", "=>", "<-", "<:", ">:", "<%", ":", "#"});
        case TC_SEPARATOR:
            return !isOneOf(text, {",", ";", ".", ")", "]", "}", "["});
    }
    return true;
}

bool newlinesEnabled() {
    return regions.empty() || regions.back() == "}";
}

void updateRegions(TokenClass cls, const string& text) {
    if (cls == TC_SEPARATOR) {
        if (text == "(") regions.push_back(")");
        else if (text == "[") regions.push_back("]");
        else if (text == "{") regions.push_back("}");
        else if (text == "}") {
            while (!regions.empty() && regions.back() != "}") regions.pop_back();
            if (!regions.empty()) regions.pop_back();
        } else if (text == ")" || text == "]") {
            if (!regions.empty() && regions.back() == text) regions.pop_back();
        }
    } else if (cls == TC_OPERATOR && text == "=>") {
        if (!regions.empty() && regions.back() == "=>") regions.pop_back();
    } else if (cls == TC_KEYWORD && text == "case") {
        pendingCase = true;
    }
}

void onGap(const char* text) {
    for (const char* p = text; *p; p++) {
        unsigned char c = (unsigned char)*p;
        if (c == '\n' || c == '\f') {
            if (gapAfterLF) gapHasBlankLine = true;
            gapAfterLF = true;
            gapHasNewline = true;
        } else if (c > ' ') {
            gapAfterLF = false;
        }
    }
}

void onToken(TokenClass cls, const string& text) {
    if (pendingCase) {
        pendingCase = false;
        // у case class / case object нет "=>", область для них не открывается
        if (!(cls == TC_KEYWORD && isOneOf(text, {"class", "object"}))) regions.push_back("=>");
    }
    if (gapHasNewline && lastCanEnd && canBeginStatement(cls, text) && newlinesEnabled()) {
        printNewline(gapHasBlankLine ? "nlnl" : "nl");
    }
    gapHasNewline = gapHasBlankLine = gapAfterLF = false;
    updateRegions(cls, text);
    lastCanEnd = canEndStatement(cls, text);
}

void printNewline(string kind) {
    cout << "newline: " << kind << endl;
}

void printLiteral(string type, string literal) {
    onToken(TC_LITERAL, literal);
    cout << type << " literal: " << literal << endl;
}

void printType(string type) {
    onToken(TC_IDENT, type);
    cout << "type: " << type << endl;
}

void printKeyword(string keyword) {
    onToken(TC_KEYWORD, keyword);
    cout << "keyword: " << keyword << endl;
}

void printOperator(string op) {
    onToken(TC_OPERATOR, op);
    cout << "operator: " << op << endl;
}

void printIdentificator(string id) {
    onToken(TC_IDENT, id);
    cout << "id: " << id << endl;
}

void printSeparator(string separator) {
    onToken(TC_SEPARATOR, separator);
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

    if (!result.empty() && result[0] == '.') {
        return "0" + result;
    }

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