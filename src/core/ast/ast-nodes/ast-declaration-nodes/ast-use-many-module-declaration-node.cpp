//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseManyModuleDeclarationNode::ASTUseManyModuleDeclarationNode(std::shared_ptr<ASTUseNode> useKeyword, std::shared_ptr<ASTImportModuleListByGroupItemNode> importModuleListByGroupItem, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path) {
    _useKeyword = useKeyword;
    _importModuleListByGroupItem = importModuleListByGroupItem;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_useKeyword);
    _children.push_back(_importModuleListByGroupItem);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

std::shared_ptr<ASTImportModuleListByGroupItemNode> ASTUseManyModuleDeclarationNode::getImportModuleListByGroupItem() {
    return _importModuleListByGroupItem;
}

std::shared_ptr<ASTImportModuleNameNode> ASTUseManyModuleDeclarationNode::getModuleName() {
    return _importModuleListByGroupItem->getModuleName();
}

std::shared_ptr<ASTImportModuleListNode> ASTUseManyModuleDeclarationNode::getModuleList() {
    return _importModuleListByGroupItem->getModuleList();
}

std::shared_ptr<ASTImportPathNode> ASTUseManyModuleDeclarationNode::getPath() {
    return _path;
}

Position* ASTUseManyModuleDeclarationNode::getStartPosition() {
    return _useKeyword->getStartPosition();
}

Position* ASTUseManyModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTUseManyModuleDeclarationNode::getNodeType() {
    return AST_USE_MANY_MODULE_DECLARATION_NODE;
}

std::string ASTUseManyModuleDeclarationNode::toString() {
    return "USE_MANY_MODULE_DECLARATION";
}

bool ASTUseManyModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTUseManyModuleDeclarationNode>(other);
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
    ->add(_importModuleListByGroupItem)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}