#ifndef SCALA_NODES_SIMPLETYPENODE_H
#define SCALA_NODES_SIMPLETYPENODE_H

#include "../Node.h"
#include "../id/IdNode.h"

class SimpleTypeNode : public Node {
public:
    IdNode* fullId = nullptr;
    SimpleTypeNode* arrayElemType = nullptr;

    SimpleTypeNode() : Node("SimpleType") {}

    static SimpleTypeNode* createIdTypeNode(IdNode* id) {
        SimpleTypeNode* node = new SimpleTypeNode();
        node->fullId = id;
        return node;
    }

    static SimpleTypeNode* createSimpleTypeNode(SimpleTypeNode* elementType) {
        SimpleTypeNode* node = new SimpleTypeNode();
        node->arrayElemType = elementType;
        return node;
    }

    std::string getDotLabel() const override {
        if (arrayElemType != nullptr) return "ArrayType";
        return "Type [" + (fullId == nullptr ? std::string() : fullId->name) + "]";
    }

    std::vector<Node*> getChildren() const override {
        return {fullId, arrayElemType};
    }
};

#endif
