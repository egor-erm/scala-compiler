#ifndef SCALA_NODES_TOPSTATNODES_H
#define SCALA_NODES_TOPSTATNODES_H

#include "../Node.h"
#include "../Types.h"
#include "../class/ClassNodes.h"
#include "../exprs/ExprNodes.h"
#include "../modifier/ModifierNodes.h"

#include "../import/ImportNodes.h"

#include <vector>

class TemplateDefNode : public Node {
public:
    StatType type = _CLASS;
    ClassDefNode* classDef = nullptr;

    TemplateDefNode() : Node("TemplateDef") {}

    static TemplateDefNode* createClassDef(ClassDefNode* definition);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class TopStatNode : public Node {
public:
    TemplateDefNode* tmplDef = nullptr;
    ImportNode* importPart = nullptr;
    ExprNode* expr = nullptr;

    TopStatNode() : Node("TopStat") {}

    static TopStatNode* createClass(TemplateDefNode* definition);
    static TopStatNode* createImport(ImportNode* importNode);
    static TopStatNode* createExpr(ExprNode* expression);
    std::vector<Node*> getChildren() const override;
};

class TopStatSeqNode : public Node {
public:
    std::vector<TopStatNode*> topStats;

    TopStatSeqNode() : Node("TopStatSeq") {}

    static TopStatSeqNode* addTopStatToList(TopStatSeqNode* list, TopStatNode* stat);
    std::vector<Node*> getChildren() const override;
};

#endif
