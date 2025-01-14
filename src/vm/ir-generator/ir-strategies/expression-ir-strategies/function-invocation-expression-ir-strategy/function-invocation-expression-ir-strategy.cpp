//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"

IRExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irFunctionType = irGenerator->generateTypeFor(node->getFunction()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType(), scope, irContext);
    if (irFunctionType->isFunctionParameterType() || irFunctionType->isLambdaType()) {
        auto function = scope->find(node->getFunction()->getId()).value()->getValue();
        return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType);
    }

    auto function = irContext->getModule()->getFunction(node->getFunction()->getId());
    return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType);
}