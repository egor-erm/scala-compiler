#include "Types.h"

std::string toString(ModifierType type) {
    switch (type) {
        case _PUBLIC: return "public";
        case _PRIVATE: return "private";
        case _PROTECTED: return "protected";
        case _ABSTRACT: return "abstract";
        case _FINAL: return "final";
        case _SEALED: return "sealed";
        case _OVERRIDE: return "override";
    }
    return "modifier";
}

std::string toString(StmtType type) {
    switch (type) {
        case _VAL_DECL: return "val";
        case _VAR_DECL: return "var";
        case _CLASS: return "class";
        case _OBJECT: return "object";
        case _TRAIT: return "trait";
        case _DEF: return "def";
        case _EXPR: return "expr";
    }
    return "stmt";
}

std::string toString(ClassParamType type) {
    switch (type) {
        case _UNMARKED_CLASS_PARAM: return "param";
        case _VAL_CLASS_PARAM: return "val param";
        case _VAR_CLASS_PARAM: return "var param";
    }
    return "param";
}

std::string toString(DefinitionType type) {
    switch (type) {
        case _VARIABLE_DEF: return "variable def";
        case _FUNCTION_DEF: return "function def";
    }
    return "definition";
}

std::string toString(ClassExtensionTemplateType type) {
    switch (type) {
        case _EXTEND_WITH_CONSTRUCTOR_AND_BODY: return "extends with constructor and body";
        case _EXTEND_WITH_BODY: return "extends with body";
    }
    return "extends";
}

std::string toString(ExprType type) {
    switch (type) {
        case _IF: return "if";
        case _IF_ELSE: return "if-else";
        case _WHILE: return "while";
        case _DO_WHILE: return "do-while";
        case _FOR: return "for";
        case _TRY: return "try";
        case _THROW: return "throw";
        case _RETURN: return "return";
        case _RETURN_EXPR: return "return expr";
        case _INFIX: return "infix";
        case _ASSIGNMENT: return "assignment";
        case _BLOCK: return "block";
    }
    return "expr";
}

std::string toString(SimpleExprType type) {
    switch (type) {
        case _NEW_OBJECT: return "new object";
        case _NEW_ARRAY: return "new array";
        case _BLOCK_EXPR: return "block expr";
        case _PRIMARY_EXPR: return "primary expr";
    }
    return "simple expr";
}

std::string toString(PrimaryExprType type) {
    switch (type) {
        case _INT_LITERAL: return "int";
        case _CHAR_LITERAL: return "char";
        case _DOUBLE_LITERAL: return "double";
        case _STRING_LITERAL: return "string";
        case _BOOL_LITERAL: return "bool";
        case _NULL_LITERAL: return "null";
        case _UNIT_LITERAL: return "unit";
        case _ID: return "id";
        case _THIS: return "this";
        case _SUPER_FIELD_ACCESS: return "super";
        case _FIELD_ACCESS: return "field access";
        case _METHOD_CALL: return "method call";
        case _PARENTHESIZED_EXPR: return "parenthesized";
        case _ARRAY_BUILDER: return "array builder";
        case _ARRAY_WITH_TYPE_BUILDER: return "array with type";
        case _ARRAY_METHOD: return "array method";
    }
    return "primary expr";
}

std::string toString(PrefixExprType type) {
    switch (type) {
        case _NO_UNARY_OPERATOR: return "no unary";
        case _UNARY_PLUS: return "unary +";
        case _UNARY_MINUS: return "unary -";
        case _LOGICAL_NOT: return "!";
        case _BIT_NOT: return "~";
    }
    return "prefix";
}
