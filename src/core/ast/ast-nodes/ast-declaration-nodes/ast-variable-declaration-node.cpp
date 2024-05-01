//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-variable-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTVariableDeclarationNode::ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer, TypeSignature* typeSignature) {
    _varInit = varInit;
    _initializer = initializer;
    _typeSignature = typeSignature;
}

ASTVariableInitNode* ASTVariableDeclarationNode::getVarInitNode() {
    return _varInit;
}

ASTExpressionNode* ASTVariableDeclarationNode::getInitializerNode() {
    return _initializer;
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
           this->getInitializerNode()->isSameAs(otherNode->getInitializerNode()) &&
           this->getTypeSignature()->isEqualTo(otherNode->getTypeSignature());
}

void ASTVariableDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _varInit->print();
    _initializer->print();
    _typeSignature->print();
    Logger::log("----------");
}