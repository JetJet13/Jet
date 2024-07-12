//
// Created by Johny Georges on 2024-07-12.
//

#include "procedure-type-signature-ir-strategy.h"

IRType* ProcedureTypeSignatureIRStrategy::generate(ProcedureTypeSignature* procedureTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto returnType = irGenerator->generateTypeFor(procedureTypeSignature->getReturnType());
    auto parameterTypes = irGenerator->generateTypeFor(procedureTypeSignature->getParameterList());
    return new IRType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getType()));
}