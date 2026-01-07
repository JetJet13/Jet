//
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"
#include "../../../../../types/ir-type-id.h"

IRInvocableType* LambdaTypeSignatureIRStrategy::generate(LambdaTypeSignature* lambdaTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = this->generateParameterTypes(lambdaTypeSignature->getParameterTypes(), irGenerator, scope, irContext);
    auto irFunction = IRPointerType::create(new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false)));
    auto irFunctionCleanup = irGenerator->generateIRInvocableCleanupType();
    auto irInvocableType = new IRInvocableType(irGenerator->getFunctionParameterType(), irFunction, irFunctionCleanup, parameterTypes, returnType);
    irInvocableType->setValue(this->generateTypeValue(irInvocableType, irGenerator, irContext));
    return irInvocableType;
}

IRLambdaType* LambdaTypeSignatureIRStrategy::generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getReturnType(), scope, irContext);
    auto lambdaScopeIrType = std::optional<IRStructType*>();
    if (lambdaExpressionTypeSignature->isScopeParameterNecessary()) {
        lambdaScopeIrType = irGenerator->generateTypeFor((LambdaScopeTypeSignature*)lambdaExpressionTypeSignature->getScopeParameter()->getTypeSignature(), scope, irContext);
    }
    auto parameterList = this->generateParameterTypes(
            lambdaExpressionTypeSignature->getParameterTypes(),
            irGenerator,
            scope,
            irContext,
            lambdaScopeIrType);
    auto functionType = llvm::FunctionType::get(returnType->getType(), parameterList->getParameterTypes(), false);
    auto irFunction = IRPointerType::create(new IRFunctionType(functionType));
    auto irFunctionCleanup = irGenerator->generateIRInvocableCleanupType();
    auto irInvocableType = new IRInvocableType(irGenerator->getFunctionParameterType(), irFunction, irFunctionCleanup, parameterList, returnType);
    irInvocableType->setValue(this->generateTypeValue(irInvocableType, irGenerator, irContext));
    auto irLambdaType = new IRLambdaType(
        functionType,
        irFunction,
        irInvocableType,
        parameterList,
        returnType,
        lambdaScopeIrType
    );
    return irLambdaType;
}

IRInvocableParameterListType* LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, std::optional<IRType*> lambdaScopeParameter) {
    auto parameterTypes = std::vector<IRType*>();
    for (auto parameterType : *parameterTypeSignatures) {
        auto parameter = irGenerator->generateTypeFor(parameterType, scope, irContext);
        parameterTypes.push_back(parameter);
    }

    return new IRInvocableParameterListType(parameterTypes, lambdaScopeParameter);
}

IRTypeValueInstructionNode* LambdaTypeSignatureIRStrategy::generateTypeValue(IRInvocableType* irType, IRGenerator* irGenerator, IRContext* irContext) {
    auto irTypeValueType = irGenerator->generateIrTypeValueType();
    auto typeValueTypeAllocation = irGenerator->generateIrTypeValueTypeAllocation();
    auto initialValue = llvm::ConstantStruct::get(irTypeValueType->getType(), {
            irGenerator->generateIntConstant(IR_TYPE_ID.LAMBDA),
            irGenerator->generateIntConstant(irType->getSizeInBytes()),
            irGenerator->generateIntConstant(1 + irType->getParameters()->getParameters()->size()), // return type + # of parameters
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            irType->hasKeyId()
            ? irGenerator->getOrInsertGlobalVariableString(irType->getKeyId(), irType->getKeyId(), irContext)
            : llvm::ConstantPointerNull::get(irGenerator->generatePointerType()),
            llvm::ConstantPointerNull::get(irGenerator->generatePointerType())
    });
    auto storeInstruction = irGenerator->generateStoreInstruction(initialValue, typeValueTypeAllocation, irTypeValueType);
    return new IRTypeValueInstructionNode(
            typeValueTypeAllocation,
            irGenerator->generateIrPointerType(irTypeValueType),
            storeInstruction
    );
}