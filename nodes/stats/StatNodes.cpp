#include "StatNodes.h"

BlockStatNode* BlockStatNode::createDefNode(DefNode* definition) {
    BlockStatNode* node = new BlockStatNode();
    node->def = definition;
    return node;
}

BlockStatNode* BlockStatNode::createExprNode(ExprNode* expression) {
    BlockStatNode* node = new BlockStatNode();
    node->expr = expression;
    return node;
}

BlockStatNode* BlockStatNode::createLocalDef(VarDefsNode* definition) {
    if (definition != nullptr) {
        definition->isLocal = true;
        DefNode* def = DefNode::createVarDefs(definition, new ModifiersNode());
        return createDefNode(def);
    }
    return new BlockStatNode();
}

std::string BlockStatNode::getDotLabel() const {
    return "BlockStat";
}

std::vector<Node*> BlockStatNode::getChildren() const {
    return {def, expr};
}

BlockStatsNode* BlockStatsNode::addBlockStatToList(BlockStatsNode* list, BlockStatNode* stat) {
    if (list == nullptr) list = new BlockStatsNode();
    if (stat != nullptr) list->blockStats.push_back(stat);
    return list;
}

std::vector<Node*> BlockStatsNode::getChildren() const {
    std::vector<Node*> children;
    for (BlockStatNode* stat : blockStats) children.push_back(stat);
    return children;
}
