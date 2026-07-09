//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-alias-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTModuleListAliasItemNode::ASTModuleListAliasItemNode(std::shared_ptr<ASTModuleNameNode> moduleName, std::shared_ptr<ASTAsNode> asNode, std::shared_ptr<ASTModuleAliasNameNode> aliasModuleName) {
    _moduleName = moduleName;
    _asNode = asNode;
    _aliasModuleName = aliasModuleName;
    _children.push_back(_moduleName);
    _children.push_back(asNode);
    _children.push_back(_aliasModuleName);
}

std::shared_ptr<ASTModuleNameNode> ASTModuleListAliasItemNode::getModuleName() {
    return _moduleName;
}

std::shared_ptr<ASTModuleAliasNameNode> ASTModuleListAliasItemNode::getAliasModuleName() {
    return _aliasModuleName;
}

std::shared_ptr<Position> ASTModuleListAliasItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

std::shared_ptr<Position> ASTModuleListAliasItemNode::getEndPosition() {
    return _aliasModuleName->getEndPosition();
}

ASTNodeType ASTModuleListAliasItemNode::getNodeType() {
    return AST_MODULE_LIST_ALIAS_ITEM_NODE;
}

std::string ASTModuleListAliasItemNode::toString() {
    return "MODULE_LIST_ALIAS_ITEM";
}

bool ASTModuleListAliasItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleListAliasItemNode>(other);
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