#ifndef SCALA_NODES_IDNODE_H
#define SCALA_NODES_IDNODE_H

#include "../Node.h"

#include <string>
#include <utility>

class IdNode : public Node {
public:
    std::string name;

    explicit IdNode(std::string value) : Node("Id"), name(std::move(value)) {}

    static IdNode* createId(const std::string& name) { return new IdNode(name); }

    std::string getDotLabel() const override { return "Id [" + name + "]"; }
};

#endif
