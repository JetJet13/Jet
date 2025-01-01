//
// Created by Johny Georges on 2024-07-12.
//

#include "parameter-type-signature-ir-strategy.h"

IRParameterType* ParameterTypeSignatureIRStrategy::generate(ParameterListItemTypeSignature* parameterListItemTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    return new IRParameterType(parameterListItemTypeSignature->getName(), irGenerator->generateTypeFor(parameterListItemTypeSignature->getTypeSignature(), scope));
}