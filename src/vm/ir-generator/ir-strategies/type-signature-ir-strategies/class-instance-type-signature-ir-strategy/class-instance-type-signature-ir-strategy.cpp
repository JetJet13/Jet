//
// Created by Johny Georges on 2025-12-26.
//

#include "class-instance-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRClassInstanceType> ClassInstanceTypeSignatureIRStrategy::generate(std::shared_ptr<ClassInstanceTypeSignature> classInstanceTypeSignature, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    if (classInstanceTypeSignature->isGeneric()) {
        return irGenerator->getGenericClassInstanceIRType();
    }
    auto irClassType = std::dynamic_pointer_cast<IRClassType>(scope->findGlobalType(classInstanceTypeSignature->getClassModuleId(), classInstanceTypeSignature->getId()).value());
    auto irType = std::make_shared<IRClassInstanceType>(irClassType);
    irType->setId(classInstanceTypeSignature->getClass()->getId());
    irType->setValue(irGenerator->generateIRTypeValueFor(irClassType->getClassProperties(), irContext));
    return irType;
}