//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-alias-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListAliasItemNode::ASTImportModuleListAliasItemNode(ASTImportModuleNameNode* moduleName, ASTAsNode* asKeyword, ASTImportModuleAliasNameNode* aliasModuleName) {
    _moduleName = moduleName;
    _asKeyword = asKeyword;
    _aliasModuleName = aliasModuleName;
    _children.push_back(_moduleName);
    _children.push_back(_asKeyword);
    _children.push_back(_aliasModuleName);
}

ASTImportModuleNameNode* ASTImportModuleListAliasItemNode::getModuleName() {
    return _moduleName;
}

ASTImportModuleAliasNameNode* ASTImportModuleListAliasItemNode::getAliasModuleName() {
    return _aliasModuleName;
}

Position* ASTImportModuleListAliasItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

Position* ASTImportModuleListAliasItemNode::getEndPosition() {
    return _aliasModuleName->getEndPosition();
}

ASTNodeType ASTImportModuleListAliasItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE;
}

std::string ASTImportModuleListAliasItemNode::toString() {
    return "IMPORT_MODULE_LIST_ALIAS_ITEM";
}

bool ASTImportModuleListAliasItemNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListAliasItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getAliasModuleName()->isSameAs(otherNode->getAliasModuleName()) ;
}

void ASTImportModuleListAliasItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _aliasModuleName->print();
    Logger::log("----------");
}

std::string ASTImportModuleListAliasItemNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleName)
    ->add(_asKeyword)
    ->add(_aliasModuleName);
    return sourceCodeBuilder.build();
}