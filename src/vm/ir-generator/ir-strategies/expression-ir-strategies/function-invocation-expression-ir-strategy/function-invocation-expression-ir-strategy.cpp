//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irModule, IR_FUNCTION_ARGUMENT_OP));
    }

    auto irFunctionType = irGenerator->generateTypeFor(node->getFunction()->getTypeSignature());
    auto irReturnType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType());
    if (irFunctionType->isFunctionParameterType()) {
        auto irFunctionParameterType = (IRFunctionParameterType*)irFunctionType;
        auto function = scope->findLoaded(irFunctionParameterType->getFunctionParameterName(node->getFunction()->getId())).value()->getValue();
        auto functionScopeArgument = scope->findLoaded(irFunctionParameterType->getFunctionScopeArgumentParameterName(node->getFunction()->getId())).value()->getValue();
        return new IRFunctionParameterInvocationExpressionNode(node, function, functionScopeArgument, irFunctionParameterType, arguments, irReturnType);
    }

    if (irFunctionType->isLambdaType()) {
        auto function = scope->find(node->getFunction()->getId()).value()->getValue();
        return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType);
    }

    auto function = irModule->getModule()->getFunction(node->getFunction()->getId());
    return new IRFunctionInvocationExpressionNode(node, function, irFunctionType, arguments, irReturnType);
}