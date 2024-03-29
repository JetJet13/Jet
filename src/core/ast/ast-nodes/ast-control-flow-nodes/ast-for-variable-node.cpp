//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-variable-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForVariableNode::ASTForVariableNode(ASTIdentifierExpressionNode* variable) {
    _variable = variable;
}

ASTIdentifierExpressionNode* ASTForVariableNode::getVariable() {
    return _variable;
}

ASTNodeType ASTForVariableNode::getNodeType() {
    return AST_FOR_VARIABLE_NODE;
}

std::string ASTForVariableNode::toString() {
    return "FOR_VARIABLE";
}

bool ASTForVariableNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTForVariableNode*)other;
    return this->getVariable()->isSameAs(otherNode->getVariable());
}

void ASTForVariableNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    Logger::log("----------");
}