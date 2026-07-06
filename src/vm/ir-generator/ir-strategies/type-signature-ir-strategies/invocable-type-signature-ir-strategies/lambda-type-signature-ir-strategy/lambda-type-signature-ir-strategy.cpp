//
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"
#include "../../../../../types/ir-type-id.h"

std::shared_ptr<IRInvocableType> LambdaTypeSignatureIRStrategy::generate(std::shared_ptr<LambdaTypeSignature> lambdaTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = this->generateParameterTypes(lambdaTypeSignature->getParameterTypes(), irGenerator, scope, irContext, irGenerator->generateIrPointerType());
    auto irFunction = IRPointerType::create(std::make_shared<IRFunctionType>(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false)));
    auto irFunctionCleanup = irGenerator->generateIRInvocableCleanupType();
    auto irInvocableType = std::make_shared<IRInvocableType>(irGenerator->getFunctionParameterType(), irFunction, irFunctionCleanup, parameterTypes, returnType);
    irInvocableType->setValue(this->generateTypeValue(irInvocableType, irGenerator, irContext));
    return irInvocableType;
}

std::shared_ptr<IRLambdaType> LambdaTypeSignatureIRStrategy::generate(std::shared_ptr<LambdaExpressionTypeSignature> lambdaExpressionTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
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

std::shared_ptr<IRInvocableParameterListType> LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<std::shared_ptr<TypeSignature>>* parameterTypeSignatures, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, std::optional<std::shared_ptr<IRType>> lambdaScopeParameter) {
    auto parameterTypes = std::vector<std::shared_ptr<IRType>>();
    for (auto parameterType : *parameterTypeSignatures) {
        auto parameter = irGenerator->generateTypeFor(parameterType, scope, irContext);
        parameterTypes.push_back(parameter);
    }

    return std::make_shared<IRInvocableParameterListType>(parameterTypes, lambdaScopeParameter);
}

std::shared_ptr<IRTypeValueInstructionNode> LambdaTypeSignatureIRStrategy::generateTypeValue(std::shared_ptr<IRInvocableType> irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.INVOCABLE),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1 + irType->getParameters()->getParameters()->size()), // return type + # of parameters
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