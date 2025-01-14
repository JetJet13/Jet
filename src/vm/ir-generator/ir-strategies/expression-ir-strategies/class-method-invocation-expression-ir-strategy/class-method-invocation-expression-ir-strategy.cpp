//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassMethodInvocationExpressionNode* ClassMethodInvocationExpressionIRStrategy::generate(ASTClassMethodInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        argument->print();
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irFunctionType = irGenerator->generateTypeFor(node->getName()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getName()->getTypeSignature()->getReturnType(), scope, irContext);
    auto function = irContext->getModule()->getFunction(node->getName()->getId());
    return new IRClassMethodInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType, scope->getClassScope().value());
}