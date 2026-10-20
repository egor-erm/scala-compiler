%{
/* Пролог (Prologue): C-объявления, макросы, #include */
%}

/* Объявления Bison (Bison declarations) */

%token WHILE DO FOR
%token VAL VAR
%token ID
%token TINT TCHAR TSTR TDOUBLE TBOOL
%token NEW TARRAY TLIST
%token EMPTY APPLY FILL TABULATE RANGE ITERATE CONCAT COPY COPY_OF FROM HEAD LAST LIFT APPLY_OR_ELSE UPDATE
%token R_ARROW
%token LITINT LITCHAR LITSTR LITDOUBLE LITBOOL
%token READINT READCHAR READLINE
%token PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN
%token IF ELSE
%token L_ARROW
%token TO
%token UNITL
%token BY
%token YIELD
%token TO_ARRAY
%token FOREACH
%token TAPEACH
%token FILTER
%token FILTER_NOT
%token PARTITION
%token PARTITION_MAP
%token DISTINCT
%token DISTINCT_BY
%token COLLECT
%token COLLECT_FIRST
%token CASE
%token DROP
%token DROP_RIGHT
%token DROP_WHILE
%token TAKE
%token TAKE_RIGHT
%token TAKE_WHILE
%token SPAN
%token SLICE
%token SPLIT_AT
%token FIND
%token FIND_LAST
%token INDEX_WHERE
%token LAST_INDEX_WHERE
%token INDEX_OF
%token LAST_INDEX_OF
%token INDEX_OF_SLICE
%token LAST_INDEX_OF_SLICE
%token CONTAINS
%token CONTAINS_SLICE
%token EXISTS
%token FORALL
%token COUNT
%token FOLD
%token FOLD_LEFT
%token FOLD_RIGHT
%token REDUCE
%token REDUCE_LEFT
%token REDUCE_RIGHT
%token REDUCE_OPTION
%token REDUCE_LEFT_OPTION
%token REDUCE_RIGHT_OPTION
%token SUM
%token MIN
%token MAX
%token MIN_BY
%token MAX_BY
%token MIN_OPTION
%token MAX_OPTION
%token MIN_BY_OPTION
%token MAX_BY_OPTION
%token GROUP_BY
%token GROUP_MAP
%token GROUP_MAP_REDUCE
%token GROUPED
%token SLIDING
%token ZIP
%token ZIP_WITH_INDEX
%token LAZY_ZIP
%token MAP
%token FLAT_MAP
%token SCAN
%token SCAN_LEFT
%token SCAN_RIGHT
%token VIEW
%token SIZE
%token IS_EMPTY
%token NON_EMPTY
%token SIZE_COMPARE
%token KNOWN_SIZE
%token HEAD_OPTION
%token LAST_OPTION
%token TAIL
%token INIT
%token IS_DEFINED_AT
%token INDICES
%token LENGTH
%token LENGTH_COMPARE
%token REVERSE
%token REVERSE_ITERATOR
%token SORTED
%token SORT_BY
%token SORT_WITH
%token SORT_IN_PLACE
%token MK_STRING
%token ADD_STRING
%token SAME_ELEMENTS
%token CORRESPONDS
%token DIFF
%token INTERSECT
%token UNION
%token PATCH
%token UPDATED
%token KEYS
%token VALUES
%token KEY_SET
%token GET
%token GET_OR_ELSE
%token HAS_NEXT
%token NEXT
%token NEXT_OPTION
%token BUFFERED
%token DUPLICATE
%token CAPITALIZE
%token TO_UPPER_CASE
%token TO_LOWER_CASE
%token STRIP_LINE_END
%token LINES_ITERATOR
%token LINES_WITH_SEPARATORS
%token SCALA IO STDIN PRINT PRINTLN PRINTF
%token EXPR_LIST MAKE_STRING
%token DEF ABSTRACT SEALED FINAL OVERRIDE LAZY TRAIT EXTENDS CLASS WITH SUPER
%token PRIVATE PROTECTED PUBLIC THIS
%token IMPORT VALUE TYPE ENUMERATION OBJECT

%left IF_EXPR WHILE_EXPR DO_WHILE_EXPR FOR_EXPR YIELD
%left EXPR_LIST
%right '='
%nonassoc EQ NEQ
%left '<' '>' LESS_EQ GREATER_EQ
%left '+' '-' PLUS_ASSIGN MINUS_ASSIGN
%left '*' '/' '%' STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN

%left OR '|' OR_ASSIGN
%left '^'
%left AND '&' AND_ASSIGN

%right UMINUS UPLUS UEXCL UTILDA

%nonassoc R_ARROW
%left '.'
%left '(' ')'
%left MAKE_STRING

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
    func_def ';'
  | var_def ';'
  | class_def ';'
  | trait_def ';'
  | enum_def ';'
  | def_prefix def

enum_def:
    OBJECT ID EXTENDS ENUMERATION '{' TYPE ID '=' VALUE ';' VAL id_list '=' VALUE '}'

def_prefix:
    ABSTRACT
  | SEALED
  | FINAL
  | OVERRIDE
  | LAZY
  | PRIVATE
  | PROTECTED
  | PUBLIC
  | PRIVATE '[' ID ']'
  | PRIVATE '[' THIS ']'

trait_def:
    TRAIT ID
  | TRAIT ID '{' def_list_e '}'
  | TRAIT ID EXTENDS id_with_id
  | TRAIT ID EXTENDS id_with_id '{' def_list_e '}'

class_def:
    CLASS ID
  | CLASS ID '{' def_list_e '}'
  | CLASS ID EXTENDS id_with_id
  | CLASS ID EXTENDS id_with_id '{' def_list_e '}'
  | CLASS ID '(' field_list_e ')' 
  | CLASS ID '(' field_list_e ')' '{' def_list_e '}'
  | CLASS ID '(' field_list_e ')' EXTENDS id_with_id
  | CLASS ID '(' field_list_e ')' EXTENDS id_with_id '{' def_list_e '}'

id_with_id:
    ID
  | ID '(' id_list_e ')'
  | id_with_id WITH ID
  | id_with_id WITH ID '(' id_list_e ')'

id_list_e:
    /* empty */
  | id_list

id_list:
    ID
  | id_list ',' ID

field_list_e:
    /* empty */
  | field_list

field_list:
    field
  | field_list ',' field

field:
    VAL ID ':' type
  | VAR ID ':' type

def_list_e:
    /* empty */
  | def_list

def_list:
    def
  | def_list def

func_def:
    DEF ID '(' param_list_e ')' '=' expr
  | DEF ID '(' param_list_e ')' ':' type '=' expr
  | VAL ID '=' '(' param_list_e ')' R_ARROW expr

var_def:
    VAL ID '=' expr
  | VAR ID '=' expr
  | VAL ID ':' type '=' expr
  | VAR ID ':' type '=' expr
  | VAL ID '=' expr '_'

param_list_e:
    /* empty */
  | param_list

param_list:
    ID ':' type
  | param_list ',' ID ':' type

type:
    var_type
  | func_type

var_type:
    TINT
  | TDOUBLE
  | TCHAR
  | TSTR
  | TBOOL
  | TARRAY
  | TARRAY '[' type ']'

func_type:
    '(' ')' R_ARROW type
  | '(' type_list ')' R_ARROW type

type_list:
    type
  | type_list ',' type

type_e:
    /* empty */
  | '[' type ']'

read_type:
    READINT
  | READCHAR
  | READLINE

/* Всё остальное - это выражения */

expr:
    ID
  | IMPORT ID '.' '_'
  | SUPER
  | '(' expr ')' R_ARROW expr
  | '_'
  | LITINT
  | LITCHAR
  | LITSTR
  | LITBOOL
  | LITDOUBLE
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
  | expr AND expr
  | expr '&' expr
  | expr OR expr
  | expr '|' expr
  | expr '^' expr
  | '!' expr %prec UEXCL
  | '~' expr %prec UTILDA
  | expr PLUS_ASSIGN expr
  | expr MINUS_ASSIGN expr
  | expr STAR_ASSIGN expr
  | expr SLASH_ASSIGN expr
  | expr PERCENT_ASSIGN expr
  | expr AND_ASSIGN
  | expr OR_ASSIGN
  | var_type '(' expr_list ')'
  | NEW var_type '(' expr ')' 
  | NEW ID '(' expr_list ')'
  | expr '.' array_postfix
  | expr '(' expr ')'
  | if_expr
  | while_expr
  | do_while_expr
  | for_expr %prec FOR_EXPR
  | SCALA '.' IO '.' STDIN '.' read_type '(' ')'
  | PRINT '(' expr ')'
  | PRINTLN '(' expr ')'
  | PRINTF '(' expr_list ')'
  | expr '.' ID

if_expr:
    IF '(' expr ')' expr %prec IF_EXPR
  | IF '(' expr ')' expr ELSE expr %prec IF_EXPR

while_expr:
    WHILE '(' expr ')' expr %prec WHILE_EXPR

do_while_expr:
    DO expr WHILE '(' expr ')' %prec DO_WHILE_EXPR

for_expr:
    FOR '(' generator_list ')' expr
  | FOR '{' generator_list '}' YIELD expr
  | expr '.' for_expr_postfix

generator_list:
    ID L_ARROW expr range_e
  | generator_list ';' ID L_ARROW expr range_e
  | generator_list ';' IF expr
  | generator_list ';' expr

range_e:
    /* empty */
  | TO expr
  | UNITL expr
  | TO expr BY expr
  | UNITL expr BY expr

expr_list:
    expr
  | expr_list ',' expr %prec EXPR_LIST

expr_list_e:
    /* empty */
  | expr_list

array_postfix:
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
  | HEAD_OPTION
  | LAST
  | LAST_OPTION
  | LIFT '(' expr ')'
  | APPLY_OR_ELSE '(' expr ',' expr ')'
  | UPDATE '(' expr ',' expr ')'
  | TO_ARRAY

mk_string_postfix:
    MK_STRING '(' ')'
  | MK_STRING '(' expr ')'
  | MK_STRING '(' expr ',' expr ',' expr ')'

for_expr_postfix:
    FOREACH '(' expr ')'
  | TAPEACH '(' expr ')'
  | FILTER '(' expr ')'
  | FILTER_NOT '(' expr ')'
  | PARTITION '(' expr ')'
  | PARTITION_MAP '(' expr ')'
  | DISTINCT
  | DISTINCT_BY '(' expr ')'
  | COLLECT '{' case_list '}'
  | COLLECT_FIRST '{' case_list '}'
  | DROP '(' expr ')'
  | DROP_RIGHT '(' expr ')'
  | DROP_WHILE '(' expr ')'
  | TAKE '(' expr ')'
  | TAKE_RIGHT '(' expr ')'
  | TAKE_WHILE '(' expr ')'
  | SPAN '(' expr ')'
  | SLICE '(' expr ',' expr ')'
  | SPLIT_AT '(' expr ')'
  | FIND '(' expr ')'
  | FIND_LAST '(' expr ')'
  | INDEX_WHERE '(' expr ')'
  | LAST_INDEX_WHERE '(' expr ')'
  | INDEX_OF '(' expr ')'
  | LAST_INDEX_OF '(' expr ')'
  | INDEX_OF_SLICE '(' expr ')'
  | LAST_INDEX_OF_SLICE '(' expr ')'
  | CONTAINS '(' expr ')'
  | CONTAINS_SLICE '(' expr ')'
  | EXISTS '(' expr ')'
  | FORALL '(' expr ')'
  | COUNT '(' expr ')'
  | FOLD '(' expr ')'
  | FOLD_LEFT '(' expr ')'
  | FOLD_RIGHT '(' expr ')'
  | REDUCE '(' expr ')'
  | REDUCE_LEFT '(' expr ')'
  | REDUCE_RIGHT '(' expr ')'
  | REDUCE_OPTION '(' expr ')'
  | REDUCE_LEFT_OPTION '(' expr ')'
  | REDUCE_RIGHT_OPTION '(' expr ')'
  | SUM
  | MIN
  | MAX
  | MIN_BY '(' expr ')'
  | MAX_BY '(' expr ')'
  | MIN_OPTION
  | MAX_OPTION
  | MIN_BY_OPTION '(' expr ')'
  | MAX_BY_OPTION '(' expr ')'
  | GROUP_BY '(' expr ')'
  | GROUP_MAP '(' expr ')' '(' expr ')'
  | GROUP_MAP_REDUCE '(' expr ')' '(' expr ')' '(' expr ')'
  | GROUPED '(' expr ')'
  | SLIDING '(' expr ')'
  | ZIP '(' expr ')'
  | ZIP_WITH_INDEX
  | LAZY_ZIP '(' expr ')'
  | MAP '(' expr ')'
  | FLAT_MAP '(' expr ')'
  | SCAN '(' expr ')' '(' expr ')'
  | SCAN_LEFT '(' expr ')' '(' expr ')'
  | SCAN_RIGHT '(' expr ')' '(' expr ')'
  | VIEW
  /* обходят массив, но не являются заменой for */
  | SIZE
  | IS_EMPTY
  | NON_EMPTY
  | SIZE_COMPARE
  | KNOWN_SIZE
  | TAIL
  | INIT
  | IS_DEFINED_AT '(' expr ')'
  | INDICES
  | LENGTH
  | LENGTH_COMPARE '(' expr ')'
  | REVERSE
  | REVERSE_ITERATOR
  | SORTED
  | SORT_BY '(' expr ')'
  | SORT_WITH '(' expr ')'
  | SORT_IN_PLACE
  | mk_string_postfix %prec MAKE_STRING
  | ADD_STRING '(' expr ')'
  | ADD_STRING '(' expr ',' expr ')'
  | ADD_STRING '(' expr ',' expr ',' expr ',' expr ')'
  | SAME_ELEMENTS '(' expr ')'
  | CORRESPONDS '(' expr ')' '(' expr ')'
  | DIFF '(' expr ')'
  | INTERSECT '(' expr ')'
  | UNION '(' expr ')'
  | PATCH '(' expr ',' expr ',' expr ')'
  | UPDATED '(' expr ',' expr ')'
  | KEYS
  | VALUES
  | KEY_SET
  | GET '(' expr ')'
  | GET_OR_ELSE '(' expr ',' expr ')'
  | HAS_NEXT
  | NEXT '(' ')'
  | NEXT_OPTION '(' ')'
  | BUFFERED
  | DUPLICATE
  | CAPITALIZE
  | TO_UPPER_CASE
  | TO_LOWER_CASE
  | STRIP_LINE_END
  | LINES_ITERATOR
  | LINES_WITH_SEPARATORS

case_list:
    case
  | case_list case

case:
    CASE expr R_ARROW expr
  | CASE expr IF expr R_ARROW expr



%%

/* Эпилог (Epilogue): дополнительный C-код */