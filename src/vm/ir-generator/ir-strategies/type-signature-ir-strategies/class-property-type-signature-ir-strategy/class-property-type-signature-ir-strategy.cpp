//
// Created by Johny Georges on 2025-10-22.
//

#include "class-property-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRType> ClassPropertyTypeSignatureIRStrategy::generate(std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irType = irGenerator->generateTypeFor(classPropertyTypeSignature->getType(), scope, irContext);
    return irType;
}