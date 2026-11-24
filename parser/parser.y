%code requires {
    #include "nodes/nodes.h"
}

%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "nodes/nodes.h"

int yylex();
void yyerror(TopStmtSeqNode** out_root, const char* message);

static void print_semantic_string(FILE* out, const char* value) {
    fputc('"', out);
    if (value != nullptr) {
        for (const unsigned char* p = reinterpret_cast<const unsigned char*>(value); *p; ++p) {
            switch (*p) {
                case '\\': fputs("\\\\", out); break;
                case '"': fputs("\\\"", out); break;
                case '\n': fputs("\\n", out); break;
                case '\r': fputs("\\r", out); break;
                case '\t': fputs("\\t", out); break;
                default:
                    if (*p < 0x20) fputc(' ', out);
                    else fputc(*p, out);
            }
        }
    }
    fputc('"', out);
}

static IdNode* makeId(char* text) {
    IdNode* node = IdNode::createId(text == nullptr ? "" : text);
    std::free(text);
    return node;
}

static PrimaryExprNode* makeIntLiteral(char* text) {
    const int value = text == nullptr ? 0 : std::atoi(text);
    std::free(text);
    return PrimaryExprNode::createIntNode(value);
}

static PrimaryExprNode* makeCharLiteral(char* text) {
    const char value = text == nullptr || text[0] == '\0' ? '\0' : text[0];
    std::free(text);
    return PrimaryExprNode::createCharNode(value);
}

static PrimaryExprNode* makeDoubleLiteral(char* text) {
    const double value = text == nullptr ? 0.0 : std::atof(text);
    std::free(text);
    return PrimaryExprNode::createDoubleNode(value);
}

static PrimaryExprNode* makeStringLiteral(char* text) {
    const std::string value = text == nullptr ? "" : text;
    std::free(text);
    return PrimaryExprNode::createStringNode(value);
}

static PrimaryExprNode* makeBoolLiteral(char* text) {
    const bool value = text != nullptr && std::strcmp(text, "true") == 0;
    std::free(text);
    return PrimaryExprNode::createBoolNode(value);
}

static ArgumentExprsNode* makeSingleArgument(ExprNode* expr) {
    return new ArgumentExprsNode(ExprsNode::addExprToList(nullptr, expr));
}

static VarDefsNode* makeVarDefs(ModifiersNode* modifiers, ClassParamType kind,
                                IdListNode* ids, SimpleTypeNode* type, ExprNode* value) {
    VarDefsNode* definition = new VarDefsNode();
    definition->type = kind == _VAL_CLASS_PARAM ? _VAL_DECL : _VAR_DECL;
    definition->simpleType = type;
    definition->expr = value;
    if (ids != nullptr) {
        definition->fullIds = ids->ids;
        ids->ids.clear();
        delete ids;
    }
    return definition;
}

static DefNode* makeLocalDef(VarDefsNode* definition) {
    definition->isLocal = true;
    return DefNode::createVarDefs(definition, new ModifiersNode());
}

static FuncParamsNode* makeFuncParamsFromClass(ClassParamsNode* classParams) {
    FuncParamsNode* params = new FuncParamsNode();
    if (classParams != nullptr) {
        for (ClassParamNode* param : classParams->classParams) {
            params->funcParams.push_back(
                FuncParamNode::createFuncParam(param->fullId, param->simpleType));
        }
    }
    return params;
}

static SimpleTypeNode* makeArrayType(SimpleTypeNode* elementType) {
    return SimpleTypeNode::createSimpleTypeNode(elementType);
}
%}

%define parse.trace
%define parse.error verbose
%token-table
%parse-param { TopStmtSeqNode** out_root }

%union {
    char* text;
    ModifiersNode* modifiers;
    ModifierNode* modifier;
    IdNode* id;
    IdListNode* idList;
    SimpleTypeNode* simpleType;
    VarDefsNode* varDefs;
    FuncParamNode* funcParam;
    FuncParamsNode* funcParams;
    FunSigNode* funSig;
    FunDefNode* funDef;
    DefNode* def;
    ClassParamType classParamType;
    ClassParamNode* classParam;
    ClassParamsNode* classParams;
    ExtensionClassTemplateNode* extensionClassTemplate;
    ClassTemplateOptNode* classTemplateOpt;
    ClassDefNode* classDef;
    TemplateDefNode* templateDef;
    TemplateStmtNode* templateStat;
    TemplateStmtsNode* templateStats;
    TopStmtNode* topStat;
    TopStmtSeqNode* topStatSeq;
    BlockStmtNode* blockStat;
    BlockStmtsNode* blockStats;
    ExprNode* expr;
    ExprsNode* exprs;
    ArgumentExprsNode* argumentExprs;
    AssignmentNode* assignment;
    InfixExprNode* infixExpr;
    PrefixExprNode* prefixExpr;
    SimpleExprNode* simpleExpr;
    PrimaryExprNode* primaryExpr;
    GeneratorNode* generator;
    EnumeratorsNode* enumerators;
    CatchNode* catchNode;
    CaseNode* caseNode;
    ImportNode* importNode;
    PathNode* path;
}

%token WHILE DO FOR
%token VAL VAR
%token <text> ID
%token NEW TARRAY
%token R_ARROW
%token <text> LITINT LITCHAR LITSTR LITDOUBLE LITBOOL
%token KNULL
%token PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN PERCENT_ASSIGN AND_ASSIGN OR_ASSIGN
%token IF ELSE
%token L_ARROW
%token CASE
%token TRY CATCH FINALLY THROW RETURN
%token DEF ABSTRACT SEALED FINAL OVERRIDE EXTENDS CLASS SUPER
%token PRIVATE PROTECTED THIS
%token IMPORT TYPE OBJECT
%token NL
%token <text> UNSUPPORTED "unsupported token"

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

%expect 2

%printer { print_semantic_string(yyo, $$); } <text>
%destructor { std::free($$); } <text>
%destructor { deleteNodeTree($$); } <modifiers> <modifier> <idList> <simpleType>
%destructor { deleteNodeTree($$); } <varDefs> <funcParam> <funcParams> <def>
%destructor { deleteNodeTree($$); } <classParam> <classParams>
%destructor { deleteNodeTree($$); } <classTemplateOpt> <classDef>
%destructor { deleteNodeTree($$); } <templateStat> <templateStats> <topStat> <topStatSeq>
%destructor { deleteNodeTree($$); } <blockStat> <blockStats> <expr> <exprs> <argumentExprs>
%destructor { deleteNodeTree($$); } <infixExpr> <prefixExpr> <simpleExpr>
%destructor { deleteNodeTree($$); } <primaryExpr> <generator> <enumerators> <catchNode>
%destructor { deleteNodeTree($$); } <caseNode> <importNode> <path>

%type <topStatSeq> program top_list
%type <topStat> top_stat
%type <importNode> import
%type <path> path
%type <templateStat> stmt
%type <def> def func_def var_def
%type <modifier> def_prefix
%type <modifiers> def_prefix_list
%type <classDef> class_def
%type <classParams> class_fields field_list
%type <classTemplateOpt> class_tail
%type <argumentExprs> args_e args
%type <templateStats> class_body stmt_list_e stmt_list
%type <idList> id_list
%type <classParam> field
%type <classParamType> val_or_var
%type <funcParams> params_e param_list_e param_list
%type <funcParam> param
%type <simpleType> type type_e
%type <blockStats> block_stats block_list
%type <blockStat> block_stat
%type <varDefs> local_def
%type <expr> expr if_expr while_expr do_while_expr for_expr finally_e
%type <enumerators> generator_list
%type <generator> generator
%type <catchNode> catch_e case_list
%type <caseNode> case
%type <infixExpr> infix
%type <prefixExpr> prefix
%type <exprs> expr_list
%type <simpleExpr> simple
%type <primaryExpr> literal

%%

program:
    semis_e
        { $$ = nullptr; *out_root = new TopStmtSeqNode(); }
  | semis_e top_list semis_e
        { $$ = nullptr; *out_root = $2; }
  ;

top_list:
    top_stat
        { $$ = TopStmtSeqNode::addTopStmtToList(nullptr, $1); }
  | top_list semis top_stat
        { $$ = TopStmtSeqNode::addTopStmtToList($1, $3); }
  ;

top_stat:
    import
        { $$ = TopStmtNode::createImport($1); }
  | class_def
        { $$ = TopStmtNode::createClass(TemplateDefNode::createClassDef($1)); }
  ;

import:
    IMPORT path
        { $$ = ImportNode::createImport($2); }
  ;

path:
    ID
        { $$ = PathNode::addPart(nullptr, makeId($1)); }
  | path '.' ID
        { $$ = PathNode::addPart($1, makeId($3)); }
  ;

semi:
    ';'
  | NL
  ;

semis:
    semi
  | semis semi
  ;

semis_e:
    /* empty */
  | semis
  ;

nls:
    /* empty */
  | nls NL
  ;

nl_e:
    /* empty */
  | NL
  ;

stmt:
    def
        { $$ = TemplateStmtNode::createDefTemplate($1); }
  | expr
        { $$ = TemplateStmtNode::createExprTemplate($1); }
  ;

def:
    func_def
        { $$ = $1; }
  | var_def
        { $$ = $1; }
  ;

def_prefix:
    ABSTRACT
        { $$ = ModifierNode::createModifier(_ABSTRACT); }
  | SEALED
        { $$ = ModifierNode::createModifier(_SEALED); }
  | FINAL
        { $$ = ModifierNode::createModifier(_FINAL); }
  | OVERRIDE
        { $$ = ModifierNode::createModifier(_OVERRIDE); }
  | PRIVATE
        { $$ = ModifierNode::createModifier(_PRIVATE); }
  | PROTECTED
        { $$ = ModifierNode::createModifier(_PROTECTED); }
  ;

def_prefix_list:
    /* empty */
        { $$ = new ModifiersNode(); }
  | def_prefix_list def_prefix
        { $$ = ModifiersNode::addModifierToList($1, $2); }
  ;

class_def:
    def_prefix_list CLASS ID class_tail
        { $$ = ClassDefNode::createClassDef(makeId($3), $1, nullptr, $4); }
  | def_prefix_list CLASS ID class_fields class_tail
        { $$ = ClassDefNode::createClassDef(makeId($3), $1, $4, $5); }
  | def_prefix_list OBJECT ID class_tail
        { $$ = ClassDefNode::createObjectDef(makeId($3), $1, $4); }
  ;

class_fields:
    nls '(' ')'
        { $$ = new ClassParamsNode(); }
  | nls '(' field_list ')'
        { $$ = $3; }
  ;

class_tail:
    class_body
        { $$ = ClassTemplateOptNode::createClassWithoutInherit($1); }
  | EXTENDS ID args_e class_body
        { $$ = ClassTemplateOptNode::createClassWithInherit(
              ExtensionClassTemplateNode::createExtendWithConstrAndBody(
                  makeId($2), $3, $4)); }
  ;

args_e:
    /* empty */
        { $$ = new ArgumentExprsNode(); }
  | args
        { $$ = $1; }
  ;

args:
    '(' ')'
        { $$ = new ArgumentExprsNode(); }
  | '(' expr_list ')'
        { $$ = new ArgumentExprsNode($2); }
  ;

class_body:
    nls '{' stmt_list_e '}'
        { $$ = $3; }
  ;

stmt_list_e:
    semis_e
        { $$ = new TemplateStmtsNode(); }
  | semis_e stmt_list semis_e
        { $$ = $2; }
  ;

stmt_list:
    stmt
        { $$ = TemplateStmtsNode::addTemplateStmtToBackToList(nullptr, $1); }
  | stmt_list semis stmt
        { $$ = TemplateStmtsNode::addTemplateStmtToBackToList($1, $3); }
  ;

id_list:
    ID
        { $$ = IdListNode::addId(nullptr, makeId($1)); }
  | id_list ',' ID
        { $$ = IdListNode::addId($1, makeId($3)); }
  ;

field_list:
    field
        { $$ = ClassParamsNode::addClassParamToList(nullptr, $1); }
  | field_list ',' field
        { $$ = ClassParamsNode::addClassParamToList($1, $3); }
  ;

field:
    ID ':' type
        { $$ = ClassParamNode::createClassParam(_UNMARKED_CLASS_PARAM,
              new ModifiersNode(), makeId($1), $3); }
  | def_prefix_list val_or_var ID ':' type
        { $$ = ClassParamNode::createClassParam($2, $1, makeId($3), $5); }
  ;

val_or_var:
    VAL
        { $$ = _VAL_CLASS_PARAM; }
  | VAR
        { $$ = _VAR_CLASS_PARAM; }
  ;

func_def:
    def_prefix_list DEF ID params_e type_e '=' expr
        { $$ = DefNode::createFunDef(FunDefNode::createFunSigFunDef(
              FunSigNode::createFunSig(makeId($3), $4), $5, $7), $1); }
  | def_prefix_list DEF ID params_e ':' type
        { $$ = DefNode::createFunDef(FunDefNode::createFunSigFunDef(
              FunSigNode::createFunSig(makeId($3), $4), $6, nullptr), $1); }
  | def_prefix_list DEF THIS params_e '=' expr
        { $$ = DefNode::createFunDef(
              FunDefNode::createThisConstrCallFunDef($4, $6), $1); }
  ;

var_def:
    def_prefix_list val_or_var id_list type_e '=' expr
        { $$ = DefNode::createVarDefs(makeVarDefs($1, $2, $3, $4, $6), nullptr); }
  | def_prefix_list val_or_var id_list ':' type
        { $$ = DefNode::createVarDefs(makeVarDefs($1, $2, $3, $5, nullptr), nullptr); }
  ;

params_e:
    /* empty */
        { $$ = new FuncParamsNode(); }
  | nl_e '(' param_list_e ')'
        { $$ = $3; }
  ;

param_list_e:
    /* empty */
        { $$ = new FuncParamsNode(); }
  | param_list
        { $$ = $1; }
  ;

param_list:
    param
        { $$ = FuncParamsNode::addFuncParamToList(nullptr, $1); }
  | param_list ',' param
        { $$ = FuncParamsNode::addFuncParamToList($1, $3); }
  ;

param:
    ID ':' type
        { $$ = FuncParamNode::createFuncParam(makeId($1), $3); }
  ;

type:
    ID
        { $$ = SimpleTypeNode::createIdTypeNode(makeId($1)); }
  | ID '.' ID
        { $$ = SimpleTypeNode::createIdTypeNode(
              IdNode::createId(std::string($1) + "." + $3)); std::free($1); std::free($3); }
  | TARRAY '[' type ']'
        { $$ = makeArrayType($3); }
  ;

type_e:
    /* empty */
        { $$ = nullptr; }
  | ':' type
        { $$ = $2; }
  ;

block_stats:
    semis_e
        { $$ = new BlockStmtsNode(); }
  | semis_e block_list semis_e
        { $$ = $2; }
  ;

block_list:
    block_stat
        { $$ = BlockStmtsNode::addBlockStmtToList(nullptr, $1); }
  | block_list semis block_stat
        { $$ = BlockStmtsNode::addBlockStmtToList($1, $3); }
  ;

block_stat:
    local_def
        { $$ = BlockStmtNode::createLocalDef($1); }
  | expr
        { $$ = BlockStmtNode::createExprNode($1); }
  ;

local_def:
    val_or_var id_list type_e '=' expr
        { $$ = makeVarDefs(new ModifiersNode(), $1, $2, $3, $5); }
  ;

expr:
    if_expr
        { $$ = $1; }
  | while_expr
        { $$ = $1; }
  | do_while_expr
        { $$ = $1; }
  | for_expr
        { $$ = $1; }
  | TRY expr catch_e finally_e
        { $$ = ExprNode::createTry(TryExprNode::createExceptionBlock($2, $3, $4)); }
  | THROW expr
        { $$ = ExprNode::createThrow($2); }
  | RETURN %prec RETURN_EMPTY
        { $$ = ExprNode::createReturn(); }
  | RETURN expr
        { $$ = ExprNode::createReturnExpr($2); }
  | simple '=' expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $3, "=")); }
  | simple PLUS_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "+=")); }
  | simple MINUS_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "-=")); }
  | simple STAR_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "*=")); }
  | simple SLASH_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "/=")); }
  | simple PERCENT_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "%=")); }
  | simple AND_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "&=")); }
  | simple OR_ASSIGN nl_e expr
        { $$ = ExprNode::createAssignment(
              AssignmentNode::createAssignment($1, $4, "|=")); }
  | infix
        { $$ = ExprNode::createInfix($1); }
  ;

if_expr:
    IF '(' expr ')' nls expr %prec IF_EXPR
        { $$ = ExprNode::createIf($3, $6); }
  | IF '(' expr ')' nls expr ELSE expr
        { $$ = ExprNode::createIfElse($3, $6, $8); }
  ;

while_expr:
    WHILE '(' expr ')' nls expr
        { $$ = ExprNode::createWhile($3, $6); }
  ;

do_while_expr:
    DO expr semis_e WHILE '(' expr ')'
        { $$ = ExprNode::createDoWhile($2, $6); }
  ;

for_expr:
    FOR '(' generator_list ')' nls expr
        { $$ = ExprNode::createFor($3, $6); }
  | FOR '{' semis_e generator_list semis_e '}' nls expr
        { $$ = ExprNode::createFor($4, $8); }
  ;

generator_list:
    generator
        { $$ = EnumeratorsNode::addEnumerator(nullptr, $1); }
  | generator_list semis generator
        { $$ = EnumeratorsNode::addEnumerator($1, $3); }
  | generator_list semis_e IF expr
        { $$ = EnumeratorsNode::addEnumerator($1, GeneratorNode::createGuard($4)); }
  ;

generator:
    ID L_ARROW expr
        { $$ = GeneratorNode::createGenerator(makeId($1), nullptr, $3); }
  ;

catch_e:
    /* empty */
        { $$ = nullptr; }
  | CATCH '{' case_list '}'
        { $$ = $3; }
  ;

case_list:
    case
        { $$ = CatchNode::addCase(nullptr, $1); }
  | case_list case
        { $$ = CatchNode::addCase($1, $2); }
  ;

case:
    CASE ID type_e R_ARROW block_stats
        { $$ = CaseNode::createCase(makeId($2), $3, $5); }
  ;

finally_e:
    /* empty */
        { $$ = nullptr; }
  | FINALLY expr
        { $$ = $2; }
  ;

infix:
    prefix
        { $$ = InfixExprNode::createInfixFromPrefix($1); }
  | infix ID nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator($2), $4); std::free($2); }
  | infix OR nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("||"), $4); }
  | infix AND nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("&&"), $4); }
  | infix '|' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("|"), $4); }
  | infix '^' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("^"), $4); }
  | infix '&' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("&"), $4); }
  | infix EQ nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("=="), $4); }
  | infix NEQ nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("!="), $4); }
  | infix '<' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("<"), $4); }
  | infix '>' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator(">"), $4); }
  | infix LESS_EQ nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("<="), $4); }
  | infix GREATER_EQ nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator(">="), $4); }
  | infix SHL nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("<<"), $4); }
  | infix SHR nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator(">>"), $4); }
  | infix '+' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("+"), $4); }
  | infix '-' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("-"), $4); }
  | infix '*' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("*"), $4); }
  | infix '/' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("/"), $4); }
  | infix '%' nl_e infix
        { $$ = InfixExprNode::createFromInfixes($1, OperatorNode::createOperator("%"), $4); }
  ;

prefix:
    simple
        { $$ = PrefixExprNode::createPrefixExprNode($1, _NO_UNARY_OPERATOR); }
  | '-' simple
        { $$ = PrefixExprNode::createPrefixExprNode($2, _UNARY_MINUS); }
  | '+' simple
        { $$ = PrefixExprNode::createPrefixExprNode($2, _UNARY_PLUS); }
  | '!' simple
        { $$ = PrefixExprNode::createPrefixExprNode($2, _LOGICAL_NOT); }
  | '~' simple
        { $$ = PrefixExprNode::createPrefixExprNode($2, _BIT_NOT); }
  ;

expr_list:
    expr
        { $$ = ExprsNode::addExprToList(nullptr, $1); }
  | expr_list ',' expr
        { $$ = ExprsNode::addExprToList($1, $3); }
  ;

simple:
    literal
        { $$ = SimpleExprNode::createPrimaryExprNode($1); }
  | ID
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createIdNode(makeId($1))); }
  | THIS
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createPlainThisNode()); }
  | SUPER '.' ID
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createSuperFieldAccessNode(makeId($3))); }
  | simple '.' ID
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createSimpleExprFieldAccessNode(makeId($3), $1)); }
  | simple args
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createMethodCallNode($1, $2)); }
  | '(' expr ')'
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createParenthesizedExprNode($2)); }
  | '{' block_stats '}'
        { $$ = SimpleExprNode::createBlockStmtsNode($2); }
  | NEW ID args
        { $$ = SimpleExprNode::createNewObjectNode(makeId($2), $3); }
  | NEW TARRAY '[' type ']' '(' expr ')'
        { $$ = SimpleExprNode::createNewArrayNode($4, makeSingleArgument($7)); }
  | TARRAY args
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createArrayBuilderNode($2)); }
  | TARRAY '[' type ']' args
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createArrayWithTypeBuilderNode($3, $5)); }
  | TARRAY '.' ID '[' type ']' args
        { $$ = SimpleExprNode::createPrimaryExprNode(
              PrimaryExprNode::createArrayMethodNode(makeId($3), $5, $7)); }
  ;

literal:
    LITINT
        { $$ = makeIntLiteral($1); }
  | LITCHAR
        { $$ = makeCharLiteral($1); }
  | LITBOOL
        { $$ = makeBoolLiteral($1); }
  | LITDOUBLE
        { $$ = makeDoubleLiteral($1); }
  | LITSTR
        { $$ = makeStringLiteral($1); }
  | KNULL
        { $$ = PrimaryExprNode::createNullNode(); }
  | '(' ')'
        { $$ = PrimaryExprNode::createUnitLiteralNode(); }
  ;

%%
