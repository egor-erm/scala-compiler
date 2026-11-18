#ifndef SCALA_NODES_STATNODES_H
#define SCALA_NODES_STATNODES_H

#include "../Node.h"
#include "../definitions/DefNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class BlockStatNode : public Node {
public:
    DefNode* def = nullptr;
    ExprNode* expr = nullptr;

    BlockStatNode() : Node("BlockStat") {}

    static BlockStatNode* createDefNode(DefNode* definition);
    static BlockStatNode* createExprNode(ExprNode* expression);
    static BlockStatNode* createLocalDef(VarDefsNode* definition);

    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class BlockStatsNode : public Node {
public:
    std::vector<BlockStatNode*> blockStats;

    BlockStatsNode() : Node("BlockStats") {}

    static BlockStatsNode* addBlockStatToList(BlockStatsNode* list, BlockStatNode* stat);
    std::vector<Node*> getChildren() const override;
};

#endif
