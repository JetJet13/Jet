//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-package-path-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTPackagePathNode::ASTPackagePathNode(ASTStringLiteralNode* packagePath) {
    _packagePath = packagePath;
    _children.push_back(_packagePath);
}

ASTStringLiteralNode* ASTPackagePathNode::getPackagePath() {
    return _packagePath;
}

Position* ASTPackagePathNode::getStartPosition() {
    return _packagePath->getStartPosition();
}

Position* ASTPackagePathNode::getEndPosition() {
    return _packagePath->getEndPosition();
}

ASTNodeType ASTPackagePathNode::getNodeType() {
    return AST_PACKAGE_PATH_NODE;
}

std::string ASTPackagePathNode::toString() {
    return "PACKAGE_PATH";
}

bool ASTPackagePathNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTPackagePathNode*)other;
    return this->getPackagePath()->isSameAs(otherNode->getPackagePath());
}

void ASTPackagePathNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _packagePath->print();
    Logger::log("----------");
}

std::string ASTPackagePathNode::toSourceCode() {
    return _packagePath->toSourceCode();
}