//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTUseManyModuleDeclarationNode::ASTUseManyModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportModuleListNode* importModuleList, ASTImportPathNode* path) {
    _moduleName = moduleName;
    _importModuleList = importModuleList;
    _path = path;
    _children.push_back(_moduleName);
    _children.push_back(_importModuleList);
    _children.push_back(_path);
}

ASTImportModuleNameNode* ASTUseManyModuleDeclarationNode::getModuleName() {
    return _moduleName;
}

ASTImportModuleListNode* ASTUseManyModuleDeclarationNode::getModuleList() {
    return _importModuleList;
}

ASTImportPathNode* ASTUseManyModuleDeclarationNode::getPath() {
    return _path;
}

ASTNodeType ASTUseManyModuleDeclarationNode::getNodeType() {
    return AST_USE_MANY_MODULE_DECLARATION_NODE;
}

std::string ASTUseManyModuleDeclarationNode::toString() {
    return "USE_MANY_MODULE_DECLARATION";
}

bool ASTUseManyModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUseManyModuleDeclarationNode*)other;

    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
           this->getModuleList()->isSameAs(otherNode->getModuleList()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseManyModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _importModuleList->print();
    _path->print();
    Logger::log("----------");
}