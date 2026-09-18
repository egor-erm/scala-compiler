%option noyywrap 
%option never-interactive

%{
%}

whitespace [ \t\r\n]
upper [A-Z$]
lower [a-z_]
letter {upper}|{lower}
digit [0-9]
paren [()[]{}]
delim [`'";.,]
opchar [!#%&*+-/:<=>?@\^|~]
printableChar [\x20-\x7E]
UnicodeEscape \\u+{hexDigit}{4}
hexDigit {digit}|[a-fA-F]
charEscapeSeq \\[btnfr"'\]
escapeSeq {UnicodeEscape}|{charEscapeSeq}

op {opchar}+
varid {lower}{idrest}
boundvarid {varid}|\`{varid}\`
plainid {alphaid}|{op}
id {plainid}|\`({charNoBackQuoteOrNewline}|{escapeSeq})*\`
idrest ({letter}|{digit})*(\_{op})?
quoteId \'{alphaid}
spliceId \${alphaid}

integerLiteral ({decimalNumeral}|{hexNumeral}|{binaryNumeral})[Ll]?
decimalNumeral 0|{digit}(({digit}|\_)*{digit})?
hexNumeral 0[xX]{hexDigit}(({hexDigit|\_)*{hexDigit})?
binaryNumeral 0[bB]{binaryDigit}(({binaryDigit}|\_)*{binaryDigit})?

floatingPointLiteral {decimalNumeral}?\.{digit}(({digit}|\_)*{digit})?{exponentPart}?{floatType}?|{decimalNumeral}{exponentPart}{floatType}?|{decimalNumeral}{floatType}
exponentPart [eE][+-]?{digit}(({digit}|\_)*{digit})?
floatType [fFdD]

booleanLiteral true|false

characterLiteral \'({charNoQuoteOrNewline}|{escapeSeq})\'

stringLiteral \"{stringElement}*\"|\"{3}{multiLineChars}\"{3}
stringElement {charNoDoubleQuoteOrNewline}|{escapeSeq}
multiLineChars (\"?\"?{charNoDoubleQuote})*\"*

interpolatedString {alphaid}\"(\\?{interpolatedStringPart}|\\\\|\\\")*\"|{alphaid}\"{3}(\"?\"?{char}\\(\"|\\\$)|{escape})*\"*\"{3}
interpolatedStringPart {printableChar}\\["$\]|{escape}
escape \\\$(\\\$|\"\|{alphaid}|{BlockExpr})
alphaid {upper}{idrest}|{varid}

comment \/\*([^*]|\*+[^*/])*\*+\/|\/\/[^\n]* 

nl \n
semi \;|{nl}+

%%
