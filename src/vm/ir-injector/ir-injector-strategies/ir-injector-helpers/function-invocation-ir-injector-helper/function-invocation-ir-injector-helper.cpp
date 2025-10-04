//
// Created by Johny Georges on 2024-11-09.
//

#include "function-invocation-ir-injector-helper.h"
#include "../../../../ir-type/ir-lambda-type.h"
#include "../../../../ir-type/ir-array-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-type/ir-type-value-type.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    auto functionTypeSignature = irExpression->getTypeSignature()->getFunctionType();
    for (int i = 0; i < irExpression->getIRArguments()->size(); ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto operationType = functionTypeSignature->isArgumentVarArg(i)
                ? new IROperation(IR_OPERAND_POINTER_OP)
                : new IROperation(IR_OPERAND_VALUE_OP);
        auto irArgument = irInjector->inject(irBlock, argument, operationType, irModule, scope);
        arguments.push_back(irArgument);
    }

    // this is only here because of the built-in print function
    // the front-end does not currently support variadic functions/lambdas
    if (irExpression->getVarArgsTypeValueArgument()) {
        auto startIndex = irExpression->getTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex();
        auto typeValueType = (IRTypeValueType*)irExpression->getVarArgsTypeValueArgument().value()->getParentAllocation().value()->getIRType()->getUnderlyingType();
        auto arrayPointerType = (IRArrayPointerType*)irExpression->getVarArgsTypeValueArgument().value()->getIRType()->getUnderlyingType();
        auto varArgsArrayAllocation = InstructionIRInjectorHelper::inject(irExpression->getVarArgsTypeValueArgument().value()->getParentAllocation().value(), irBlock);
        auto varArgsArrayPointerAllocation = InstructionIRInjectorHelper::inject(irExpression->getVarArgsTypeValueArgument().value(), irBlock);
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        for (int i = startIndex; i < irExpression->getIRArguments()->size(); ++i) {
            auto argument = irExpression->getIRArguments()->at(i);
            auto index = irBlock->getBuilder()->get()->getInt64(i);
            auto pointerToTypeValue = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                    typeValueType->getType(),
                    varArgsArrayAllocation,
                    { index }
            );
            auto typeValue = irInjector->inject(irBlock, argument->getIRType()->getSourceType());
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), typeValue, irBlock, typeValueType);
            InstructionIRInjectorHelper::injectStore(loadedTypeValue, pointerToTypeValue, irBlock);
        }
        auto numElementsIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getNumElementsIndex());
        auto depthIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getDepthIndex());
        auto pointerToNumElements = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                arrayPointerType->getType(),
                varArgsArrayPointerAllocation,
                { zeroIndex, numElementsIndex }
        );
        auto numElements = irBlock->getBuilder()->get()->getInt64(arguments.size() - irExpression->getTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex());
        InstructionIRInjectorHelper::injectStore(numElements, pointerToNumElements, irBlock);

        auto pointerToDepth = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                arrayPointerType->getType(),
                varArgsArrayPointerAllocation,
                { zeroIndex, depthIndex }
        );
        auto depth = irBlock->getBuilder()->get()->getInt64(1);
        InstructionIRInjectorHelper::injectStore(depth, pointerToDepth, irBlock);

        auto allocIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
        auto pointerToArrayAllocation = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                arrayPointerType->getType(),
                varArgsArrayPointerAllocation,
                { zeroIndex, allocIndex }
        );
        InstructionIRInjectorHelper::injectStore(varArgsArrayAllocation, pointerToArrayAllocation, irBlock);
        auto loadedVarArgsArrayPointer = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), varArgsArrayPointerAllocation, irBlock, arrayPointerType);
        arguments.insert(arguments.begin() + startIndex, loadedVarArgsArrayPointer);
    }

    if (irExpression->getFunctionIRType()->isLambdaType()) {
        auto irLambdaType = (IRLambdaType*)irExpression->getFunctionIRType();
        auto lambdaIndex = irLambdaType->getLambdaVariableType()->getFunctionIndex();
        auto lambdaPointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getValue(), lambdaIndex);
        auto loadedLambda = InstructionIRInjectorHelper::injectLoad(irLambdaType->getFunctionPointerType(), lambdaPointer, irBlock);
        if (irLambdaType->getLambdaScopeType() && ((IRStructType*)irLambdaType->getLambdaScopeType().value())->size() > 0) {
            auto lambdaScopeArgumentIndex = irLambdaType->getLambdaVariableType()->getFunctionScopeArgumentIndex();
            auto lambdaScopeArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getValue(), lambdaScopeArgumentIndex);
            auto loadedLambdaScopeArgument = InstructionIRInjectorHelper::injectLoad(irLambdaType->getLambdaScopeType().value()->getType(), lambdaScopeArgumentPointer, irBlock);
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
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        auto functionIndex = irBlock->getBuilder()->get()->getInt64(irFunctionParameterType->getFunctionIndex());
        auto functionPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irFunctionParameterType->getType(), irExpression->getValue(), { zeroIndex, functionIndex });
        auto loadedFunctionParameter = InstructionIRInjectorHelper::injectLoad(irFunctionParameterType->getIRFunctionPointer()->getType(), functionPointer, irBlock);

        auto functionScopeArgumentIndex = irFunctionParameterType->getFunctionScopeArgumentIndex();
        auto functionScopeArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(irFunctionParameterType->getType(), irExpression->getValue(), functionScopeArgumentIndex);
        auto loadedFunctionScopeArgument = InstructionIRInjectorHelper::injectLoad(irFunctionParameterType->getFunctionScopeArgumentType(), functionScopeArgumentPointer, irBlock);
        arguments.push_back(loadedFunctionScopeArgument);
        return irBlock->getBuilder()->get()->CreateCall(
                irFunctionParameterType->getFunctionType(),
                loadedFunctionParameter,
                arguments
        );
    }

    auto value = irBlock->getBuilder()->get()->CreateCall(
        llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
        irExpression->getValue(),
        arguments
    );
    return value;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionParameterInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument,  new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope)
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
                irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope)
        );
    }
    arguments.push_back(irExpression->getClassScopeArgument()->getValue());
    return irBlock->getBuilder()->get()->CreateCall(
            llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
            irExpression->getValue(),
            arguments
    );
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRArrayPrototypeInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope, IROperation* irOperation) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
            irInjector->inject(irBlock, argument, new IROperation(IR_OPERAND_POINTER_OP), irModule, scope)
        );
    }
    auto arrayValue = irInjector->inject(irBlock, irExpression->getIRArrayValue(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    arguments.insert(arguments.begin(), arrayValue);
    auto arrayTypeValue = irInjector->inject(irBlock, irExpression->getIRArrayValue()->getIRType()->getUnderlyingType());
    auto loadedArrayTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getIRArrayValue()->getIRType()->getUnderlyingType()->getValue()->getAllocatedType(), arrayTypeValue, irBlock);
    arguments.push_back(loadedArrayTypeValue);
    auto result = irBlock->getBuilder()->get()->CreateCall(
            llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
            irExpression->getValue(),
            arguments
    );

    if (irOperation->isOperandPointer() && !result->getType()->isPointerTy()) {
        auto alloc = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getUnderlyingIRType()->getType());
        InstructionIRInjectorHelper::injectStore(result, alloc, irBlock, irExpression->getUnderlyingIRType());
        return alloc;
    }

    if ((irOperation->isCopy() || irOperation->isOperandValue()) && result->getType()->isPointerTy()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), result, irBlock);
    }

    return result;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRTupleAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope)
        );
    }
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto pointerToLambda = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRTupleAccessExpression()->getSource()->getSourceAllocation().value()->getAllocatedType(), irExpression->getIRTupleAccessExpression()->getValue(), { zeroIndex, irExpression->getIRTupleAccessExpression()->getIRTargetKeyIndex() });
    auto irFunctionParameterType = (IRFunctionParameterType*)irExpression->getFunctionIRType();
    auto loadedLambdaAtIndex = InstructionIRInjectorHelper::injectLoad(irFunctionParameterType->getType(), pointerToLambda, irBlock);
    auto lambda = irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irFunctionParameterType->getFunctionIndex() });
    auto lambdaScopeArgument= irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irFunctionParameterType->getFunctionScopeArgumentIndex() });
    arguments.push_back(lambdaScopeArgument);
    return irBlock->getBuilder()->get()->CreateCall(
            irFunctionParameterType->getFunctionType(),
            lambda,
            arguments
    );
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRObjectAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope)
        );
    }
    return irBlock->getBuilder()->get()->CreateCall(
            llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
            irExpression->getFunction(),
            arguments
    );
}