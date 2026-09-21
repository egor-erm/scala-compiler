%option noyywrap 
%option never-interactive

%{
%}

whitespace [ \t\r\n]
nl \n

upper [A-Z$]
lower [a-z_]
letter {upper}|{lower}
digit [0-9]

paren [()[]{}]
delim [`'";.,]

opid [!#%&*+-/:<=>?@\^|~]+
idrest ({letter}|{digit})*(\_{opid})?
varid {lower}{idrest}
boundvarid {varid}|\`{varid}\`
alphaid {upper}{idrest}|{varid}
plainid {alphaid}|{opid}
id {plainid}|\`({charNoBackQuoteOrNewline}|{escapeSeq})*\`
quoteId \'{alphaid}
spliceId \${alphaid}

decimalBody (\_*{digit})*
decimalNumeral {digit}{decimalBody}

hexDigit {digit}|[a-fA-F]
hexNumeral 0[xX](\_*{hexDigit})+

binaryDigit [01]
binaryNumeral 0[bB](\_*{binaryDigit})+

floatType [fFdD]

decimalFraction {decimalNumeral}\.{decimalNumeral}?|\.{decimalNumeral}
mantissa {decimalNumeral}|{decimalFraction}
exponentPart [eE][+-]?{decimalNumeral}
expDecimal {mantissa}{exponentPart}

integerLiteral ({decimalNumeral}|{hexNumeral}|{binaryNumeral})[Ll]?
floatingPointLiteral ({decimalNumeral}|{expDecimal}){floatType}?|{decimalNumeral}{floatType}
booleanLiteral true|false

UnicodeEscape \\u+{hexDigit}{4}
charEscapeSeq \\[btnfr"'\]
escapeSeq {UnicodeEscape}|{charEscapeSeq}

semi \;|{nl}+

=== diff modes ===

	characterLiteral \'({charNoQuoteOrNewline}|{escapeSeq})\'
	
	stringLiteral \"{stringElement}*\"
	\" { BEGIN(STRING); }
	<STRING>
	{
		\" { BEGIN(INITIAL); /*возввращаем строку*/; }
	}
	
	\"{3} { BEGIN(MULTILINE); }
	<MULTILINE>
	{
		\"{3} { BEGIN(INITIAL); /*возввращаем строку*/ }
		[^"]+ { /*пишем в строку*/ }
		\"[^"] { /*пишем в строку*/ }
		\"\"[^"] { /*пишем в строку*/ }
	}
	
	===\\\===
	interpolatedString {alphaid}\"(\\?{interpolatedStringPart}|\\\\|\\\")*\"|{alphaid}\"{3}(\"?\"?([^"\\]|\\/[^$])|{escape})*\"*\"{3}
	===\\\===
	INTERP_START — после alphaid"
	INTERP_MIDDLE — между $...$
	INTERP_BLOCK — внутри ${...}
	===\\\===

	=== deprecated ===
	
		symbolLiteral \'{idrest}
		
	=== deprecated ===

	stringElement {charNoDoubleQuoteOrNewline}|{escapeSeq}
	multiLineChars (\"?\"?{charNoDoubleQuote})*\"*

	interpolatedStringPart [\x20-\x21\x23\x25-\x5B\x5D-\x7E]|{escape}
	escape \\\$(\\\$|\"\|{alphaid}|{BlockExpr})

	comment \/\*([^*]|\*+[^*/])*\*+\/|\/\/[^\n]*

=== diff modes ===

%%
