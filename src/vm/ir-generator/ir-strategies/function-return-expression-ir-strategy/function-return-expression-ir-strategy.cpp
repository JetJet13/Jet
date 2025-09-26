//
// Created by Johny Georges on 2024-07-13.
//

#include "function-return-expression-ir-strategy.h"

IRFunctionReturnExpressionNode* FunctionReturnExpressionIRStrategy::generate(ASTFunctionReturnExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    return new IRFunctionReturnExpressionNode(node, irExpressionNode);
}