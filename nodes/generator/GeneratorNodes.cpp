#include "GeneratorNodes.h"

GeneratorNode* GeneratorNode::createGenerator(IdNode* id, SimpleTypeNode* type, ExprNode* value) {
    GeneratorNode* node = new GeneratorNode();
    node->fullId = id;
    node->simpleType = type;
    node->expr = value;
    return node;
}

GeneratorNode* GeneratorNode::createGuard(ExprNode* condition) {
    GeneratorNode* node = new GeneratorNode();
    node->expr = condition;
    node->isGuard = true;
    return node;
}

std::string GeneratorNode::getDotLabel() const {
    return isGuard ? "Guard" : "Generator";
}

std::vector<Node*> GeneratorNode::getChildren() const {
    return {fullId, simpleType, expr};
}

EnumeratorsNode* EnumeratorsNode::addEnumerator(EnumeratorsNode* list, GeneratorNode* generator) {
    if (list == nullptr) list = new EnumeratorsNode();
    if (generator != nullptr) list->enumerators.push_back(generator);
    return list;
}

std::vector<Node*> EnumeratorsNode::getChildren() const {
    std::vector<Node*> children;
    for (GeneratorNode* generator : enumerators) children.push_back(generator);
    return children;
}
