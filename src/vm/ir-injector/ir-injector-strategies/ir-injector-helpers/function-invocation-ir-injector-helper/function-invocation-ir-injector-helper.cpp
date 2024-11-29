//
// Created by Johny Georges on 2024-11-09.
//

#include "function-invocation-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjectorMap->getInjector(argument->getTypeSignature())->inject(argument, builder, irInjectorMap, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }

    if (irExpression->getLambdaScopeArgument()) {
        auto lambdaScopeArgument = irExpression->getLambdaScopeArgument().value();
        auto lambdaScopeAllocation = builder->get()->Insert(lambdaScopeArgument->getValue());
        auto irLambdaScopeType = (IRStructType*)lambdaScopeArgument->getIRType()->getSourceType();
        auto zeroIndex = builder->get()->getInt32(0);
        for (int i = 0; i < irLambdaScopeType->size(); ++i) {
            auto index = builder->get()->getInt32(i);
            auto key = irLambdaScopeType->getKeyForIndex(i);
            auto allocationForKey = lambdaScopeArgument->getChildAllocationForKey(key);
            auto pointer = builder->get()->CreateGEP(irLambdaScopeType->getType(), lambdaScopeAllocation, { zeroIndex, index });
            builder->get()->CreateStore(allocationForKey->getValue(), pointer);
        }
        arguments.push_back(lambdaScopeAllocation);
    }

    return builder->get()->CreateCall(
        llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
        irExpression->getValue(),
        arguments
    );
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionParameterInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjectorMap->getInjector(argument->getTypeSignature())->inject(argument, builder, irInjectorMap, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }

    arguments.push_back(irExpression->getFunctionScopeArgument());
    return builder->get()->CreateCall(
            irExpression->getFunctionIRType()->getFunctionType(),
            irExpression->getFunction(),
            arguments
    );
}