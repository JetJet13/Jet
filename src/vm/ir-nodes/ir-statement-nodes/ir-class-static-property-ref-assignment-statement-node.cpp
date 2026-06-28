//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-class-static-property-ref-assignment-statement-node.h"

IRClassStaticPropertyRefAssignmentStatementNode::IRClassStaticPropertyRefAssignmentStatementNode(ASTObjectAccessRefAssignmentStatementNode* node, IRClassStaticPropertyAccessExpressionNode* irClassStaticPropertyAccessExpressionNode, IRExpressionNode* irExpression) {
    _node = node;
    _irClassStaticPropertyAccessExpressionNode = irClassStaticPropertyAccessExpressionNode;
    _irExpression = irExpression;
}

IRClassStaticPropertyAccessExpressionNode* IRClassStaticPropertyRefAssignmentStatementNode::getIRClassStaticPropertyAccessExpressionNode() {
    return _irClassStaticPropertyAccessExpressionNode;
}

IRExpressionNode* IRClassStaticPropertyRefAssignmentStatementNode::getIRExpression() {
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