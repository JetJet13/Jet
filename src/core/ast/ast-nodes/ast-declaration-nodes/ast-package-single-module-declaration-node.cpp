//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-package-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTPackageSingleModuleDeclarationNode::ASTPackageSingleModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportPathNode* path) {
    _moduleName = moduleName;
    _path = path;
}

ASTImportModuleNameNode* ASTPackageSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportPathNode* ASTPackageSingleModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTPackageSingleModuleDeclarationNode::getNodeType() {
    return AST_PACKAGE_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTPackageSingleModuleDeclarationNode::toString() {
    return "PACKAGE_SINGLE_MODULE_DECLARATION";
}

bool ASTPackageSingleModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTPackageSingleModuleDeclarationNode*)other;

    return  this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getPath()->isSameAs(otherNode->getPath());
}

void ASTPackageSingleModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _path->print();
    Logger::log("----------");
}