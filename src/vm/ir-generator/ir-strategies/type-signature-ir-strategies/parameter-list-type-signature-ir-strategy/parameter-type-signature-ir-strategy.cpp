//
// Created by Johny Georges on 2024-07-12.
//

#include "parameter-type-signature-ir-strategy.h"

std::shared_ptr<IRParameterType> ParameterTypeSignatureIRStrategy::generate(std::shared_ptr<ParameterListItemTypeSignature> parameterListItemTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return std::make_shared<IRParameterType>(parameterListItemTypeSignature->getName(), irGenerator->generateTypeFor(parameterListItemTypeSignature->getTypeSignature()->convertToVariableTypeSignature(), scope, irContext));
}
