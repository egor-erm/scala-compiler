#ifndef SCALA_NODES_OPERATORNODE_H
#define SCALA_NODES_OPERATORNODE_H

#include "../Node.h"

#include <string>
#include <utility>

class OperatorNode : public Node {
public:
    std::string op;

    explicit OperatorNode(std::string value) : Node("Operator"), op(std::move(value)) {}

    static OperatorNode* createOperator(const std::string& op) { return new OperatorNode(op); }

    std::string getDotLabel() const override { return "Operator [" + op + "]"; }
};

#endif
