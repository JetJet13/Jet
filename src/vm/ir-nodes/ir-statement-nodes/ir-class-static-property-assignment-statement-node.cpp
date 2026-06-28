//
// Created by Johny Georges on 2026-03-16.
//

#include "ir-class-static-property-assignment-statement-node.h"

IRClassStaticPropertyAssignmentStatementNode::IRClassStaticPropertyAssignmentStatementNode(ASTObjectAccessAssignmentStatementNode* node, IRClassStaticPropertyAccessExpressionNode* irClassStaticPropertyAccessExpressionNode, IRExpressionNode* irExpression) {
    _node = node;
    _irClassStaticPropertyAccessExpressionNode = irClassStaticPropertyAccessExpressionNode;
    _irExpression = irExpression;
}

IRClassStaticPropertyAccessExpressionNode* IRClassStaticPropertyAssignmentStatementNode::getIRClassStaticPropertyAccessExpressionNode() {
    return _irClassStaticPropertyAccessExpressionNode;
}

IRExpressionNode* IRClassStaticPropertyAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRClassStaticPropertyAssignmentStatementNode::getNodeType() {
    return IR_CLASS_STATIC_PROPERTY_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRClassStaticPropertyAssignmentStatementNode::toString() {
    return "IR_CLASS_STATIC_PROPERTY_REF_ASSIGNMENT_STATEMENT_NODE";
}

void IRClassStaticPropertyAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irClassStaticPropertyAccessExpressionNode->print(stream);
    _irExpression->print(stream);
}