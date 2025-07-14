//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-alias-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTModuleListAliasItemNode::ASTModuleListAliasItemNode(ASTModuleNameNode* moduleName, ASTAsNode* asNode, ASTModuleAliasNameNode* aliasModuleName) {
    _moduleName = moduleName;
    _asNode = asNode;
    _aliasModuleName = aliasModuleName;
    _children.push_back(_moduleName);
    _children.push_back(asNode);
    _children.push_back(_aliasModuleName);
}

ASTModuleNameNode* ASTModuleListAliasItemNode::getModuleName() {
    return _moduleName;
}

ASTModuleAliasNameNode* ASTModuleListAliasItemNode::getAliasModuleName() {
    return _aliasModuleName;
}

Position* ASTModuleListAliasItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

Position* ASTModuleListAliasItemNode::getEndPosition() {
    return _aliasModuleName->getEndPosition();
}

ASTNodeType ASTModuleListAliasItemNode::getNodeType() {
    return AST_MODULE_LIST_ALIAS_ITEM_NODE;
}

std::string ASTModuleListAliasItemNode::toString() {
    return "MODULE_LIST_ALIAS_ITEM";
}

bool ASTModuleListAliasItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListAliasItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getAliasModuleName()->isSameAs(otherNode->getAliasModuleName()) ;
}

void ASTModuleListAliasItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _aliasModuleName->print();
    Logger::log("----------");
}

std::string ASTModuleListAliasItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_asNode)
    ->add(_aliasModuleName);
    return sourceCodeBuilder.build();
}