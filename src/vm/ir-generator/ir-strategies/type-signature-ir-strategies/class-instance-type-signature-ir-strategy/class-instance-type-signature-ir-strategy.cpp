//
// Created by Johny Georges on 2025-12-26.
//

#include "class-instance-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassInstanceType* ClassInstanceTypeSignatureIRStrategy::generate(std::shared_ptr<ClassInstanceTypeSignature> classInstanceTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    if (classInstanceTypeSignature->isGeneric()) {
        return irGenerator->getGenericClassInstanceIRType();
    }
    auto irClassType = (IRClassType*)scope->findGlobalType(classInstanceTypeSignature->getClassModuleId(), classInstanceTypeSignature->getId()).value();
    auto irType = new IRClassInstanceType(irClassType);
    irType->setId(classInstanceTypeSignature->getClass()->getId());
    irType->setValue(irGenerator->generateIRTypeValueFor(irClassType->getClassProperties(), irContext));
    return irType;
}