//
// Created by Johny Georges on 2026-03-27.
//

#include "ir-module-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-type/ir-new-class-instance-type.h"
#include "../../ir-type/ir-class-instance-type.h"

IRModuleAccessExpressionNode::IRModuleAccessExpressionNode(std::shared_ptr<ASTModuleAccessExpressionNode> node, llvm::Value* irValue, std::shared_ptr<IRType> irType) {
    _node = node;
    _irValue = irValue;
    _irType = irType;
}

void IRModuleAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
}

std::shared_ptr<ASTModuleAccessExpressionNode> IRModuleAccessExpressionNode::getNode() {
    return _node;
}

std::shared_ptr<IRType> IRModuleAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRModuleAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRModuleAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRModuleAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRModuleAccessExpressionNode::getValue() {
    return _irValue;
}

IRNodeType IRModuleAccessExpressionNode::getNodeType() {
    return IR_MODULE_ACCESS_EXPRESSION_NODE;
}

std::string IRModuleAccessExpressionNode::toString() {
    return "IR_MODULE_ACCESS_EXPRESSION_NODE";
}

void IRModuleAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(llvm::outs());
}