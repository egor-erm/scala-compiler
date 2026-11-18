#include "ClassNodes.h"

ClassParamNode* ClassParamNode::createClassParam(ClassParamType paramType, ModifiersNode* mods,
                                                 IdNode* id, SimpleTypeNode* type) {
    ClassParamNode* node = new ClassParamNode();
    node->type = paramType;
    node->modifiers = mods == nullptr ? new ModifiersNode() : mods;
    node->fullId = id;
    node->simpleType = type;
    return node;
}

std::string ClassParamNode::getDotLabel() const {
    return "ClassParam [" + toString(type) + "]";
}

std::vector<Node*> ClassParamNode::getChildren() const {
    return {modifiers, fullId, simpleType};
}

ClassParamsNode* ClassParamsNode::addClassParamToList(ClassParamsNode* list, ClassParamNode* param) {
    if (list == nullptr) list = new ClassParamsNode();
    if (param != nullptr) list->classParams.push_back(param);
    return list;
}

std::vector<Node*> ClassParamsNode::getChildren() const {
    std::vector<Node*> children;
    for (ClassParamNode* param : classParams) children.push_back(param);
    return children;
}

ExtensionClassTemplateNode* ExtensionClassTemplateNode::createExtendWithConstrAndBody(
        IdNode* id, ArgumentExprsNode* args, TemplateStatsNode* body) {
    ExtensionClassTemplateNode* node = new ExtensionClassTemplateNode();
    node->type = _EXTEND_WITH_CONSTRUCTOR_AND_BODY;
    node->fullId = id;
    node->argumentExprs = args;
    node->templateStats = body;
    return node;
}

ExtensionClassTemplateNode* ExtensionClassTemplateNode::createExtendWithBody(
        IdNode* id, TemplateStatsNode* body) {
    ExtensionClassTemplateNode* node = new ExtensionClassTemplateNode();
    node->type = _EXTEND_WITH_BODY;
    node->fullId = id;
    node->templateStats = body;
    return node;
}

std::string ExtensionClassTemplateNode::getDotLabel() const {
    return "Extends [" + toString(type) + "]";
}

std::vector<Node*> ExtensionClassTemplateNode::getChildren() const {
    return {fullId, argumentExprs, templateStats};
}

ClassTemplateOptNode* ClassTemplateOptNode::createClassWithInherit(
        ExtensionClassTemplateNode* extension) {
    ClassTemplateOptNode* node = new ClassTemplateOptNode();
    node->extensionPartClassTemplate = extension;
    if (extension != nullptr) node->templateStats = extension->templateStats;
    return node;
}

ClassTemplateOptNode* ClassTemplateOptNode::createClassWithoutInherit(TemplateStatsNode* body) {
    ClassTemplateOptNode* node = new ClassTemplateOptNode();
    node->templateStats = body;
    return node;
}

std::vector<Node*> ClassTemplateOptNode::getChildren() const {
    std::vector<Node*> children;
    children.push_back(modifiers);
    if (extensionPartClassTemplate != nullptr) {
        children.push_back(extensionPartClassTemplate);
    } else {
        children.push_back(templateStats);
    }
    return children;
}

ClassDefNode* ClassDefNode::createClassDef(IdNode* id, ModifiersNode* mods,
                                           ClassParamsNode* params, ClassTemplateOptNode* body) {
    ClassDefNode* node = new ClassDefNode();
    node->type = _CLASS;
    node->fullId = id;
    node->modifiers = mods == nullptr ? new ModifiersNode() : mods;
    node->classParams = params;
    node->classTemplateOpt = body;
    node->primaryConstructModifier = ModifierNode::createModifier(_PUBLIC);
    return node;
}

ClassDefNode* ClassDefNode::createObjectDef(IdNode* id, ModifiersNode* mods,
                                            ClassTemplateOptNode* body) {
    ClassDefNode* node = new ClassDefNode();
    node->type = _OBJECT;
    node->fullId = id;
    node->modifiers = mods == nullptr ? new ModifiersNode() : mods;
    node->classTemplateOpt = body;
    return node;
}

std::string ClassDefNode::getDotLabel() const {
    const std::string prefix = type == _OBJECT ? "ObjectDef" : "ClassDef";
    return fullId == nullptr ? prefix : prefix + " [" + fullId->name + "]";
}

std::vector<Node*> ClassDefNode::getChildren() const {
    return {modifiers, primaryConstructModifier, fullId, classParams, classTemplateOpt};
}
