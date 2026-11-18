#ifndef SCALA_NODES_EXPRNODES_H
#define SCALA_NODES_EXPRNODES_H

#include "../Node.h"
#include "../Types.h"
#include "../id/IdNode.h"
#include "../type/SimpleTypeNode.h"

#include <string>
#include <vector>

class ArgumentExprsNode;
class AssignmentNode;
class BlockStatsNode;
class EnumeratorsNode;
class InfixExprNode;
class PrefixExprNode;
class SimpleExprNode;
class SimpleExpr1Node;
class TryExprNode;

class ExprNode : public Node {
public:
    ExprType type = _BLOCK;
    ExprNode* condition = nullptr;
    ExprNode* thenExpr = nullptr;
    ExprNode* elseExpr = nullptr;
    ExprNode* body = nullptr;
    ExprNode* value = nullptr;
    EnumeratorsNode* enumerators = nullptr;
    InfixExprNode* infixExpr = nullptr;
    AssignmentNode* assignment = nullptr;
    TryExprNode* tryExpr = nullptr;

    ExprNode() : Node("Expr") {}

    static ExprNode* createIfElse(ExprNode* condition, ExprNode* thenExpr, ExprNode* elseExpr);
    static ExprNode* createIf(ExprNode* condition, ExprNode* thenExpr);
    static ExprNode* createWhile(ExprNode* condition, ExprNode* body);
    static ExprNode* createDoWhile(ExprNode* body, ExprNode* condition);
    static ExprNode* createFor(EnumeratorsNode* enumerators, ExprNode* body);
    static ExprNode* createThrow(ExprNode* value);
    static ExprNode* createReturn();
    static ExprNode* createReturnExpr(ExprNode* value);
    static ExprNode* createInfix(InfixExprNode* infix);
    static ExprNode* createAssignment(AssignmentNode* assignment);
    static ExprNode* createTry(TryExprNode* tryNode);

    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class ExprsNode : public Node {
public:
    std::vector<ExprNode*> exprs;

    ExprsNode() : Node("Exprs") {}

    static ExprsNode* addExprToList(ExprsNode* list, ExprNode* expr);
    std::vector<Node*> getChildren() const override;
};

class ArgumentExprsNode : public Node {
public:
    ExprsNode* exprs = nullptr;

    ArgumentExprsNode() : Node("ArgumentExprs") { exprs = new ExprsNode(); }
    explicit ArgumentExprsNode(ExprsNode* values) : Node("ArgumentExprs"), exprs(values) {}

    std::vector<Node*> getChildren() const override;
};

class AssignmentNode : public Node {
public:
    SimpleExprNode* target = nullptr;
    ExprNode* expr = nullptr;
    std::string op = "=";

    AssignmentNode() : Node("Assignment") {}

    static AssignmentNode* createAssignment(SimpleExprNode* target, ExprNode* value,
                                            const std::string& op = "=");
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class InfixExprNode : public Node {
public:
    InfixExprNode* left = nullptr;
    InfixExprNode* right = nullptr;
    IdNode* fullId = nullptr;
    PrefixExprNode* prefixExpr = nullptr;

    InfixExprNode() : Node("InfixExpr") {}

    static InfixExprNode* createInfixFromPrefix(PrefixExprNode* prefix);
    static InfixExprNode* createFromInfixes(InfixExprNode* left, IdNode* op, InfixExprNode* right);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class PrefixExprNode : public Node {
public:
    PrefixExprType type = _NO_UNARY_OPERATOR;
    SimpleExprNode* simpleExpr = nullptr;

    PrefixExprNode() : Node("PrefixExpr") {}

    static PrefixExprNode* createPrefixExprNode(SimpleExprNode* expr, PrefixExprType type);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class SimpleExprNode : public Node {
public:
    SimpleExprType type = _SIMPLE_EXPR_1;
    IdNode* fullId = nullptr;
    ArgumentExprsNode* arguments = nullptr;
    SimpleTypeNode* simpleType = nullptr;
    BlockStatsNode* blockStats = nullptr;
    SimpleExpr1Node* simpleExpr1 = nullptr;

    SimpleExprNode() : Node("SimpleExpr") {}

    static SimpleExprNode* createNewObjectNode(IdNode* id, ArgumentExprsNode* args);
    static SimpleExprNode* createNewArrayNode(SimpleTypeNode* type, ArgumentExprsNode* args);
    static SimpleExprNode* createBlockStatsNode(BlockStatsNode* stats);
    static SimpleExprNode* createSimpleExpr1Node(SimpleExpr1Node* expr);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class SimpleExpr1Node : public Node {
public:
    SimpleExpr1Type type = _ID;
    int intValue = 0;
    char charValue = '\0';
    double doubleValue = 0.0;
    std::string stringValue;
    bool boolValue = false;
    SimpleExprNode* simpleExpr = nullptr;
    ExprNode* expr = nullptr;
    ArgumentExprsNode* argumentExprs = nullptr;
    SimpleExpr1Node* simpleExpr1 = nullptr;
    IdNode* identifier = nullptr;
    SimpleTypeNode* simpleType = nullptr;

    SimpleExpr1Node() : Node("SimpleExpr1") {}

    static SimpleExpr1Node* createIntNode(int value);
    static SimpleExpr1Node* createCharNode(char value);
    static SimpleExpr1Node* createDoubleNode(double value);
    static SimpleExpr1Node* createStringNode(const std::string& value);
    static SimpleExpr1Node* createBoolNode(bool value);
    static SimpleExpr1Node* createNullNode();
    static SimpleExpr1Node* createUnitLiteralNode();
    static SimpleExpr1Node* createIdNode(IdNode* id);
    static SimpleExpr1Node* createPlainThisNode();
    static SimpleExpr1Node* createSuperFieldAccessNode(IdNode* id);
    static SimpleExpr1Node* createSimpleExprFieldAccessNode(IdNode* id, SimpleExprNode* expr);
    static SimpleExpr1Node* createMethodCallNode(SimpleExpr1Node* target, ArgumentExprsNode* args);
    static SimpleExpr1Node* createMethodCallNode(SimpleExprNode* target, ArgumentExprsNode* args);
    static SimpleExpr1Node* createParenthesizedExprNode(ExprNode* expr);
    static SimpleExpr1Node* createArrayBuilderNode(ArgumentExprsNode* args);
    static SimpleExpr1Node* createArrayWithTypeBuilderNode(SimpleTypeNode* type, ArgumentExprsNode* args);
    static SimpleExpr1Node* createArrayMethodNode(IdNode* method, SimpleTypeNode* type,
                                                  ArgumentExprsNode* args);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class ConstrExprNode : public Node {
public:
    ArgumentExprsNode* arguments = nullptr;
    BlockStatsNode* blockStats = nullptr;
    bool isBlock = false;

    ConstrExprNode() : Node("ConstrExpr") {}

    static ConstrExprNode* createConstrExpr(ArgumentExprsNode* args, BlockStatsNode* stats = nullptr,
                                            bool isBlock = false);
    std::vector<Node*> getChildren() const override;
};

#endif
