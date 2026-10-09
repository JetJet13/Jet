// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2026-03-14.
//

#include "ir-class-static-property-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassStaticPropertyAccessExpressionNode::IRClassStaticPropertyAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRInstructionNode> irStaticProperty, std::shared_ptr<IRType> irType) {
    _node = node;
    _irStaticProperty = irStaticProperty;
    _irType = irType;
}

std::shared_ptr<ASTObjectAccessExpressionNode> IRClassStaticPropertyAccessExpressionNode::getNode() {
    return _node;
}

std::shared_ptr<IRPointerType> IRClassStaticPropertyAccessExpressionNode::getPointerIRType() {
    return _irStaticProperty->getIRType();
}

std::shared_ptr<IRType> IRClassStaticPropertyAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRClassStaticPropertyAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRClassStaticPropertyAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRClassStaticPropertyAccessExpressionNode::getEndPosition() {
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