#include "ExprNodes.h"

#include "../generator/GeneratorNodes.h"
#include "../stmts/StmtNodes.h"
#include "../try/TryNodes.h"

ExprNode* ExprNode::createIfElse(ExprNode* cond, ExprNode* thenBranch, ExprNode* elseBranch) {
    ExprNode* node = new ExprNode();
    node->type = _IF_ELSE;
    node->condition = cond;
    node->thenExpr = thenBranch;
    node->elseExpr = elseBranch;
    return node;
}

ExprNode* ExprNode::createIf(ExprNode* cond, ExprNode* thenBranch) {
    ExprNode* node = createIfElse(cond, thenBranch, nullptr);
    node->type = _IF;
    return node;
}

ExprNode* ExprNode::createWhile(ExprNode* cond, ExprNode* loopBody) {
    ExprNode* node = new ExprNode();
    node->type = _WHILE;
    node->condition = cond;
    node->body = loopBody;
    return node;
}

ExprNode* ExprNode::createDoWhile(ExprNode* loopBody, ExprNode* cond) {
    ExprNode* node = new ExprNode();
    node->type = _DO_WHILE;
    node->body = loopBody;
    node->condition = cond;
    return node;
}

ExprNode* ExprNode::createFor(EnumeratorsNode* enums, ExprNode* loopBody) {
    ExprNode* node = new ExprNode();
    node->type = _FOR;
    node->enumerators = enums;
    node->body = loopBody;
    return node;
}

ExprNode* ExprNode::createThrow(ExprNode* thrown) {
    ExprNode* node = new ExprNode();
    node->type = _THROW;
    node->value = thrown;
    return node;
}

ExprNode* ExprNode::createReturn() {
    ExprNode* node = new ExprNode();
    node->type = _RETURN;
    return node;
}

ExprNode* ExprNode::createReturnExpr(ExprNode* returned) {
    ExprNode* node = createReturn();
    node->type = _RETURN_EXPR;
    node->value = returned;
    return node;
}

ExprNode* ExprNode::createInfix(InfixExprNode* infix) {
    ExprNode* node = new ExprNode();
    node->type = _INFIX;
    node->infixExpr = infix;
    return node;
}

ExprNode* ExprNode::createAssignment(AssignmentNode* assigned) {
    ExprNode* node = new ExprNode();
    node->type = _ASSIGNMENT;
    node->assignment = assigned;
    return node;
}

ExprNode* ExprNode::createTry(TryExprNode* tryNode) {
    ExprNode* node = new ExprNode();
    node->type = _TRY;
    node->tryExpr = tryNode;
    return node;
}

std::string ExprNode::getDotLabel() const {
    return "Expr [" + toString(type) + "]";
}

std::vector<Node*> ExprNode::getChildren() const {
    return {condition, thenExpr, elseExpr, body, value, enumerators, infixExpr,
            assignment, tryExpr};
}

ExprsNode* ExprsNode::addExprToList(ExprsNode* list, ExprNode* expr) {
    if (list == nullptr) list = new ExprsNode();
    if (expr != nullptr) list->exprs.push_back(expr);
    return list;
}

std::vector<Node*> ExprsNode::getChildren() const {
    std::vector<Node*> children;
    for (ExprNode* expr : exprs) children.push_back(expr);
    return children;
}

std::vector<Node*> ArgumentExprsNode::getChildren() const {
    return {exprs};
}

AssignmentNode* AssignmentNode::createAssignment(SimpleExprNode* target, ExprNode* value,
                                                 const std::string& op) {
    AssignmentNode* node = new AssignmentNode();
    node->target = target;
    node->expr = value;
    node->op = op;
    return node;
}

std::string AssignmentNode::getDotLabel() const {
    return "Assignment [" + op + "]";
}

std::vector<Node*> AssignmentNode::getChildren() const {
    return {target, expr};
}

InfixExprNode* InfixExprNode::createInfixFromPrefix(PrefixExprNode* prefix) {
    InfixExprNode* node = new InfixExprNode();
    node->prefixExpr = prefix;
    return node;
}

InfixExprNode* InfixExprNode::createFromInfixes(InfixExprNode* lhs, OperatorNode* op, InfixExprNode* rhs) {
    InfixExprNode* node = new InfixExprNode();
    node->left = lhs;
    node->op = op;
    node->right = rhs;
    return node;
}

std::string InfixExprNode::getDotLabel() const {
    return op == nullptr ? "InfixExpr" : "InfixExpr [" + op->op + "]";
}

std::vector<Node*> InfixExprNode::getChildren() const {
    return {left, op, right, prefixExpr};
}

PrefixExprNode* PrefixExprNode::createPrefixExprNode(SimpleExprNode* expr, PrefixExprType type) {
    PrefixExprNode* node = new PrefixExprNode();
    node->simpleExpr = expr;
    node->type = type;
    return node;
}

std::string PrefixExprNode::getDotLabel() const {
    return "PrefixExpr [" + toString(type) + "]";
}

std::vector<Node*> PrefixExprNode::getChildren() const {
    return {simpleExpr};
}

SimpleExprNode* SimpleExprNode::createNewObjectNode(IdNode* id, ArgumentExprsNode* args) {
    SimpleExprNode* node = new SimpleExprNode();
    node->type = _NEW_OBJECT;
    node->fullId = id;
    node->arguments = args;
    return node;
}

SimpleExprNode* SimpleExprNode::createNewArrayNode(SimpleTypeNode* type, ArgumentExprsNode* args) {
    SimpleExprNode* node = new SimpleExprNode();
    node->type = _NEW_ARRAY;
    node->simpleType = type;
    node->arguments = args;
    return node;
}

SimpleExprNode* SimpleExprNode::createBlockStmtsNode(BlockStmtsNode* stmts) {
    SimpleExprNode* node = new SimpleExprNode();
    node->type = _BLOCK_EXPR;
    node->blockStmts = stmts;
    return node;
}

SimpleExprNode* SimpleExprNode::createPrimaryExprNode(PrimaryExprNode* expr) {
    SimpleExprNode* node = new SimpleExprNode();
    node->type = _PRIMARY_EXPR;
    node->primaryExpr = expr;
    return node;
}

std::string SimpleExprNode::getDotLabel() const {
    return "SimpleExpr [" + toString(type) + "]";
}

std::vector<Node*> SimpleExprNode::getChildren() const {
    return {fullId, arguments, simpleType, blockStmts, primaryExpr};
}

PrimaryExprNode* PrimaryExprNode::createIntNode(int value) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _INT_LITERAL;
    node->intValue = value;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createCharNode(char value) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _CHAR_LITERAL;
    node->charValue = value;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createDoubleNode(double value) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _DOUBLE_LITERAL;
    node->doubleValue = value;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createStringNode(const std::string& value) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _STRING_LITERAL;
    node->stringValue = value;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createBoolNode(bool value) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _BOOL_LITERAL;
    node->boolValue = value;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createNullNode() {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _NULL_LITERAL;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createUnitLiteralNode() {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _UNIT_LITERAL;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createIdNode(IdNode* id) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _ID;
    node->identifier = id;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createPlainThisNode() {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _THIS;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createSuperFieldAccessNode(IdNode* id) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _SUPER_FIELD_ACCESS;
    node->identifier = id;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createSimpleExprFieldAccessNode(IdNode* id, SimpleExprNode* expr) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _FIELD_ACCESS;
    node->identifier = id;
    node->simpleExpr = expr;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createMethodCallNode(PrimaryExprNode* target,
                                                       ArgumentExprsNode* args) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _METHOD_CALL;
    node->primaryExpr = target;
    node->argumentExprs = args == nullptr ? new ArgumentExprsNode() : args;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createMethodCallNode(SimpleExprNode* target,
                                                       ArgumentExprsNode* args) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _METHOD_CALL;
    node->simpleExpr = target;
    node->argumentExprs = args == nullptr ? new ArgumentExprsNode() : args;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createParenthesizedExprNode(ExprNode* parenthesized) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _PARENTHESIZED_EXPR;
    node->expr = parenthesized;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createArrayBuilderNode(ArgumentExprsNode* args) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _ARRAY_BUILDER;
    node->argumentExprs = args;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createArrayWithTypeBuilderNode(SimpleTypeNode* type,
                                                                  ArgumentExprsNode* args) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _ARRAY_WITH_TYPE_BUILDER;
    node->simpleType = type;
    node->argumentExprs = args;
    return node;
}

PrimaryExprNode* PrimaryExprNode::createArrayMethodNode(IdNode* method, SimpleTypeNode* type,
                                                        ArgumentExprsNode* args) {
    PrimaryExprNode* node = new PrimaryExprNode();
    node->type = _ARRAY_METHOD;
    node->identifier = method;
    node->simpleType = type;
    node->argumentExprs = args;
    return node;
}

std::string PrimaryExprNode::getDotLabel() const {
    switch (type) {
        case _INT_LITERAL: return "Int [" + std::to_string(intValue) + "]";
        case _CHAR_LITERAL: return std::string("Char [") + charValue + "]";
        case _DOUBLE_LITERAL: return "Double [" + std::to_string(doubleValue) + "]";
        case _STRING_LITERAL: return "String [" + stringValue + "]";
        case _BOOL_LITERAL: return std::string("Bool [") + (boolValue ? "true" : "false") + "]";
        case _NULL_LITERAL: return "Null";
        case _UNIT_LITERAL: return "Unit ()";
        default: return "PrimaryExpr [" + toString(type) + "]";
    }
}

std::vector<Node*> PrimaryExprNode::getChildren() const {
    return {simpleExpr, expr, argumentExprs, primaryExpr, identifier, simpleType};
}

ConstrExprNode* ConstrExprNode::createConstrExpr(ArgumentExprsNode* args, BlockStmtsNode* stmts,
                                                 bool isBlock) {
    ConstrExprNode* node = new ConstrExprNode();
    node->arguments = args;
    node->blockStmts = stmts;
    node->isBlock = isBlock;
    return node;
}

std::vector<Node*> ConstrExprNode::getChildren() const {
    return {arguments, blockStmts};
}
