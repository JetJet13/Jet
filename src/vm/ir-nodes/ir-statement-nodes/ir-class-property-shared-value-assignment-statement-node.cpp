//
// Created by Johny Georges on 2026-02-20.
//

#include "ir-class-property-shared-value-assignment-statement-node.h"

IRClassPropertySharedValueAssignmentStatementNode::IRClassPropertySharedValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertySharedValueAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::string propertyName, uint64_t propertyIndex) {
    _node = node;
    _irExpression = irExpression;
    _propertyName = propertyName;
    _propertyIndex = propertyIndex;
}

std::shared_ptr<IRExpressionNode> IRClassPropertySharedValueAssignmentStatementNode::getExpression() {
    return _irExpression;
}

uint64_t IRClassPropertySharedValueAssignmentStatementNode::getPropertyIndex() {
    return _propertyIndex;
}

IRNodeType IRClassPropertySharedValueAssignmentStatementNode::getNodeType() {
    return IR_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRClassPropertySharedValueAssignmentStatementNode::toString() {
    return "IR_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRClassPropertySharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}