//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-variable-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForInVariableNode::ASTForInVariableNode(std::shared_ptr<ASTIdentifierExpressionNode> variable) {
    _variable = variable;
    _children.push_back(_variable);
    _id = _variable->getId();
}

void ASTForInVariableNode::markAsCaptured() {
    _captureCount++;
}

unsigned long ASTForInVariableNode::getCaptureCount() {
    return _captureCount;
}

bool ASTForInVariableNode::isCaptured() {
    return _captureCount > 0;
}

std::shared_ptr<ASTIdentifierExpressionNode> ASTForInVariableNode::getVariable() {
    return _variable;
}

void ASTForInVariableNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTForInVariableNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTForInVariableNode::getStartPosition() {
    return _variable->getStartPosition();
}

Position* ASTForInVariableNode::getEndPosition() {
    return _variable->getEndPosition();
}

ASTNodeType ASTForInVariableNode::getNodeType() {
    return AST_FOR_IN_VARIABLE_NODE;
}

std::string ASTForInVariableNode::toString() {
    return "FOR_IN_VARIABLE";
}

bool ASTForInVariableNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTForInVariableNode>(other);
    return this->getVariable()->isSameAs(otherNode->getVariable());
}

void ASTForInVariableNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    Logger::log("----------");
}

std::string ASTForInVariableNode::toSourceCode() {
    return _variable->toSourceCode();
}