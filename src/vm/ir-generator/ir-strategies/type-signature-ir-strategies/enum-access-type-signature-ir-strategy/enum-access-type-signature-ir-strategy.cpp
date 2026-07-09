//
// Created by Johny Georges on 2024-07-25.
//

#include "enum-access-type-signature-ir-strategy.h"

std::shared_ptr<IRType> EnumAccessTypeSignatureIRStrategy::generate(std::shared_ptr<EnumAccessTypeSignature> enumAccessTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    return irGenerator->generateTypeFor(enumAccessTypeSignature->getEnum()->getType(), scope, irContext);
}