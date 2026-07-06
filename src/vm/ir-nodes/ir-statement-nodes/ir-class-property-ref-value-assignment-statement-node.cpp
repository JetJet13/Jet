//
// Created by Johny Georges on 2026-02-20.
//

#include "ir-class-property-ref-value-assignment-statement-node.h"

IRClassPropertyRefValueAssignmentStatementNode::IRClassPropertyRefValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertyRefValueAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::string propertyName, unsigned long propertyIndex) {
    _node = node;
    _irExpression = irExpression;
    _propertyName = propertyName;
    _propertyIndex = propertyIndex;
}

std::shared_ptr<IRExpressionNode> IRClassPropertyRefValueAssignmentStatementNode::getExpression() {
    return _irExpression;
}

unsigned long IRClassPropertyRefValueAssignmentStatementNode::getPropertyIndex() {
    return _propertyIndex;
}

IRNodeType IRClassPropertyRefValueAssignmentStatementNode::getNodeType() {
    return IR_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRClassPropertyRefValueAssignmentStatementNode::toString() {
    return "IR_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRClassPropertyRefValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}