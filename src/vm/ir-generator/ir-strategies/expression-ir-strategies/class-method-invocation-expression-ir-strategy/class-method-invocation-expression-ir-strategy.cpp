//
// Created by Johny Georges on 2024-12-27.
//

#include "class-method-invocation-expression-ir-strategy.h"

IRClassMethodInvocationExpressionNode* ClassMethodInvocationExpressionIRStrategy::generate(ASTClassMethodInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, new IROperation(IR_FUNCTION_ARGUMENT_OP)));
    }

    auto irFunctionType = (IRFunctionType*)irGenerator->generateTypeFor(node->getName()->getTypeSignature(), scope, irContext);
    auto irReturnType = irGenerator->generateTypeFor(node->getName()->getTypeSignature()->getReturnType(), scope, irContext);
    auto function = irContext->getModule()->getFunction(node->getName()->getId());
    auto argList = irGenerator->generateArgumentPlaceholderList(irFunctionType);
    auto callInstruction = llvm::CallInst::Create(irFunctionType->getType(), function, argList);
    return new IRClassMethodInvocationExpressionNode(node, function, callInstruction, irFunctionType, arguments, irReturnType, scope->getClassScope().value());
}
