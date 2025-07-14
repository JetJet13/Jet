//
// Created by Johny Georges on 2024-06-04.
//

#include "ast-use-many-by-wildcard-module-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTUseManyByWildcardModuleDeclarationNode::ASTUseManyByWildcardModuleDeclarationNode(ASTUseNode* useKeyword, ASTImportModuleListByWildcardItemNode* importModuleListByWildcardItemNode, ASTFromNode* fromKeyword, ASTImportPathNode* path) {
    _useKeyword = useKeyword;
    _importModuleListByWildcardItemNode = importModuleListByWildcardItemNode;
    _fromKeyword = fromKeyword;
    _path = path;
    _children.push_back(_useKeyword);
    _children.push_back(_importModuleListByWildcardItemNode);
    _children.push_back(_fromKeyword);
    _children.push_back(_path);
}

ASTImportModuleListByWildcardItemNode* ASTUseManyByWildcardModuleDeclarationNode::getImportModuleListByWildcardItemNode() {
    return _importModuleListByWildcardItemNode;
}

ASTImportPathNode* ASTUseManyByWildcardModuleDeclarationNode::getPath() {
    return _path;
}

Position* ASTUseManyByWildcardModuleDeclarationNode::getStartPosition() {
    return _useKeyword->getStartPosition();
}

Position* ASTUseManyByWildcardModuleDeclarationNode::getEndPosition() {
    return _path->getEndPosition();
}

ASTNodeType ASTUseManyByWildcardModuleDeclarationNode::getNodeType() {
    return AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE;
}

std::string ASTUseManyByWildcardModuleDeclarationNode::toString() {
    return "USE_MANY_BY_WILDCARD_MODULE_DECLARATION";
}

bool ASTUseManyByWildcardModuleDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUseManyByWildcardModuleDeclarationNode*)other;
    return this->getImportModuleListByWildcardItemNode()->isSameAs(otherNode->getImportModuleListByWildcardItemNode()) &&
           this->getPath()->isSameAs(otherNode->getPath());
}

void ASTUseManyByWildcardModuleDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _useKeyword->print();
    _importModuleListByWildcardItemNode->print();
    _fromKeyword->print();
    _path->print();
    Logger::log("----------");
}

std::string ASTUseManyByWildcardModuleDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_useKeyword)
    ->add(_importModuleListByWildcardItemNode)
    ->add(_fromKeyword)
    ->add(_path);
    return sourceCodeBuilder.build();
}