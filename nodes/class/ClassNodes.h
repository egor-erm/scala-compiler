#ifndef SCALA_NODES_CLASSNODES_H
#define SCALA_NODES_CLASSNODES_H

#include "../Node.h"
#include "../Types.h"
#include "../exprs/ExprNodes.h"
#include "../id/IdNode.h"
#include "../modifier/ModifierNodes.h"
#include "../templates/TemplateNodes.h"
#include "../type/SimpleTypeNode.h"

#include <vector>

class ClassParamNode : public Node {
public:
    ClassParamType type = _UNMARKED_CLASS_PARAM;
    ModifiersNode* modifiers = nullptr;
    IdNode* fullId = nullptr;
    SimpleTypeNode* simpleType = nullptr;

    ClassParamNode() : Node("ClassParam") {}

    static ClassParamNode* createClassParam(ClassParamType type, ModifiersNode* modifiers,
                                            IdNode* id, SimpleTypeNode* simpleType);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class ClassParamsNode : public Node {
public:
    std::vector<ClassParamNode*> classParams;

    ClassParamsNode() : Node("ClassParams") {}

    static ClassParamsNode* addClassParamToList(ClassParamsNode* list, ClassParamNode* param);
    std::vector<Node*> getChildren() const override;
};

class ExtensionClassTemplateNode : public Node {
public:
    ClassExtensionTemplateType type = _EXTEND_WITH_BODY;
    IdNode* fullId = nullptr;
    ArgumentExprsNode* argumentExprs = nullptr;
    TemplateStmtsNode* templateStmts = nullptr;

    ExtensionClassTemplateNode() : Node("ExtensionClassTemplate") {}

    static ExtensionClassTemplateNode* createExtendWithConstrAndBody(IdNode* id,
                                                                     ArgumentExprsNode* args,
                                                                     TemplateStmtsNode* body);
    static ExtensionClassTemplateNode* createExtendWithBody(IdNode* id,
                                                            TemplateStmtsNode* body);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class ClassTemplateOptNode : public Node {
public:
    ExtensionClassTemplateNode* extensionPartClassTemplate = nullptr;
    TemplateStmtsNode* templateStmts = nullptr;
    ModifiersNode* modifiers = nullptr;

    ClassTemplateOptNode() : Node("ClassTemplateOpt") {}

    static ClassTemplateOptNode* createClassWithInherit(ExtensionClassTemplateNode* extension);
    static ClassTemplateOptNode* createClassWithoutInherit(TemplateStmtsNode* body);
    std::vector<Node*> getChildren() const override;
};

class ClassDefNode : public Node {
public:
    IdNode* fullId = nullptr;
    ModifiersNode* modifiers = nullptr;
    ModifierNode* primaryConstructModifier = nullptr;
    ClassParamsNode* classParams = nullptr;
    ClassTemplateOptNode* classTemplateOpt = nullptr;
    StmtType type = _CLASS;

    ClassDefNode() : Node("ClassDef") {}

    static ClassDefNode* createClassDef(IdNode* id, ModifiersNode* modifiers,
                                        ClassParamsNode* params, ClassTemplateOptNode* body);
    static ClassDefNode* createObjectDef(IdNode* id, ModifiersNode* modifiers,
                                         ClassTemplateOptNode* body);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

#endif
