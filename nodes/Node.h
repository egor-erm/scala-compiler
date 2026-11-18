#ifndef SCALA_NODES_NODE_H
#define SCALA_NODES_NODE_H

#include <string>
#include <vector>

class Node {
private:
    static unsigned int seqId;

protected:
    void addDotNode(std::string& dot) const;
    void addDotChild(std::string& dot, const Node* child, const std::string& arrowLabel = "") const;
    static std::string escapeDot(const std::string& text);

public:
    const unsigned int id;
    std::string nodeName;

    explicit Node(std::string name);
    virtual ~Node();

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;

    virtual std::string toDot() const;
    virtual std::string getDotLabel() const;
    virtual std::vector<Node*> getChildren() const;
};

std::string createDotTree(const Node* root);
void deleteNodeTree(Node* root);

#endif
