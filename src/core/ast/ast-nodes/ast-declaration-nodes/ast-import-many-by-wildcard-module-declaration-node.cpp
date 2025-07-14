//
// Created by Johny Georges on 2024-06-01.
//

#include "ast-import-many-by-wildcard-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportManyByWildcardModuleDeclarationNode::ASTImportManyByWildcardModuleDeclarationNode(ASTImportNode* importKeyword, ASTImportModuleListByWildcardItemNode* importModuleListByWildcardItemNode, ASTFromNode* fromKeyword, ASTImportPathNode* path) {
    _importKeyword = importKeyword;
    _importModuleListByWildcardItemNode = importModuleListByWildcardItemNode;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(importKeyword);
    _children.push_back(importModuleListByWildcardItemNode);
    _children.push_back(fromKeyword);
    _children.push_back(_path);
}

ASTImportModuleListByWildcardItemNode* ASTImportManyByWildcardModuleDeclarationNode::getImportModuleListByWildcardItemNode() {
    return _importModuleListByWildcardItemNode;
}

ASTImportPathNode* ASTImportManyByWildcardModuleDeclarationNode::getPath() {
    return _path;
}

Position* ASTImportManyByWildcardModuleDeclarationNode::getStartPosition() {
    return _importKeyword->getStartPosition();
}

Position* ASTImportManyByWildcardModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTImportManyByWildcardModuleDeclarationNode::getNodeType() {
    return AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE;
}

std::string ASTImportManyByWildcardModuleDeclarationNode::toString() {
    return "IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION";
}

bool ASTImportManyByWildcardModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportManyByWildcardModuleDeclarationNode*)other;

    return this->getImportModuleListByWildcardItemNode()->isSameAs(otherNode->getImportModuleListByWildcardItemNode()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTImportManyByWildcardModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _importModuleListByWildcardItemNode->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTImportManyByWildcardModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_importKeyword)
    ->add(_importModuleListByWildcardItemNode)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}