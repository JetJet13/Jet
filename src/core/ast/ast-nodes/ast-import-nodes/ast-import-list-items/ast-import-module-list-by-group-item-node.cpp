//
// Created by Johny Georges on 2024-04-16.
//

#include "ast-import-module-list-by-group-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListByGroupItemNode::ASTImportModuleListByGroupItemNode(ASTImportModuleNameNode* moduleName, ASTModuleAccessNode* moduleAccessNode, ASTImportModuleListNode* importModuleList) {
    _moduleName = moduleName;
    _moduleAccessNode = moduleAccessNode;
    _importModuleList = importModuleList;
    _children.push_back(_moduleName);
    _children.push_back(_importModuleList);
}

ASTImportModuleNameNode* ASTImportModuleListByGroupItemNode::getModuleName() {
    return _moduleName;
}

ASTImportModuleListNode* ASTImportModuleListByGroupItemNode::getModuleList() {
    return _importModuleList;
}

Position* ASTImportModuleListByGroupItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

Position* ASTImportModuleListByGroupItemNode::getEndPosition() {
    return _importModuleList->getEndPosition();
}

ASTNodeType ASTImportModuleListByGroupItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE;
}

std::string ASTImportModuleListByGroupItemNode::toString() {
    return "IMPORT_MODULE_LIST_BY_GROUP_ITEM";
}

bool ASTImportModuleListByGroupItemNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportModuleListByGroupItemNode*)other;

    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
           this->getModuleList()->isSameAs(otherNode->getModuleList());
}

void ASTImportModuleListByGroupItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _importModuleList->print();
    Logger::log("----------");
}

std::string ASTImportModuleListByGroupItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_moduleAccessNode)
    ->add(_importModuleList);
    return sourceCodeBuilder.build();
}