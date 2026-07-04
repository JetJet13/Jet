//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportManyModuleDeclarationNode::ASTImportManyModuleDeclarationNode(std::shared_ptr<ASTImportNode> importKeyword, std::shared_ptr<ASTImportModuleListByGroupItemNode> importModuleListByGroupItem, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path) {
    _importKeyword = importKeyword;
    _importModuleListByGroupItem = importModuleListByGroupItem;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_importKeyword);
    _children.push_back(_importModuleListByGroupItem);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

std::shared_ptr<ASTImportModuleNameNode> ASTImportManyModuleDeclarationNode::getModuleName() {
    return _importModuleListByGroupItem->getModuleName();
}

std::shared_ptr<ASTImportModuleListNode> ASTImportManyModuleDeclarationNode::getModuleList() {
    return _importModuleListByGroupItem->getModuleList();
}

std::shared_ptr<ASTImportPathNode> ASTImportManyModuleDeclarationNode::getPath() {
    return _path;
}

Position* ASTImportManyModuleDeclarationNode::getStartPosition() {
    return _importKeyword->getStartPosition();
}

Position* ASTImportManyModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTImportManyModuleDeclarationNode::getNodeType() {
    return AST_IMPORT_MANY_MODULE_DECLARATION_NODE;
}

std::string ASTImportManyModuleDeclarationNode::toString() {
    return "IMPORT_MANY_MODULE_DECLARATION";
}

bool ASTImportManyModuleDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportManyModuleDeclarationNode>(other);

    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
           this->getModuleList()->isSameAs(otherNode->getModuleList()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTImportManyModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importModuleListByGroupItem->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTImportManyModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_importKeyword)
    ->add(_importModuleListByGroupItem)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}