#include "StmtNodes.h"

BlockStmtNode* BlockStmtNode::createDefNode(DefNode* definition) {
    BlockStmtNode* node = new BlockStmtNode();
    node->def = definition;
    return node;
}

BlockStmtNode* BlockStmtNode::createExprNode(ExprNode* expression) {
    BlockStmtNode* node = new BlockStmtNode();
    node->expr = expression;
    return node;
}

BlockStmtNode* BlockStmtNode::createLocalDef(VarDefsNode* definition) {
    if (definition != nullptr) {
        definition->isLocal = true;
        DefNode* def = DefNode::createVarDefs(definition, new ModifiersNode());
        return createDefNode(def);
    }
    return new BlockStmtNode();
}

std::string BlockStmtNode::getDotLabel() const {
    return "BlockStmt";
}

std::vector<Node*> BlockStmtNode::getChildren() const {
    return {def, expr};
}

BlockStmtsNode* BlockStmtsNode::addBlockStmtToList(BlockStmtsNode* list, BlockStmtNode* stmt) {
    if (list == nullptr) list = new BlockStmtsNode();
    if (stmt != nullptr) list->blockStmts.push_back(stmt);
    return list;
}

std::vector<Node*> BlockStmtsNode::getChildren() const {
    std::vector<Node*> children;
    for (BlockStmtNode* stmt : blockStmts) children.push_back(stmt);
    return children;
}
