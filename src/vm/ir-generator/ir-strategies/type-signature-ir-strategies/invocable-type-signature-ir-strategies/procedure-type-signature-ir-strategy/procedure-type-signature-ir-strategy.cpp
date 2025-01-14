//
// Created by Johny Georges on 2024-07-12.
//

#include "procedure-type-signature-ir-strategy.h"

IRFunctionType* ProcedureTypeSignatureIRStrategy::generate(ProcedureTypeSignature* procedureTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto returnType = irGenerator->generateTypeFor(procedureTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = irGenerator->generateParameterList(procedureTypeSignature->getParameterList(), scope, irContext);
    return new IRFunctionType(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}