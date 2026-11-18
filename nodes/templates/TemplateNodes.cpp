#include "TemplateNodes.h"

TemplateStatNode* TemplateStatNode::createDefTemplate(DefNode* definition) {
    TemplateStatNode* node = new TemplateStatNode();
    node->def = definition;
    return node;
}

TemplateStatNode* TemplateStatNode::createExprTemplate(ExprNode* expression) {
    TemplateStatNode* node = new TemplateStatNode();
    node->expr = expression;
    return node;
}

std::vector<Node*> TemplateStatNode::getChildren() const {
    return {def, expr};
}

TemplateStatsNode* TemplateStatsNode::addTemplateStatToBackToList(TemplateStatsNode* list,
                                                                   TemplateStatNode* stat) {
    if (list == nullptr) list = new TemplateStatsNode();
    if (stat != nullptr) list->templateStats.push_back(stat);
    return list;
}

std::vector<Node*> TemplateStatsNode::getChildren() const {
    std::vector<Node*> children;
    for (TemplateStatNode* stat : templateStats) children.push_back(stat);
    return children;
}
