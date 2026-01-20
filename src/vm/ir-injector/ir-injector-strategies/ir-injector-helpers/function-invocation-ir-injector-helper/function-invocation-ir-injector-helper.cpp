//
// Created by Johny Georges on 2024-11-09.
//

#include "function-invocation-ir-injector-helper.h"
#include "../../../../ir-type/ir-lambda-type.h"
#include "../../../../ir-type/ir-array-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-pointer-type.h"
#include "../../../../ir-type/ir-type-value-type.h"
#include "../../../../../shared/utils/logger/logger.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    auto functionTypeSignature = irExpression->getTypeSignature()->getFunctionType();
    auto arguments = std::vector<llvm::Value*>();
    for (unsigned long i = 0; i < irExpression->getIRArguments()->size(); ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto operationType = functionTypeSignature->isArgumentVarArg(i)
                             || functionTypeSignature->getParameterTypes()->at(i)->isGeneric()
                ? new IROperation(IR_OPERAND_POINTER_OP)
                : new IROperation(IR_FUNCTION_ARGUMENT_OP);
        auto irArgument = irInjector->inject(irBlock, argument, operationType, irModule, scope);
        if (functionTypeSignature->isArgumentVarArg(i)) {
            auto index = functionTypeSignature->getVariableLengthParametersStartIndex() + 1 + i;
            irExpression->getValue()->setArgOperand(index, irArgument);
        } else {
            irExpression->getValue()->setArgOperand(i, irArgument);
        }
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
        for (unsigned long i = startIndex; i < irExpression->getIRArguments()->size(); ++i) {
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
        auto numElements = irBlock->getBuilder()->get()->getInt64(irExpression->getIRArguments()->size() - irExpression->getTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex());
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
        irExpression->getValue()->setArgOperand(startIndex, loadedVarArgsArrayPointer);
    }

    if (irExpression->getFunctionIRType()->isLambdaType()) {
        auto irLambdaType = (IRLambdaType*)irExpression->getFunctionIRType();
        auto lambdaIndex = irLambdaType->getLambdaVariableType()->getFunctionIndex();
        auto lambdaPointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getFunctionValue(), lambdaIndex);
        auto loadedLambda = InstructionIRInjectorHelper::injectLoad(irLambdaType->getFunctionPointerType(), lambdaPointer, irBlock);
        irExpression->getValue()->setCalledOperand(loadedLambda);
        if (irLambdaType->getLambdaScopeType() && irLambdaType->getLambdaScopeType().value()->size() > 0) {
            auto lambdaScopeArgumentIndex = irLambdaType->getLambdaVariableType()->getFunctionScopeArgumentIndex();
            auto lambdaScopeArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(irLambdaType->getLambdaVariableType()->getType(), irExpression->getFunctionValue(), lambdaScopeArgumentIndex);
            auto loadedLambdaScopeArgument = InstructionIRInjectorHelper::injectLoad(irLambdaType->getLambdaScopeType().value()->getType(), lambdaScopeArgumentPointer, irBlock);
            irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, loadedLambdaScopeArgument);
        }
        auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

        if (irOperation->isOperandPointer()) {
            auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
            InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
            return pointerToValue;
        }
        return value;
    }

    if (irExpression->getFunctionIRType()->isInvocableType()) {
        auto irInvocableType = (IRInvocableType*)irExpression->getFunctionIRType();
        auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), irExpression->getFunctionValue(), irInvocableType->getFunctionIndex());
        auto loadedFunctionParameter = InstructionIRInjectorHelper::injectLoad(irInvocableType->getIRFunctionPointer()->getType(), functionPointer, irBlock);
        irExpression->getValue()->setCalledOperand(loadedFunctionParameter);
        auto functionScopeArgumentIndex = irInvocableType->getFunctionScopeArgumentIndex();
        auto functionScopeArgumentPointer = irBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), irExpression->getFunctionValue(), functionScopeArgumentIndex);
        auto loadedFunctionScopeArgument = InstructionIRInjectorHelper::injectLoad(irInvocableType->getFunctionScopeArgumentType(), functionScopeArgumentPointer, irBlock);
        irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, loadedFunctionScopeArgument);
        auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
        if (irOperation->isOperandPointer()) {
            auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
            InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
            return pointerToValue;
        }
        return value;
    }

    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRClassMethodInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (unsigned long i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, irExpression->getClassScopeArgument()->getValue());
    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRArrayPrototypeInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (unsigned long i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument, new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        irExpression->getValue()->setArgOperand(i + 1, argumentValue);
    }

    auto arrayValue = irInjector->inject(irBlock, irExpression->getIRArrayValue(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    irExpression->getValue()->setArgOperand(0, arrayValue);
    if (irExpression->requiresTypeValueArgument()) {
        auto arrayTypeValue = irInjector->inject(irBlock, irExpression->getIRArrayValue()->getIRType()->getUnderlyingType());
        auto loadedArrayTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getIRArrayValue()->getIRType()->getUnderlyingType()->getValue()->getAllocatedType(), arrayTypeValue, irBlock);
        irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, loadedArrayTypeValue);
    }
    auto result = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

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

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRRefPrototypeInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {

    auto numArgs = irExpression->getIRArguments()->size();
    for (unsigned long i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument, new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        irExpression->getValue()->setArgOperand(i + 1, argumentValue);
    }
    auto refValue = irInjector->inject(irBlock, irExpression->getIRRefValue(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    irExpression->getValue()->setArgOperand(0, refValue);
    auto result = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

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

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRTupleAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (unsigned long i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto pointerToLambda = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRTupleAccessExpression()->getSource()->getSourceAllocation().value()->getAllocatedType(), irExpression->getIRTupleAccessExpression()->getValue(), { zeroIndex, irExpression->getIRTupleAccessExpression()->getIRTargetKeyIndex() });
    auto irInvocableType = (IRInvocableType*)irExpression->getFunctionIRType();
    auto loadedLambdaAtIndex = InstructionIRInjectorHelper::injectLoad(irInvocableType->getType(), pointerToLambda, irBlock);
    auto lambda = irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irInvocableType->getFunctionIndex() });
    auto lambdaScopeArgument= irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irInvocableType->getFunctionScopeArgumentIndex() });
    irExpression->getValue()->setCalledOperand(lambda);
    irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, lambdaScopeArgument);
    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(IRObjectAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (unsigned long i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument, new IROperation(IR_FUNCTION_ARGUMENT_OP), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    auto irType = irExpression->getFunctionIRType();
    if (irType->isInvocableType()) {
        auto irInvocableType = (IRInvocableType*)irType;
        auto loadedLambdaAtIndex = InstructionIRInjectorHelper::inject(irExpression->getFunction(), irBlock);
        auto lambda = irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irInvocableType->getFunctionIndex() });
        auto lambdaScopeArgument= irBlock->getBuilder()->get()->CreateExtractValue(loadedLambdaAtIndex, { irInvocableType->getFunctionScopeArgumentIndex() });
        irExpression->getValue()->setCalledOperand(lambda);
        irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, lambdaScopeArgument);
        auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
        if (irOperation->isOperandPointer()) {
            auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
            InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
            return pointerToValue;
        }
        return value;
    }

    auto scopeArgument = irExpression->getScopeArgument();
    if (scopeArgument) {
        auto scopeArgumentValue = irInjector->inject(irBlock, scopeArgument.value(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, scopeArgumentValue);
    }

    auto function = InstructionIRInjectorHelper::inject(irExpression->getFunction(), irBlock);
    irExpression->getValue()->setCalledOperand(function);
    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}