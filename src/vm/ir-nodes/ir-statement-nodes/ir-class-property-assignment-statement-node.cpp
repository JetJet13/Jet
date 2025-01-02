//
// Created by Johny Georges on 2025-01-02.
//

#include "ir-class-property-assignment-statement-node.h"

IRClassPropertyAssignmentStatementNode::IRClassPropertyAssignmentStatementNode(ASTClassPropertyAssignmentStatementNode* node, IRExpressionNode* irExpression, std::string propertyName, unsigned long propertyIndex) {
    _node = node;
    _irExpression = irExpression;
    _propertyName = propertyName;
    _propertyIndex = propertyIndex;
}

IRExpressionNode* IRClassPropertyAssignmentStatementNode::getExpression() {
    return _irExpression;
}

unsigned long IRClassPropertyAssignmentStatementNode::getPropertyIndex() {
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