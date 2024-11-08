//
// Created by Johny Georges on 2024-11-08.
//

#include "function-invocation-expression-ir-strategy.h"

IRFunctionInvocationExpressionNode* FunctionInvocationExpressionIRStrategy::generate(ASTFunctionInvocationExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto function = irModule->getModule()->getFunction(node->getFunction()->getId());
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        auto irNode = irGenerator->generateFor(argument, scope, irModule, IR_FUNCTION_ARGUMENT_OP);
        arguments.push_back(irNode->getValue());
    }
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature()->getReturnType());
    auto functionCall = llvm::CallInst::Create(function->getFunctionType(), function, arguments);
    return new IRFunctionInvocationExpressionNode(node, functionCall, irType);
}