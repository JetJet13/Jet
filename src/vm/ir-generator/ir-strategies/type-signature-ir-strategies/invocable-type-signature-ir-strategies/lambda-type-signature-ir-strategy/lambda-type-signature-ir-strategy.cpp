//
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"

IRPointerType* LambdaTypeSignatureIRStrategy::generate(ProcedureLambdaTypeSignature* procedureLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(procedureLambdaTypeSignature->getReturnType());
    auto parameterTypes = this->generateParameterTypes(procedureLambdaTypeSignature->getParameterTypes(), irGenerator);
    return IRPointerType::create(new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false)));
}

IRPointerType* LambdaTypeSignatureIRStrategy::generate(FunctionLambdaTypeSignature* functionLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(functionLambdaTypeSignature->getReturnType());
    auto parameterTypes = this->generateParameterTypes(functionLambdaTypeSignature->getParameterTypes(), irGenerator);
    return IRPointerType::create(new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false)));
}

IRFunctionType* LambdaTypeSignatureIRStrategy::generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getReturnType());
    auto parameterTypes = this->generateParameterTypes(
            lambdaExpressionTypeSignature->getParameterTypes(),
            irGenerator,
            lambdaExpressionTypeSignature->isScopeParameterNecessary()
            ? lambdaExpressionTypeSignature->getScopeParameter()->getTypeSignature()
            : std::optional<TypeSignature*>());
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false));
}

std::vector<llvm::Type*> LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator, std::optional<TypeSignature*> lambdaScopeParameter) {
    auto parameterTypes = std::vector<llvm::Type*>();
    if (lambdaScopeParameter) {
        parameterTypes.push_back(irGenerator->generateTypeFor(lambdaScopeParameter.value())->getType());
    }
    for (auto parameterType : *parameterTypeSignatures) {
        auto parameter = irGenerator->generateTypeFor(parameterType);
        parameterTypes.push_back(parameter->getType());
    }
    return parameterTypes;
}