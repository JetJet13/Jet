//
// Created by Johny Georges on 2024-07-12.
//

#include "parameter-type-signature-ir-strategy.h"

IRParameterType* ParameterTypeSignatureIRStrategy::generate(ParameterListItemTypeSignature* parameterListItemTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return new IRParameterType(parameterListItemTypeSignature->getName(), irGenerator->generateTypeFor(parameterListItemTypeSignature->getTypeSignature(), scope, irContext));
}