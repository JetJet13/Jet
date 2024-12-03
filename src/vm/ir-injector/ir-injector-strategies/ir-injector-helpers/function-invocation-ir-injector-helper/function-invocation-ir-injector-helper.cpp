//
// Created by Johny Georges on 2024-11-09.
//

#include "function-invocation-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-type/ir-lambda-type.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjectorMap->getInjector(argument->getTypeSignature())->inject(argument, builder, irInjectorMap, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }

    if (irExpression->getFunctionIRType()->isLambdaType()) {
        auto irLambdaType = (IRLambdaType*)irExpression->getFunctionIRType();
        auto zeroIndex = builder->get()->getInt32(0);
        auto lambdaIndex = builder->get()->getInt32(irLambdaType->getLambdaVariableType()->getFunctionIndex());
        auto lambdaPointer = builder->get()->CreateInBoundsGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getValue(), { zeroIndex, lambdaIndex });
        auto loadedLambda = builder->get()->CreateLoad(irLambdaType->getFunctionPointerType(), lambdaPointer);
        if (irLambdaType->getLambdaScopeType()) {
            auto lambdaScopeArgumentIndex = builder->get()->getInt32(irLambdaType->getLambdaVariableType()->getFunctionScopeArgumentIndex());
            auto lambdaScopeArgumentPointer = builder->get()->CreateInBoundsGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getValue(), { zeroIndex, lambdaScopeArgumentIndex });
            auto loadedLambdaScopeArgument = builder->get()->CreateLoad(irLambdaType->getLambdaScopeType().value()->getType(), lambdaScopeArgumentPointer);
            arguments.push_back(loadedLambdaScopeArgument);
        }
        return builder->get()->CreateCall(
                irLambdaType->getType(),
                loadedLambda,
                arguments
        );
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