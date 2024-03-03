//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-assignment-operator-node.h"
#include "../../../../shared/utils/logger/logger.h"

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

bool ASTAssignmentOperatorNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTAssignmentOperatorNode*)other;
    return this->getAssignmentOperator()->hasSameSymbolTypeAs(otherNode->getAssignmentOperator());
}

void ASTAssignmentOperatorNode::print() {
    Logger::log(this->toString(), "-", _assignment->toString());
}