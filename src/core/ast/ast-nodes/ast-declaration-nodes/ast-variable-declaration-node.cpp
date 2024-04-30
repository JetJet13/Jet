//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-variable-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTVariableDeclarationNode::ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer) {
    _varInit = varInit;
    _initializer = initializer;
    _type = varInit->getTypeNode().value_or(initializer.getType());
}

ASTVariableInitNode* ASTVariableDeclarationNode::getVarInitNode() {
    return _varInit;
}

ASTExpressionNode* ASTVariableDeclarationNode::getInitializerNode() {
    return _initializer;
}

ASTTypeNode* ASTVariableDeclarationNode::getTypeNode() {
    return _type;
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
           this->getTypeNode()->isSameAs(otherNode->getTypeNode());
}

void ASTVariableDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _varInit->print();
    _initializer->print();
    _type->print();
    Logger::log("----------");
}