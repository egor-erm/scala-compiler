#include "TemplateNodes.h"

TemplateStmtNode* TemplateStmtNode::createDefTemplate(DefNode* definition) {
    TemplateStmtNode* node = new TemplateStmtNode();
    node->def = definition;
    return node;
}

TemplateStmtNode* TemplateStmtNode::createExprTemplate(ExprNode* expression) {
    TemplateStmtNode* node = new TemplateStmtNode();
    node->expr = expression;
    return node;
}

std::vector<Node*> TemplateStmtNode::getChildren() const {
    return {def, expr};
}

TemplateStmtsNode* TemplateStmtsNode::addTemplateStmtToBackToList(TemplateStmtsNode* list,
                                                                   TemplateStmtNode* stmt) {
    if (list == nullptr) list = new TemplateStmtsNode();
    if (stmt != nullptr) list->templateStmts.push_back(stmt);
    return list;
}

std::vector<Node*> TemplateStmtsNode::getChildren() const {
    std::vector<Node*> children;
    for (TemplateStmtNode* stmt : templateStmts) children.push_back(stmt);
    return children;
}
