%{
/* Пролог (Prologue): C-объявления, макросы, #include */
%}

/* Объявления Bison (Bison declarations) */

%token WHILE DO FOR
%token VAL VAR
%token ID
%token NEW TARRAY
%token R_ARROW
%token LITINT LITCHAR LITSTR LITDOUBLE LITBOOL KNULL
%token PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN AND_ASSIGN OR_ASSIGN
%token IF ELSE
%token L_ARROW
%token CASE
%token TRY CATCH FINALLY THROW RETURN
%token DEF ABSTRACT SEALED FINAL OVERRIDE EXTENDS CLASS SUPER
%token PRIVATE PROTECTED THIS
%token IMPORT TYPE OBJECT
%token NL NLNL
%token UNSUPPORTED "unsupported token"

/* Приоритеты как в Scala: определяются первым символом оператора */

/* return без значения: следующий if/while относится к return как значение */
%nonassoc RETURN_EMPTY
%nonassoc IF WHILE
%nonassoc IF_EXPR
%nonassoc ELSE
%left ID
%left OR
%left AND
%left '|'
%left '^'
%left '&'
%left EQ NEQ
%left '<' '>' LESS_EQ GREATER_EQ SHL SHR
%left '+' '-'
%left '*' '/' '%'

%start program

/* Ожидаемые конфликты, сдвиг в них верен: аргументы new A (...) и catch/finally у вложенного try */

%expect 3

%%

/* Грамматические правила (Grammar rules) */

/* Программа - это набор классов и объектов. Этот набор может быть пустым. */

program:
    semis_e
  | semis_e top_list semis_e
  ;

top_list:
    top_stat
  | top_list semis top_stat
  ;

top_stat:
    import
  | class_def
  ;

import:
    IMPORT path
  ;

path:
    ID
  | path '.' ID
  ;

/* Разделители: nl и nlnl работают как ';' */

semi:
    ';'
  | NL
  | NLNL
  ;

semis:
    semi
  | semis semi
  ;

semis_e:
    /* empty */
  | semis
  ;

semi_e:
    /* empty */
  | semi
  ;

/* Любое число переводов строк (после условий и генераторов) */
nls:
    /* empty */
  | nls NL
  | nls NLNL
  ;

/* Перевод строки после инфиксного оператора */
nl_e:
    /* empty */
  | NL
  ;

/* Инструкциями являются определения и выражения. Между инструкциями идёт разделитель */

stmt:
    def
  | expr
  ;

/* Определение - это объявление новой переменной и присвоение ей значения */
def:
    func_def
  | var_def
  | TYPE ID '=' type
  ;

/* Не все не для всего. Надо разбить под дефам и выписать варианты. Не забыть про повторения. */
def_prefix:
    ABSTRACT
  | SEALED
  | FINAL
  | OVERRIDE
  | PRIVATE
  | PROTECTED
  ;

def_prefix_list:
    /* empty */
  | def_prefix_list def_prefix
  ;

class_def:
    def_prefix_list CLASS ID field_list_e extends_e class_body_e
  | def_prefix_list OBJECT ID extends_e class_body_e
  ;

extends_e:
    /* empty */
  | EXTENDS ID args_e
  ;

args_e:
    /* empty */
  | args
  ;

args:
    '(' ')'
  | '(' expr_list ')'
  ;

class_body_e:
    /* empty */
  | class_body
  ;

class_body:
    '{' stmt_list_e '}'
  ;

stmt_list_e:
    semis_e
  | semis_e stmt_list semis_e
  ;

stmt_list:
    stmt
  | stmt_list semis stmt
  ;

id_list:
    ID
  | id_list ',' ID
  ;

field_list_e:
    /* empty */
  | '(' ')'
  | '(' field_list ')'
  ;

field_list:
    field
  | field_list ',' field
  ;

field:
    ID ':' type
  | def_prefix_list val_or_var ID ':' type
  ;

val_or_var:
    VAL
  | VAR
  ;

func_def:
    def_prefix_list DEF ID params_e type_e '=' expr
  | def_prefix_list DEF ID params_e ':' type
  | def_prefix_list DEF THIS params_e '=' expr
  ;

var_def:
    def_prefix_list val_or_var id_list type_e '=' expr
  | def_prefix_list val_or_var id_list ':' type
  ;

params_e:
    /* empty */
  | '(' param_list_e ')'
  ;

param_list_e:
    /* empty */
  | param_list
  ;

param_list:
    ID ':' type
  | param_list ',' ID ':' type
  ;

type:
    ID
  | ID '.' ID
  | TARRAY '[' type ']'
  ;

type_e:
    /* empty */
  | ':' type
  ;

/* Блок: определения локальных переменных и выражения */

block_stats:
    semis_e
  | semis_e block_list semis_e
  ;

block_list:
    block_stat
  | block_list semis block_stat
  ;

block_stat:
    local_def
  | expr
  ;

local_def:
    val_or_var id_list type_e '=' expr
  ;

/* Всё остальное - это выражения */

expr:
    if_expr
  | while_expr
  | do_while_expr
  | for_expr
  | TRY expr catch_e finally_e
  | THROW expr
  | RETURN %prec RETURN_EMPTY
  | RETURN expr
  | simple '=' expr
  | simple PLUS_ASSIGN expr
  | simple MINUS_ASSIGN expr
  | simple STAR_ASSIGN expr
  | simple SLASH_ASSIGN expr
  | simple PERCENT_ASSIGN expr
  | simple AND_ASSIGN expr
  | simple OR_ASSIGN expr
  | infix
  ;

/* Проверить, можно ли без else'а присваивать значение переменной (по умолчанию вернётся () - Unit, тип AnyVar) */
if_expr:
    IF '(' expr ')' nls expr %prec IF_EXPR
  | IF '(' expr ')' nls expr ELSE expr
  ;

while_expr:
    WHILE '(' expr ')' nls expr
  ;

do_while_expr:
    DO expr semi_e WHILE '(' expr ')'
  ;

for_expr:
    FOR '(' generator_list ')' nls expr
  | FOR '{' semis_e generator_list semis_e '}' nls expr
  ;

generator_list:
    generator
  | generator_list semis generator
  | generator_list semis IF expr
  | generator_list IF expr
  ;

generator:
    ID L_ARROW expr
  ;

catch_e:
    /* empty */
  | CATCH '{' case_list '}'
  ;

case_list:
    case
  | case_list case
  ;

case:
    CASE ID ':' type R_ARROW block_stats
  ;

finally_e:
    /* empty */
  | FINALLY expr
  ;

infix:
    prefix
  | infix ID nl_e infix
  | infix OR nl_e infix
  | infix AND nl_e infix
  | infix '|' nl_e infix
  | infix '^' nl_e infix
  | infix '&' nl_e infix
  | infix EQ nl_e infix
  | infix NEQ nl_e infix
  | infix '<' nl_e infix
  | infix '>' nl_e infix
  | infix LESS_EQ nl_e infix
  | infix GREATER_EQ nl_e infix
  | infix SHL nl_e infix
  | infix SHR nl_e infix
  | infix '+' nl_e infix
  | infix '-' nl_e infix
  | infix '*' nl_e infix
  | infix '/' nl_e infix
  | infix '%' nl_e infix
  ;

prefix:
    simple
  | '-' simple
  | '+' simple
  | '!' simple
  | '~' simple
  ;

expr_list:
    expr
  | expr_list ',' expr
  ;

simple:
    literal
  | ID
  | THIS
  | SUPER '.' ID
  | simple '.' ID
  | simple args
  | '(' expr ')'
  | '{' block_stats '}'
  | NEW ID args_e
  | NEW TARRAY '[' type ']' '(' expr ')'
  | TARRAY args
  | TARRAY '[' type ']' args
  | TARRAY '.' ID '[' type ']' args
  ;

literal:
    LITINT
  | LITCHAR
  | LITBOOL
  | LITDOUBLE
  | LITSTR
  | KNULL
  | '(' ')'
  ;

%%

/* Эпилог (Epilogue): дополнительный C-код */