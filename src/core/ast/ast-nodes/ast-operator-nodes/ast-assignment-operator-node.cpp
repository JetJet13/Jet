//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-assignment-operator-node.h"

ASTAssignmentOperatorNode::ASTAssignmentOperatorNode(Lexeme *lexeme) {
    _assignment = lexeme;
}

Lexeme* ASTAssignmentOperatorNode::getAssignmentOperator() {
    return _assignment;
}

ASTNodeType ASTAssignmentOperatorNode::getNodeType() {
    return AST_ASSIGNMENT_OPERATOR_NODE;
}

std::string ASTAssignmentOperatorNode::toString() {
    return "ASSIGNMENT_OPERATOR";
}

bool ASTAssignmentOperatorNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTAssignmentOperatorNode*)other;
    return this->getAssignmentOperator()->isEqual(otherNode->getAssignmentOperator());
}