//
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"

IRFunctionParameterType* LambdaTypeSignatureIRStrategy::generate(LambdaTypeSignature* lambdaTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = this->generateParameterTypes(lambdaTypeSignature->getParameterTypes(), irGenerator, scope, irContext);
    auto irFunction = IRPointerType::create(new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false)));
    auto irFunctionScopeArgumentType = irGenerator->generateIrPointerType();
    return new IRFunctionParameterType(llvm::StructType::get(**irContext->getContext(), { irFunction->getType(), irFunctionScopeArgumentType->getType() }), irFunction);
}

IRLambdaType* LambdaTypeSignatureIRStrategy::generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getReturnType(), scope, irContext);
    auto lambdaScopeIrType = std::optional<IRType*>();
    if (lambdaExpressionTypeSignature->isScopeParameterNecessary()) {
        lambdaScopeIrType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getScopeParameter()->getTypeSignature(), scope, irContext);
    }
    auto parameterTypes = this->generateParameterTypes(
            lambdaExpressionTypeSignature->getParameterTypes(),
            irGenerator,
            scope,
            irContext,
            lambdaScopeIrType);
    auto functionType = llvm::FunctionType::get(returnType->getType(), parameterTypes, false);
    auto irFunction = IRPointerType::create(new IRFunctionType(functionType));
    auto irFunctionScopeArgumentType = irGenerator->generateIrPointerType();
    return new IRLambdaType(
        functionType,
        irFunction,
        new IRFunctionParameterType(llvm::StructType::get(**irContext->getContext(), { irFunction->getType(), irFunctionScopeArgumentType->getType() }), irFunction),
        lambdaScopeIrType
    );
}

std::vector<llvm::Type*> LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, std::optional<IRType*> lambdaScopeParameter) {
    auto parameterTypes = std::vector<llvm::Type*>();
    for (auto parameterType : *parameterTypeSignatures) {
        auto parameter = irGenerator->generateTypeFor(parameterType, scope, irContext);
        parameterTypes.push_back(parameter->getType());
    }
    if (lambdaScopeParameter) {
        parameterTypes.push_back(lambdaScopeParameter.value()->getType()->getPointerTo());
    }
    return parameterTypes;
}