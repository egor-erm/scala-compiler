#ifndef SCALA_NODES_TEMPLATENODES_H
#define SCALA_NODES_TEMPLATENODES_H

#include "../Node.h"
#include "../definitions/DefNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class TemplateStatNode : public Node {
public:
    DefNode* def = nullptr;
    ExprNode* expr = nullptr;

    TemplateStatNode() : Node("TemplateStat") {}

    static TemplateStatNode* createDefTemplate(DefNode* definition);
    static TemplateStatNode* createExprTemplate(ExprNode* expression);
    std::vector<Node*> getChildren() const override;
};

class TemplateStatsNode : public Node {
public:
    std::vector<TemplateStatNode*> templateStats;

    TemplateStatsNode() : Node("TemplateStats") {}

    static TemplateStatsNode* addTemplateStatToBackToList(TemplateStatsNode* list,
                                                           TemplateStatNode* stat);
    std::vector<Node*> getChildren() const override;
};

#endif
