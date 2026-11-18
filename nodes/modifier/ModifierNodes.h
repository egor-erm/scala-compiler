#ifndef SCALA_NODES_MODIFIERNODES_H
#define SCALA_NODES_MODIFIERNODES_H

#include "../Node.h"
#include "../Types.h"

#include <vector>

class ModifierNode : public Node {
public:
    ModifierType type;

    explicit ModifierNode(ModifierType modifierType)
        : Node("Modifier"), type(modifierType) {}

    static ModifierNode* createModifier(ModifierType type) { return new ModifierNode(type); }
    std::string getDotLabel() const override { return "Modifier [" + toString(type) + "]"; }
};

class ModifiersNode : public Node {
public:
    std::vector<ModifierNode*> modifiers;

    ModifiersNode() : Node("Modifiers") {}

    static ModifiersNode* addModifierToList(ModifiersNode* list, ModifierNode* modifier) {
        if (list == nullptr) list = new ModifiersNode();
        if (modifier != nullptr) list->modifiers.push_back(modifier);
        return list;
    }

    std::vector<Node*> getChildren() const override {
        std::vector<Node*> children;
        for (ModifierNode* modifier : modifiers) children.push_back(modifier);
        return children;
    }
};

#endif
