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
    #include <cstring>
    #include <deque>
    #include <vector>
    #include "parser.tab.h"
    #include "lexer_driver.h"

#ifdef SCALA_LEXER_STANDALONE
    YYSTYPE yylval;
#endif
    using namespace std;

    enum TokenClass { TC_LITERAL, TC_IDENT, TC_KEYWORD, TC_OPERATOR, TC_SEPARATOR };

    void onGap(const char* text);                     // пробелы и комментарии между токенами
    int onToken(TokenClass cls, const string& text, int tokenCode, bool hasValue);
    void printNewline();

    /*
     * Состояние для удаления блочных комментариев, занимающих целые строки.
     * Такой комментарий не должен добавлять лишний nl: в конструкции
     *   a = b + <перенос> <блочный комментарий на несколько строк> <перенос> c
     * между '+' и 'c' должен остаться ровно один nl.
     */
    bool atLineStart = true;          // на текущей строке ещё не было токенов
    bool commentOwnLine = false;      // блочный комментарий начинается с начала строки
    bool skipOneGapNewline = false;   // не считать первый nl после закрытия комментария

    size_t commentStart(const string& text);          // начало "//" или "/*" внутри токена
    bool isOperator(const string& text);              // оператор, а не символьный идентификатор

    int printLiteral(string type, string literal);
    int printType(string type);
    int printKeyword(string keyword);
    int printOperator(string op);
    int printIdentificator(string id);
    int printSeparator(string separator);

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

"//"[^\n]*           {
    onGap(YYText()); /* однострочный комментарий сам nl не добавляет */
    // если комментарий занимал целую строку, удаляем и её завершающий nl
    skipOneGapNewline = atLineStart;
}

<ML_COMMENT>"/*"     { mlCommentDepth++; }
<ML_COMMENT>"*/"     {
    if (--mlCommentDepth == 0) {
        BEGIN(INITIAL);
        // комментарий, занимавший целую строку, удаляем вместе с её концом
        skipOneGapNewline = commentOwnLine;
        commentOwnLine = false;
    }
}
<ML_COMMENT>\n|.     { /* переводы строк внутри комментария не учитываются */ }
<ML_COMMENT><<EOF>>  { cerr << "ERROR: unterminated multi-line comment" << endl;
                       BEGIN(INITIAL); }

Int     { return printType(YYText()); }
Double  { return printType(YYText()); }
String  { return printType(YYText()); }
Char    { return printType(YYText()); }
Array   { return printType(YYText()); }
Unit    { return printType(YYText()); } /* аналог void */

abstract    { return printKeyword(YYText()); } /* Regular keywords */
case        { return printKeyword(YYText()); }
catch       { return printKeyword(YYText()); }
class       { return printKeyword(YYText()); }
def         { return printKeyword(YYText()); }
do          { return printKeyword(YYText()); }
else        { return printKeyword(YYText()); }
extends     { return printKeyword(YYText()); }
false       { return printKeyword(YYText()); }
final       { return printKeyword(YYText()); }
finally     { return printKeyword(YYText()); }
for         { return printKeyword(YYText()); }
if          { return printKeyword(YYText()); }
implicit    { return printKeyword(YYText()); }
import      { return printKeyword(YYText()); }
lazy        { return printKeyword(YYText()); }
macro       { return printKeyword(YYText()); }
match       { return printKeyword(YYText()); }
new         { return printKeyword(YYText()); }
null        { return printKeyword(YYText()); }
object      { return printKeyword(YYText()); }
override    { return printKeyword(YYText()); }
package     { return printKeyword(YYText()); }
private     { return printKeyword(YYText()); }
protected   { return printKeyword(YYText()); }
return      { return printKeyword(YYText()); }
sealed      { return printKeyword(YYText()); }
super       { return printKeyword(YYText()); }
this        { return printKeyword(YYText()); }
throw       { return printKeyword(YYText()); }
trait       { return printKeyword(YYText()); }
true        { return printKeyword(YYText()); }
try         { return printKeyword(YYText()); }
type        { return printKeyword(YYText()); }
val         { return printKeyword(YYText()); }
var         { return printKeyword(YYText()); }
while       { return printKeyword(YYText()); }
with        { return printKeyword(YYText()); }
yield       { return printKeyword(YYText()); }

as          { return printKeyword(YYText()); } /* Soft keywords */
derives     { return printKeyword(YYText()); }
end         { return printKeyword(YYText()); }
extension   { return printKeyword(YYText()); }
infix       { return printKeyword(YYText()); }
inline      { return printKeyword(YYText()); }
opaque      { return printKeyword(YYText()); }
open        { return printKeyword(YYText()); }
transparent { return printKeyword(YYText()); }
using       { return printKeyword(YYText()); }

{FLOATING_POINT_LITERAL}    { return printLiteral("double", normalizeDouble(YYText())); }

{NUMBER}                    { return printLiteral("int", normalizeInt(YYText())); }
{BIN_LITERAL}               { return printLiteral("int", normalizeBinInt(YYText())); }
{HEX_LITERAL}               { return printLiteral("int", normalizeHexInt(YYText())); }

"("         { return printSeparator(YYText()); } /* Разделители */
")"         { return printSeparator(YYText()); }
"["         { return printSeparator(YYText()); }
"]"         { return printSeparator(YYText()); }
"{"         { return printSeparator(YYText()); }
"}"         { return printSeparator(YYText()); }
","         { return printSeparator(YYText()); }
"."         { return printSeparator(YYText()); }

{CHAR_LITERAL}            { return printLiteral("char", normalizeChar(YYText())); }

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

<STRING>\"           { BEGIN(INITIAL);
                       return printLiteral("string", stringBuffer); }

<STRING>\n           { cerr << "ERROR: EOL in string" << endl;
                       BEGIN(INITIAL); }

{VARID}|{CONID}  {
    /* операторная часть имени обрывается на комментарии: a_+/*...*/
    string text = YYText();
    size_t cut = commentStart(text);
    if (cut != string::npos) {
        yyless(cut);
        text = text.substr(0, cut);
    }
    return printIdentificator(text);
}

{OP} {
    /* Обработка ситуаций по типу "a +/* c * b" (чтобы +/* не распознался как идентификатор) */
    string text = YYText();
    size_t cut = commentStart(text);

    if (cut == 0) {                 /* "//" сюда не попадает: его правило длиннее или выше */
        yyless(2);
        mlCommentDepth = 1;
        commentOwnLine = atLineStart;
        skipOneGapNewline = false;
        BEGIN(ML_COMMENT);
    } else {
        if (cut != string::npos) {
            yyless(cut);
            text = text.substr(0, cut);
        }
        if (isOperator(text)) return printOperator(text);
        else return printIdentificator(text);
    }
}

";"      { return printSeparator(YYText()); }

<*>.     { cerr << "Unexpected char \'" << YYText()[0] << "\'" << endl; atLineStart = false; BEGIN(INITIAL);}

%%

namespace {

struct PendingToken {
    int code;
    char* value;
};

yyFlexLexer* activeLexer = nullptr;
std::deque<PendingToken> tokenBuffer;
bool parserMode = false;

char* copyTokenValue(const string& text) {
    char* result = static_cast<char*>(std::malloc(text.size() + 1));
    if (result == nullptr) {
        std::cerr << "Out of memory while copying token value" << std::endl;
        std::exit(1);
    }
    std::memcpy(result, text.c_str(), text.size() + 1);
    return result;
}

int popBufferedToken() {
    PendingToken token = tokenBuffer.front();
    tokenBuffer.pop_front();
    yylval.text = token.value;
    return token.code;
}

} // namespace

void setScalaLexer(yyFlexLexer* lexer) {
    activeLexer = lexer;
}

void setScalaLexerParserMode(bool enabled) {
    parserMode = enabled;
}

int yylex() {
    if (!tokenBuffer.empty()) {
        return popBufferedToken();
    }
    return activeLexer == nullptr ? 0 : activeLexer->yylex();
}

#ifdef SCALA_LEXER_STANDALONE
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
    setScalaLexer(&lexer);
    setScalaLexerParserMode(false);
    while (yylex() != 0) {}

    return 0;
}
#endif

int gapNewlineCount = 0;        // фактическое число переводов строк между токенами
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

// Позиция первого "//" или "/*" в токене либо string::npos
size_t commentStart(const string& text) {
    size_t lineComment = text.find("//");
    size_t blockComment = text.find("/*");
    return lineComment < blockComment ? lineComment : blockComment;
}

// Остальные последовательности символов операторов — идентификаторы
bool isOperator(const string& text) {
    return isOneOf(text, {"=>", "<-", "<:", ">:", ":", "#", "@",
                          "+", "-", "*", "/", "%",
                          "==", "!=", ">", "<", ">=", "<=",
                          "&&", "||", "!",
                          "&", "^", "|", "~", ">>", "<<",
                          "=", "+=", "-=", "*=", "/=", "%=",
                          "<<=", ">>=", "&=", "^=", "|="});
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
    bool hasNewline = false;
    for (const char* p = text; *p; p++) {
        unsigned char c = (unsigned char)*p;
        if (c == '\n' || c == '\f') {
            hasNewline = true;
            if (skipOneGapNewline) {
                // первый перевод строки после блочного комментария относится
                // к удалённой строке комментария и не порождает nl
                skipOneGapNewline = false;
            } else {
                gapNewlineCount++;
            }
        }
    }
    if (hasNewline) {
        atLineStart = true;
    } else {
        // промежуток без перевода строки: дальше на этой же строке идёт код
        skipOneGapNewline = false;
    }
}

int onToken(TokenClass cls, const string& text, int tokenCode, bool hasValue) {
    if (pendingCase) {
        pendingCase = false;
        // у case class / case object нет "=>", область для них не открывается
        if (!(cls == TC_KEYWORD && isOneOf(text, {"class", "object"}))) regions.push_back("=>");
    }

    const bool insertNewlines = gapNewlineCount > 0 && lastCanEnd &&
        canBeginStatement(cls, text) && newlinesEnabled();

    char* value = hasValue ? copyTokenValue(text) : nullptr;
    int result = tokenCode;

    if (insertNewlines) {
        for (int i = 0; i < gapNewlineCount; i++) {
            printNewline();
            tokenBuffer.push_back({NL, nullptr});
        }
        tokenBuffer.push_back({tokenCode, value});
        result = popBufferedToken();
    } else {
        yylval.text = value;
    }

    gapNewlineCount = 0;
    updateRegions(cls, text);
    lastCanEnd = canEndStatement(cls, text);
    atLineStart = false;
    skipOneGapNewline = false;
    return result;
}

void printNewline() {
    if (!parserMode) {
        cout << "newline: nl" << endl;
    }
}

int printLiteral(string type, string literal) {
    int code = UNSUPPORTED;
    if (type == "int") code = LITINT;
    else if (type == "double") code = LITDOUBLE;
    else if (type == "char") code = LITCHAR;
    else if (type == "string") code = LITSTR;

    int result = onToken(TC_LITERAL, literal, code, true);
    if (!parserMode) cout << type << " literal: " << literal << endl;
    return result;
}

int printType(string type) {
    const bool isArray = type == "Array";
    int result = onToken(TC_IDENT, type, isArray ? TARRAY : ID, !isArray);
    if (!parserMode) cout << "type: " << type << endl;
    return result;
}

int printKeyword(string keyword) {
    struct KeywordToken { const char* word; int code; };
    static const KeywordToken tokens[] = {
        {"while", WHILE}, {"do", DO}, {"for", FOR},
        {"val", VAL}, {"var", VAR}, {"new", NEW},
        {"if", IF}, {"else", ELSE}, {"case", CASE},
        {"try", TRY}, {"catch", CATCH}, {"finally", FINALLY},
        {"throw", THROW}, {"return", RETURN}, {"def", DEF},
        {"abstract", ABSTRACT}, {"sealed", SEALED}, {"final", FINAL},
        {"override", OVERRIDE}, {"extends", EXTENDS}, {"class", CLASS},
        {"super", SUPER}, {"private", PRIVATE}, {"protected", PROTECTED},
        {"this", THIS}, {"import", IMPORT}, {"type", TYPE}, {"object", OBJECT}
    };

    int code = UNSUPPORTED;
    for (const KeywordToken& token : tokens) {
        if (keyword == token.word) {
            code = token.code;
            break;
        }
    }

    TokenClass tokenClass = TC_KEYWORD;
    bool hasValue = code == UNSUPPORTED;

    if (keyword == "true" || keyword == "false") {
        code = LITBOOL;
        tokenClass = TC_LITERAL;
        hasValue = true;
    } else if (keyword == "null") {
        code = KNULL;
        tokenClass = TC_LITERAL;
    } else if (isOneOf(keyword, {"as", "derives", "end", "extension", "infix", "inline",
                                 "opaque", "open", "transparent", "using"})) {
        code = ID;
        tokenClass = TC_IDENT;
        hasValue = true;
    }

    int result = onToken(tokenClass, keyword, code, hasValue);
    if (!parserMode) cout << "keyword: " << keyword << endl;
    return result;
}

int printOperator(string op) {
    struct OperatorToken { const char* text; int code; };
    static const OperatorToken tokens[] = {
        {"=>", R_ARROW}, {"<-", L_ARROW},
        {"==", EQ}, {"!=", NEQ}, {"<=", LESS_EQ}, {">=", GREATER_EQ},
        {"<<", SHL}, {">>", SHR}, {"&&", AND}, {"||", OR},
        {"+=", PLUS_ASSIGN}, {"-=", MINUS_ASSIGN}, {"*=", STAR_ASSIGN},
        {"/=", SLASH_ASSIGN}, {"%=", PERCENT_ASSIGN},
        {"&=", AND_ASSIGN}, {"|=", OR_ASSIGN},
        {"+", '+'}, {"-", '-'}, {"*", '*'}, {"/", '/'}, {"%", '%'},
        {">", '>'}, {"<", '<'}, {"!", '!'}, {"&", '&'}, {"^", '^'},
        {"|", '|'}, {"~", '~'}, {"=", '='}, {":", ':'}
    };

    int code = UNSUPPORTED;
    for (const OperatorToken& token : tokens) {
        if (op == token.text) {
            code = token.code;
            break;
        }
    }

    int result = onToken(TC_OPERATOR, op, code, code == UNSUPPORTED);
    if (!parserMode) cout << "operator: " << op << endl;
    return result;
}

int printIdentificator(string id) {
    int result = onToken(TC_IDENT, id, ID, true);
    if (!parserMode) cout << "id: " << id << endl;
    return result;
}

int printSeparator(string separator) {
    const int code = static_cast<unsigned char>(separator[0]);
    int result = onToken(TC_SEPARATOR, separator, code, false);
    if (!parserMode) cout << "separator: " << separator << endl;
    return result;
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