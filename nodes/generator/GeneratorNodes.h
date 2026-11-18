#ifndef SCALA_NODES_GENERATORNODES_H
#define SCALA_NODES_GENERATORNODES_H

#include "../Node.h"
#include "../id/IdNode.h"
#include "../type/SimpleTypeNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class GeneratorNode : public Node {
public:
    IdNode* fullId = nullptr;
    SimpleTypeNode* simpleType = nullptr;
    ExprNode* expr = nullptr;
    bool isGuard = false;

    GeneratorNode() : Node("Generator") {}

    static GeneratorNode* createGenerator(IdNode* id, SimpleTypeNode* type, ExprNode* value);
    static GeneratorNode* createGuard(ExprNode* condition);

    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class EnumeratorsNode : public Node {
public:
    std::vector<GeneratorNode*> enumerators;

    EnumeratorsNode() : Node("Enumerators") {};

    static EnumeratorsNode* addEnumerator(EnumeratorsNode* list, GeneratorNode* generator);
    std::vector<Node*> getChildren() const override;
};

#endif
