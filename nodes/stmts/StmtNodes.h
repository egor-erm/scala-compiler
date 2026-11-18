#ifndef SCALA_NODES_STMTNODES_H
#define SCALA_NODES_STMTNODES_H

#include "../Node.h"
#include "../definitions/DefNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class BlockStmtNode : public Node {
public:
    DefNode* def = nullptr;
    ExprNode* expr = nullptr;

    BlockStmtNode() : Node("BlockStmt") {}

    static BlockStmtNode* createDefNode(DefNode* definition);
    static BlockStmtNode* createExprNode(ExprNode* expression);
    static BlockStmtNode* createLocalDef(VarDefsNode* definition);

    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class BlockStmtsNode : public Node {
public:
    std::vector<BlockStmtNode*> blockStmts;

    BlockStmtsNode() : Node("BlockStmts") {}

    static BlockStmtsNode* addBlockStmtToList(BlockStmtsNode* list, BlockStmtNode* stmt);
    std::vector<Node*> getChildren() const override;
};

#endif
