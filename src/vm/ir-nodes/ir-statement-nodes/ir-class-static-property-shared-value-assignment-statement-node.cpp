//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-class-static-property-shared-value-assignment-statement-node.h"

IRClassStaticPropertySharedValueAssignmentStatementNode::IRClassStaticPropertySharedValueAssignmentStatementNode(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRClassStaticPropertyAccessExpressionNode> irClassStaticPropertyAccessExpressionNode, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irClassStaticPropertyAccessExpressionNode = irClassStaticPropertyAccessExpressionNode;
    _irExpression = irExpression;
}

std::shared_ptr<IRClassStaticPropertyAccessExpressionNode> IRClassStaticPropertySharedValueAssignmentStatementNode::getIRClassStaticPropertyAccessExpressionNode() {
    return _irClassStaticPropertyAccessExpressionNode;
}

std::shared_ptr<IRExpressionNode> IRClassStaticPropertySharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRClassStaticPropertySharedValueAssignmentStatementNode::getNodeType() {
    return IR_CLASS_STATIC_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRClassStaticPropertySharedValueAssignmentStatementNode::toString() {
    return "IR_CLASS_STATIC_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRClassStaticPropertySharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irClassStaticPropertyAccessExpressionNode->print(stream);
    _irExpression->print(stream);
}