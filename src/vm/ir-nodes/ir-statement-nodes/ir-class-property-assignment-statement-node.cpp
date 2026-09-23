//
// Created by Johny Georges on 2025-01-02.
//

#include "ir-class-property-assignment-statement-node.h"

IRClassPropertyAssignmentStatementNode::IRClassPropertyAssignmentStatementNode(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::string propertyName, uint64_t propertyIndex) {
    _node = node;
    _irExpression = irExpression;
    _propertyName = propertyName;
    _propertyIndex = propertyIndex;
}

std::shared_ptr<IRExpressionNode> IRClassPropertyAssignmentStatementNode::getExpression() {
    return _irExpression;
}

uint64_t IRClassPropertyAssignmentStatementNode::getPropertyIndex() {
    return _propertyIndex;
}

IRNodeType IRClassPropertyAssignmentStatementNode::getNodeType() {
    return IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRClassPropertyAssignmentStatementNode::toString() {
    return "IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE";
}

void IRClassPropertyAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}