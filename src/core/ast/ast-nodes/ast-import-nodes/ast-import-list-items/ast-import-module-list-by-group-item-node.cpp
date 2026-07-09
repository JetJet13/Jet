//
// Created by Johny Georges on 2024-04-16.
//

#include "ast-import-module-list-by-group-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListByGroupItemNode::ASTImportModuleListByGroupItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTModuleAccessNode> moduleAccessNode, std::shared_ptr<ASTImportModuleListNode> importModuleList) {
    _moduleName = moduleName;
    _moduleAccessNode = moduleAccessNode;
    _importModuleList = importModuleList;
    _children.push_back(_moduleName);
    _children.push_back(_importModuleList);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportModuleListByGroupItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<ASTImportModuleListNode> ASTImportModuleListByGroupItemNode::getModuleList() {
    return _importModuleList;
}

std::shared_ptr<Position> ASTImportModuleListByGroupItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

std::shared_ptr<Position> ASTImportModuleListByGroupItemNode::getEndPosition() {
    return _importModuleList->getEndPosition();
}

ASTNodeType ASTImportModuleListByGroupItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE;
}

std::string ASTImportModuleListByGroupItemNode::toString() {
    return "IMPORT_MODULE_LIST_BY_GROUP_ITEM";
}

bool ASTImportModuleListByGroupItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListByGroupItemNode>(other);

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