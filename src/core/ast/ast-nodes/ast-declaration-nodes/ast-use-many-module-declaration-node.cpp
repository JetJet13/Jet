//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseManyModuleDeclarationNode::ASTUseManyModuleDeclarationNode(ASTUseNode* useKeyword, ASTImportModuleListByGroupItemNode* importModuleListByGroupItem, ASTFromNode* fromKeyword, ASTImportPathNode* path) {
    _useKeyword = useKeyword;
    _importModuleListByGroupItem = importModuleListByGroupItem;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_useKeyword);
    _children.push_back(_importModuleListByGroupItem);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

ASTImportModuleListByGroupItemNode* ASTUseManyModuleDeclarationNode::getImportModuleListByGroupItem() {
    return _importModuleListByGroupItem;
}

ASTImportModuleNameNode* ASTUseManyModuleDeclarationNode::getModuleName() {
    return _importModuleListByGroupItem->getModuleName();
}

ASTImportModuleListNode* ASTUseManyModuleDeclarationNode::getModuleList() {
    return _importModuleListByGroupItem->getModuleList();
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
    return this->getImportModuleListByGroupItem()->isSameAs(otherNode->getImportModuleListByGroupItem()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseManyModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importModuleListByGroupItem->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTUseManyModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_useKeyword)
    ->addWithWhitespace(_importModuleListByGroupItem)
    ->addWithWhitespace(_fromKeyword)
    ->addWithWhitespace(_path);
    return sourceCodeBuilder.build();
}