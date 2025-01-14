//
// Created by Johny Georges on 2024-12-30.
//

#include "new-class-instance-expression-ir-strategy.h"

IRNewClassInstanceExpressionNode* NewClassInstanceExpressionIRStrategy::generate(ASTNewClassInstanceExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irClassType = (IRClassType*)scope->findType(node->getClassName()->getId()).value();
    auto irConstructorType = irClassType->getIRTypeForConstructor(node->getTypeSignature()->getConstructorId());

    auto function = irContext->getModule()->getFunction(node->getTypeSignature()->getConstructorId());
    return new IRNewClassInstanceExpressionNode(node, function, irConstructorType.value(), arguments, irClassType);
}