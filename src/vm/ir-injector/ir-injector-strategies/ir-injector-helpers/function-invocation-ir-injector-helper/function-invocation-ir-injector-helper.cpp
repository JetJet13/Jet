//
// Created by Johny Georges on 2024-11-09.
//

#include "function-invocation-ir-injector-helper.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../../ir-type/ir-lambda-type.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }

    if (irExpression->getFunctionIRType()->isLambdaType()) {
        auto irLambdaType = (IRLambdaType*)irExpression->getFunctionIRType();
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        auto lambdaIndex = irBlock->getBuilder()->get()->getInt32(irLambdaType->getLambdaVariableType()->getFunctionIndex());
        auto lambdaPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getValue(), { zeroIndex, lambdaIndex });
        auto loadedLambda = irBlock->getBuilder()->get()->CreateLoad(irLambdaType->getFunctionPointerType(), lambdaPointer);
        if (irLambdaType->getLambdaScopeType()) {
            auto lambdaScopeArgumentIndex = irBlock->getBuilder()->get()->getInt32(irLambdaType->getLambdaVariableType()->getFunctionScopeArgumentIndex());
            auto lambdaScopeArgumentPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getValue(), { zeroIndex, lambdaScopeArgumentIndex });
            auto loadedLambdaScopeArgument = irBlock->getBuilder()->get()->CreateLoad(irLambdaType->getLambdaScopeType().value()->getType(), lambdaScopeArgumentPointer);
            arguments.push_back(loadedLambdaScopeArgument);
        }
        return irBlock->getBuilder()->get()->CreateCall(
                irLambdaType->getType(),
                loadedLambda,
                arguments
        );
    }

    if (irExpression->getFunctionIRType()->isFunctionParameterType()) {
        auto irFunctionParameterType = (IRFunctionParameterType*)irExpression->getFunctionIRType();
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        auto functionIndex = irBlock->getBuilder()->get()->getInt32(irFunctionParameterType->getFunctionIndex());
        auto functionPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irFunctionParameterType->getType(), irExpression->getValue(), { zeroIndex, functionIndex });
        auto loadedFunctionParameter = irBlock->getBuilder()->get()->CreateLoad(irFunctionParameterType->getIRFunctionPointer()->getType(), functionPointer);

        auto functionScopeArgumentIndex = irBlock->getBuilder()->get()->getInt32(irFunctionParameterType->getFunctionScopeArgumentIndex());
        auto functionScopeArgumentPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irFunctionParameterType->getType(), irExpression->getValue(), { zeroIndex, functionScopeArgumentIndex });
        auto loadedFunctionScopeArgument = irBlock->getBuilder()->get()->CreateLoad(irFunctionParameterType->getFunctionScopeArgumentType(), functionScopeArgumentPointer);
        arguments.push_back(loadedFunctionScopeArgument);
        return irBlock->getBuilder()->get()->CreateCall(
                irFunctionParameterType->getFunctionType(),
                loadedFunctionParameter,
                arguments
        );
    }

    return irBlock->getBuilder()->get()->CreateCall(
        llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
        irExpression->getValue(),
        arguments
    );
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionParameterInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument,  IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }

    arguments.push_back(irExpression->getFunctionScopeArgument());
    return irBlock->getBuilder()->get()->CreateCall(
            irExpression->getFunctionIRType()->getFunctionType(),
            irExpression->getFunction(),
            arguments
    );
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRClassMethodInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }
    arguments.push_back(irExpression->getClassScopeArgument()->getValue());
    return irBlock->getBuilder()->get()->CreateCall(
            llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
            irExpression->getValue(),
            arguments
    );
}