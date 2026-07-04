//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-normal-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListNormalItemNode::ASTImportModuleListNormalItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName) {
    _moduleName = moduleName;
    _children.push_back(_moduleName);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportModuleListNormalItemNode::getModuleName() {
    return _moduleName;
}

Position* ASTImportModuleListNormalItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

Position* ASTImportModuleListNormalItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTImportModuleListNormalItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE;
}

std::string ASTImportModuleListNormalItemNode::toString() {
    return "IMPORT_MODULE_LIST_NORMAL_ITEM";
}

bool ASTImportModuleListNormalItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListNormalItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTImportModuleListNormalItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTImportModuleListNormalItemNode::toSourceCode() {
    return _moduleName->toSourceCode();
}