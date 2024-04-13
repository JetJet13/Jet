//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-single-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportSingleModuleDeclarationNode::ASTImportSingleModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportPathNode* path) {
    _moduleName = moduleName;
    _path = path;
}

ASTImportModuleNameNode* ASTImportSingleModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportPathNode* ASTImportSingleModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTImportSingleModuleDeclarationNode::getNodeType() {
    return AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE;
}

std::string ASTImportSingleModuleDeclarationNode::toString() {
    return "IMPORT_SINGLE_MODULE_DECLARATION";
}

bool ASTImportSingleModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportSingleModuleDeclarationNode*)other;

    return  this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getPath()->isSameAs(otherNode->getPath());
}

void ASTImportSingleModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _path->print();
    Logger::log("----------");
}