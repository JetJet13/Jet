//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-path-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportPathNode::ASTImportPathNode(ASTStringLiteralNode* importPath) {
    _importPath = importPath;
}

ASTStringLiteralNode* ASTImportPathNode::getImportPath() {
    return _importPath;
}

ASTNodeType ASTImportPathNode::getNodeType() {
    return AST_IMPORT_PATH_NODE;
}

std::string ASTImportPathNode::toString() {
    return "IMPORT_PATH";
}

bool ASTImportPathNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportPathNode*)other;
    return this->getImportPath()->isSameAs(otherNode->getImportPath());
}

void ASTImportPathNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importPath->print();
    Logger::log("----------");
}