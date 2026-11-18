#include "TryNodes.h"

CaseNode* CaseNode::createCase(IdNode* patternName, SimpleTypeNode* type, BlockStatsNode* body) {
    CaseNode* node = new CaseNode();
    node->pattern = patternName;
    node->simpleType = type;
    node->blockStats = body;
    return node;
}

std::string CaseNode::getDotLabel() const {
    return pattern == nullptr ? "Case" : "Case [" + pattern->name + "]";
}

std::vector<Node*> CaseNode::getChildren() const {
    return {pattern, simpleType, blockStats};
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

TryExprNode* TryExprNode::createExceptionBlockWithStats(ExprNode* body, CatchNode* catchPart,
                                                        BlockStatsNode* finallyPart) {
    TryExprNode* node = new TryExprNode();
    node->tryExpr = body;
    node->catchPart = catchPart;
    node->finallyStats = finallyPart;
    return node;
}

std::vector<Node*> TryExprNode::getChildren() const {
    return {tryExpr, catchPart, finallyExpr, finallyStats};
}
