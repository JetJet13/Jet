//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-variable-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTVariableAssignmentNode::ASTVariableAssignmentNode(ASTIdentifierNode* astIdentifierNode) {
    _identifier = astIdentifierNode;
    _children.push_back(_identifier);
}

ASTIdentifierNode* ASTVariableAssignmentNode::getIdentifierNode() {
    return _identifier;
}

void ASTVariableAssignmentNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTVariableAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTVariableAssignmentNode::getNodeType() {
    return AST_VARIABLE_ASSIGNMENT_NODE;
}

std::string ASTVariableAssignmentNode::toString() {
    return "VARIABLE_ASSIGNMENT";
}

bool ASTVariableAssignmentNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableAssignmentNode*)other;
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}