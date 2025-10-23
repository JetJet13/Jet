//
// Created by Johny Georges on 2025-10-22.
//

#include "class-property-type-signature-ir-strategy.h"

IRType* ClassPropertyTypeSignatureIRStrategy::generate(ClassPropertyTypeSignature* classPropertyTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return irGenerator->generateTypeFor(classPropertyTypeSignature->getType(), scope, irContext);
}