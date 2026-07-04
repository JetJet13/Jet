//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-path-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportPathNode::ASTImportPathNode(std::shared_ptr<ASTStringLiteralNode> importPath) {
    _importPath = importPath;
    _children.push_back(_importPath);
}

std::shared_ptr<ASTStringLiteralNode> ASTImportPathNode::getImportPath() {
    return _importPath;
}

Position* ASTImportPathNode::getStartPosition() {
    return _importPath->getStartPosition();
}

Position* ASTImportPathNode::getEndPosition() {
    return _importPath->getEndPosition();
}

ASTNodeType ASTImportPathNode::getNodeType() {
    return AST_IMPORT_PATH_NODE;
}

std::string ASTImportPathNode::toString() {
    return "IMPORT_PATH";
}

bool ASTImportPathNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportPathNode>(other);
    return this->getImportPath()->isSameAs(otherNode->getImportPath());
}

void ASTImportPathNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importPath->print();
    Logger::log("----------");
}

std::string ASTImportPathNode::toSourceCode() {
    return _importPath->toSourceCode();
}