#include "TopStatNodes.h"

TemplateDefNode* TemplateDefNode::createClassDef(ClassDefNode* definition) {
    TemplateDefNode* node = new TemplateDefNode();
    node->type = definition == nullptr ? _CLASS : definition->type;
    node->classDef = definition;
    return node;
}

std::string TemplateDefNode::getDotLabel() const {
    return "TemplateDef [" + toString(type) + "]";
}

std::vector<Node*> TemplateDefNode::getChildren() const {
    return {classDef};
}

TopStatNode* TopStatNode::createClass(TemplateDefNode* definition) {
    TopStatNode* node = new TopStatNode();
    node->tmplDef = definition;
    return node;
}

TopStatNode* TopStatNode::createImport(ImportNode* importNode) {
    TopStatNode* node = new TopStatNode();
    node->importPart = importNode;
    return node;
}

TopStatNode* TopStatNode::createExpr(ExprNode* expression) {
    TopStatNode* node = new TopStatNode();
    node->expr = expression;
    return node;
}

std::vector<Node*> TopStatNode::getChildren() const {
    return {tmplDef, importPart, expr};
}

TopStatSeqNode* TopStatSeqNode::addTopStatToList(TopStatSeqNode* list, TopStatNode* stat) {
    if (list == nullptr) list = new TopStatSeqNode();
    if (stat != nullptr) list->topStats.push_back(stat);
    return list;
}

std::vector<Node*> TopStatSeqNode::getChildren() const {
    std::vector<Node*> children;
    for (TopStatNode* stat : topStats) children.push_back(stat);
    return children;
}
