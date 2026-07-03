//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-many-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportManyModuleDeclarationNode::ASTImportManyModuleDeclarationNode(ASTImportNode* importKeyword, ASTImportModuleListByGroupItemNode* importModuleListByGroupItem, ASTFromNode* fromKeyword, ASTImportPathNode* path) {
    _importKeyword = importKeyword;
    _importModuleListByGroupItem = importModuleListByGroupItem;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_importKeyword);
    _children.push_back(_importModuleListByGroupItem);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

ASTImportModuleNameNode* ASTImportManyModuleDeclarationNode::getModuleName() {
    return _importModuleListByGroupItem->getModuleName();
}

ASTImportModuleListNode* ASTImportManyModuleDeclarationNode::getModuleList() {
    return _importModuleListByGroupItem->getModuleList();
}

ASTImportPathNode* ASTImportManyModuleDeclarationNode::getPath() {
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

bool ASTImportManyModuleDeclarationNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportManyModuleDeclarationNode*)other;

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