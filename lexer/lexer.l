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
binaryDigit [01]
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

charNoQuoteOrNewline [\x20-\x26\x28-\x7E]
charNoDoubleQuoteOrNewline [\x20-\x21\x23-\x7E]
charNoDoubleQuote [^"]
charNoBackQuoteOrNewline [\x20-\x5F\x61-\x7E]

integerLiteral ({decimalNumeral}|{hexNumeral}|{binaryNumeral})[Ll]?
decimalNumeral 0|[1-9]{decimalBody}?
hexNumeral 0[xX]({hexDigit|\_)*{hexDigit}
binaryNumeral 0[bB]({binaryDigit}|\_)*{binaryDigit}

decimalBody (({digit}|\_)*{digit})

floatingPointLiteral {decimalNumeral}?\.{digit}{decimalBody}?{exponentPart}?{floatType}?|{decimalNumeral}{exponentPart}{floatType}?|{decimalNumeral}{floatType}
exponentPart [eE][+-]?{digit}{decimalBody}?
floatType [fFdD]

booleanLiteral true|false

characterLiteral \'({charNoQuoteOrNewline}|{escapeSeq})\'

stringLiteral \"{stringElement}*\"|\"{3}{multiLineChars}\"{3}
stringElement {charNoDoubleQuoteOrNewline}|{escapeSeq}
multiLineChars (\"?\"?{charNoDoubleQuote})*\"*

interpolatedString {alphaid}\"(\\?{interpolatedStringPart}|\\\\|\\\")*\"|{alphaid}\"{3}(\"?\"?([^"\\]|\\/[^$])|{escape})*\"*\"{3}
interpolatedStringPart [\x20-\x21\x23\x25-\x5B\x5D-\x7E]|escape
escape \\\$(\\\$|\"\|{alphaid}|{BlockExpr})
alphaid {upper}{idrest}|{varid}

comment \/\*([^*]|\*+[^*/])*\*+\/|\/\/[^\n]* 

nl \n
semi \;|{nl}+

%%
