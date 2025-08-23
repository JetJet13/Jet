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
                ? IR_OPERAND_POINTER_OP
                : IR_OPERAND_VALUE_OP;
        auto irArgument = irInjector->inject(irBlock, argument, operationType, irModule, scope);
        arguments.push_back(irArgument);
    }

    // this is only here because of the built-in print function
    // the front-end does not currently support variadic functions/lambdas
    if (irExpression->getVarArgsTypeValueArgument()) {
        auto startIndex = irExpression->getTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex();
        auto typeValueType = (IRTypeValueType*)irExpression->getVarArgsTypeValueArgument().value()->getParentAllocation().value()->getIRType()->getSourceType();
        auto arrayPointerType = (IRArrayPointerType*)irExpression->getVarArgsTypeValueArgument().value()->getIRType()->getSourceType();
        auto varArgsArrayAllocation = InstructionIRInjectorHelper::inject(irExpression->getVarArgsTypeValueArgument().value()->getParentAllocation().value(), irBlock);
        auto varArgsArrayPointerAllocation = InstructionIRInjectorHelper::inject(irExpression->getVarArgsTypeValueArgument().value(), irBlock);
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        for (int i = startIndex; i < irExpression->getIRArguments()->size(); ++i) {
            auto argument = irExpression->getIRArguments()->at(i);
            auto index = irBlock->getBuilder()->get()->getInt32(i);
            auto pointerToTypeValue = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                    typeValueType->getType(),
                    varArgsArrayAllocation,
                    { index }
            );
            auto typeValue = irInjector->inject(irBlock, argument->getIRType()->getSourceType());
            auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), typeValue);
            irBlock->getBuilder()->get()->CreateStore(loadedTypeValue, pointerToTypeValue);
        }
        auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
        auto depthIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getDepthIndex());
        auto pointerToNumElements = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                arrayPointerType->getType(),
                varArgsArrayPointerAllocation,
                { zeroIndex, numElementsIndex }
        );
        auto numElements = irBlock->getBuilder()->get()->getInt32(arguments.size() - irExpression->getTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex());
        irBlock->getBuilder()->get()->CreateStore(numElements, pointerToNumElements);

        auto pointerToDepth = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                arrayPointerType->getType(),
                varArgsArrayPointerAllocation,
                { zeroIndex, depthIndex }
        );
        auto depth = irBlock->getBuilder()->get()->getInt32(1);
        irBlock->getBuilder()->get()->CreateStore(depth, pointerToDepth);

        auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
        auto pointerToArrayAllocation = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                arrayPointerType->getType(),
                varArgsArrayPointerAllocation,
                { zeroIndex, allocIndex }
        );
        irBlock->getBuilder()->get()->CreateStore(varArgsArrayAllocation, pointerToArrayAllocation);
        auto loadedVarArgsArrayPointer = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), varArgsArrayPointerAllocation);
        arguments.insert(arguments.begin() + startIndex, loadedVarArgsArrayPointer);
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

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRArrayPrototypeInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope, IROperationType irOperationType) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
            irInjector->inject(irBlock, argument, IR_OPERAND_POINTER_OP, irModule, scope)
        );
    }
    auto arrayValue = irInjector->inject(irBlock, irExpression->getIRArrayValue(), IR_OPERAND_POINTER_OP, irModule, scope);
    arguments.insert(arguments.begin(), arrayValue);
    auto arrayTypeValue = irInjector->inject(irBlock, irExpression->getIRArrayValue()->getIRType()->getSourceType());
    auto loadedArrayTypeValue = irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRArrayValue()->getIRType()->getSourceType()->getValue()->getAllocatedType(), arrayTypeValue);
    arguments.push_back(loadedArrayTypeValue);
    auto result = irBlock->getBuilder()->get()->CreateCall(
            llvm::cast<llvm::FunctionType>(irExpression->getFunctionIRType()->getType()),
            irExpression->getValue(),
            arguments
    );

    if (irOperationType == IR_OPERAND_POINTER_OP && !result->getType()->isPointerTy()) {
        auto alloc = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getType());
        irBlock->getBuilder()->get()->CreateStore(result, alloc);
        return alloc;
    }

    if ((irOperationType == IR_COPY_ASSIGNMENT_OP || irOperationType == IR_OPERAND_VALUE_OP) && result->getType()->isPointerTy()) {
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), result);
    }

    return result;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRTupleAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arguments = std::vector<llvm::Value*>();
    for (auto argument : *irExpression->getIRArguments()) {
        arguments.push_back(
                irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto pointerToLambda = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRTupleAccessExpression()->getSource()->getSourceAllocation().value()->getAllocatedType(), irExpression->getIRTupleAccessExpression()->getValue(), { zeroIndex, irExpression->getIRTupleAccessExpression()->getIRTargetKeyIndex() });
    auto irFunctionParameterType = (IRFunctionParameterType*)irExpression->getFunctionIRType();
    auto loadedLambdaAtIndex = irBlock->getBuilder()->get()->CreateLoad(irFunctionParameterType->getType(), pointerToLambda);
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
                irInjector->inject(irBlock, argument, IR_FUNCTION_ARGUMENT_OP, irModule, scope)
        );
    }
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto pointerToLambda = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRObjectAccessExpression()->getSource()->getSourceAllocation().value()->getAllocatedType(), irExpression->getIRObjectAccessExpression()->getValue(), { zeroIndex, irExpression->getIRObjectAccessExpression()->getIRTargetKeyIndex() });
    auto irFunctionParameterType = (IRFunctionParameterType*)irExpression->getFunctionIRType();
    auto loadedLambdaAtIndex = irBlock->getBuilder()->get()->CreateLoad(irFunctionParameterType->getType(), pointerToLambda);
    auto lambda = irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irFunctionParameterType->getFunctionIndex() });
    auto lambdaScopeArgument= irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irFunctionParameterType->getFunctionScopeArgumentIndex() });
    arguments.push_back(lambdaScopeArgument);
    return irBlock->getBuilder()->get()->CreateCall(
            irFunctionParameterType->getFunctionType(),
            lambda,
            arguments
    );
}