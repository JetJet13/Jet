//
// Created by Johny Georges on 2024-04-15.
//

#include "ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListByWildcardItemNode::ASTImportModuleListByWildcardItemNode(ASTImportModuleNameNode* moduleName, ASTModuleAccessNode* moduleAccessNode, ASTImportWildcardNode* wildcard) {
    _moduleName = moduleName;
    _moduleAccessNode = moduleAccessNode;
    _wildcard = wildcard;
    _children.push_back(_moduleName);
    _children.push_back(_moduleAccessNode);
    _children.push_back(_wildcard);
}

ASTImportModuleNameNode* ASTImportModuleListByWildcardItemNode::getModuleName() {
    return _moduleName;
}

ASTImportWildcardNode* ASTImportModuleListByWildcardItemNode::getWildcard() {
    return _wildcard;
}

Position* ASTImportModuleListByWildcardItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

Position* ASTImportModuleListByWildcardItemNode::getEndPosition() {
    return _wildcard->getEndPosition();
}

ASTNodeType ASTImportModuleListByWildcardItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE;
}

std::string ASTImportModuleListByWildcardItemNode::toString() {
    return "IMPORT_MODULE_LIST_BY_WILDCARD_ITEM";
}

bool ASTImportModuleListByWildcardItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListByWildcardItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
           this->getWildcard()->isSameAs(otherNode->getWildcard());
}

void ASTImportModuleListByWildcardItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _wildcard->print();
    Logger::log("----------");
}

std::string ASTImportModuleListByWildcardItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_moduleAccessNode)
    ->add(_wildcard);
    return sourceCodeBuilder.build();
}