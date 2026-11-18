#ifndef SCALA_NODES_TOPSTMTNODES_H
#define SCALA_NODES_TOPSTMTNODES_H

#include "../Node.h"
#include "../Types.h"
#include "../class/ClassNodes.h"
#include "../exprs/ExprNodes.h"
#include "../modifier/ModifierNodes.h"

#include "../import/ImportNodes.h"

#include <vector>

class TemplateDefNode : public Node {
public:
    StmtType type = _CLASS;
    ClassDefNode* classDef = nullptr;

    TemplateDefNode() : Node("TemplateDef") {}

    static TemplateDefNode* createClassDef(ClassDefNode* definition);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class TopStmtNode : public Node {
public:
    TemplateDefNode* tmplDef = nullptr;
    ImportNode* importPart = nullptr;
    ExprNode* expr = nullptr;

    TopStmtNode() : Node("TopStmt") {}

    static TopStmtNode* createClass(TemplateDefNode* definition);
    static TopStmtNode* createImport(ImportNode* importNode);
    static TopStmtNode* createExpr(ExprNode* expression);
    std::vector<Node*> getChildren() const override;
};

class TopStmtSeqNode : public Node {
public:
    std::vector<TopStmtNode*> topStmts;

    TopStmtSeqNode() : Node("TopStmtSeq") {}

    static TopStmtSeqNode* addTopStmtToList(TopStmtSeqNode* list, TopStmtNode* stmt);
    std::vector<Node*> getChildren() const override;
};

#endif
