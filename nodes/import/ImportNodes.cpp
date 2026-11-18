#include "ImportNodes.h"

PathNode* PathNode::addPart(PathNode* path, IdNode* part) {
    if (path == nullptr) path = new PathNode();
    if (part != nullptr) path->parts.push_back(part);
    return path;
}

std::string PathNode::getDotLabel() const {
    std::string result = "Path [";
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i != 0) result += ".";
        result += parts[i]->name;
    }
    return result + "]";
}

std::vector<Node*> PathNode::getChildren() const {
    std::vector<Node*> children;
    for (IdNode* part : parts) children.push_back(part);
    return children;
}

ImportNode* ImportNode::createImport(PathNode* importedPath) {
    ImportNode* node = new ImportNode();
    node->path = importedPath;
    return node;
}

std::vector<Node*> ImportNode::getChildren() const {
    return {path};
}
