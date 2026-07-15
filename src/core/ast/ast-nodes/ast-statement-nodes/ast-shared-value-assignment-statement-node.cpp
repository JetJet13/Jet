//
// Created by Johny Georges on 2026-02-16.
//

#include "ast-shared-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTSharedValueAssignmentStatementNode::ASTSharedValueAssignmentStatementNode(std::shared_ptr<ASTSharedValueAssignmentNode> assignment, std::shared_ptr<ASTExpressionNode> expression) {
    _assignment = assignment;
    _expression = expression;
    _children.push_back(_assignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTSharedValueAssignmentNode> ASTSharedValueAssignmentStatementNode::getVariableAssignment() {
    return _assignment;
}

std::shared_ptr<ASTExpressionNode> ASTSharedValueAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTSharedValueAssignmentStatementNode::getStartPosition() {
    return _assignment->getStartPosition();
}

std::shared_ptr<Position> ASTSharedValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTSharedValueAssignmentStatementNode::getNodeType() {
    return AST_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTSharedValueAssignmentStatementNode::toString() {
    return "SHARED_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTSharedValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTSharedValueAssignmentStatementNode>(other);
    return this->getVariableAssignment()->isSameAs(otherNode->getVariableAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTSharedValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTSharedValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_assignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}