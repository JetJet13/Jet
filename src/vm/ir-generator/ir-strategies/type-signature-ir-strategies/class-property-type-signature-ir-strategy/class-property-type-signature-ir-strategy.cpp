//
// Created by Johny Georges on 2025-10-22.
//

#include "class-property-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRType* ClassPropertyTypeSignatureIRStrategy::generate(std::shared_ptr<ClassPropertyTypeSignature> classPropertyTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irType = irGenerator->generateTypeFor(classPropertyTypeSignature->getType(), scope, irContext);
    return irType;
}