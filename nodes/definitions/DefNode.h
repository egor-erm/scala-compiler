#ifndef SCALA_NODES_DEFNODE_H
#define SCALA_NODES_DEFNODE_H

#include "../Node.h"
#include "../Types.h"
#include "../func/FuncNodes.h"
#include "../modifier/ModifierNodes.h"
#include "../var/VarDefsNode.h"

class DefNode : public Node {
public:
    DefinitionType type = _VARIABLE_DEF;
    VarDefsNode* varDefs = nullptr;
    FunDefNode* funDef = nullptr;
    ModifiersNode* modifiers = nullptr;

    DefNode() : Node("Def") {}

    static DefNode* createVarDefs(VarDefsNode* definition, ModifiersNode* mods = nullptr) {
        DefNode* node = new DefNode();
        node->type = _VARIABLE_DEF;
        node->varDefs = definition;
        node->modifiers = mods;
        return node;
    }

    static DefNode* createFunDef(FunDefNode* definition, ModifiersNode* mods = nullptr) {
        DefNode* node = new DefNode();
        node->type = _FUNCTION_DEF;
        node->funDef = definition;
        node->modifiers = mods;
        return node;
    }

    std::string getDotLabel() const override { return "Def [" + toString(type) + "]"; }

    std::vector<Node*> getChildren() const override {
        return {modifiers, varDefs, funDef};
    }
};

#endif
