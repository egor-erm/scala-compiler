#include "Node.h"

#include <sstream>
#include <utility>

unsigned int Node::seqId = 0;

Node::Node(std::string name)
    : id(++seqId), nodeName(std::move(name)) {}

Node::~Node() = default;

std::string Node::escapeDot(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (unsigned char c : text) {
        switch (c) {
            case '\\': result += "\\\\"; break;
            case '"': result += "\\\""; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default:
                result += c < 0x20 ? ' ' : static_cast<char>(c);
        }
    }
    return result;
}

void Node::addDotNode(std::string& dot) const {
    std::ostringstream out;
    out << id << " [label=\"" << escapeDot(getDotLabel()) << "\"];\n";
    dot += out.str();
}

void Node::addDotChild(std::string& dot, const Node* child, const std::string& arrowLabel) const {
    if (child == nullptr) {
        return;
    }
    std::ostringstream out;
    out << id << " -> " << child->id;
    if (!arrowLabel.empty()) {
        out << " [label=\"" << escapeDot(arrowLabel) << "\"]";
    }
    out << ";\n";
    dot += out.str();
    dot += child->toDot();
}

std::string Node::toDot() const {
    std::string dot;
    addDotNode(dot);
    for (Node* child : getChildren()) {
        addDotChild(dot, child);
    }
    return dot;
}

std::string Node::getDotLabel() const {
    return nodeName;
}

std::vector<Node*> Node::getChildren() const {
    return {};
}

std::string createDotTree(const Node* root) {
    if (root == nullptr) {
        return "digraph AST {\n}\n";
    }
    return "digraph AST {\n" + root->toDot() + "}\n";
}

void deleteNodeTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    for (Node* child : root->getChildren()) {
        deleteNodeTree(child);
    }
    delete root;
}
