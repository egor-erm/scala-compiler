/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser\\parser.y"

    #include "nodes/nodes.h"

#line 53 "parser\\parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WHILE = 258,                   /* WHILE  */
    DO = 259,                      /* DO  */
    FOR = 260,                     /* FOR  */
    VAL = 261,                     /* VAL  */
    VAR = 262,                     /* VAR  */
    ID = 263,                      /* ID  */
    NEW = 264,                     /* NEW  */
    TARRAY = 265,                  /* TARRAY  */
    R_ARROW = 266,                 /* R_ARROW  */
    LITINT = 267,                  /* LITINT  */
    LITCHAR = 268,                 /* LITCHAR  */
    LITSTR = 269,                  /* LITSTR  */
    LITDOUBLE = 270,               /* LITDOUBLE  */
    LITBOOL = 271,                 /* LITBOOL  */
    KNULL = 272,                   /* KNULL  */
    PLUS_ASSIGN = 273,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 274,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 275,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 276,            /* SLASH_ASSIGN  */
    PERCENT_ASSIGN = 277,          /* PERCENT_ASSIGN  */
    AND_ASSIGN = 278,              /* AND_ASSIGN  */
    OR_ASSIGN = 279,               /* OR_ASSIGN  */
    IF = 280,                      /* IF  */
    ELSE = 281,                    /* ELSE  */
    L_ARROW = 282,                 /* L_ARROW  */
    CASE = 283,                    /* CASE  */
    TRY = 284,                     /* TRY  */
    CATCH = 285,                   /* CATCH  */
    FINALLY = 286,                 /* FINALLY  */
    THROW = 287,                   /* THROW  */
    RETURN = 288,                  /* RETURN  */
    DEF = 289,                     /* DEF  */
    ABSTRACT = 290,                /* ABSTRACT  */
    SEALED = 291,                  /* SEALED  */
    FINAL = 292,                   /* FINAL  */
    OVERRIDE = 293,                /* OVERRIDE  */
    EXTENDS = 294,                 /* EXTENDS  */
    CLASS = 295,                   /* CLASS  */
    SUPER = 296,                   /* SUPER  */
    PRIVATE = 297,                 /* PRIVATE  */
    PROTECTED = 298,               /* PROTECTED  */
    THIS = 299,                    /* THIS  */
    IMPORT = 300,                  /* IMPORT  */
    TYPE = 301,                    /* TYPE  */
    OBJECT = 302,                  /* OBJECT  */
    NL = 303,                      /* NL  */
    UNSUPPORTED = 304,             /* "unsupported token"  */
    RETURN_EMPTY = 305,            /* RETURN_EMPTY  */
    IF_EXPR = 306,                 /* IF_EXPR  */
    OR = 307,                      /* OR  */
    AND = 308,                     /* AND  */
    EQ = 309,                      /* EQ  */
    NEQ = 310,                     /* NEQ  */
    LESS_EQ = 311,                 /* LESS_EQ  */
    GREATER_EQ = 312,              /* GREATER_EQ  */
    SHL = 313,                     /* SHL  */
    SHR = 314                      /* SHR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 115 "parser\\parser.y"

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

#line 171 "parser\\parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (TopStmtSeqNode** out_root);


#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */
