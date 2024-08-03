//
// Created by Johny Georges on 2024-07-12.
//

#include "lambda-type-signature-ir-strategy.h"

IRFunctionType* LambdaTypeSignatureIRStrategy::generate(ProcedureLambdaTypeSignature* procedureLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(procedureLambdaTypeSignature->getReturnType());
    auto parameterTypes = this->generateParameterTypes(procedureLambdaTypeSignature->getParameterTypes(), irGenerator);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false));
}

IRFunctionType* LambdaTypeSignatureIRStrategy::generate(FunctionLambdaTypeSignature* functionLambdaTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(functionLambdaTypeSignature->getReturnType());
    auto parameterTypes = this->generateParameterTypes(functionLambdaTypeSignature->getParameterTypes(), irGenerator);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false));
}

IRFunctionType* LambdaTypeSignatureIRStrategy::generate(LambdaExpressionTypeSignature* lambdaExpressionTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(lambdaExpressionTypeSignature->getReturnType());
    auto parameterTypes = this->generateParameterTypes(lambdaExpressionTypeSignature->getParameterTypes(), irGenerator);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes, false));
}

std::vector<llvm::Type*> LambdaTypeSignatureIRStrategy::generateParameterTypes(std::vector<TypeSignature*>* parameterTypeSignatures, IRGenerator* irGenerator) {
    auto parameterTypes = std::vector<llvm::Type*>();
    for (auto parameterType : *parameterTypeSignatures) {
        parameterTypes.push_back(irGenerator->generateTypeFor(parameterType)->getType());
    }
    return parameterTypes;
}