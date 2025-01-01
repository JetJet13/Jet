//
// Created by Johny Georges on 2024-07-12.
//

#include "procedure-type-signature-ir-strategy.h"

IRFunctionType* ProcedureTypeSignatureIRStrategy::generate(ProcedureTypeSignature* procedureTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto returnType = irGenerator->generateTypeFor(procedureTypeSignature->getReturnType(), scope);
    auto parameterTypes = irGenerator->generateParameterList(procedureTypeSignature->getParameterList(), scope);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}