//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-package-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTPackageManyModuleDeclarationNode::ASTPackageManyModuleDeclarationNode(ASTImportModuleListNode* importModuleList, ASTImportPathNode* path) {
    _importModuleList = importModuleList;
    _path = path;
}

ASTImportModuleListNode* ASTPackageManyModuleDeclarationNode::getModuleList() {
    return _importModuleList;
}

ASTImportPathNode* ASTPackageManyModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTPackageManyModuleDeclarationNode::getNodeType() {
    return AST_PACKAGE_MANY_MODULE_DECLARATION_NODE;
}

std::string ASTPackageManyModuleDeclarationNode::toString() {
    return "PACKAGE_MANY_MODULE_DECLARATION";
}

bool ASTPackageManyModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTPackageManyModuleDeclarationNode*)other;

    return  this->getModuleList()->isSameAs(otherNode->getModuleList()) &&
            this->getPath()->isSameAs(otherNode->getPath());
}

void ASTPackageManyModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importModuleList->print();
    _path->print();
    Logger::log("----------");
}