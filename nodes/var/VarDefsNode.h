#ifndef SCALA_NODES_VARDEFSNODE_H
#define SCALA_NODES_VARDEFSNODE_H

#include "../Node.h"
#include "../Types.h"
#include "../id/IdNode.h"
#include "../type/SimpleTypeNode.h"

#include <vector>

class ExprNode;

class VarDefsNode : public Node {
public:
    std::vector<IdNode*> fullIds;
    SimpleTypeNode* simpleType = nullptr;
    ExprNode* expr = nullptr;
    StmtType type = _VAL_DECL;
    bool isLocal = false;

    VarDefsNode() : Node("VarDef") {}

    static VarDefsNode* createVal(IdNode* id, SimpleTypeNode* type, ExprNode* value) {
        VarDefsNode* node = new VarDefsNode();
        node->type = _VAL_DECL;
        if (id != nullptr) node->fullIds.push_back(id);
        node->simpleType = type;
        node->expr = value;
        return node;
    }

    static VarDefsNode* createVar(IdNode* id, SimpleTypeNode* type, ExprNode* value) {
        VarDefsNode* node = createVal(id, type, value);
        node->type = _VAR_DECL;
        return node;
    }

    std::string getDotLabel() const override { return toString(type); }

    std::vector<Node*> getChildren() const override {
        std::vector<Node*> children;
        for (IdNode* id : fullIds) children.push_back(id);
        children.push_back(simpleType);
        children.push_back(expr);
        return children;
    }
};

#endif
