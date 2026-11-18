/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser\\parser.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "nodes/nodes.h"

int yylex();
void yyerror(TopStatSeqNode** out_root, const char* message);

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

static SimpleExpr1Node* makeIntLiteral(char* text) {
    const int value = text == nullptr ? 0 : std::atoi(text);
    std::free(text);
    return SimpleExpr1Node::createIntNode(value);
}

static SimpleExpr1Node* makeCharLiteral(char* text) {
    const char value = text == nullptr || text[0] == '\0' ? '\0' : text[0];
    std::free(text);
    return SimpleExpr1Node::createCharNode(value);
}

static SimpleExpr1Node* makeDoubleLiteral(char* text) {
    const double value = text == nullptr ? 0.0 : std::atof(text);
    std::free(text);
    return SimpleExpr1Node::createDoubleNode(value);
}

static SimpleExpr1Node* makeStringLiteral(char* text) {
    const std::string value = text == nullptr ? "" : text;
    std::free(text);
    return SimpleExpr1Node::createStringNode(value);
}

static SimpleExpr1Node* makeBoolLiteral(char* text) {
    const bool value = text != nullptr && std::strcmp(text, "true") == 0;
    std::free(text);
    return SimpleExpr1Node::createBoolNode(value);
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

#line 176 "parser\\parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_WHILE = 3,                      /* WHILE  */
  YYSYMBOL_DO = 4,                         /* DO  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_VAL = 6,                        /* VAL  */
  YYSYMBOL_VAR = 7,                        /* VAR  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_NEW = 9,                        /* NEW  */
  YYSYMBOL_TARRAY = 10,                    /* TARRAY  */
  YYSYMBOL_R_ARROW = 11,                   /* R_ARROW  */
  YYSYMBOL_LITINT = 12,                    /* LITINT  */
  YYSYMBOL_LITCHAR = 13,                   /* LITCHAR  */
  YYSYMBOL_LITSTR = 14,                    /* LITSTR  */
  YYSYMBOL_LITDOUBLE = 15,                 /* LITDOUBLE  */
  YYSYMBOL_LITBOOL = 16,                   /* LITBOOL  */
  YYSYMBOL_KNULL = 17,                     /* KNULL  */
  YYSYMBOL_PLUS_ASSIGN = 18,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 19,              /* MINUS_ASSIGN  */
  YYSYMBOL_STAR_ASSIGN = 20,               /* STAR_ASSIGN  */
  YYSYMBOL_SLASH_ASSIGN = 21,              /* SLASH_ASSIGN  */
  YYSYMBOL_PERCENT_ASSIGN = 22,            /* PERCENT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 23,                /* AND_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 24,                 /* OR_ASSIGN  */
  YYSYMBOL_IF = 25,                        /* IF  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_L_ARROW = 27,                   /* L_ARROW  */
  YYSYMBOL_CASE = 28,                      /* CASE  */
  YYSYMBOL_TRY = 29,                       /* TRY  */
  YYSYMBOL_CATCH = 30,                     /* CATCH  */
  YYSYMBOL_FINALLY = 31,                   /* FINALLY  */
  YYSYMBOL_THROW = 32,                     /* THROW  */
  YYSYMBOL_RETURN = 33,                    /* RETURN  */
  YYSYMBOL_DEF = 34,                       /* DEF  */
  YYSYMBOL_ABSTRACT = 35,                  /* ABSTRACT  */
  YYSYMBOL_SEALED = 36,                    /* SEALED  */
  YYSYMBOL_FINAL = 37,                     /* FINAL  */
  YYSYMBOL_OVERRIDE = 38,                  /* OVERRIDE  */
  YYSYMBOL_EXTENDS = 39,                   /* EXTENDS  */
  YYSYMBOL_CLASS = 40,                     /* CLASS  */
  YYSYMBOL_SUPER = 41,                     /* SUPER  */
  YYSYMBOL_PRIVATE = 42,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 43,                 /* PROTECTED  */
  YYSYMBOL_THIS = 44,                      /* THIS  */
  YYSYMBOL_IMPORT = 45,                    /* IMPORT  */
  YYSYMBOL_TYPE = 46,                      /* TYPE  */
  YYSYMBOL_OBJECT = 47,                    /* OBJECT  */
  YYSYMBOL_NL = 48,                        /* NL  */
  YYSYMBOL_UNSUPPORTED = 49,               /* "unsupported token"  */
  YYSYMBOL_RETURN_EMPTY = 50,              /* RETURN_EMPTY  */
  YYSYMBOL_IF_EXPR = 51,                   /* IF_EXPR  */
  YYSYMBOL_OR = 52,                        /* OR  */
  YYSYMBOL_AND = 53,                       /* AND  */
  YYSYMBOL_54_ = 54,                       /* '|'  */
  YYSYMBOL_55_ = 55,                       /* '^'  */
  YYSYMBOL_56_ = 56,                       /* '&'  */
  YYSYMBOL_EQ = 57,                        /* EQ  */
  YYSYMBOL_NEQ = 58,                       /* NEQ  */
  YYSYMBOL_59_ = 59,                       /* '<'  */
  YYSYMBOL_60_ = 60,                       /* '>'  */
  YYSYMBOL_LESS_EQ = 61,                   /* LESS_EQ  */
  YYSYMBOL_GREATER_EQ = 62,                /* GREATER_EQ  */
  YYSYMBOL_SHL = 63,                       /* SHL  */
  YYSYMBOL_SHR = 64,                       /* SHR  */
  YYSYMBOL_65_ = 65,                       /* '+'  */
  YYSYMBOL_66_ = 66,                       /* '-'  */
  YYSYMBOL_67_ = 67,                       /* '*'  */
  YYSYMBOL_68_ = 68,                       /* '/'  */
  YYSYMBOL_69_ = 69,                       /* '%'  */
  YYSYMBOL_70_ = 70,                       /* '.'  */
  YYSYMBOL_71_ = 71,                       /* ';'  */
  YYSYMBOL_72_ = 72,                       /* '('  */
  YYSYMBOL_73_ = 73,                       /* ')'  */
  YYSYMBOL_74_ = 74,                       /* '{'  */
  YYSYMBOL_75_ = 75,                       /* '}'  */
  YYSYMBOL_76_ = 76,                       /* ','  */
  YYSYMBOL_77_ = 77,                       /* ':'  */
  YYSYMBOL_78_ = 78,                       /* '='  */
  YYSYMBOL_79_ = 79,                       /* '['  */
  YYSYMBOL_80_ = 80,                       /* ']'  */
  YYSYMBOL_81_ = 81,                       /* '!'  */
  YYSYMBOL_82_ = 82,                       /* '~'  */
  YYSYMBOL_YYACCEPT = 83,                  /* $accept  */
  YYSYMBOL_program = 84,                   /* program  */
  YYSYMBOL_top_list = 85,                  /* top_list  */
  YYSYMBOL_top_stat = 86,                  /* top_stat  */
  YYSYMBOL_import = 87,                    /* import  */
  YYSYMBOL_path = 88,                      /* path  */
  YYSYMBOL_semi = 89,                      /* semi  */
  YYSYMBOL_semis = 90,                     /* semis  */
  YYSYMBOL_semis_e = 91,                   /* semis_e  */
  YYSYMBOL_nls = 92,                       /* nls  */
  YYSYMBOL_nl_e = 93,                      /* nl_e  */
  YYSYMBOL_stmt = 94,                      /* stmt  */
  YYSYMBOL_def = 95,                       /* def  */
  YYSYMBOL_def_prefix = 96,                /* def_prefix  */
  YYSYMBOL_def_prefix_list = 97,           /* def_prefix_list  */
  YYSYMBOL_class_def = 98,                 /* class_def  */
  YYSYMBOL_class_fields = 99,              /* class_fields  */
  YYSYMBOL_class_tail = 100,               /* class_tail  */
  YYSYMBOL_args_e = 101,                   /* args_e  */
  YYSYMBOL_args = 102,                     /* args  */
  YYSYMBOL_class_body = 103,               /* class_body  */
  YYSYMBOL_stmt_list_e = 104,              /* stmt_list_e  */
  YYSYMBOL_stmt_list = 105,                /* stmt_list  */
  YYSYMBOL_id_list = 106,                  /* id_list  */
  YYSYMBOL_field_list = 107,               /* field_list  */
  YYSYMBOL_field = 108,                    /* field  */
  YYSYMBOL_val_or_var = 109,               /* val_or_var  */
  YYSYMBOL_func_def = 110,                 /* func_def  */
  YYSYMBOL_var_def = 111,                  /* var_def  */
  YYSYMBOL_params_e = 112,                 /* params_e  */
  YYSYMBOL_param_list_e = 113,             /* param_list_e  */
  YYSYMBOL_param_list = 114,               /* param_list  */
  YYSYMBOL_param = 115,                    /* param  */
  YYSYMBOL_type = 116,                     /* type  */
  YYSYMBOL_type_e = 117,                   /* type_e  */
  YYSYMBOL_block_stats = 118,              /* block_stats  */
  YYSYMBOL_block_list = 119,               /* block_list  */
  YYSYMBOL_block_stat = 120,               /* block_stat  */
  YYSYMBOL_local_def = 121,                /* local_def  */
  YYSYMBOL_expr = 122,                     /* expr  */
  YYSYMBOL_if_expr = 123,                  /* if_expr  */
  YYSYMBOL_while_expr = 124,               /* while_expr  */
  YYSYMBOL_do_while_expr = 125,            /* do_while_expr  */
  YYSYMBOL_for_expr = 126,                 /* for_expr  */
  YYSYMBOL_generator_list = 127,           /* generator_list  */
  YYSYMBOL_generator = 128,                /* generator  */
  YYSYMBOL_catch_e = 129,                  /* catch_e  */
  YYSYMBOL_case_list = 130,                /* case_list  */
  YYSYMBOL_case = 131,                     /* case  */
  YYSYMBOL_finally_e = 132,                /* finally_e  */
  YYSYMBOL_infix = 133,                    /* infix  */
  YYSYMBOL_prefix = 134,                   /* prefix  */
  YYSYMBOL_expr_list = 135,                /* expr_list  */
  YYSYMBOL_simple = 136,                   /* simple  */
  YYSYMBOL_literal = 137                   /* literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   868

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  347

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,     2,     2,     2,    69,    56,     2,
      72,    73,    67,    65,    76,    66,    70,    68,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    71,
      59,    78,    60,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    79,     2,    80,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    54,    75,    82,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    57,
      58,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   242,   242,   244,   249,   251,   256,   258,   263,   268,
     270,   275,   276,   280,   281,   284,   286,   289,   291,   294,
     296,   300,   302,   307,   309,   314,   316,   318,   320,   322,
     324,   330,   331,   336,   338,   340,   345,   347,   352,   354,
     362,   363,   368,   370,   375,   380,   382,   387,   389,   394,
     396,   401,   403,   408,   411,   416,   418,   423,   426,   429,
     435,   437,   443,   444,   450,   451,   456,   458,   463,   468,
     470,   473,   479,   480,   485,   487,   492,   494,   499,   501,
     506,   511,   513,   515,   517,   519,   521,   523,   525,   527,
     530,   533,   536,   539,   542,   545,   548,   551,   556,   558,
     563,   568,   573,   575,   580,   582,   584,   586,   591,   597,
     598,   603,   605,   610,   616,   617,   622,   624,   626,   628,
     630,   632,   634,   636,   638,   640,   642,   644,   646,   648,
     650,   652,   654,   656,   658,   660,   665,   667,   669,   671,
     673,   678,   680,   685,   687,   690,   693,   696,   699,   702,
     705,   707,   709,   711,   714,   717,   723,   725,   727,   729,
     731,   733,   735
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "WHILE", "DO", "FOR",
  "VAL", "VAR", "ID", "NEW", "TARRAY", "R_ARROW", "LITINT", "LITCHAR",
  "LITSTR", "LITDOUBLE", "LITBOOL", "KNULL", "PLUS_ASSIGN", "MINUS_ASSIGN",
  "STAR_ASSIGN", "SLASH_ASSIGN", "PERCENT_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "IF", "ELSE", "L_ARROW", "CASE", "TRY", "CATCH", "FINALLY",
  "THROW", "RETURN", "DEF", "ABSTRACT", "SEALED", "FINAL", "OVERRIDE",
  "EXTENDS", "CLASS", "SUPER", "PRIVATE", "PROTECTED", "THIS", "IMPORT",
  "TYPE", "OBJECT", "NL", "\"unsupported token\"", "RETURN_EMPTY",
  "IF_EXPR", "OR", "AND", "'|'", "'^'", "'&'", "EQ", "NEQ", "'<'", "'>'",
  "LESS_EQ", "GREATER_EQ", "SHL", "SHR", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'.'", "';'", "'('", "')'", "'{'", "'}'", "','", "':'", "'='", "'['",
  "']'", "'!'", "'~'", "$accept", "program", "top_list", "top_stat",
  "import", "path", "semi", "semis", "semis_e", "nls", "nl_e", "stmt",
  "def", "def_prefix", "def_prefix_list", "class_def", "class_fields",
  "class_tail", "args_e", "args", "class_body", "stmt_list_e", "stmt_list",
  "id_list", "field_list", "field", "val_or_var", "func_def", "var_def",
  "params_e", "param_list_e", "param_list", "param", "type", "type_e",
  "block_stats", "block_list", "block_stat", "local_def", "expr",
  "if_expr", "while_expr", "do_while_expr", "for_expr", "generator_list",
  "generator", "catch_e", "case_list", "case", "finally_e", "infix",
  "prefix", "expr_list", "simple", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-223)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-74)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      25,  -223,  -223,    33,  -223,    25,    22,  -223,  -223,    53,
      25,  -223,  -223,   269,  -223,  -223,   -25,     5,  -223,  -223,
    -223,  -223,  -223,    54,  -223,  -223,    87,  -223,    98,  -223,
     -27,   -27,  -223,   101,    55,   -27,  -223,  -223,   -16,  -223,
      56,  -223,    -1,    25,  -223,   484,  -223,  -223,    94,  -223,
     217,    21,  -223,   530,   103,   107,   666,    84,  -223,   149,
      28,  -223,  -223,  -223,  -223,  -223,  -223,   109,   666,   666,
     666,   112,  -223,    27,    27,   574,  -223,    25,    27,    27,
    -223,  -223,  -223,  -223,  -223,   659,  -223,    32,   102,  -223,
    -223,   152,  -223,  -223,   177,  -223,   178,  -223,  -223,    49,
      25,  -223,  -223,  -223,  -223,   666,    25,   180,    25,    56,
     110,   182,   152,  -223,   666,   161,  -223,  -223,   186,   105,
     105,  -223,   122,   440,   124,   105,   105,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,  -223,   666,   155,   155,
     155,   155,   155,   155,   155,   192,   666,  -223,   134,   126,
    -223,   129,  -223,    38,   199,   360,  -223,   136,   207,   184,
       6,  -223,   180,  -223,   152,   143,   135,   153,   154,   201,
    -223,  -223,   199,    25,  -223,  -223,  -223,  -223,  -223,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,  -223,   666,
     666,   666,   666,   666,   666,   666,  -223,  -223,   222,   152,
     152,    18,   -29,  -223,    12,  -223,  -223,   168,   666,   666,
    -223,     9,     3,   162,   152,    56,  -223,   205,   666,  -223,
      37,   285,  -223,   744,   105,   761,   280,   354,   775,   788,
     799,   799,    86,    86,    86,    86,    86,    86,    50,    50,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,   163,  -223,   169,   167,   171,   239,   152,   172,   620,
     666,  -223,  -223,   620,   666,  -223,     9,   176,   185,   183,
    -223,   620,   248,   -10,  -223,  -223,   152,   187,  -223,  -223,
     254,   152,   188,   666,  -223,   190,   666,  -223,   191,  -223,
    -223,  -223,   666,    56,   245,   195,  -223,  -223,  -223,   666,
     196,   202,   220,  -223,   190,   666,  -223,  -223,  -223,   620,
     208,  -223,   666,   152,  -223,   152,  -223,   254,  -223,  -223,
    -223,  -223,   266,  -223,  -223,    25,  -223
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      15,    12,    11,     0,    13,    16,    31,     1,    14,     0,
      15,     4,     6,     0,     7,     9,     8,    31,     3,    25,
      26,    27,    28,     0,    29,    30,     0,    32,     0,     5,
      17,    17,    10,     0,     0,    17,    33,    38,     0,    35,
      40,    18,    31,    15,    34,     0,    17,    41,     0,    36,
       0,     0,    51,    31,     0,     0,     0,     0,   144,     0,
       0,   156,   157,   160,   159,   158,   161,     0,     0,     0,
      87,     0,   145,     0,     0,     0,    42,    15,     0,     0,
     141,    81,    82,    83,    84,    97,   116,     0,   136,   143,
      39,     0,    55,    56,     0,    37,    31,    47,    21,     0,
      15,    23,    24,    22,    44,     0,    15,     0,    15,     0,
       0,     0,     0,   153,     0,   109,    86,    88,     0,   138,
     137,   162,     0,    74,     0,   139,   140,    19,    19,    19,
      19,    19,    19,    19,    19,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    19,    19,    43,     0,    19,    19,
      19,    19,    19,    19,    19,     0,     0,   148,    69,     0,
      53,     0,    52,     0,     0,    31,    46,     0,     0,     0,
       0,   104,     0,   151,     0,     0,     0,     0,     0,   114,
     146,   149,     0,    15,    76,    78,    79,   150,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,     0,
       0,     0,     0,     0,     0,     0,   147,    89,     0,     0,
       0,    62,    19,    49,    72,    48,    17,     0,     0,     0,
      17,     0,    15,     0,     0,     0,    17,     0,     0,    85,
      72,    16,    75,   117,   136,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,    90,    91,    92,    93,    94,    95,    96,
      70,     0,    54,     0,    72,     0,     0,     0,     0,     0,
       0,   108,   107,     0,     0,   105,    16,     0,     0,     0,
     154,     0,     0,     0,   111,   115,     0,     0,    77,    71,
      64,     0,     0,     0,    50,    61,     0,   100,     0,   102,
     106,    17,     0,     0,    98,     0,   110,   112,    73,     0,
       0,     0,    65,    66,    58,     0,    59,    60,   101,     0,
       0,   155,     0,     0,    80,     0,    63,     0,    57,   103,
     152,    99,     0,    68,    67,    15,   113
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,  -223,   286,  -223,  -223,    -4,    -7,     4,   -28,
     622,   148,  -223,  -223,   -15,  -223,  -223,    17,  -223,   -34,
     262,  -223,  -223,   133,  -223,   223,   -40,  -223,  -223,    99,
    -223,  -223,   -17,  -104,  -211,   -23,  -223,    82,  -223,   -45,
    -223,  -223,  -223,  -223,   156,  -222,  -223,  -223,    31,  -223,
     588,  -223,  -223,   -58,  -223
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,    10,    11,    12,    16,     4,     5,   123,    38,
     273,    97,    98,    27,    13,    14,    35,    36,    46,   157,
      37,    54,   100,   224,    51,    52,   182,   101,   102,   274,
     321,   322,   323,   160,   278,   124,   183,   184,   185,   103,
      81,    82,    83,    84,   170,   171,   179,   293,   294,   239,
      85,    86,    87,    88,    89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,     8,    34,    17,     6,   -16,    47,    48,   176,   285,
      94,   106,    33,     8,    18,   119,   120,   169,   292,   188,
     125,   126,    -2,   115,   116,   117,   113,    50,   229,   297,
     122,   229,    41,     7,   284,    58,    59,    60,    99,    61,
      62,    63,    64,    65,    66,    28,   221,    53,    39,   -62,
       9,     1,    44,     1,     1,    92,    93,     1,    43,   164,
     167,    15,    30,   302,   285,   316,   188,     9,    71,   177,
     233,    72,    49,     1,     2,   173,     2,     2,   186,   230,
       2,    50,   222,   163,    19,    20,    21,    22,   276,   277,
     -19,    24,    25,   165,    95,    31,     2,    96,   111,    75,
      45,    77,   208,    41,   166,   146,    32,   112,   147,    40,
     168,   217,   172,   276,   296,   271,   272,   143,   144,   145,
     148,   149,   150,   151,   152,   153,   154,    42,    45,    43,
     289,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
      99,   141,   142,   143,   144,   145,   107,   109,   108,   110,
     158,     8,   159,   231,   263,   264,   265,   266,   267,   268,
     269,    91,   155,   305,    45,   155,   241,    45,   104,   105,
     156,   114,   118,   281,   282,   161,    48,   242,   169,   174,
     175,   178,   318,   295,   180,   181,   186,   324,   279,   187,
     216,   290,   283,   188,   218,   219,   220,   223,   291,   226,
     227,   228,    58,    59,    60,   235,    61,    62,    63,    64,
      65,    66,   234,    92,    93,   286,   236,     8,   237,   342,
     270,   343,   238,   292,   307,   308,   287,     8,   309,   310,
     280,   300,   288,   299,   301,    71,   314,   304,    72,   303,
     306,   311,    19,    20,    21,    22,   315,   312,   326,    24,
      25,   327,   320,   313,   328,   319,   325,   330,   -73,    73,
      74,   332,   333,   335,   334,   336,    75,   345,    77,   331,
     338,   340,     8,   329,   339,    78,    79,   341,    55,    56,
      57,    92,    93,    58,    59,    60,   337,    61,    62,    63,
      64,    65,    66,    29,    19,    20,    21,    22,    90,    23,
      67,    24,    25,   225,    68,   240,    26,    69,    70,   162,
     344,   275,   346,   298,   317,     0,    71,     0,   232,    72,
       0,     0,     0,     1,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
      73,    74,     0,     0,     0,     0,     2,    75,     0,    77,
       0,     0,     0,    55,    56,    57,    78,    79,    58,    59,
      60,     0,    61,    62,    63,    64,    65,    66,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,    68,
       0,     0,    69,    70,     0,     0,     0,     0,     0,     0,
       0,    71,     0,     0,    72,     0,     0,     0,     1,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,     0,    73,    74,     0,     0,     0,
       0,     2,    75,     0,    77,   -16,     0,     0,     0,     0,
       0,    78,    79,    55,    56,    57,    92,    93,    58,    59,
      60,     0,    61,    62,    63,    64,    65,    66,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,    68,
       0,     0,    69,    70,     0,     0,     0,     0,     0,     0,
       0,    71,     0,     0,    72,     0,     0,    55,    56,    57,
       0,     0,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,     0,     0,     0,    73,    74,     0,     0,    67,
       0,     0,    75,    68,    77,     0,    69,    70,     0,     0,
       0,    78,    79,     0,     0,    71,     0,     0,    72,     0,
       0,     0,     0,    55,    56,    57,     0,     0,    58,    59,
      60,     0,    61,    62,    63,    64,    65,    66,     0,    73,
      74,     0,     0,     0,     0,    67,    75,    76,    77,    68,
       0,     0,    69,    70,     0,    78,    79,     0,     0,     0,
       0,    71,     0,     0,    72,     0,     0,    55,    56,    57,
       0,     0,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,     0,     0,     0,    73,    74,     0,     0,    67,
       0,     0,    75,    68,    77,   -45,    69,    70,     0,     0,
       0,    78,    79,     0,     0,    71,     0,     0,    72,     0,
       0,     0,     0,    55,    56,    57,     0,     0,    58,    59,
      60,     0,    61,    62,    63,    64,    65,    66,     0,    73,
      74,     0,     0,     0,     0,    67,    75,   121,    77,    68,
       0,     0,    69,    70,     0,    78,    79,     0,     0,     0,
       0,    71,     0,     0,    72,     0,     0,   127,    41,    55,
      56,    57,     0,     0,    58,    59,    60,     0,    61,    62,
      63,    64,    65,    66,     0,    73,    74,     0,     0,     0,
       0,    67,    75,     0,    77,    68,     0,     0,    69,    70,
       0,    78,    79,     0,     0,     0,     0,    71,     0,     0,
      72,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,     0,
       0,    73,    74,     0,     0,     0,     0,     0,    75,     0,
      77,     0,     0,     0,     0,     0,     0,    78,    79,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     0,
     209,   210,   211,   212,   213,   214,   215,   243,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145
};

static const yytype_int16 yycheck[] =
{
      45,     5,    30,    10,     0,     0,    40,     8,   112,   231,
      50,    56,    39,    17,    10,    73,    74,     8,    28,    48,
      78,    79,     0,    68,    69,    70,    60,    42,    25,   240,
      75,    25,    48,     0,    25,     8,     9,    10,    53,    12,
      13,    14,    15,    16,    17,    70,     8,    43,    31,    78,
      45,    48,    35,    48,    48,     6,     7,    48,    74,    99,
     105,     8,     8,   274,   286,    75,    48,    45,    41,   114,
     174,    44,    73,    48,    71,   109,    71,    71,   123,    73,
      71,    96,    44,    34,    35,    36,    37,    38,    76,    77,
      72,    42,    43,   100,    73,     8,    71,    76,    70,    72,
      72,    74,   147,    48,   100,    73,     8,    79,    76,     8,
     106,   156,   108,    76,    77,   219,   220,    67,    68,    69,
      18,    19,    20,    21,    22,    23,    24,    72,    72,    74,
     234,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     165,    65,    66,    67,    68,    69,    72,     8,    74,    10,
       8,   165,    10,   170,   209,   210,   211,   212,   213,   214,
     215,    77,    70,   277,    72,    70,   183,    72,    75,    72,
      78,    72,    70,   228,   229,     8,     8,   183,     8,    79,
       8,    30,   296,   238,     8,    73,   241,   301,   226,    75,
       8,   235,   230,    48,    70,    79,    77,     8,   236,    73,
       3,    27,     8,     9,    10,    80,    12,    13,    14,    15,
      16,    17,    79,     6,     7,   232,    73,   231,    74,   333,
       8,   335,    31,    28,   279,   280,   232,   241,   283,   284,
      72,    72,    80,    80,    77,    41,   291,     8,    44,    78,
      78,    75,    35,    36,    37,    38,     8,    72,   303,    42,
      43,   306,     8,    80,    73,    78,    78,   312,    78,    65,
      66,    26,    77,    77,   319,    73,    72,    11,    74,   313,
     325,    73,   286,   311,   329,    81,    82,   332,     3,     4,
       5,     6,     7,     8,     9,    10,    76,    12,    13,    14,
      15,    16,    17,    17,    35,    36,    37,    38,    46,    40,
      25,    42,    43,   165,    29,   182,    47,    32,    33,    96,
     337,   222,   345,   241,   293,    -1,    41,    -1,   172,    44,
      -1,    -1,    -1,    48,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      65,    66,    -1,    -1,    -1,    -1,    71,    72,    -1,    74,
      -1,    -1,    -1,     3,     4,     5,    81,    82,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    44,    -1,    -1,    -1,    48,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    65,    66,    -1,    -1,    -1,
      -1,    71,    72,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    81,    82,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    44,    -1,    -1,     3,     4,     5,
      -1,    -1,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    65,    66,    -1,    -1,    25,
      -1,    -1,    72,    29,    74,    -1,    32,    33,    -1,    -1,
      -1,    81,    82,    -1,    -1,    41,    -1,    -1,    44,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,    -1,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    -1,    65,
      66,    -1,    -1,    -1,    -1,    25,    72,    73,    74,    29,
      -1,    -1,    32,    33,    -1,    81,    82,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    44,    -1,    -1,     3,     4,     5,
      -1,    -1,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    65,    66,    -1,    -1,    25,
      -1,    -1,    72,    29,    74,    75,    32,    33,    -1,    -1,
      -1,    81,    82,    -1,    -1,    41,    -1,    -1,    44,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,    -1,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    -1,    65,
      66,    -1,    -1,    -1,    -1,    25,    72,    73,    74,    29,
      -1,    -1,    32,    33,    -1,    81,    82,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    44,    -1,    -1,     8,    48,     3,
       4,     5,    -1,    -1,     8,     9,    10,    -1,    12,    13,
      14,    15,    16,    17,    -1,    65,    66,    -1,    -1,    -1,
      -1,    25,    72,    -1,    74,    29,    -1,    -1,    32,    33,
      -1,    81,    82,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      44,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    65,    66,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,    -1,    -1,
     148,   149,   150,   151,   152,   153,   154,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    71,    84,    89,    90,    91,     0,    89,    45,
      85,    86,    87,    97,    98,     8,    88,    90,    91,    35,
      36,    37,    38,    40,    42,    43,    47,    96,    70,    86,
       8,     8,     8,    39,    92,    99,   100,   103,    92,   100,
       8,    48,    72,    74,   100,    72,   101,   102,     8,    73,
      97,   107,   108,    91,   104,     3,     4,     5,     8,     9,
      10,    12,    13,    14,    15,    16,    17,    25,    29,    32,
      33,    41,    44,    65,    66,    72,    73,    74,    81,    82,
     122,   123,   124,   125,   126,   133,   134,   135,   136,   137,
     103,    77,     6,     7,   109,    73,    76,    94,    95,    97,
     105,   110,   111,   122,    75,    72,   122,    72,    74,     8,
      10,    70,    79,   102,    72,   122,   122,   122,    70,   136,
     136,    73,   122,    91,   118,   136,   136,     8,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    73,    76,    18,    19,
      20,    21,    22,    23,    24,    70,    78,   102,     8,    10,
     116,     8,   108,    34,   109,    90,    91,   122,    91,     8,
     127,   128,    91,   102,    79,     8,   116,   122,    30,   129,
       8,    73,   109,   119,   120,   121,   122,    75,    48,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,   122,    93,
      93,    93,    93,    93,    93,    93,     8,   122,    70,    79,
      77,     8,    44,     8,   106,    94,    73,     3,    27,    25,
      73,    90,   127,   116,    79,    80,    73,    74,    31,   132,
     106,    90,    91,   133,   136,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   122,   122,   122,   122,   122,   122,   122,
       8,   116,   116,    93,   112,   112,    76,    77,   117,    92,
      72,   122,   122,    92,    25,   128,    90,    91,    80,   116,
     102,    92,    28,   130,   131,   122,    77,   117,   120,    80,
      72,    77,   117,    78,     8,   116,    78,   122,   122,   122,
     122,    75,    72,    80,   122,     8,    75,   131,   116,    78,
       8,   113,   114,   115,   116,    78,   122,   122,    73,    92,
     122,   102,    26,    77,   122,    77,    73,    76,   122,   122,
      73,   122,   116,   116,   115,    11,   118
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    94,    95,    95,    96,    96,    96,    96,    96,
      96,    97,    97,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   104,   104,   105,   105,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   114,   115,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     124,   125,   126,   126,   127,   127,   127,   127,   128,   129,
     129,   130,   130,   131,   132,   132,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   134,   134,   134,   134,
     134,   135,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     3,     1,     1,     2,     1,
       3,     1,     1,     1,     2,     0,     1,     0,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     4,     5,     4,     3,     4,     1,     4,
       0,     1,     2,     3,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     5,     1,     1,     7,     6,     6,
       6,     5,     0,     4,     0,     1,     1,     3,     3,     1,
       3,     4,     0,     2,     1,     3,     1,     3,     1,     1,
       5,     1,     1,     1,     1,     4,     2,     1,     2,     3,
       4,     4,     4,     4,     4,     4,     4,     1,     6,     8,
       6,     7,     6,     8,     1,     3,     4,     3,     3,     0,
       4,     1,     2,     6,     0,     2,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     1,     2,     2,     2,
       2,     1,     3,     1,     1,     1,     3,     3,     2,     3,
       3,     3,     8,     2,     5,     7,     1,     1,     1,     1,
       1,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (out_root, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, out_root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, TopStatSeqNode** out_root)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (out_root);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1264 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITINT: /* LITINT  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1270 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITCHAR: /* LITCHAR  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1276 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITSTR: /* LITSTR  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1282 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITDOUBLE: /* LITDOUBLE  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1288 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITBOOL: /* LITBOOL  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1294 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_UNSUPPORTED: /* "unsupported token"  */
#line 194 "parser\\parser.y"
         { print_semantic_string(yyo, ((*yyvaluep).text)); }
#line 1300 "parser\\parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, TopStatSeqNode** out_root)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, out_root);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, TopStatSeqNode** out_root)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], out_root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, out_root); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, TopStatSeqNode** out_root)
{
  YY_USE (yyvaluep);
  YY_USE (out_root);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1698 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITINT: /* LITINT  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1704 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITCHAR: /* LITCHAR  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1710 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITSTR: /* LITSTR  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1716 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITDOUBLE: /* LITDOUBLE  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1722 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_LITBOOL: /* LITBOOL  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1728 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_UNSUPPORTED: /* "unsupported token"  */
#line 195 "parser\\parser.y"
            { std::free(((*yyvaluep).text)); }
#line 1734 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_program: /* program  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).topStatSeq)); }
#line 1740 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_top_list: /* top_list  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).topStatSeq)); }
#line 1746 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_top_stat: /* top_stat  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).topStat)); }
#line 1752 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_import: /* import  */
#line 204 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).importNode)); }
#line 1758 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_path: /* path  */
#line 204 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).path)); }
#line 1764 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).templateStat)); }
#line 1770 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_def: /* def  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).def)); }
#line 1776 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_def_prefix: /* def_prefix  */
#line 196 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).modifier)); }
#line 1782 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_def_prefix_list: /* def_prefix_list  */
#line 196 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).modifiers)); }
#line 1788 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_class_def: /* class_def  */
#line 199 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).classDef)); }
#line 1794 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_class_fields: /* class_fields  */
#line 198 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).classParams)); }
#line 1800 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_class_tail: /* class_tail  */
#line 199 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).classTemplateOpt)); }
#line 1806 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_args_e: /* args_e  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).argumentExprs)); }
#line 1812 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_args: /* args  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).argumentExprs)); }
#line 1818 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_class_body: /* class_body  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).templateStats)); }
#line 1824 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_stmt_list_e: /* stmt_list_e  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).templateStats)); }
#line 1830 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 200 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).templateStats)); }
#line 1836 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_id_list: /* id_list  */
#line 196 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).idList)); }
#line 1842 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_field_list: /* field_list  */
#line 198 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).classParams)); }
#line 1848 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_field: /* field  */
#line 198 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).classParam)); }
#line 1854 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_func_def: /* func_def  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).def)); }
#line 1860 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_var_def: /* var_def  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).def)); }
#line 1866 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_params_e: /* params_e  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).funcParams)); }
#line 1872 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_param_list_e: /* param_list_e  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).funcParams)); }
#line 1878 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_param_list: /* param_list  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).funcParams)); }
#line 1884 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_param: /* param  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).funcParam)); }
#line 1890 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_type: /* type  */
#line 196 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).simpleType)); }
#line 1896 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_type_e: /* type_e  */
#line 196 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).simpleType)); }
#line 1902 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_block_stats: /* block_stats  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).blockStats)); }
#line 1908 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_block_list: /* block_list  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).blockStats)); }
#line 1914 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_block_stat: /* block_stat  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).blockStat)); }
#line 1920 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_local_def: /* local_def  */
#line 197 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).varDefs)); }
#line 1926 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).expr)); }
#line 1932 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_if_expr: /* if_expr  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).expr)); }
#line 1938 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_while_expr: /* while_expr  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).expr)); }
#line 1944 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_do_while_expr: /* do_while_expr  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).expr)); }
#line 1950 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_for_expr: /* for_expr  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).expr)); }
#line 1956 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_generator_list: /* generator_list  */
#line 203 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).enumerators)); }
#line 1962 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_generator: /* generator  */
#line 203 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).generator)); }
#line 1968 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_catch_e: /* catch_e  */
#line 203 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).catchNode)); }
#line 1974 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_case_list: /* case_list  */
#line 203 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).catchNode)); }
#line 1980 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_case: /* case  */
#line 204 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).caseNode)); }
#line 1986 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_finally_e: /* finally_e  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).expr)); }
#line 1992 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_infix: /* infix  */
#line 202 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).infixExpr)); }
#line 1998 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_prefix: /* prefix  */
#line 202 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).prefixExpr)); }
#line 2004 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 201 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).exprs)); }
#line 2010 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_simple: /* simple  */
#line 202 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).simpleExpr)); }
#line 2016 "parser\\parser.tab.c"
        break;

    case YYSYMBOL_literal: /* literal  */
#line 203 "parser\\parser.y"
            { deleteNodeTree(((*yyvaluep).simpleExpr1)); }
#line 2022 "parser\\parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (TopStatSeqNode** out_root)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: semis_e  */
#line 243 "parser\\parser.y"
        { (yyval.topStatSeq) = nullptr; *out_root = new TopStatSeqNode(); }
#line 2295 "parser\\parser.tab.c"
    break;

  case 3: /* program: semis_e top_list semis_e  */
#line 245 "parser\\parser.y"
        { (yyval.topStatSeq) = nullptr; *out_root = (yyvsp[-1].topStatSeq); }
#line 2301 "parser\\parser.tab.c"
    break;

  case 4: /* top_list: top_stat  */
#line 250 "parser\\parser.y"
        { (yyval.topStatSeq) = TopStatSeqNode::addTopStatToList(nullptr, (yyvsp[0].topStat)); }
#line 2307 "parser\\parser.tab.c"
    break;

  case 5: /* top_list: top_list semis top_stat  */
#line 252 "parser\\parser.y"
        { (yyval.topStatSeq) = TopStatSeqNode::addTopStatToList((yyvsp[-2].topStatSeq), (yyvsp[0].topStat)); }
#line 2313 "parser\\parser.tab.c"
    break;

  case 6: /* top_stat: import  */
#line 257 "parser\\parser.y"
        { (yyval.topStat) = TopStatNode::createImport((yyvsp[0].importNode)); }
#line 2319 "parser\\parser.tab.c"
    break;

  case 7: /* top_stat: class_def  */
#line 259 "parser\\parser.y"
        { (yyval.topStat) = TopStatNode::createClass(TemplateDefNode::createClassDef((yyvsp[0].classDef))); }
#line 2325 "parser\\parser.tab.c"
    break;

  case 8: /* import: IMPORT path  */
#line 264 "parser\\parser.y"
        { (yyval.importNode) = ImportNode::createImport((yyvsp[0].path)); }
#line 2331 "parser\\parser.tab.c"
    break;

  case 9: /* path: ID  */
#line 269 "parser\\parser.y"
        { (yyval.path) = PathNode::addPart(nullptr, makeId((yyvsp[0].text))); }
#line 2337 "parser\\parser.tab.c"
    break;

  case 10: /* path: path '.' ID  */
#line 271 "parser\\parser.y"
        { (yyval.path) = PathNode::addPart((yyvsp[-2].path), makeId((yyvsp[0].text))); }
#line 2343 "parser\\parser.tab.c"
    break;

  case 21: /* stmt: def  */
#line 301 "parser\\parser.y"
        { (yyval.templateStat) = TemplateStatNode::createDefTemplate((yyvsp[0].def)); }
#line 2349 "parser\\parser.tab.c"
    break;

  case 22: /* stmt: expr  */
#line 303 "parser\\parser.y"
        { (yyval.templateStat) = TemplateStatNode::createExprTemplate((yyvsp[0].expr)); }
#line 2355 "parser\\parser.tab.c"
    break;

  case 23: /* def: func_def  */
#line 308 "parser\\parser.y"
        { (yyval.def) = (yyvsp[0].def); }
#line 2361 "parser\\parser.tab.c"
    break;

  case 24: /* def: var_def  */
#line 310 "parser\\parser.y"
        { (yyval.def) = (yyvsp[0].def); }
#line 2367 "parser\\parser.tab.c"
    break;

  case 25: /* def_prefix: ABSTRACT  */
#line 315 "parser\\parser.y"
        { (yyval.modifier) = ModifierNode::createModifier(_ABSTRACT); }
#line 2373 "parser\\parser.tab.c"
    break;

  case 26: /* def_prefix: SEALED  */
#line 317 "parser\\parser.y"
        { (yyval.modifier) = ModifierNode::createModifier(_SEALED); }
#line 2379 "parser\\parser.tab.c"
    break;

  case 27: /* def_prefix: FINAL  */
#line 319 "parser\\parser.y"
        { (yyval.modifier) = ModifierNode::createModifier(_FINAL); }
#line 2385 "parser\\parser.tab.c"
    break;

  case 28: /* def_prefix: OVERRIDE  */
#line 321 "parser\\parser.y"
        { (yyval.modifier) = ModifierNode::createModifier(_OVERRIDE); }
#line 2391 "parser\\parser.tab.c"
    break;

  case 29: /* def_prefix: PRIVATE  */
#line 323 "parser\\parser.y"
        { (yyval.modifier) = ModifierNode::createModifier(_PRIVATE); }
#line 2397 "parser\\parser.tab.c"
    break;

  case 30: /* def_prefix: PROTECTED  */
#line 325 "parser\\parser.y"
        { (yyval.modifier) = ModifierNode::createModifier(_PROTECTED); }
#line 2403 "parser\\parser.tab.c"
    break;

  case 31: /* def_prefix_list: %empty  */
#line 330 "parser\\parser.y"
        { (yyval.modifiers) = new ModifiersNode(); }
#line 2409 "parser\\parser.tab.c"
    break;

  case 32: /* def_prefix_list: def_prefix_list def_prefix  */
#line 332 "parser\\parser.y"
        { (yyval.modifiers) = ModifiersNode::addModifierToList((yyvsp[-1].modifiers), (yyvsp[0].modifier)); }
#line 2415 "parser\\parser.tab.c"
    break;

  case 33: /* class_def: def_prefix_list CLASS ID class_tail  */
#line 337 "parser\\parser.y"
        { (yyval.classDef) = ClassDefNode::createClassDef(makeId((yyvsp[-1].text)), (yyvsp[-3].modifiers), nullptr, (yyvsp[0].classTemplateOpt)); }
#line 2421 "parser\\parser.tab.c"
    break;

  case 34: /* class_def: def_prefix_list CLASS ID class_fields class_tail  */
#line 339 "parser\\parser.y"
        { (yyval.classDef) = ClassDefNode::createClassDef(makeId((yyvsp[-2].text)), (yyvsp[-4].modifiers), (yyvsp[-1].classParams), (yyvsp[0].classTemplateOpt)); }
#line 2427 "parser\\parser.tab.c"
    break;

  case 35: /* class_def: def_prefix_list OBJECT ID class_tail  */
#line 341 "parser\\parser.y"
        { (yyval.classDef) = ClassDefNode::createObjectDef(makeId((yyvsp[-1].text)), (yyvsp[-3].modifiers), (yyvsp[0].classTemplateOpt)); }
#line 2433 "parser\\parser.tab.c"
    break;

  case 36: /* class_fields: nls '(' ')'  */
#line 346 "parser\\parser.y"
        { (yyval.classParams) = new ClassParamsNode(); }
#line 2439 "parser\\parser.tab.c"
    break;

  case 37: /* class_fields: nls '(' field_list ')'  */
#line 348 "parser\\parser.y"
        { (yyval.classParams) = (yyvsp[-1].classParams); }
#line 2445 "parser\\parser.tab.c"
    break;

  case 38: /* class_tail: class_body  */
#line 353 "parser\\parser.y"
        { (yyval.classTemplateOpt) = ClassTemplateOptNode::createClassWithoutInherit((yyvsp[0].templateStats)); }
#line 2451 "parser\\parser.tab.c"
    break;

  case 39: /* class_tail: EXTENDS ID args_e class_body  */
#line 355 "parser\\parser.y"
        { (yyval.classTemplateOpt) = ClassTemplateOptNode::createClassWithInherit(
              ExtensionClassTemplateNode::createExtendWithConstrAndBody(
                  makeId((yyvsp[-2].text)), (yyvsp[-1].argumentExprs), (yyvsp[0].templateStats))); }
#line 2459 "parser\\parser.tab.c"
    break;

  case 40: /* args_e: %empty  */
#line 362 "parser\\parser.y"
        { (yyval.argumentExprs) = new ArgumentExprsNode(); }
#line 2465 "parser\\parser.tab.c"
    break;

  case 41: /* args_e: args  */
#line 364 "parser\\parser.y"
        { (yyval.argumentExprs) = (yyvsp[0].argumentExprs); }
#line 2471 "parser\\parser.tab.c"
    break;

  case 42: /* args: '(' ')'  */
#line 369 "parser\\parser.y"
        { (yyval.argumentExprs) = new ArgumentExprsNode(); }
#line 2477 "parser\\parser.tab.c"
    break;

  case 43: /* args: '(' expr_list ')'  */
#line 371 "parser\\parser.y"
        { (yyval.argumentExprs) = new ArgumentExprsNode((yyvsp[-1].exprs)); }
#line 2483 "parser\\parser.tab.c"
    break;

  case 44: /* class_body: nls '{' stmt_list_e '}'  */
#line 376 "parser\\parser.y"
        { (yyval.templateStats) = (yyvsp[-1].templateStats); }
#line 2489 "parser\\parser.tab.c"
    break;

  case 45: /* stmt_list_e: semis_e  */
#line 381 "parser\\parser.y"
        { (yyval.templateStats) = new TemplateStatsNode(); }
#line 2495 "parser\\parser.tab.c"
    break;

  case 46: /* stmt_list_e: semis_e stmt_list semis_e  */
#line 383 "parser\\parser.y"
        { (yyval.templateStats) = (yyvsp[-1].templateStats); }
#line 2501 "parser\\parser.tab.c"
    break;

  case 47: /* stmt_list: stmt  */
#line 388 "parser\\parser.y"
        { (yyval.templateStats) = TemplateStatsNode::addTemplateStatToBackToList(nullptr, (yyvsp[0].templateStat)); }
#line 2507 "parser\\parser.tab.c"
    break;

  case 48: /* stmt_list: stmt_list semis stmt  */
#line 390 "parser\\parser.y"
        { (yyval.templateStats) = TemplateStatsNode::addTemplateStatToBackToList((yyvsp[-2].templateStats), (yyvsp[0].templateStat)); }
#line 2513 "parser\\parser.tab.c"
    break;

  case 49: /* id_list: ID  */
#line 395 "parser\\parser.y"
        { (yyval.idList) = IdListNode::addId(nullptr, makeId((yyvsp[0].text))); }
#line 2519 "parser\\parser.tab.c"
    break;

  case 50: /* id_list: id_list ',' ID  */
#line 397 "parser\\parser.y"
        { (yyval.idList) = IdListNode::addId((yyvsp[-2].idList), makeId((yyvsp[0].text))); }
#line 2525 "parser\\parser.tab.c"
    break;

  case 51: /* field_list: field  */
#line 402 "parser\\parser.y"
        { (yyval.classParams) = ClassParamsNode::addClassParamToList(nullptr, (yyvsp[0].classParam)); }
#line 2531 "parser\\parser.tab.c"
    break;

  case 52: /* field_list: field_list ',' field  */
#line 404 "parser\\parser.y"
        { (yyval.classParams) = ClassParamsNode::addClassParamToList((yyvsp[-2].classParams), (yyvsp[0].classParam)); }
#line 2537 "parser\\parser.tab.c"
    break;

  case 53: /* field: ID ':' type  */
#line 409 "parser\\parser.y"
        { (yyval.classParam) = ClassParamNode::createClassParam(_UNMARKED_CLASS_PARAM,
              new ModifiersNode(), makeId((yyvsp[-2].text)), (yyvsp[0].simpleType)); }
#line 2544 "parser\\parser.tab.c"
    break;

  case 54: /* field: def_prefix_list val_or_var ID ':' type  */
#line 412 "parser\\parser.y"
        { (yyval.classParam) = ClassParamNode::createClassParam((yyvsp[-3].classParamType), (yyvsp[-4].modifiers), makeId((yyvsp[-2].text)), (yyvsp[0].simpleType)); }
#line 2550 "parser\\parser.tab.c"
    break;

  case 55: /* val_or_var: VAL  */
#line 417 "parser\\parser.y"
        { (yyval.classParamType) = _VAL_CLASS_PARAM; }
#line 2556 "parser\\parser.tab.c"
    break;

  case 56: /* val_or_var: VAR  */
#line 419 "parser\\parser.y"
        { (yyval.classParamType) = _VAR_CLASS_PARAM; }
#line 2562 "parser\\parser.tab.c"
    break;

  case 57: /* func_def: def_prefix_list DEF ID params_e type_e '=' expr  */
#line 424 "parser\\parser.y"
        { (yyval.def) = DefNode::createFunDef(FunDefNode::createFunSigFunDef(
              FunSigNode::createFunSig(makeId((yyvsp[-4].text)), (yyvsp[-3].funcParams)), (yyvsp[-2].simpleType), (yyvsp[0].expr)), (yyvsp[-6].modifiers)); }
#line 2569 "parser\\parser.tab.c"
    break;

  case 58: /* func_def: def_prefix_list DEF ID params_e ':' type  */
#line 427 "parser\\parser.y"
        { (yyval.def) = DefNode::createFunDef(FunDefNode::createFunSigFunDef(
              FunSigNode::createFunSig(makeId((yyvsp[-3].text)), (yyvsp[-2].funcParams)), (yyvsp[0].simpleType), nullptr), (yyvsp[-5].modifiers)); }
#line 2576 "parser\\parser.tab.c"
    break;

  case 59: /* func_def: def_prefix_list DEF THIS params_e '=' expr  */
#line 430 "parser\\parser.y"
        { (yyval.def) = DefNode::createFunDef(
              FunDefNode::createThisConstrCallFunDef((yyvsp[-2].funcParams), (yyvsp[0].expr)), (yyvsp[-5].modifiers)); }
#line 2583 "parser\\parser.tab.c"
    break;

  case 60: /* var_def: def_prefix_list val_or_var id_list type_e '=' expr  */
#line 436 "parser\\parser.y"
        { (yyval.def) = DefNode::createVarDefs(makeVarDefs((yyvsp[-5].modifiers), (yyvsp[-4].classParamType), (yyvsp[-3].idList), (yyvsp[-2].simpleType), (yyvsp[0].expr)), nullptr); }
#line 2589 "parser\\parser.tab.c"
    break;

  case 61: /* var_def: def_prefix_list val_or_var id_list ':' type  */
#line 438 "parser\\parser.y"
        { (yyval.def) = DefNode::createVarDefs(makeVarDefs((yyvsp[-4].modifiers), (yyvsp[-3].classParamType), (yyvsp[-2].idList), (yyvsp[0].simpleType), nullptr), nullptr); }
#line 2595 "parser\\parser.tab.c"
    break;

  case 62: /* params_e: %empty  */
#line 443 "parser\\parser.y"
        { (yyval.funcParams) = new FuncParamsNode(); }
#line 2601 "parser\\parser.tab.c"
    break;

  case 63: /* params_e: nl_e '(' param_list_e ')'  */
#line 445 "parser\\parser.y"
        { (yyval.funcParams) = (yyvsp[-1].funcParams); }
#line 2607 "parser\\parser.tab.c"
    break;

  case 64: /* param_list_e: %empty  */
#line 450 "parser\\parser.y"
        { (yyval.funcParams) = new FuncParamsNode(); }
#line 2613 "parser\\parser.tab.c"
    break;

  case 65: /* param_list_e: param_list  */
#line 452 "parser\\parser.y"
        { (yyval.funcParams) = (yyvsp[0].funcParams); }
#line 2619 "parser\\parser.tab.c"
    break;

  case 66: /* param_list: param  */
#line 457 "parser\\parser.y"
        { (yyval.funcParams) = FuncParamsNode::addFuncParamToList(nullptr, (yyvsp[0].funcParam)); }
#line 2625 "parser\\parser.tab.c"
    break;

  case 67: /* param_list: param_list ',' param  */
#line 459 "parser\\parser.y"
        { (yyval.funcParams) = FuncParamsNode::addFuncParamToList((yyvsp[-2].funcParams), (yyvsp[0].funcParam)); }
#line 2631 "parser\\parser.tab.c"
    break;

  case 68: /* param: ID ':' type  */
#line 464 "parser\\parser.y"
        { (yyval.funcParam) = FuncParamNode::createFuncParam(makeId((yyvsp[-2].text)), (yyvsp[0].simpleType)); }
#line 2637 "parser\\parser.tab.c"
    break;

  case 69: /* type: ID  */
#line 469 "parser\\parser.y"
        { (yyval.simpleType) = SimpleTypeNode::createIdTypeNode(makeId((yyvsp[0].text))); }
#line 2643 "parser\\parser.tab.c"
    break;

  case 70: /* type: ID '.' ID  */
#line 471 "parser\\parser.y"
        { (yyval.simpleType) = SimpleTypeNode::createIdTypeNode(
              IdNode::createId(std::string((yyvsp[-2].text)) + "." + (yyvsp[0].text))); std::free((yyvsp[-2].text)); std::free((yyvsp[0].text)); }
#line 2650 "parser\\parser.tab.c"
    break;

  case 71: /* type: TARRAY '[' type ']'  */
#line 474 "parser\\parser.y"
        { (yyval.simpleType) = makeArrayType((yyvsp[-1].simpleType)); }
#line 2656 "parser\\parser.tab.c"
    break;

  case 72: /* type_e: %empty  */
#line 479 "parser\\parser.y"
        { (yyval.simpleType) = nullptr; }
#line 2662 "parser\\parser.tab.c"
    break;

  case 73: /* type_e: ':' type  */
#line 481 "parser\\parser.y"
        { (yyval.simpleType) = (yyvsp[0].simpleType); }
#line 2668 "parser\\parser.tab.c"
    break;

  case 74: /* block_stats: semis_e  */
#line 486 "parser\\parser.y"
        { (yyval.blockStats) = new BlockStatsNode(); }
#line 2674 "parser\\parser.tab.c"
    break;

  case 75: /* block_stats: semis_e block_list semis_e  */
#line 488 "parser\\parser.y"
        { (yyval.blockStats) = (yyvsp[-1].blockStats); }
#line 2680 "parser\\parser.tab.c"
    break;

  case 76: /* block_list: block_stat  */
#line 493 "parser\\parser.y"
        { (yyval.blockStats) = BlockStatsNode::addBlockStatToList(nullptr, (yyvsp[0].blockStat)); }
#line 2686 "parser\\parser.tab.c"
    break;

  case 77: /* block_list: block_list semis block_stat  */
#line 495 "parser\\parser.y"
        { (yyval.blockStats) = BlockStatsNode::addBlockStatToList((yyvsp[-2].blockStats), (yyvsp[0].blockStat)); }
#line 2692 "parser\\parser.tab.c"
    break;

  case 78: /* block_stat: local_def  */
#line 500 "parser\\parser.y"
        { (yyval.blockStat) = BlockStatNode::createLocalDef((yyvsp[0].varDefs)); }
#line 2698 "parser\\parser.tab.c"
    break;

  case 79: /* block_stat: expr  */
#line 502 "parser\\parser.y"
        { (yyval.blockStat) = BlockStatNode::createExprNode((yyvsp[0].expr)); }
#line 2704 "parser\\parser.tab.c"
    break;

  case 80: /* local_def: val_or_var id_list type_e '=' expr  */
#line 507 "parser\\parser.y"
        { (yyval.varDefs) = makeVarDefs(new ModifiersNode(), (yyvsp[-4].classParamType), (yyvsp[-3].idList), (yyvsp[-2].simpleType), (yyvsp[0].expr)); }
#line 2710 "parser\\parser.tab.c"
    break;

  case 81: /* expr: if_expr  */
#line 512 "parser\\parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 2716 "parser\\parser.tab.c"
    break;

  case 82: /* expr: while_expr  */
#line 514 "parser\\parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 2722 "parser\\parser.tab.c"
    break;

  case 83: /* expr: do_while_expr  */
#line 516 "parser\\parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 2728 "parser\\parser.tab.c"
    break;

  case 84: /* expr: for_expr  */
#line 518 "parser\\parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 2734 "parser\\parser.tab.c"
    break;

  case 85: /* expr: TRY expr catch_e finally_e  */
#line 520 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createTry(TryExprNode::createExceptionBlock((yyvsp[-2].expr), (yyvsp[-1].catchNode), (yyvsp[0].expr))); }
#line 2740 "parser\\parser.tab.c"
    break;

  case 86: /* expr: THROW expr  */
#line 522 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createThrow((yyvsp[0].expr)); }
#line 2746 "parser\\parser.tab.c"
    break;

  case 87: /* expr: RETURN  */
#line 524 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createReturn(); }
#line 2752 "parser\\parser.tab.c"
    break;

  case 88: /* expr: RETURN expr  */
#line 526 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createReturnExpr((yyvsp[0].expr)); }
#line 2758 "parser\\parser.tab.c"
    break;

  case 89: /* expr: simple '=' expr  */
#line 528 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-2].simpleExpr), (yyvsp[0].expr), "=")); }
#line 2765 "parser\\parser.tab.c"
    break;

  case 90: /* expr: simple PLUS_ASSIGN nl_e expr  */
#line 531 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "+=")); }
#line 2772 "parser\\parser.tab.c"
    break;

  case 91: /* expr: simple MINUS_ASSIGN nl_e expr  */
#line 534 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "-=")); }
#line 2779 "parser\\parser.tab.c"
    break;

  case 92: /* expr: simple STAR_ASSIGN nl_e expr  */
#line 537 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "*=")); }
#line 2786 "parser\\parser.tab.c"
    break;

  case 93: /* expr: simple SLASH_ASSIGN nl_e expr  */
#line 540 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "/=")); }
#line 2793 "parser\\parser.tab.c"
    break;

  case 94: /* expr: simple PERCENT_ASSIGN nl_e expr  */
#line 543 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "%=")); }
#line 2800 "parser\\parser.tab.c"
    break;

  case 95: /* expr: simple AND_ASSIGN nl_e expr  */
#line 546 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "&=")); }
#line 2807 "parser\\parser.tab.c"
    break;

  case 96: /* expr: simple OR_ASSIGN nl_e expr  */
#line 549 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createAssignment(
              AssignmentNode::createAssignment((yyvsp[-3].simpleExpr), (yyvsp[0].expr), "|=")); }
#line 2814 "parser\\parser.tab.c"
    break;

  case 97: /* expr: infix  */
#line 552 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createInfix((yyvsp[0].infixExpr)); }
#line 2820 "parser\\parser.tab.c"
    break;

  case 98: /* if_expr: IF '(' expr ')' nls expr  */
#line 557 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createIf((yyvsp[-3].expr), (yyvsp[0].expr)); }
#line 2826 "parser\\parser.tab.c"
    break;

  case 99: /* if_expr: IF '(' expr ')' nls expr ELSE expr  */
#line 559 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createIfElse((yyvsp[-5].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2832 "parser\\parser.tab.c"
    break;

  case 100: /* while_expr: WHILE '(' expr ')' nls expr  */
#line 564 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createWhile((yyvsp[-3].expr), (yyvsp[0].expr)); }
#line 2838 "parser\\parser.tab.c"
    break;

  case 101: /* do_while_expr: DO expr semis_e WHILE '(' expr ')'  */
#line 569 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createDoWhile((yyvsp[-5].expr), (yyvsp[-1].expr)); }
#line 2844 "parser\\parser.tab.c"
    break;

  case 102: /* for_expr: FOR '(' generator_list ')' nls expr  */
#line 574 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createFor((yyvsp[-3].enumerators), (yyvsp[0].expr)); }
#line 2850 "parser\\parser.tab.c"
    break;

  case 103: /* for_expr: FOR '{' semis_e generator_list semis_e '}' nls expr  */
#line 576 "parser\\parser.y"
        { (yyval.expr) = ExprNode::createFor((yyvsp[-4].enumerators), (yyvsp[0].expr)); }
#line 2856 "parser\\parser.tab.c"
    break;

  case 104: /* generator_list: generator  */
#line 581 "parser\\parser.y"
        { (yyval.enumerators) = EnumeratorsNode::addEnumerator(nullptr, (yyvsp[0].generator)); }
#line 2862 "parser\\parser.tab.c"
    break;

  case 105: /* generator_list: generator_list semis generator  */
#line 583 "parser\\parser.y"
        { (yyval.enumerators) = EnumeratorsNode::addEnumerator((yyvsp[-2].enumerators), (yyvsp[0].generator)); }
#line 2868 "parser\\parser.tab.c"
    break;

  case 106: /* generator_list: generator_list semis IF expr  */
#line 585 "parser\\parser.y"
        { (yyval.enumerators) = EnumeratorsNode::addEnumerator((yyvsp[-3].enumerators), GeneratorNode::createGuard((yyvsp[0].expr))); }
#line 2874 "parser\\parser.tab.c"
    break;

  case 107: /* generator_list: generator_list IF expr  */
#line 587 "parser\\parser.y"
        { (yyval.enumerators) = EnumeratorsNode::addEnumerator((yyvsp[-2].enumerators), GeneratorNode::createGuard((yyvsp[0].expr))); }
#line 2880 "parser\\parser.tab.c"
    break;

  case 108: /* generator: ID L_ARROW expr  */
#line 592 "parser\\parser.y"
        { (yyval.generator) = GeneratorNode::createGenerator(makeId((yyvsp[-2].text)), nullptr, (yyvsp[0].expr)); }
#line 2886 "parser\\parser.tab.c"
    break;

  case 109: /* catch_e: %empty  */
#line 597 "parser\\parser.y"
        { (yyval.catchNode) = nullptr; }
#line 2892 "parser\\parser.tab.c"
    break;

  case 110: /* catch_e: CATCH '{' case_list '}'  */
#line 599 "parser\\parser.y"
        { (yyval.catchNode) = (yyvsp[-1].catchNode); }
#line 2898 "parser\\parser.tab.c"
    break;

  case 111: /* case_list: case  */
#line 604 "parser\\parser.y"
        { (yyval.catchNode) = CatchNode::addCase(nullptr, (yyvsp[0].caseNode)); }
#line 2904 "parser\\parser.tab.c"
    break;

  case 112: /* case_list: case_list case  */
#line 606 "parser\\parser.y"
        { (yyval.catchNode) = CatchNode::addCase((yyvsp[-1].catchNode), (yyvsp[0].caseNode)); }
#line 2910 "parser\\parser.tab.c"
    break;

  case 113: /* case: CASE ID ':' type R_ARROW block_stats  */
#line 611 "parser\\parser.y"
        { (yyval.caseNode) = CaseNode::createCase(makeId((yyvsp[-4].text)), (yyvsp[-2].simpleType), (yyvsp[0].blockStats)); }
#line 2916 "parser\\parser.tab.c"
    break;

  case 114: /* finally_e: %empty  */
#line 616 "parser\\parser.y"
        { (yyval.expr) = nullptr; }
#line 2922 "parser\\parser.tab.c"
    break;

  case 115: /* finally_e: FINALLY expr  */
#line 618 "parser\\parser.y"
        { (yyval.expr) = (yyvsp[0].expr); }
#line 2928 "parser\\parser.tab.c"
    break;

  case 116: /* infix: prefix  */
#line 623 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createInfixFromPrefix((yyvsp[0].prefixExpr)); }
#line 2934 "parser\\parser.tab.c"
    break;

  case 117: /* infix: infix ID nl_e infix  */
#line 625 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), makeId((yyvsp[-2].text)), (yyvsp[0].infixExpr)); }
#line 2940 "parser\\parser.tab.c"
    break;

  case 118: /* infix: infix OR nl_e infix  */
#line 627 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("||"), (yyvsp[0].infixExpr)); }
#line 2946 "parser\\parser.tab.c"
    break;

  case 119: /* infix: infix AND nl_e infix  */
#line 629 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("&&"), (yyvsp[0].infixExpr)); }
#line 2952 "parser\\parser.tab.c"
    break;

  case 120: /* infix: infix '|' nl_e infix  */
#line 631 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("|"), (yyvsp[0].infixExpr)); }
#line 2958 "parser\\parser.tab.c"
    break;

  case 121: /* infix: infix '^' nl_e infix  */
#line 633 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("^"), (yyvsp[0].infixExpr)); }
#line 2964 "parser\\parser.tab.c"
    break;

  case 122: /* infix: infix '&' nl_e infix  */
#line 635 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("&"), (yyvsp[0].infixExpr)); }
#line 2970 "parser\\parser.tab.c"
    break;

  case 123: /* infix: infix EQ nl_e infix  */
#line 637 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("=="), (yyvsp[0].infixExpr)); }
#line 2976 "parser\\parser.tab.c"
    break;

  case 124: /* infix: infix NEQ nl_e infix  */
#line 639 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("!="), (yyvsp[0].infixExpr)); }
#line 2982 "parser\\parser.tab.c"
    break;

  case 125: /* infix: infix '<' nl_e infix  */
#line 641 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("<"), (yyvsp[0].infixExpr)); }
#line 2988 "parser\\parser.tab.c"
    break;

  case 126: /* infix: infix '>' nl_e infix  */
#line 643 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator(">"), (yyvsp[0].infixExpr)); }
#line 2994 "parser\\parser.tab.c"
    break;

  case 127: /* infix: infix LESS_EQ nl_e infix  */
#line 645 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("<="), (yyvsp[0].infixExpr)); }
#line 3000 "parser\\parser.tab.c"
    break;

  case 128: /* infix: infix GREATER_EQ nl_e infix  */
#line 647 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator(">="), (yyvsp[0].infixExpr)); }
#line 3006 "parser\\parser.tab.c"
    break;

  case 129: /* infix: infix SHL nl_e infix  */
#line 649 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("<<"), (yyvsp[0].infixExpr)); }
#line 3012 "parser\\parser.tab.c"
    break;

  case 130: /* infix: infix SHR nl_e infix  */
#line 651 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator(">>"), (yyvsp[0].infixExpr)); }
#line 3018 "parser\\parser.tab.c"
    break;

  case 131: /* infix: infix '+' nl_e infix  */
#line 653 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("+"), (yyvsp[0].infixExpr)); }
#line 3024 "parser\\parser.tab.c"
    break;

  case 132: /* infix: infix '-' nl_e infix  */
#line 655 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("-"), (yyvsp[0].infixExpr)); }
#line 3030 "parser\\parser.tab.c"
    break;

  case 133: /* infix: infix '*' nl_e infix  */
#line 657 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("*"), (yyvsp[0].infixExpr)); }
#line 3036 "parser\\parser.tab.c"
    break;

  case 134: /* infix: infix '/' nl_e infix  */
#line 659 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("/"), (yyvsp[0].infixExpr)); }
#line 3042 "parser\\parser.tab.c"
    break;

  case 135: /* infix: infix '%' nl_e infix  */
#line 661 "parser\\parser.y"
        { (yyval.infixExpr) = InfixExprNode::createFromInfixes((yyvsp[-3].infixExpr), IdNode::createOperator("%"), (yyvsp[0].infixExpr)); }
#line 3048 "parser\\parser.tab.c"
    break;

  case 136: /* prefix: simple  */
#line 666 "parser\\parser.y"
        { (yyval.prefixExpr) = PrefixExprNode::createPrefixExprNode((yyvsp[0].simpleExpr), _NO_UNARY_OPERATOR); }
#line 3054 "parser\\parser.tab.c"
    break;

  case 137: /* prefix: '-' simple  */
#line 668 "parser\\parser.y"
        { (yyval.prefixExpr) = PrefixExprNode::createPrefixExprNode((yyvsp[0].simpleExpr), _UNARY_MINUS); }
#line 3060 "parser\\parser.tab.c"
    break;

  case 138: /* prefix: '+' simple  */
#line 670 "parser\\parser.y"
        { (yyval.prefixExpr) = PrefixExprNode::createPrefixExprNode((yyvsp[0].simpleExpr), _UNARY_PLUS); }
#line 3066 "parser\\parser.tab.c"
    break;

  case 139: /* prefix: '!' simple  */
#line 672 "parser\\parser.y"
        { (yyval.prefixExpr) = PrefixExprNode::createPrefixExprNode((yyvsp[0].simpleExpr), _LOGICAL_NOT); }
#line 3072 "parser\\parser.tab.c"
    break;

  case 140: /* prefix: '~' simple  */
#line 674 "parser\\parser.y"
        { (yyval.prefixExpr) = PrefixExprNode::createPrefixExprNode((yyvsp[0].simpleExpr), _BIT_NOT); }
#line 3078 "parser\\parser.tab.c"
    break;

  case 141: /* expr_list: expr  */
#line 679 "parser\\parser.y"
        { (yyval.exprs) = ExprsNode::addExprToList(nullptr, (yyvsp[0].expr)); }
#line 3084 "parser\\parser.tab.c"
    break;

  case 142: /* expr_list: expr_list ',' expr  */
#line 681 "parser\\parser.y"
        { (yyval.exprs) = ExprsNode::addExprToList((yyvsp[-2].exprs), (yyvsp[0].expr)); }
#line 3090 "parser\\parser.tab.c"
    break;

  case 143: /* simple: literal  */
#line 686 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node((yyvsp[0].simpleExpr1)); }
#line 3096 "parser\\parser.tab.c"
    break;

  case 144: /* simple: ID  */
#line 688 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createIdNode(makeId((yyvsp[0].text)))); }
#line 3103 "parser\\parser.tab.c"
    break;

  case 145: /* simple: THIS  */
#line 691 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createPlainThisNode()); }
#line 3110 "parser\\parser.tab.c"
    break;

  case 146: /* simple: SUPER '.' ID  */
#line 694 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createSuperFieldAccessNode(makeId((yyvsp[0].text)))); }
#line 3117 "parser\\parser.tab.c"
    break;

  case 147: /* simple: simple '.' ID  */
#line 697 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createSimpleExprFieldAccessNode(makeId((yyvsp[0].text)), (yyvsp[-2].simpleExpr))); }
#line 3124 "parser\\parser.tab.c"
    break;

  case 148: /* simple: simple args  */
#line 700 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createMethodCallNode((yyvsp[-1].simpleExpr), (yyvsp[0].argumentExprs))); }
#line 3131 "parser\\parser.tab.c"
    break;

  case 149: /* simple: '(' expr ')'  */
#line 703 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createParenthesizedExprNode((yyvsp[-1].expr))); }
#line 3138 "parser\\parser.tab.c"
    break;

  case 150: /* simple: '{' block_stats '}'  */
#line 706 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createBlockStatsNode((yyvsp[-1].blockStats)); }
#line 3144 "parser\\parser.tab.c"
    break;

  case 151: /* simple: NEW ID args  */
#line 708 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createNewObjectNode(makeId((yyvsp[-1].text)), (yyvsp[0].argumentExprs)); }
#line 3150 "parser\\parser.tab.c"
    break;

  case 152: /* simple: NEW TARRAY '[' type ']' '(' expr ')'  */
#line 710 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createNewArrayNode((yyvsp[-4].simpleType), makeSingleArgument((yyvsp[-1].expr))); }
#line 3156 "parser\\parser.tab.c"
    break;

  case 153: /* simple: TARRAY args  */
#line 712 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createArrayBuilderNode((yyvsp[0].argumentExprs))); }
#line 3163 "parser\\parser.tab.c"
    break;

  case 154: /* simple: TARRAY '[' type ']' args  */
#line 715 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createArrayWithTypeBuilderNode((yyvsp[-2].simpleType), (yyvsp[0].argumentExprs))); }
#line 3170 "parser\\parser.tab.c"
    break;

  case 155: /* simple: TARRAY '.' ID '[' type ']' args  */
#line 718 "parser\\parser.y"
        { (yyval.simpleExpr) = SimpleExprNode::createSimpleExpr1Node(
              SimpleExpr1Node::createArrayMethodNode(makeId((yyvsp[-4].text)), (yyvsp[-2].simpleType), (yyvsp[0].argumentExprs))); }
#line 3177 "parser\\parser.tab.c"
    break;

  case 156: /* literal: LITINT  */
#line 724 "parser\\parser.y"
        { (yyval.simpleExpr1) = makeIntLiteral((yyvsp[0].text)); }
#line 3183 "parser\\parser.tab.c"
    break;

  case 157: /* literal: LITCHAR  */
#line 726 "parser\\parser.y"
        { (yyval.simpleExpr1) = makeCharLiteral((yyvsp[0].text)); }
#line 3189 "parser\\parser.tab.c"
    break;

  case 158: /* literal: LITBOOL  */
#line 728 "parser\\parser.y"
        { (yyval.simpleExpr1) = makeBoolLiteral((yyvsp[0].text)); }
#line 3195 "parser\\parser.tab.c"
    break;

  case 159: /* literal: LITDOUBLE  */
#line 730 "parser\\parser.y"
        { (yyval.simpleExpr1) = makeDoubleLiteral((yyvsp[0].text)); }
#line 3201 "parser\\parser.tab.c"
    break;

  case 160: /* literal: LITSTR  */
#line 732 "parser\\parser.y"
        { (yyval.simpleExpr1) = makeStringLiteral((yyvsp[0].text)); }
#line 3207 "parser\\parser.tab.c"
    break;

  case 161: /* literal: KNULL  */
#line 734 "parser\\parser.y"
        { (yyval.simpleExpr1) = SimpleExpr1Node::createNullNode(); }
#line 3213 "parser\\parser.tab.c"
    break;

  case 162: /* literal: '(' ')'  */
#line 736 "parser\\parser.y"
        { (yyval.simpleExpr1) = SimpleExpr1Node::createUnitLiteralNode(); }
#line 3219 "parser\\parser.tab.c"
    break;


#line 3223 "parser\\parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (out_root, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, out_root);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, out_root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (out_root, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, out_root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, out_root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 739 "parser\\parser.y"

