// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
#include "../../../../../core/pre-processor/semantic-analyzer/types/function-id-generator/function-id-generator.h"

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRFunctionInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto functionTypeSignature = irExpression->getInvocationTypeSignature()->getFunctionType();
    auto arguments = std::vector<llvm::Value*>();
    for (uint64_t i = 0; i < irExpression->getIRArguments()->size(); ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto irArgument = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
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
        auto startIndex = irExpression->getInvocationTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex();
        auto typeValueType = std::dynamic_pointer_cast<IRTypeValueType>(irExpression->getVarArgsTypeValueArgument().value()->getParentAllocation().value()->getIRType()->getUnderlyingType());
        auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getVarArgsTypeValueArgument().value()->getIRType()->getUnderlyingType());
        auto varArgsArrayAllocation = InstructionIRInjectorHelper::inject(irExpression->getVarArgsTypeValueArgument().value()->getParentAllocation().value(), irBlock);
        auto varArgsArrayPointerAllocation = InstructionIRInjectorHelper::inject(irExpression->getVarArgsTypeValueArgument().value(), irBlock);
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        for (uint64_t i = startIndex; i < irExpression->getIRArguments()->size(); ++i) {
            auto argument = irExpression->getIRArguments()->at(i);
            auto index = irBlock->getBuilder()->get()->getInt64(i);
            auto pointerToTypeValue = irBlock->getBuilder()->get()->CreateInBoundsGEP(
                    typeValueType->getType(),
                    varArgsArrayAllocation,
                    { index }
            );
            auto typeValue = irInjector->inject(irBlock, argument->getArgument()->getIRType()->getSourceType(), irModule);
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
        auto numElements = irBlock->getBuilder()->get()->getInt64(irExpression->getIRArguments()->size() - irExpression->getInvocationTypeSignature()->getFunctionType()->getVariableLengthParametersStartIndex());
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
        irExpression->getValue()->setArgOperand(startIndex, varArgsArrayPointerAllocation);
    }

    if (irExpression->getFunctionIRType()->isLambdaType()) {
        auto irLambdaType = std::dynamic_pointer_cast<IRLambdaType>(irExpression->getFunctionIRType());
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
        auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getFunctionIRType());
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

    if (!functionTypeSignature->isBuiltIn()) {
        auto irFunctionId = FunctionIdGenerator::generateFor(functionTypeSignature->getModuleId(), functionTypeSignature->getId(), functionTypeSignature);
        auto function = irModule->getModule()->get()->getFunction(irFunctionId);
        irExpression->getValue()->setCalledOperand(function);
    }
    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRClassMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    auto classScopeArgument = InstructionIRInjectorHelper::injectLoad(
            irExpression->getClassScopeArgument()->getIRType()->getType(),
            irExpression->getClassScopeArgument()->getValue(),
            irBlock
    );
    irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, classScopeArgument);

    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRArrayPrototypeInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i + 1, argumentValue);
    }

    auto arrayValue = irInjector->inject(irBlock, irExpression->getIRArrayValue(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    irExpression->getValue()->setArgOperand(0, arrayValue);
    if (irExpression->requiresTypeValueArgument()) {
        auto arrayTypeValue = irInjector->inject(irBlock, irExpression->getIRArrayValue()->getIRType()->getUnderlyingType(), irModule);
        auto loadedArrayTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getIRArrayValue()->getIRType()->getUnderlyingType()->getValue()->getAllocatedType(), arrayTypeValue, irBlock);
        irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, loadedArrayTypeValue);
    }
    auto result = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

    if (irOperation->isOperandPointer() && !result->getType()->isPointerTy()) {
        auto alloc = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getUnderlyingIRType()->getType());
        InstructionIRInjectorHelper::injectStore(result, alloc, irBlock, irExpression->getUnderlyingIRType());
        return alloc;
    }

    if ((irOperation->isCopy() || irOperation->isOperandValue())
        && result->getType()->isPointerTy()
        && !irExpression->getIRType()->getUnderlyingType()->isVoidType()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), result, irBlock);
    }

    return result;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRStringPrototypeInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i + 1, argumentValue);
    }

    auto stringValue = irInjector->inject(irBlock, irExpression->getIRStringValue(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    irExpression->getValue()->setArgOperand(0, stringValue);

    auto result = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

    if (irOperation->isOperandPointer() && !result->getType()->isPointerTy()) {
        auto alloc = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getUnderlyingIRType()->getType());
        InstructionIRInjectorHelper::injectStore(result, alloc, irBlock, irExpression->getUnderlyingIRType());
        return alloc;
    }

    if ((irOperation->isCopy() || irOperation->isOperandValue())
        && result->getType()->isPointerTy()
        && !irExpression->getIRType()->getUnderlyingType()->isVoidType()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), result, irBlock);
    }

    return result;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRSharedPtrPrototypeInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {

    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i + 1, argumentValue);
    }
    auto sharedValue = irInjector->inject(irBlock, irExpression->getIRSharedValue(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
    irExpression->getValue()->setArgOperand(0, sharedValue);
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

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRTupleAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getFunctionIRType());
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    auto sourceIrType = std::dynamic_pointer_cast<IRStructRefType>(irExpression->getSource()->getUnderlyingIRType());
    auto tupleSourcePointer = irBlock->getBuilder()->get()->CreateExtractValue(sourceValue, sourceIrType->getStructIndex());
    auto targetPointer = irBlock->getBuilder()->get()->CreateStructGEP(sourceIrType->getStructIRType()->getType(), tupleSourcePointer, irExpression->getTargetIndex());
    auto targetValue = InstructionIRInjectorHelper::injectLoad(irInvocableType->getType(), targetPointer, irBlock, irInvocableType);
    auto lambda = irBlock->getBuilder()->get()->CreateExtractValue(targetValue, { irInvocableType->getFunctionIndex() });
    auto lambdaScopeArgument = irBlock->getBuilder()->get()->CreateExtractValue(targetValue, { irInvocableType->getFunctionScopeArgumentIndex() });
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

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRObjectAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    auto irType = irExpression->getFunctionIRType();
    if (irType->isInvocableType()) {
        auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irType);
        auto sourceValue = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
        auto sourceIrType = std::dynamic_pointer_cast<IRStructRefType>(irExpression->getSource()->getUnderlyingIRType());
        auto tupleSourcePointer = irBlock->getBuilder()->get()->CreateExtractValue(sourceValue, sourceIrType->getStructIndex());
        auto targetPointer = irBlock->getBuilder()->get()->CreateStructGEP(sourceIrType->getStructIRType()->getType(), tupleSourcePointer, irExpression->getTargetIndex());
        auto targetValue = InstructionIRInjectorHelper::injectLoad(irInvocableType->getType(), targetPointer, irBlock, irInvocableType);
        auto lambda = irBlock->getBuilder()->get()->CreateExtractValue(targetValue, { irInvocableType->getFunctionIndex() });
        auto lambdaScopeArgument = irBlock->getBuilder()->get()->CreateExtractValue(targetValue, { irInvocableType->getFunctionScopeArgumentIndex() });
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
        auto scopeArgumentValue = irInjector->inject(irBlock, scopeArgument.value(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
        irExpression->getValue()->setArgOperand(irExpression->getValue()->arg_size() - 1, scopeArgumentValue);
    }

    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());

    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRArrayAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }
    auto pointerToLambda = irInjector->inject(irBlock, irExpression->getIRArrayAccessExpression(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto irInvocableType = std::dynamic_pointer_cast<IRInvocableType>(irExpression->getFunctionIRType());
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

llvm::Value* FunctionInvocationIRInjectorHelper::inject(std::shared_ptr<IRClassStaticMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (uint64_t i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    auto value = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    if (irOperation->isOperandPointer()) {
        auto pointerToValue = irBlock->getBuilder()->get()->CreateAlloca(value->getType());
        InstructionIRInjectorHelper::injectStore(value, pointerToValue, irBlock, irExpression->getIRType());
        return pointerToValue;
    }
    return value;
}