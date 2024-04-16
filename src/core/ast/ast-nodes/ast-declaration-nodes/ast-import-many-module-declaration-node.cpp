//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportManyModuleDeclarationNode::ASTImportManyModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportModuleListNode* importModuleList, ASTImportPathNode* path) {
    _moduleName = moduleName;
    _importModuleList = importModuleList;
    _path = path;
}

ASTImportModuleNameNode* ASTImportManyModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportModuleListNode* ASTImportManyModuleDeclarationNode::getModuleList() {
    return _importModuleList;
}

ASTImportPathNode* ASTImportManyModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTImportManyModuleDeclarationNode::getNodeType() {
    return AST_IMPORT_MANY_MODULE_DECLARATION_NODE;
}

std::string ASTImportManyModuleDeclarationNode::toString() {
    return "IMPORT_MANY_MODULE_DECLARATION";
}

bool ASTImportManyModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportManyModuleDeclarationNode*)other;

    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
           this->getModuleList()->isSameAs(otherNode->getModuleList()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTImportManyModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _importModuleList->print();
    _path->print();
    Logger::log("----------");
}