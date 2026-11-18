#ifndef SCALA_NODES_TYPES_H
#define SCALA_NODES_TYPES_H

#include <string>

enum ModifierType {
    _PUBLIC,
    _PRIVATE,
    _PROTECTED,
    _ABSTRACT,
    _FINAL,
    _SEALED,
    _OVERRIDE
};

enum StmtType {
    _VAL_DECL,
    _VAR_DECL,
    _CLASS,
    _OBJECT,
    _TRAIT,
    _DEF,
    _EXPR
};

enum ClassParamType {
    _UNMARKED_CLASS_PARAM,
    _VAL_CLASS_PARAM,
    _VAR_CLASS_PARAM
};

enum DefinitionType {
    _VARIABLE_DEF,
    _FUNCTION_DEF
};

enum ClassExtensionTemplateType {
    _EXTEND_WITH_CONSTRUCTOR_AND_BODY,
    _EXTEND_WITH_BODY
};

enum ExprType {
    _IF,
    _IF_ELSE,
    _WHILE,
    _DO_WHILE,
    _FOR,
    _TRY,
    _THROW,
    _RETURN,
    _RETURN_EXPR,
    _INFIX,
    _ASSIGNMENT,
    _BLOCK
};

enum SimpleExprType {
    _NEW_OBJECT,
    _NEW_ARRAY,
    _BLOCK_EXPR,
    _SIMPLE_EXPR_1
};

enum SimpleExpr1Type {
    _INT_LITERAL,
    _CHAR_LITERAL,
    _DOUBLE_LITERAL,
    _STRING_LITERAL,
    _BOOL_LITERAL,
    _NULL_LITERAL,
    _UNIT_LITERAL,
    _ID,
    _THIS,
    _SUPER_FIELD_ACCESS,
    _FIELD_ACCESS,
    _METHOD_CALL,
    _PARENTHESIZED_EXPR,
    _ARRAY_BUILDER,
    _ARRAY_WITH_TYPE_BUILDER,
    _ARRAY_METHOD
};

enum PrefixExprType {
    _NO_UNARY_OPERATOR,
    _UNARY_PLUS,
    _UNARY_MINUS,
    _LOGICAL_NOT,
    _BIT_NOT
};

std::string toString(ModifierType type);
std::string toString(StmtType type);
std::string toString(ClassParamType type);
std::string toString(DefinitionType type);
std::string toString(ClassExtensionTemplateType type);
std::string toString(ExprType type);
std::string toString(SimpleExprType type);
std::string toString(SimpleExpr1Type type);
std::string toString(PrefixExprType type);

#endif
