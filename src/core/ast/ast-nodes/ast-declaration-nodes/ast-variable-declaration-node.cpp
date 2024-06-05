//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-variable-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTVariableDeclarationNode::ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer) {
    _varInit = varInit;
    _initializer = initializer;
    _children.push_back(_varInit);
    _children.push_back(_initializer);
}

ASTVariableInitNode* ASTVariableDeclarationNode::getVarInitNode() {
    return _varInit;
}

ASTExpressionNode* ASTVariableDeclarationNode::getInitializerNode() {
    return _initializer;
}

void ASTVariableDeclarationNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTVariableDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTVariableDeclarationNode::getNodeType() {
    return AST_VARIABLE_DECLARATION_NODE;
}

std::string ASTVariableDeclarationNode::toString() {
    return "VARIABLE_DECLARATION";
}

bool ASTVariableDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableDeclarationNode*)other;
    return this->getVarInitNode()->isSameAs(otherNode->getVarInitNode()) &&
           this->getInitializerNode()->isSameAs(otherNode->getInitializerNode());
}

void ASTVariableDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _varInit->print();
    _initializer->print();
    Logger::log("----------");
}

std::string ASTVariableDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_varInit)
    ->addWithWhitespace(_initializer);
    return sourceCodeBuilder.build();
}