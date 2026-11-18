#ifndef SCALA_NODES_TEMPLATENODES_H
#define SCALA_NODES_TEMPLATENODES_H

#include "../Node.h"
#include "../definitions/DefNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class TemplateStmtNode : public Node {
public:
    DefNode* def = nullptr;
    ExprNode* expr = nullptr;

    TemplateStmtNode() : Node("TemplateStmt") {}

    static TemplateStmtNode* createDefTemplate(DefNode* definition);
    static TemplateStmtNode* createExprTemplate(ExprNode* expression);
    std::vector<Node*> getChildren() const override;
};

class TemplateStmtsNode : public Node {
public:
    std::vector<TemplateStmtNode*> templateStmts;

    TemplateStmtsNode() : Node("TemplateStmts") {}

    static TemplateStmtsNode* addTemplateStmtToBackToList(TemplateStmtsNode* list,
                                                           TemplateStmtNode* stmt);
    std::vector<Node*> getChildren() const override;
};

#endif
