%{
/* Пролог (Prologue): C-объявления, макросы, #include */
%}

/* Объявления Bison (Bison declarations) */

%token VAL VAR
%token ID
%token TINT TCHAR TSTR LITINT LITCHAR LITSTR
%token PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN

%right '='
%nonassoc EQ NEQ
%left '<' '>' LESS_EQ GREATER_EQ
%left '+' '-' PLUS_ASSIGN MINUS_ASSIGN
%left '*' '/' '%' STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN
%right UMINUS UPLUS

/* Стартер - программа */

%start program

%%

/* Грамматические правила (Grammar rules) */

/* Программа - это набор инструкций (утверждений). Этот набор может быть пустым. */

program:
    /* empty */
  | program stmt
  ;

/* Инструкциями являются определения и выражения. В конце каждой инструкции идёт разделитель */

stmt:
    def
  | expr ';'

/* Определение - это объявление новой переменной и присвоение ей значения */

def:
    VAL ID '=' expr ';'
  | VAR ID '=' expr ';'
  | VAL ID ':' type '=' expr ';'
  | VAR ID ':' type '=' expr ';'

type:
    TINT
  | TCHAR
  | TSTR

/* Всё остальное - это выражения */

expr:
    ID
  | LITINT
  | LITCHAR
  | LITSTR
  | '(' expr ')'
  | expr '+' expr
  | expr '-' expr
  | expr '*' expr
  | expr '/' expr
  | expr '%' expr
  | '+' expr %prec UPLUS
  | '-' expr %prec UMINUS
  | expr EQ expr
  | expr NEQ expr
  | expr '<' expr
  | expr '>' expr
  | expr LESS_EQ expr
  | expr GREATER_EQ expr
  | expr '=' expr
  | expr PLUS_ASSIGN expr
  | expr MINUS_ASSIGN expr
  | expr STAR_ASSIGN expr
  | expr SLASH_ASSIGN expr
  | expr PERCENT_ASSIGN expr

%%

/* Эпилог (Epilogue): дополнительный C-код */