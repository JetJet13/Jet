//
// Created by Johny Georges on 2024-07-12.
//

#include "procedure-type-signature-ir-strategy.h"

std::shared_ptr<IRFunctionType> ProcedureTypeSignatureIRStrategy::generate(std::shared_ptr<ProcedureTypeSignature> procedureTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto returnType = irGenerator->generateTypeFor(procedureTypeSignature->getReturnType(), scope, irContext);
    auto parameterTypes = irGenerator->generateParameterList(procedureTypeSignature->getParameterList(), scope, irContext);
    return std::make_shared<IRFunctionType>(llvm::FunctionType::get(returnType->getType(), parameterTypes->getParameterTypes(), false));
}