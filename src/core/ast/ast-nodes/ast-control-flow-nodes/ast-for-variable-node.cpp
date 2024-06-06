//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-variable-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForVariableNode::ASTForVariableNode(ASTIdentifierExpressionNode* variable) {
    _variable = variable;
    _children.push_back(_variable);
}

ASTIdentifierExpressionNode* ASTForVariableNode::getVariable() {
    return _variable;
}

void ASTForVariableNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTForVariableNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTForVariableNode::getStartPosition() {
    return _variable->getStartPosition();
}

Position* ASTForVariableNode::getEndPosition() {
    return _variable->getEndPosition();
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

std::string ASTForVariableNode::toSourceCode() {
    return _variable->toSourceCode();
}