#ifndef SCALA_NODES_IMPORTNODES_H
#define SCALA_NODES_IMPORTNODES_H

#include "../Node.h"
#include "../id/IdNode.h"

#include <vector>

class PathNode : public Node {
public:
    std::vector<IdNode*> parts;

    PathNode() : Node("Path") {}

    static PathNode* addPart(PathNode* path, IdNode* part);
    std::string getDotLabel() const override;
    std::vector<Node*> getChildren() const override;
};

class ImportNode : public Node {
public:
    PathNode* path = nullptr;

    ImportNode() : Node("Import") {}

    static ImportNode* createImport(PathNode* importedPath);
    std::vector<Node*> getChildren() const override;
};

#endif
