//
// Created by Johny Georges on 2025-12-26.
//

#include "class-instance-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassInstanceType* ClassInstanceTypeSignatureIRStrategy::generate(ClassInstanceTypeSignature* classInstanceTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    if (classInstanceTypeSignature->isGeneric()) {
        return irGenerator->getGenericClassInstanceIRType();
    }
    auto irClassType = (IRClassType*)scope->findGlobalType(classInstanceTypeSignature->getClassModuleId(), classInstanceTypeSignature->getId()).value();
    auto classInstanceProperties = irClassType->getClassProperties()->clone();
    classInstanceProperties->setAlignmentAndSizeForIRTypes();
    classInstanceProperties->setKeyId(classInstanceTypeSignature->getKeyId());
    classInstanceProperties->setId(classInstanceTypeSignature->getId());
    classInstanceProperties->setValue(irGenerator->generateIRTypeValueFor(classInstanceProperties, irContext));
    auto classInstancePropertiesPointerType = irGenerator->generateIRStructRefType(classInstanceProperties);
    classInstancePropertiesPointerType->setKeyId(classInstanceTypeSignature->getKeyId());
    classInstancePropertiesPointerType->setId(classInstanceTypeSignature->getId());
    classInstancePropertiesPointerType->setValue(irGenerator->generateIRTypeValueFor(classInstancePropertiesPointerType, irContext));
    return new IRClassInstanceType(irClassType, classInstancePropertiesPointerType);
}