//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTUseSingleModuleDeclarationNode::ASTUseSingleModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportPathNode* path) {
    _moduleName = moduleName;
    _path = path;
}

ASTImportModuleNameNode* ASTUseSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportPathNode* ASTUseSingleModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTUseSingleModuleDeclarationNode::getNodeType() {
    return AST_USE_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTUseSingleModuleDeclarationNode::toString() {
    return "USE_SINGLE_MODULE_DECLARATION";
}

bool ASTUseSingleModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUseSingleModuleDeclarationNode*)other;

    return  this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseSingleModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _path->print();
    Logger::log("----------");
}