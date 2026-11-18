#include "TryNodes.h"

CaseNode* CaseNode::createCase(IdNode* patternName, SimpleTypeNode* type, BlockStmtsNode* body) {
    CaseNode* node = new CaseNode();
    node->pattern = patternName;
    node->simpleType = type;
    node->blockStmts = body;
    return node;
}

std::string CaseNode::getDotLabel() const {
    return pattern == nullptr ? "Case" : "Case [" + pattern->name + "]";
}

std::vector<Node*> CaseNode::getChildren() const {
    return {pattern, simpleType, blockStmts};
}

CatchNode* CatchNode::addCase(CatchNode* list, CaseNode* caseNode) {
    if (list == nullptr) list = new CatchNode();
    if (caseNode != nullptr) list->cases.push_back(caseNode);
    return list;
}

std::vector<Node*> CatchNode::getChildren() const {
    std::vector<Node*> children;
    for (CaseNode* caseNode : cases) children.push_back(caseNode);
    return children;
}

TryExprNode* TryExprNode::createExceptionBlock(ExprNode* body, CatchNode* catchPart,
                                               ExprNode* finallyPart) {
    TryExprNode* node = new TryExprNode();
    node->tryExpr = body;
    node->catchPart = catchPart;
    node->finallyExpr = finallyPart;
    return node;
}

TryExprNode* TryExprNode::createExceptionBlockWithStmts(ExprNode* body, CatchNode* catchPart,
                                                        BlockStmtsNode* finallyPart) {
    TryExprNode* node = new TryExprNode();
    node->tryExpr = body;
    node->catchPart = catchPart;
    node->finallyStmts = finallyPart;
    return node;
}

std::vector<Node*> TryExprNode::getChildren() const {
    return {tryExpr, catchPart, finallyExpr, finallyStmts};
}
