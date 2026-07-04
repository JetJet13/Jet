//
// Created by Johny Georges on 2026-02-16.
//

#include "ast-ref-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTRefValueAssignmentStatementNode::ASTRefValueAssignmentStatementNode(std::shared_ptr<ASTRefValueAssignmentNode> assignment, std::shared_ptr<ASTExpressionNode> expression) {
    _assignment = assignment;
    _expression = expression;
    _children.push_back(_assignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTRefValueAssignmentNode> ASTRefValueAssignmentStatementNode::getVariableAssignment() {
    return _assignment;
}

std::shared_ptr<ASTExpressionNode> ASTRefValueAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTRefValueAssignmentStatementNode::getStartPosition() {
    return _assignment->getStartPosition();
}

Position* ASTRefValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTRefValueAssignmentStatementNode::getNodeType() {
    return AST_REF_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTRefValueAssignmentStatementNode::toString() {
    return "REF_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTRefValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTRefValueAssignmentStatementNode>(other);
    return this->getVariableAssignment()->isSameAs(otherNode->getVariableAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTRefValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTRefValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_assignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}