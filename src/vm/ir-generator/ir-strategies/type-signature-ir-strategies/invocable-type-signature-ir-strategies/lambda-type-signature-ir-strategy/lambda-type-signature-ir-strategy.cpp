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
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"
#include "../../../../../types/ir-type-id.h"

std::shared_ptr<IRInvocableType> LambdaTypeSignatureIRStrategy::generate(std::shared_ptr<LambdaTypeSignature> lambdaTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = this->generateParameterTypes(lambdaTypeSignature->getParameterTypes(), irGenerator, scope, irContext, irGenerator->generateIrPointerType());
    auto irFunction = IRPointerType::create(std::make_shared<IRFunctionType>(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false)));
    auto irFunctionCleanup = irGenerator->generateIRInvocableCleanupType();
    auto irInvocableType = std::make_shared<IRInvocableType>(irGenerator->getFunctionParameterType(), irFunction, irFunctionCleanup, parameterTypes, returnType);
    irInvocableType->setValue(this->generateTypeValue(irInvocableType, irGenerator, irContext));
    return irInvocableType;
}

std::shared_ptr<IRLambdaType> LambdaTypeSignatureIRStrategy::generate(std::shared_ptr<LambdaExpressionTypeSignature> lambdaExpressionTypeSignature,  std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getReturnType(), scope, irContext);
    auto lambdaScopeIrType = irGenerator->generateTypeFor(std::dynamic_pointer_cast<LambdaScopeTypeSignature>(lambdaExpressionTypeSignature->getScopeParameter()->getTypeSignature()), scope, irContext);
    auto parameterList = this->generateParameterTypes(
        lambdaExpressionTypeSignature->getParameterTypes(),
        irGenerator,
        scope,
        irContext,
        lambdaScopeIrType
    );
    auto functionType = llvm::FunctionType::get(returnType->getType(), parameterList->getParameterTypes(), false);
    auto irFunction = IRPointerType::create(std::make_shared<IRFunctionType>(functionType));
    auto irFunctionCleanup = irGenerator->generateIRInvocableCleanupType();
    auto irInvocableType = std::make_shared<IRInvocableType>(irGenerator->getFunctionParameterType(), irFunction, irFunctionCleanup, parameterList, returnType);
    irInvocableType->setValue(this->generateTypeValue(irInvocableType, irGenerator, irContext));
    auto irLambdaType = std::make_shared<IRLambdaType>(
        functionType,
        irFunction,
        irInvocableType,
        parameterList,
        returnType,
        lambdaScopeIrType
    );
    return irLambdaType;
}

std::shared_ptr<IRInvocableParameterListType> LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<std::shared_ptr<TypeSignature>>* parameterTypeSignatures, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::optional<std::shared_ptr<IRType>> lambdaScopeParameter) {
    auto parameterTypes = std::vector<std::shared_ptr<IRType>>();
    for (auto parameterType : *parameterTypeSignatures) {
        auto parameter = irGenerator->generateTypeFor(parameterType, scope, irContext);
        parameterTypes.push_back(parameter);
    }

    return std::make_shared<IRInvocableParameterListType>(parameterTypes, lambdaScopeParameter);
}

std::shared_ptr<IRTypeValueInstructionNode> LambdaTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRInvocableType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    uint64_t totalNumOfTypes = 1 + irType->getParameters()->getParameters()->size(); // return type + # of parameters
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.INVOCABLE),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(totalNumOfTypes),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return std::make_shared<IRTypeValueInstructionNode>(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}