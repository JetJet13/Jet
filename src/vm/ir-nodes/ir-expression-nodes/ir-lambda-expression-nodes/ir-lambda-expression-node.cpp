//
// Created by Johny Georges on 2025-12-31.
//

#include "ir-lambda-expression-node.h"

std::shared_ptr<IRLambdaType> IRLambdaExpressionNode::getIRLambdaType() {
    return std::dynamic_pointer_cast<IRLambdaType>(this->getIRType());
}