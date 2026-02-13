//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-invocation-expression-ir-strategy.h"

IRClassMethodInvocationExpressionNode* ClassMethodInvocationExpressionIRStrategy::generate(ASTClassMethodInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRFunctionArgumentNode*>();
    for (int i = 0; i < node->getArguments()->numArguments(); ++i) {
        auto argument = node->getArguments()->getArguments()->at(i);
        arguments.push_back(
            irGenerator->generateFor(
                argument,
                i,
                scope,
                irContext,
                new IROperation(IR_FUNCTION_ARGUMENT_OP),
                node->getName()->getTypeSignature()
            )
        );
    }

    auto irFunctionType = (IRFunctionType*)irGenerator->generateTypeFor(node->getName()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getName()->getTypeSignature()->getReturnType(), scope, irContext);
    auto function = irContext->getModule()->getFunction(node->getName()->getId());
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
    return new IRClassMethodInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, scope->getClassScope().value());
}
