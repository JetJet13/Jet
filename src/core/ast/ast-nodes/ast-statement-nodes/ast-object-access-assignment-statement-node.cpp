//
// Created by Johny Georges on 2025-08-27.
//

#include "ast-object-access-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessAssignmentStatementNode::ASTObjectAccessAssignmentStatementNode(ASTObjectAccessAssignmentNode* objectAccessAssignment, ASTExpressionNode* expression) {
    _objectAccessAssignment = objectAccessAssignment;
    _expression = expression;
    _children.push_back(_objectAccessAssignment);
    _children.push_back(_expression);
}

ASTObjectAccessAssignmentNode* ASTObjectAccessAssignmentStatementNode::getObjectAccessAssignment() {
    return _objectAccessAssignment;
}

ASTExpressionNode* ASTObjectAccessAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTObjectAccessAssignmentStatementNode::getStartPosition() {
    return _objectAccessAssignment->getStartPosition();
}

Position* ASTObjectAccessAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTObjectAccessAssignmentStatementNode::getNodeType() {
    return AST_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTObjectAccessAssignmentStatementNode::toString() {
    return "OBJECT_ACCESS_ASSIGNMENT_STATEMENT";
}

bool ASTObjectAccessAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessAssignmentStatementNode*)other;
    return this->getObjectAccessAssignment()->isSameAs(otherNode->getObjectAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTObjectAccessAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTObjectAccessAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}