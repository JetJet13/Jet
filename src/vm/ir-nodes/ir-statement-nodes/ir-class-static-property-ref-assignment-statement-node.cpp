//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-class-static-property-ref-assignment-statement-node.h"

IRClassStaticPropertyRefAssignmentStatementNode::IRClassStaticPropertyRefAssignmentStatementNode(std::shared_ptr<ASTObjectAccessRefAssignmentStatementNode> node, std::shared_ptr<IRClassStaticPropertyAccessExpressionNode> irClassStaticPropertyAccessExpressionNode, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irClassStaticPropertyAccessExpressionNode = irClassStaticPropertyAccessExpressionNode;
    _irExpression = irExpression;
}

std::shared_ptr<IRClassStaticPropertyAccessExpressionNode> IRClassStaticPropertyRefAssignmentStatementNode::getIRClassStaticPropertyAccessExpressionNode() {
    return _irClassStaticPropertyAccessExpressionNode;
}

std::shared_ptr<IRExpressionNode> IRClassStaticPropertyRefAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRClassStaticPropertyRefAssignmentStatementNode::getNodeType() {
    return IR_CLASS_STATIC_PROPERTY_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRClassStaticPropertyRefAssignmentStatementNode::toString() {
    return "IR_CLASS_STATIC_PROPERTY_REF_ASSIGNMENT_STATEMENT_NODE";
}

void IRClassStaticPropertyRefAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irClassStaticPropertyAccessExpressionNode->print(stream);
    _irExpression->print(stream);
}