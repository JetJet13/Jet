//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-variable-declaration-node.h"
#include "ast-variable-init-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTVariableDeclarationNode::ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer) {
    _varInit = varInit;
    _initializer = initializer;
}

ASTVariableInitNode* ASTVariableDeclarationNode::getVarInitNode() {
    return _varInit;
}

ASTExpressionNode* ASTVariableDeclarationNode::getInitializerNode() {
    return _initializer;
}

ASTNodeType ASTVariableDeclarationNode::getNodeType() {
    return AST_VARIABLE_DECLARATION_NODE;
}

std::string ASTVariableDeclarationNode::toString() {
    return "VARIABLE_DECLARATION";
}

bool ASTVariableDeclarationNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    Logger::log("ASTVariableDeclarationNode", "other node is same type");
    auto otherNode = (ASTVariableDeclarationNode*)other;
    return this->getVarInitNode()->isEqual(otherNode->getVarInitNode()) &&
           this->getInitializerNode()->isEqual(otherNode->getInitializerNode());
}
