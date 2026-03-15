//
// Created by Johny Georges on 2026-03-14.
//

#include "ir-class-static-property-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassStaticPropertyAccessExpressionNode::IRClassStaticPropertyAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRInstructionNode* irStaticProperty, IRType* irType) {
    _node = node;
    _irStaticProperty = irStaticProperty;
    _irType = irType;
}

ASTObjectAccessExpressionNode* IRClassStaticPropertyAccessExpressionNode::getNode() {
    return _node;
}

IRPointerType* IRClassStaticPropertyAccessExpressionNode::getPointerIRType() {
    return _irStaticProperty->getIRType();
}

IRType* IRClassStaticPropertyAccessExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRClassStaticPropertyAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRClassStaticPropertyAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRClassStaticPropertyAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRClassStaticPropertyAccessExpressionNode::getValue() {
    return _irStaticProperty->getValue();
}

IRNodeType IRClassStaticPropertyAccessExpressionNode::getNodeType() {
    return IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE;
}

std::string IRClassStaticPropertyAccessExpressionNode::toString() {
    return "IR_CLASS_STATIC_PROPERTY_ACCESS_EXPRESSION_NODE";
}

void IRClassStaticPropertyAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irStaticProperty->print(stream);
}