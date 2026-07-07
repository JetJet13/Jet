//
// Created by Johny Georges on 2024-07-13.
//

#include "function-return-expression-ir-strategy.h"

std::shared_ptr<IRFunctionReturnExpressionNode> FunctionReturnExpressionIRStrategy::generate(std::shared_ptr<ASTFunctionReturnExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    if (node->getExpression()) {
        auto irExpressionNode = irGenerator->generateFor(node->getExpression().value(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
        irExpressionNode->markAsReturned();
        return std::make_shared<IRFunctionReturnExpressionNode>(node, irExpressionNode);
    }
    return std::make_shared<IRFunctionReturnExpressionNode>(node);
}