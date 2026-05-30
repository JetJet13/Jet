//
// Created by Johny Georges on 2024-12-31.
//

#include "new-class-instance-type-signature-ir-strategy.h"

IRNewClassInstanceType* NewClassInstanceTypeSignatureIRStrategy::generate(NewClassInstanceTypeSignature* newClassInstanceTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : newClassInstanceTypeSignature->getClassTypeSignature()->getInstanceProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
            std::pair(keyValue.first, newClassInstanceTypeSignature->getClassTypeSignature()->getInstanceProperties()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto classInstanceProperties = new IRStructType(llvm::StructType::get(**irContext->getContext(), classPropertyTypes), keyIndexMap, keyTypeMap);
    classInstanceProperties->setAlignmentAndSizeForIRTypes();
    classInstanceProperties->setKeyId(newClassInstanceTypeSignature->getKeyId());
    classInstanceProperties->setId(newClassInstanceTypeSignature->getClassTypeSignature()->getId());
    classInstanceProperties->setValue(irGenerator->generateIRTypeValueFor(classInstanceProperties, irContext));
    auto classInstancePropertiesPointerType = irGenerator->generateIRStructRefType(classInstanceProperties);
    classInstancePropertiesPointerType->setKeyId(newClassInstanceTypeSignature->getKeyId());
    classInstancePropertiesPointerType->setId(newClassInstanceTypeSignature->getClassTypeSignature()->getId());
    classInstancePropertiesPointerType->setValue(irGenerator->generateIRTypeValueFor(classInstancePropertiesPointerType, irContext));

    auto irClassType = (IRClassType*)scope->findGlobalType(newClassInstanceTypeSignature->getClassTypeSignature()->getModuleId(), newClassInstanceTypeSignature->getClassTypeSignature()->getId()).value();
    auto irType = new IRNewClassInstanceType(
        irClassType,
        newClassInstanceTypeSignature->getConstructorId(),
        classInstancePropertiesPointerType
    );
    irType->setId(newClassInstanceTypeSignature->getClassTypeSignature()->getId());
    irType->setKeyId(newClassInstanceTypeSignature->getKeyId());
    return irType;
}