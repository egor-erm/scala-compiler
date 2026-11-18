#ifndef SCALA_NODES_FUNCNODES_H
#define SCALA_NODES_FUNCNODES_H

#include "../Node.h"
#include "../id/IdNode.h"
#include "../type/SimpleTypeNode.h"
#include "../exprs/ExprNodes.h"

#include <vector>

class ExprNode;

class FuncParamNode : public Node {
public:
    IdNode* fullId = nullptr;
    SimpleTypeNode* simpleType = nullptr;

    FuncParamNode() : Node("FuncParam") {}

    static FuncParamNode* createFuncParam(IdNode* id, SimpleTypeNode* type) {
        FuncParamNode* node = new FuncParamNode();
        node->fullId = id;
        node->simpleType = type;
        return node;
    }

    std::string getDotLabel() const override {
        return "Param [" + (fullId == nullptr ? std::string() : fullId->name) + "]";
    }

    std::vector<Node*> getChildren() const override { return {fullId, simpleType}; }
};

class FuncParamsNode : public Node {
public:
    std::vector<FuncParamNode*> funcParams;

    FuncParamsNode() : Node("FuncParams") {}

    static FuncParamsNode* addFuncParamToList(FuncParamsNode* list, FuncParamNode* param) {
        if (list == nullptr) list = new FuncParamsNode();
        if (param != nullptr) list->funcParams.push_back(param);
        return list;
    }

    std::vector<Node*> getChildren() const override {
        std::vector<Node*> children;
        for (FuncParamNode* param : funcParams) children.push_back(param);
        return children;
    }
};

class FunSigNode : public Node {
public:
    IdNode* fullId = nullptr;
    FuncParamsNode* params = nullptr;

    FunSigNode() : Node("FunSig") {}

    static FunSigNode* createFunSig(IdNode* id, FuncParamsNode* parameters) {
        FunSigNode* node = new FunSigNode();
        node->fullId = id;
        node->params = parameters;
        return node;
    }

    std::string getDotLabel() const override {
        return "FunSig [" + (fullId == nullptr ? std::string() : fullId->name) + "]";
    }

    std::vector<Node*> getChildren() const override { return {fullId, params}; }
};

class FunDefNode : public Node {
public:
    FunSigNode* funSig = nullptr;
    SimpleTypeNode* simpleType = nullptr;
    ExprNode* expr = nullptr;
    SimpleExpr1Node* constrExpr = nullptr;
    bool primaryConstructor = false;
    bool secondaryConstructor = false;

    FunDefNode() : Node("FunDef") {}

    static FunDefNode* createFunSigFunDef(FunSigNode* sig, SimpleTypeNode* type, ExprNode* body) {
        FunDefNode* node = new FunDefNode();
        node->funSig = sig;
        node->simpleType = type;
        node->expr = body;
        return node;
    }

    static FunDefNode* createThisConstrCallFunDef(FuncParamsNode* params, SimpleExpr1Node* call) {
        FunDefNode* node = new FunDefNode();
        node->funSig = FunSigNode::createFunSig(IdNode::createId("this"), params);
        node->constrExpr = call;
        node->secondaryConstructor = true;
        return node;
    }

    static FunDefNode* createThisConstrCallFunDef(FuncParamsNode* params, ExprNode* call) {
        FunDefNode* node = new FunDefNode();
        node->funSig = FunSigNode::createFunSig(IdNode::createId("this"), params);
        node->expr = call;
        node->secondaryConstructor = true;
        return node;
    }

    std::string getDotLabel() const override {
        if (secondaryConstructor) return "SecondaryConstructor";
        return "FunDef";
    }

    std::vector<Node*> getChildren() const override {
        return {funSig, simpleType, expr, constrExpr};
    }
};

#endif
