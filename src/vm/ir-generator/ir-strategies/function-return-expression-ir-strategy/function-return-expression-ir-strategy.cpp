//
// Created by Johny Georges on 2024-07-13.
//

#include "function-return-expression-ir-strategy.h"

IRFunctionReturnExpressionNode* FunctionReturnExpressionIRStrategy::generate(std::shared_ptr<ASTFunctionReturnExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    if (node->getExpression()) {
        auto irExpressionNode = irGenerator->generateFor(node->getExpression().value(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
        irExpressionNode->markAsReturned();
        return new IRFunctionReturnExpressionNode(node, irExpressionNode);
    }
    return new IRFunctionReturnExpressionNode(node);
}