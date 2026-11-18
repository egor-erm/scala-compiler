#ifndef SCALA_NODES_TRYNODES_H
#define SCALA_NODES_TRYNODES_H

#include "../Node.h"
#include "../id/IdNode.h"
#include "../stmts/StmtNodes.h"
#include "../type/SimpleTypeNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class CaseNode : public Node {
public:
    IdNode* pattern = nullptr;
    SimpleTypeNode* simpleType = nullptr;
    BlockStmtsNode* blockStmts = nullptr;

    CaseNode() : Node("Case") {}

    static CaseNode* createCase(IdNode* pattern, SimpleTypeNode* type, BlockStmtsNode* body);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class CatchNode : public Node {
public:
    std::vector<CaseNode*> cases;

    CatchNode() : Node("Catch") {}

    static CatchNode* addCase(CatchNode* list, CaseNode* caseNode);
    std::vector<Node*> getChildren() const override;
};

class TryExprNode : public Node {
public:
    ExprNode* tryExpr = nullptr;
    CatchNode* catchPart = nullptr;
    ExprNode* finallyExpr = nullptr;
    BlockStmtsNode* finallyStmts = nullptr;

    TryExprNode() : Node("TryExpr") {}

    static TryExprNode* createExceptionBlock(ExprNode* body, CatchNode* catchPart,
                                             ExprNode* finallyPart);
    static TryExprNode* createExceptionBlockWithStmts(ExprNode* body, CatchNode* catchPart,
                                                      BlockStmtsNode* finallyPart);
    std::vector<Node*> getChildren() const override;
};

#endif
