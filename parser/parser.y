%{
/* Пролог (Prologue): C-объявления, макросы, #include */
%}

/* Объявления Bison (Bison declarations) */

%token VAL VAR
%token ID
%token TINT TCHAR TSTR
%token NEW TARRAY TLIST
%token EMPTY APPLY FILL TABULATE RANGE ITERATE CONCAT COPY COPY_OF FROM HEAD LAST LIFT APPLY_OR_ELSE UPDATE
%token R_ARROW
%token LITINT LITCHAR LITSTR
%token PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN
%token IF ELSE

%left IF_EXPR
%right '='
%nonassoc EQ NEQ
%left '<' '>' LESS_EQ GREATER_EQ
%left '+' '-' PLUS_ASSIGN MINUS_ASSIGN
%left '*' '/' '%' STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN
%right UMINUS UPLUS
%left '.'
%left '('

/* Стартер - программа */

%start program

/* Ожидаем один конфликт - болтающийся else */

%expect 1

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
  | TARRAY
  | TARRAY '[' type ']'

type_e:
    /* empty */
  | '[' type ']'

/* Всё остальное - это выражения */

expr:
    ID
  | LITINT
  | LITCHAR
  | LITSTR
  | '(' expr ')'
  | '{' program '}'
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
  | type '(' expr_list_e ')'
  | NEW type '(' expr ')'
  | expr '.' postfix
  | expr '(' expr ')'
  | IF '(' expr ')' expr %prec IF_EXPR
  | IF '(' expr ')' expr ELSE expr %prec IF_EXPR

expr_list:
    expr
  | expr_list ',' expr

expr_list_e:
    /* empty */
  | expr_list

postfix:
    EMPTY type_e
  | APPLY '(' expr_list_e ')'
  | FILL type_e '(' expr ')' '(' expr ')'
  | TABULATE type_e '(' expr ')' '(' ID R_ARROW expr ')'
  | ITERATE type_e '(' expr ',' expr ')' '(' ID R_ARROW expr ')'
  | RANGE '(' expr ',' expr ')'
  | RANGE '(' expr ',' expr ',' expr ')'
  | CONCAT '(' expr_list_e ')'
  | COPY '(' expr ',' expr ',' expr ',' expr ',' expr ')'
  | COPY_OF '(' expr ',' expr ')'
  | FROM type_e '(' expr ')'
  | HEAD
  | LAST
  | LIFT '(' expr ')'
  | APPLY_OR_ELSE '(' expr ',' expr ')'
  | UPDATE '(' expr ',' expr ')'

%%

/* Эпилог (Epilogue): дополнительный C-код */