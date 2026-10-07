/* токены */

%token UNDERSCORE
%token SEPARATOR
%token VAL VAR
%token ID
%token TINT TCHAR TSTR
%token TARRAY TLIST TDOUBLE TFLOAT TBOOL
%token LITINT LITCHAR LITSTR
%token COLON
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN
%token PLUS MINUS STAR SLASH PERCENT EXCL TILDA
%token EQ NEQ LESS_EQ GREATER_EQ LESS_NEQ GREATER_NEQ
%token LPAR RPAR SQ_LPAR SQ_RPAR CURV_LPAR CURV_RPAR
%token NEW DOT FROM FILL TABULATE RANGE COMMA ITERATE RARROW CONCAT TO TOTARRAY TOARRAY EMPTY
%token LIST NIL CONS VECTOR SEQ SET MAP ARRAY APPLY UPDATE HEAD LAST
%token IF ELSE MATCH CASE AT_SIGN SOME NONE OR
%token WHILE DO FOR BY UNTIL YIELD
%token DEF PRINT PRINTLN PRINTF CONSOLE ERR READINT READCHAR READLINE
%token CLASS FINAL ABSTRACT SEALED TRAIT EXTENDS WITH PRIVATE PROTECTED PACKAGE THIS OVERRIDE SUPER
%token AND BYTE_AND BYTE_OR BYTE_XOR
%token OBJECT ENUMERATION TYPE VALUE IMPORT
%token TRY CATCH FINALLY E EXCEPTION THROW SUCCESS V FAILURE NONFATAL
%token EITHER OPTION
%token LARROW TOLIST
%token OR_ASSIGN XOR_ASSIGN AND_ASSIGN SUBTYPE SUPERTYPE CONTEXT_FUNC HASH QMARK BACKSLASH
%token UMINUS UPLUS UEXCL UTILDA

/* приоритеты и ассоциативность */

%right ASSIGN
%left OR_ASSIGN OR
%left XOR_ASSIGN XOR
%left AND_ASSIGN AND
%nonassoc EQ NEQ
%left LESS_NEQ GREATER_NEQ LESS_EQ GREATER_EQ
%right SUBTYPE SUPERTYPE
%right COLON
%left PLUS MINUS PLUS_ASSIGN MINUS_ASSIGN
%left STAR SLASH PERCENT STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN
%left CONTEXT_FUNC HASH AT_SIGN QMARK BACKSLASH
%right UMINUS UPLUS UEXCL UTILDA

%start program

%%

/* стартер, инструкции */

program:
    stmt_list_e
;

stmt_list_e:
    /* empty */
  | stmt_list
;

stmt_list:
    stmt
  | stmt_list stmt
;

stmt:
    def
  | expr SEPARATOR
  | output SEPARATOR
  | input SEPARATOR
;

/* определения */

def:
    var_def SEPARATOR
  | func_def SEPARATOR
  | class_def SEPARATOR
  | trait_def SEPARATOR
  | aux_constructor_def SEPARATOR
  | final_func_def SEPARATOR
  | enum_def SEPARATOR
;

/* переменные, массивы, списки */

var_def:
    VAL ID opt_type_ann ASSIGN expr
  | VAR ID opt_type_ann ASSIGN expr
;

opt_type_ann:
    /* empty */
  | COLON type
;

/* типы */

type:
    simple_type
  | simple_type WITH trait_list
;

simple_type:
    TINT
  | TCHAR
  | TSTR
  | TDOUBLE
  | TFLOAT
  | TBOOL
  | TARRAY
  | TARRAY SQ_LPAR type SQ_RPAR
  | TLIST SQ_LPAR type SQ_RPAR
  | EITHER SQ_LPAR type COMMA type SQ_RPAR
  | OPTION SQ_LPAR type SQ_RPAR
  | ID
;

/* функции */

func_def:
    DEF ID LPAR param_list_e RPAR COLON type ASSIGN expr
  | DEF ID LPAR param_list_e RPAR ASSIGN expr
  | DEF ID COLON type ASSIGN expr
  | DEF ID ASSIGN expr
  | DEF ID param_list_e_seq COLON type ASSIGN expr
  | DEF ID param_list_e_seq ASSIGN expr
  | VAL ID COLON type RARROW type ASSIGN ID RARROW expr
  | VAL ID COLON LPAR type_list_e RPAR RARROW type ASSIGN LPAR expr_list_e RPAR RARROW expr
  | VAL ID ASSIGN LPAR param_list_e RPAR RARROW expr
  | VAL ID COLON type RARROW type ASSIGN expr
  | VAL ID COLON LPAR type_list_e RPAR RARROW type ASSIGN expr
  | VAL ID COLON type RARROW type ASSIGN CURV_LPAR ID RARROW stmt_list expr CURV_RPAR
  | VAL ID COLON LPAR type_list_e RPAR RARROW type ASSIGN CURV_LPAR ID RARROW stmt_list expr CURV_RPAR
;

final_func_def:
    FINAL func_def
;

param_list_e_seq:
    LPAR param_list_e RPAR
  | param_list_e_seq LPAR param_list_e RPAR
;

type_list_e:
    /* empty */
  | type_list
;

type_list:
    type
  | type_list COMMA type
;

param_list_e:
    /* empty */
  | param_list
;

param_list:
    param
  | param_list COMMA param
;

param:
    ID COLON type
  | ID COLON type ASSIGN expr
  | ID COLON type STAR
  | ID COLON type RARROW type
  | ID COLON LPAR type_list_e RPAR RARROW type
;

/* классы, трейты, конструкторы */

class_id:
    CLASS ID
  | FINAL CLASS ID
  | ABSTRACT CLASS ID
  | SEALED CLASS ID
  | SEALED ABSTRACT CLASS ID
;

trait_list:
    ID
  | trait_list WITH ID
;

class_def:
    class_id class_params_opt class_parent_opt class_body_opt
;

class_params_opt:
    /* empty */
  | LPAR class_field_list_e RPAR
;

class_parent_opt:
    /* empty */
  | EXTENDS parent_ref
;

class_body_opt:
    /* empty */
  | CURV_LPAR prop_def_list_e CURV_RPAR
;

parent_ref:
    ID parent_args_opt parent_with_opt
;

parent_args_opt:
    /* empty */
  | LPAR expr_list_e RPAR
;

parent_with_opt:
    /* empty */
  | WITH trait_list
;

trait_def:
    opt_sealed TRAIT ID trait_parent_opt trait_body_opt
;

opt_sealed:
    /* empty */
  | SEALED
;

trait_parent_opt:
    /* empty */
  | EXTENDS parent_ref
;

trait_body_opt:
    /* empty */
  | CURV_LPAR prop_def_list_e CURV_RPAR
;

aux_constructor_def:
    DEF THIS LPAR param_list_e RPAR ASSIGN THIS LPAR expr_list_e RPAR
;

class_field_list_e:
    /* empty */
  | class_field_list
;

class_field_list:
    class_field
  | class_field_list COMMA class_field
;

class_field:
    ID COLON type
  | VAL ID COLON type
;

/* пропсы */

prop_def_list_e:
    /* empty */
  | prop_def_list
;

prop_def_list:
    member_def
  | prop_def_list SEPARATOR member_def
;

member_def:
    THIS COLON ID RARROW def
  | member_modifiers def
;

member_modifiers:
    /* empty */
  | PRIVATE
  | PROTECTED
  | PROTECTED SQ_LPAR PACKAGE SQ_RPAR
  | PRIVATE SQ_LPAR THIS SQ_RPAR
  | PRIVATE SQ_LPAR PACKAGE SQ_RPAR
  | OVERRIDE
  | ABSTRACT PRIVATE
  | ABSTRACT PROTECTED
  | ABSTRACT PROTECTED SQ_LPAR PACKAGE SQ_RPAR
  | ABSTRACT PRIVATE SQ_LPAR THIS SQ_RPAR
  | ABSTRACT PRIVATE SQ_LPAR PACKAGE SQ_RPAR
  | ABSTRACT OVERRIDE
;

/* перечисления */

enum_def:
    OBJECT ID EXTENDS ENUMERATION CURV_LPAR expr_list_e CURV_RPAR
;

/* выражения */

expr:
    assign_expr
;

assign_expr:
    or_expr
  | or_expr ASSIGN         assign_expr
  | or_expr PLUS_ASSIGN    assign_expr
  | or_expr MINUS_ASSIGN   assign_expr
  | or_expr STAR_ASSIGN    assign_expr
  | or_expr SLASH_ASSIGN   assign_expr
  | or_expr PERCENT_ASSIGN assign_expr
;

or_expr:
    and_expr
  | or_expr OR and_expr
;

and_expr:
    bit_expr
  | and_expr AND bit_expr
;

bit_expr:
    eq_expr
  | bit_expr BYTE_OR  eq_expr
  | bit_expr BYTE_XOR eq_expr
  | bit_expr BYTE_AND eq_expr
;

eq_expr:
    rel_expr
  | eq_expr EQ  rel_expr
  | eq_expr NEQ rel_expr
;

rel_expr:
    range_expr
  | rel_expr LESS_EQ     range_expr
  | rel_expr GREATER_EQ  range_expr
  | rel_expr LESS_NEQ    range_expr
  | rel_expr GREATER_NEQ range_expr
;

range_expr:
    cons_expr
  | cons_expr TO range_expr
;

cons_expr:
    add_expr
  | add_expr CONS cons_expr
;

add_expr:
    mul_expr
  | add_expr PLUS  mul_expr
  | add_expr MINUS mul_expr
;

mul_expr:
    unary_expr
  | mul_expr STAR    unary_expr
  | mul_expr SLASH   unary_expr
  | mul_expr PERCENT unary_expr
;

unary_expr:
    postfix_expr
  | PLUS  unary_expr %prec UPLUS
  | MINUS unary_expr %prec UMINUS
  | EXCL  unary_expr %prec UEXCL
  | TILDA unary_expr %prec UTILDA
;

postfix_expr:
    primary_expr
  | postfix_expr LPAR expr_list_e RPAR          
  | postfix_expr SQ_LPAR type_list_e SQ_RPAR    
  | postfix_expr DOT method_suffix              
  | SUPER DOT method_suffix
;

method_suffix:
    method_name
  | method_name LPAR expr_list_e RPAR
  | method_name SQ_LPAR type_list_e SQ_RPAR
  | method_name SQ_LPAR type_list_e SQ_RPAR LPAR expr_list_e RPAR
;

method_name:
    ID
  | APPLY 
  | UPDATE 
  | HEAD 
  | LAST 
  | TOLIST 
  | TOARRAY 
  | EMPTY 
  | CONCAT
  | RANGE 
  | FILL 
  | TABULATE 
  | ITERATE 
  | FROM
;

primary_expr:
    LITINT
  | LITCHAR
  | LITSTR
  | ID
  | UNDERSCORE
  | TARRAY
  | TLIST
  | LPAR expr_list_e RPAR
  | block_expr
  | if_expr
  | match_expr
  | SOME LPAR expr RPAR
  | NONE
  | while_expr
  | do_while_expr
  | for_expr
  | YIELD LPAR expr_list_e RPAR
  | try_catch_expr
  | THROW NEW EXCEPTION LPAR RPAR
  | THROW NEW EXCEPTION LPAR expr RPAR
  | TYPE ID ASSIGN VALUE
  | ID DOT VALUE
  | IMPORT ID DOT UNDERSCORE
  | NEW type LPAR expr_list_e RPAR
  | iterable_once LPAR expr_list_e RPAR
  | UNDERSCORE RARROW expr
  | NIL
  | LIST LPAR expr_list RPAR
  | CONS LPAR expr COMMA cons_expr RPAR
  | NEW CONS LPAR expr COMMA cons_expr RPAR
;

iterable_once:
    LIST
  | VECTOR
  | SEQ
  | SET
  | MAP
  | RANGE
  | ARRAY
;

expr_list:
    expr
  | expr_list COMMA expr
;

expr_list_e:
    /* empty */
  | expr_list
;

block_expr:
    CURV_LPAR stmt_list_e CURV_RPAR
;

/* развилки */

if_expr:
    IF LPAR expr RPAR expr
  | IF LPAR expr RPAR expr ELSE expr
;

match_expr:
    postfix_expr MATCH CURV_LPAR case_list CURV_RPAR
  | postfix_expr MATCH CURV_LPAR except_case_list CURV_RPAR
;

case_list:
    wildcard_case
  | case_list case
;

wildcard_case:
    CASE UNDERSCORE RARROW expr
;

case:
    CASE expr RARROW expr
  | CASE expr IF expr RARROW expr
  | CASE ID COLON type RARROW expr
  | CASE ID COLON type IF expr RARROW expr
  | CASE ID AT_SIGN expr RARROW expr
  | CASE ID AT_SIGN expr IF expr RARROW expr
  | CASE ID COLON type AT_SIGN expr RARROW expr
  | CASE ID COLON type AT_SIGN expr IF expr RARROW expr
;

/* циклы */

while_expr:
    WHILE LPAR expr RPAR expr
;

do_while_expr:
    DO expr WHILE LPAR expr RPAR
;

for_expr:
    FOR LPAR generator RPAR expr
  | FOR LPAR generator guard RPAR expr
  | FOR CURV_LPAR generator_list CURV_RPAR expr
  | FOR LPAR ID LARROW expr TO expr BY expr RPAR expr
;

generator_list:
    generator
  | generator_list generator
  | generator_list guard
;

generator:
    ID LARROW expr
  | ID LARROW expr TO expr
  | ID LARROW expr UNTIL expr
;

guard:
    IF expr
;

/* консоль */

output:
    PRINT LPAR expr RPAR
  | PRINTLN LPAR expr RPAR
  | PRINTF LPAR LITSTR COMMA args_e RPAR
  | CONSOLE DOT ERR DOT PRINTLN LPAR expr RPAR
;

input:
    READINT LPAR RPAR
  | READCHAR LPAR RPAR
  | READLINE LPAR RPAR
;

args_e:
    /* empty */
  | args
;

args:
    expr
  | args COMMA expr
;

/* исключения */

try_catch_expr:
    TRY expr CATCH CURV_LPAR err_case_list CURV_RPAR FINALLY expr
  | TRY expr CATCH CURV_LPAR err_case_list wildcard_err_case CURV_RPAR FINALLY expr
;

err_case_list:
    err_case
  | err_case_list err_case
;

err_case:
    CASE E COLON EXCEPTION RARROW PRINTLN LPAR expr RPAR
;

wildcard_err_case:
    CASE UNDERSCORE COLON EXCEPTION RARROW PRINTLN LPAR expr RPAR
;

except_case_list:
    except_case
  | except_case_list SEPARATOR except_case
;

except_case:
    CASE SUCCESS LPAR V RPAR RARROW expr
  | CASE FAILURE LPAR E RPAR RARROW expr
  | CASE NONFATAL LPAR E RPAR RARROW expr
;

%%