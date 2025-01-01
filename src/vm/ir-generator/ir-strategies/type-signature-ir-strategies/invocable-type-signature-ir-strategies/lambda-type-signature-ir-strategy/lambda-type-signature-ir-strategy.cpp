//
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"

IRFunctionParameterType* LambdaTypeSignatureIRStrategy::generate(ProcedureLambdaTypeSignature* procedureLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto returnType = irGenerator->generateTypeFor(procedureLambdaTypeSignature->getReturnType(), scope);
    auto parameterTypes = this->generateParameterTypes(procedureLambdaTypeSignature->getParameterTypes(), irGenerator, scope);
    auto irFunction = IRPointerType::create(new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false)));
    auto irFunctionScopeArgumentType = irGenerator->generateIrPointerType();
    return new IRFunctionParameterType(llvm::StructType::get(**context, { irFunction->getType(), irFunctionScopeArgumentType->getType() }), irFunction);
}

IRFunctionParameterType* LambdaTypeSignatureIRStrategy::generate(FunctionLambdaTypeSignature* functionLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto returnType = irGenerator->generateTypeFor(functionLambdaTypeSignature->getReturnType(), scope);
    auto parameterTypes = this->generateParameterTypes(functionLambdaTypeSignature->getParameterTypes(), irGenerator, scope);
    auto irFunction = IRPointerType::create(new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false)));
    auto irFunctionScopeArgumentType = irGenerator->generateIrPointerType();
    return new IRFunctionParameterType(llvm::StructType::get(**context, { irFunction->getType(), irFunctionScopeArgumentType->getType() }), irFunction);
}

IRLambdaType* LambdaTypeSignatureIRStrategy::generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto returnType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getReturnType(), scope);
    auto lambdaScopeIrType = std::optional<IRType*>();
    if (lambdaExpressionTypeSignature->isScopeParameterNecessary()) {
        lambdaScopeIrType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getScopeParameter()->getTypeSignature(), scope);
    }
    auto parameterTypes = this->generateParameterTypes(
            lambdaExpressionTypeSignature->getParameterTypes(),
            irGenerator,
            scope,
            lambdaScopeIrType);
    auto functionType = llvm::FunctionType::get(returnType->getType(), parameterTypes, false);
    auto irFunction = IRPointerType::create(new IRFunctionType(functionType));
    auto irFunctionScopeArgumentType = irGenerator->generateIrPointerType();
    return new IRLambdaType(
        functionType,
        irFunction,
        new IRFunctionParameterType(llvm::StructType::get(**context, { irFunction->getType(), irFunctionScopeArgumentType->getType() }), irFunction),
        lambdaScopeIrType
    );
}

std::vector<llvm::Type*> LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator, IRLookupTable* scope, std::optional<IRType*> lambdaScopeParameter) {
    auto parameterTypes = std::vector<llvm::Type*>();
    for (auto parameterType : *parameterTypeSignatures) {
        auto parameter = irGenerator->generateTypeFor(parameterType, scope);
        parameterTypes.push_back(parameter->getType());
    }
    if (lambdaScopeParameter) {
        parameterTypes.push_back(lambdaScopeParameter.value()->getType());
    }
    return parameterTypes;
}