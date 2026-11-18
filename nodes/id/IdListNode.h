#ifndef SCALA_NODES_IDLISTNODE_H
#define SCALA_NODES_IDLISTNODE_H

#include "../Node.h"
#include "IdNode.h"

#include <vector>

class IdListNode : public Node {
public:
    std::vector<IdNode*> ids;

    IdListNode() : Node("IdList") {}

    static IdListNode* addId(IdListNode* list, IdNode* id) {
        if (list == nullptr) list = new IdListNode();
        if (id != nullptr) list->ids.push_back(id);
        return list;
    }

    std::vector<Node*> getChildren() const override {
        std::vector<Node*> children;
        for (IdNode* id : ids) children.push_back(id);
        return children;
    }
};

#endif
