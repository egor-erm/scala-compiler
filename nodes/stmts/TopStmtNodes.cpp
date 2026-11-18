#include "TopStmtNodes.h"

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

TopStmtNode* TopStmtNode::createClass(TemplateDefNode* definition) {
    TopStmtNode* node = new TopStmtNode();
    node->tmplDef = definition;
    return node;
}

TopStmtNode* TopStmtNode::createImport(ImportNode* importNode) {
    TopStmtNode* node = new TopStmtNode();
    node->importPart = importNode;
    return node;
}

TopStmtNode* TopStmtNode::createExpr(ExprNode* expression) {
    TopStmtNode* node = new TopStmtNode();
    node->expr = expression;
    return node;
}

std::vector<Node*> TopStmtNode::getChildren() const {
    return {tmplDef, importPart, expr};
}

TopStmtSeqNode* TopStmtSeqNode::addTopStmtToList(TopStmtSeqNode* list, TopStmtNode* stmt) {
    if (list == nullptr) list = new TopStmtSeqNode();
    if (stmt != nullptr) list->topStmts.push_back(stmt);
    return list;
}

std::vector<Node*> TopStmtSeqNode::getChildren() const {
    std::vector<Node*> children;
    for (TopStmtNode* stmt : topStmts) children.push_back(stmt);
    return children;
}
